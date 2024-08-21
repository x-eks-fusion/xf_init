# 详细说明

## 基于 section 的自动初始化

**基于 section 的自动初始化的基本原理**是:

1. 定义某个包含某个模块的初始化函数指针以及初始化函数的函数名的常变量, 并将其放置到某个段中(本组件中是 `.xf_auto_init.` 段);

   ```c
   int component1(void)
   {
       printf("hello, I'm %s\n", __FUNCTION__);
       return 0;
   }
   XF_INIT_EXPORT_BOARD(component1);
   ```

   宏会展开为:

   ```c
   __used __section(".xf_auto_init." "1") const xf_init_desc_t __xf_init_component1 = {
       .func = (component1),
       .func_name = "component1",
   };
   ```

   其中 `__used` 用于对通知编译器该变量是需要保留的, `__section` 用于通知编译器该变量保存到 `".xf_auto_init.1"` 段中.

   `__xf_init_component1` 常变量包含了初始化函数 `component1()` 信息和初始化函数名(用于调试).

1. 链接时依靠链接器**将所有属于 `.xf_auto_init.` 段的内容集中放置到某个连续内存/闪存中**, 同时定义该段的开始变量和结尾变量以供检测;

   在编译后生成出来的 map 表中可以看到 `__xf_init_component1` 常变量, 同时的开始变量和结尾变量也已经定义了出来(`__xf_init_start` 和 `__xf_init_end`):

   ```
   xf_auto_init    0x0000000000002010      0x100
                  0x0000000000002010                . = ALIGN (0x8)
                  0x0000000000002010                __xf_init_start = .
   *(SORT_BY_NAME(.xf_auto_init*))
   // ...
   .xf_auto_init.1
                  0x0000000000002060       0x10 build/.objs/linux/linux/x86_64/release/examples/other_component/component1.c.o
                  0x0000000000002060                __xf_init_component1
   // ...
   .xf_auto_init.1.end
                  0x0000000000002080       0x10 build/.objs/linux/linux/x86_64/release/src/xf_init.c.o
                  0x0000000000002080                __xf_init_board_end
   // ...
    .xf_auto_init.6.end
                  0x0000000000002100       0x10 build/.objs/linux/linux/x86_64/release/src/xf_init.c.o
                  0x0000000000002110                __xf_init_end = .
                  0x0000000000002110                . = ALIGN (0x8)
   ```

   Linux 编译环境下的编译脚本(**仅供参考, 不是所有情况都适用**)位于 `linker/xf_linker.gcc.64.ld`, `.64` 标识使用 8 字节对齐方式, `.32` 标识使用 4 字节对齐方式, 内容如下:

   ```linkscript
   SECTIONS
   {
     xf_auto_init : {
     . = ALIGN(8);
     __xf_init_start = .;
     KEEP(*(SORT(.xf_auto_init*)))
     __xf_init_end = .;
     . = ALIGN(8);
     }
   } INSERT AFTER .text;
   ```

   其大致含义是, 收集并排序(SORT) `.xf_auto_init` 段内所有内容, 并且保持(KEEP)其中内容即使没有用到也不删除.

   `INSERT AFTER .text;` 表示将 `xf_auto_init` 的内容插入到 `.text` 后面, 这样就可以不修改原始的链接脚本.

   **注意这种插入到原始链接脚本的方式并不完全通用**.

   这种方式在 stm32 gcc 和 linux gcc 的编译环境下是可以使用的;
   esp32 有自己的链接脚本插入规则;
   ws63 则会因为 xf_auto_init 段的内容没有定位到 `PROGRAM` 内存中错误.

   > **这是因为:**
   > 插入式的链接脚本不能预先知道内存名称, 不同平台上 `.text` 段所属内存名称各有不同，有的叫 `PROGRAM` ，有的叫 `FLASH` ，xf_auto_init 无法准确地放到 `.text` 段里面.

1. 运行时, 通过开始变量和结尾变量**找到所有需要运行的初始化函数, 并逐一运行**.

   见 `src/xf_init.c`, 下面一段负责板级初始化, 具体操作是再取开始变量和结尾变量的地址间逐一拿出需要初始化的函数并调用:

   ```c
   int result = 0;
   const xf_init_desc_t *desc = NULL;
   for (desc = &__xf_init_board_start; desc < &__xf_init_board_end; desc++) {
      if (NULL == desc->func) {
         continue;
      }
      result = desc->func();
   }
   ```

### 推荐做法

1. **获取目标平台的链接脚本.**

   **只要能编译成可执行文件一定会有链接脚本, 如果没有则是使用编译器自带的链接脚本.**

   1. linux gcc:

      linux gcc 使用 gcc 编译器自带的链接脚本, 可以通过以下方式获取:

      ```bash
      gcc -Wl,-verbose
      ```

      将其中的链接脚本的相关内容保存为 `gcc_x86_64.ld` 即可.

   1. stm32 arm-none-eabi-gcc:

      尽管通过 `arm-none-eabi-gcc -Wl,-verbose` 也可以得到链接脚本, 但是不同目标芯片的内存大小和分布各不相同, 因此通常需要到官方 SDK 包中找到链接脚本.

      如果使用 `arm-none-eabi-gcc` 编译器, 官方 SDK 包(STM32CubeF1-1.8.5)提供的链接脚本位于 `STM32CubeF1/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/linker` 路径下.

      > [STM32CubeF1/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/linker/STM32F103XB_FLASH.ld at v1.8.5 · STMicroelectronics/STM32CubeF1 (github.com)](https://github.com/STMicroelectronics/STM32CubeF1/blob/v1.8.5/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/linker/STM32F103XB_FLASH.ld)

      对于 `stm32f103c8t6` 来说, 使用 `STM32F103XB_FLASH.ld` 链接脚本.

   1. keil armcc:

      TODO: keil armcc

   1. esp32 xtensa-esp32-elf-gcc:

      esp-idf 构建系统已经提供了完善的链接器脚本生成机制, 因此不需要直接修改链接脚本.

      已提供链接脚本模板于 `linker/xf_linker.esp.lf` 路径内, esp32 全系列可用.

      TODO: xf_linker.esp.lf 的使用方式.

      > [链接器脚本生成机制 - ESP32 - — ESP-IDF 编程指南 v5.0.6 文档 (espressif.com)](https://docs.espressif.com/projects/esp-idf/zh_CN/v5.0.6/esp32/api-guides/linker-script-generation.html)

   1. ws63 riscv32-linux-musl-gcc:

      已提供 `linker.lds`. 如果从源码编译, 则需要修改生成链接脚本的文件 `linker.prelds`.

1. **在对应的 .text 段的末尾添加 xf_init 相关内容即可**, 其中 32 位平台使用 `ALIGN(4)`, 64 位平台使用 `ALIGN(8)`:

   ```
   . = ALIGN(4);
   __xf_init_start = .;
   KEEP(*(SORT(.xf_auto_init*)))
   __xf_init_end = .;
   . = ALIGN(4);
   ```

   1. linux gcc 的链接脚本:

      ```
      /* 省略 */
      .text           :
      {
         *(.text.unlikely .text.*_unlikely .text.unlikely.*)
         /* 省略 */
         /* .gnu.warning sections are handled specially by elf.em.  */
         *(.gnu.warning)

         /* 在此插入 xf_auto_init 段 */
         . = ALIGN(8);
         __xf_init_start = .;
         KEEP(*(SORT(.xf_auto_init*)))
         __xf_init_end = .;
         . = ALIGN(8);
         /* 此处为 xf_auto_init 段结尾 */

      }
      /* 省略 */
      ```

   1. stm32 arm-none-eabi-gcc:

      对于 `stm32f103c8t6`, 打开 `STM32F103XB_FLASH.ld` 链接脚本.

      ```
      /* 省略 */
      /* The program code and other data goes into FLASH */
      .text :
      {
         . = ALIGN(4);
         *(.text)           /* .text sections (code) */
         /* 省略 */
         KEEP (*(.init))
         KEEP (*(.fini))

         /* 在此插入 xf_auto_init 段 */
         . = ALIGN(4);
         __xf_init_start = .;
         KEEP(*(SORT(.xf_auto_init*)))
         __xf_init_end = .;
         . = ALIGN(4);
         /* 此处为 xf_auto_init 段结尾 */

         . = ALIGN(4);
         _etext = .;        /* define a global symbols at end of code */
      } >FLASH
      /* 省略 */
      ```

   1. keil armcc:

      TODO: keil armcc

   1. esp32 xtensa-esp32-elf-gcc:

      已经提供可直接使用的插件式链接脚本, 直接使用即可, 如果对原理感兴趣见 《[链接器脚本生成机制 - ESP32 - — ESP-IDF 编程指南 v5.0.6 文档 (espressif.com)](https://docs.espressif.com/projects/esp-idf/zh_CN/v5.0.6/esp32/api-guides/linker-script-generation.html)》.

   1. ws63 riscv32-linux-musl-gcc:

   ```
   /* 省略 */
   .text : ALIGN(8) {
      FILL(0xFF)
      *(.text)
      *(.text*)
      /* 省略 */
      KEEP (*(.flashtext))
      KEEP (*(.flashtext*))

      /* 在此插入 xf_auto_init 段 */
      . = ALIGN(4);
      __xf_init_start = .;
      KEEP(*(SORT(.xf_auto_init*)))
      __xf_init_end = .;
      . = ALIGN(4);
      /* 此处为 xf_auto_init 段结尾 */

      __text_end__ = .;
   } > PROGRAM
   /* 省略 */
   ```

1. **链接脚本的使用方式**.

   核心做法是链接时使用 `-T` 命令使用修改后的链接脚本. 如下所示:

   ```
   -Tlinker/gcc_x86_64.xf_init.ld
   ```

   该命令通常添加到 `ldflags` 内, 对于 xmake 就是 `add_ldflags("-Tlinker/gcc_x86_64.xf_init.ld")`.

   对于 esp32, 链接脚本的使用方式有所不同.

#### esp-idf 如何使用自动初始化

1. 只用添加链接脚本一次:

   在任意一个被使用到的组件(含 `idf_component_register`)内的 `CMakeLists.txt` 添加:

   ```cmakelists
   idf_component_register(
      SRCS                ...
      INCLUDE_DIRS        ...
      REQUIRES            ...
      LDFRAGMENTS         "xf_linker.esp.lf"
      WHOLE_ARCHIVE       # 此参数确保自动初始化时能正确访问到相应段中的数据
   )
   ```

   并将 `xf_linker.esp.lf` 复制到 `CMakeLists.txt` 同级目录:

   ```
   📦esp32_component
   ┣ 📜其他文件...
   ┣ 📜CMakeLists.txt
   ┣ 📜xf_linker.esp.lf
   ```

1. 在所有需要自动初始化的组件内的 `CMakeLists.txt` 添加 `WHOLE_ARCHIVE`.

   由于导出的常变量没有被直接调用, 如果不添加, 这些常变量会被 esp32 编译器给移除.

### 优缺点

#### 优点

所有支持 `section` 特性的平台都支持这种做法, 并且初始化函数等内容是在 `.text` 段中的, 不会额外占用 ram.

#### 缺点

需要平台移植者了解段的相关知识, 以及如何在链接脚本中插入 xf_init 所需要的段.

### 参考资料

> - [RT-Thread 自动初始化详解\_rtthread iar 初始化-CSDN 博客](https://blog.csdn.net/yang1111111112/article/details/93982354) > [`杂项命令 (LD) --- Miscellaneous Commands (LD) (sourceware.org)](https://sourceware.org/binutils/docs/ld/Miscellaneous-Commands.html#index-INSERT)
> - [链接脚本(Linker Scripts)语法和规则解析(自官方手册) - BSP-路人甲 - 博客园 (cnblogs.com)](https://www.cnblogs.com/jianhua1992/p/16852784.html)
> - [利用\_\_attribute\_\_((section()))构建初始化函数表【转】 - Sky&amp;Zhang - 博客园 (cnblogs.com)](https://www.cnblogs.com/sky-heaven/p/8275303.html)
> - [函数属性 - 使用 GNU 编译器集合 (GCC) --- Function Attributes - Using the GNU Compiler Collection (GCC)](https://gcc.gnu.org/onlinedocs/gcc-4.7.0/gcc/Function-Attributes.html)
> - [mdk keil 指定变量、函数存储位置，使用 Scatter-Loading Description File， \_\_attribute\_\_(("section")) - QIYUEXIN - 博客园 (cnblogs.com)](https://www.cnblogs.com/qiyuexin/p/9026365.html)

## 基于 constructor 和 `显式调用` 的自动初始化

这两种方式本质上只有两步:

1. **将需要初始化的函数注册到 xf_init 内置链表中;**
1. **在调用 `xf_init()` 的时候执行初始化.**

并且区别只在第一步, constructor 的方式不需要显式调用其他组件需要初始化的函数, 而 `显式调用` 的方式需要显式调用这些函数.

之所以需要第一步, 是因为通过 constructor 声明的函数会先于 `main()` 函数调用, 如果需要自动初始化的对象是任务或者其他应用层 app, 则可能因为调度器还没启动或者其他前置条件没有运行而失败.

因此需要延迟到显式调用 `xf_init()` 时初始化.

### constructor

见 `xf_init_impl_by_constructor.h`.

其原理是, 定义一个构造器函数, 并在其中执行挂载节点的任务.

修改 `examples/xf_init_config.h`:

```
#define XF_INIT_IMPL_METHOD                 XF_INIT_IMPL_BY_CONSTRUCTOR
//                                          XF_INIT_IMPL_BY_SECTION
//                                          XF_INIT_IMPL_BY_CONSTRUCTOR
//                                          XF_INIT_IMPL_BY_REGISTRY
```

对于相同的代码:

```c
int component1(void)
{
    printf("hello, I'm %s\n", __FUNCTION__);
    return 0;
}
XF_INIT_EXPORT_BOARD(component1);
```

其 `XF_INIT_EXPORT_BOARD(component1)` 部分展开如下所示:

```c
void __used __constructor __xf_init_ctors_component1(void)
{
    static const xf_init_desc_t __xf_init_desc_component1 = {
        .func = (component1),
        .func_name = "component1",
    };
    static xf_init_desc_list_t __xf_init_desc_node_component1 = {
        .node = XF_LIST_HEAD_INIT(__xf_init_desc_node_component1.node),
        .p_desc = &__xf_init_desc_component1,
    };
    xf_init_list_register_board(&__xf_init_desc_node_component1);
}
```

其中初始化函数描述信息 `__xf_init_desc_component1` 使用 `const` 修饰可以节省 ram 空间, 而 `__xf_init_desc_node_component1` 则需要固定占用若干字节的 ram 空间.

构造器函数将在 `main()` 函数前隐式调用, 因此后续 `xf_init()` 只需调用注册到链表内的函数即可.

### 显式调用

这种方式只有在禁止使用 GNU 特性的情况下使用, 因为显式调用的方式会导致 xf_init 也依赖需要自动初始化的组件, 而不是通常的"需要自动初始化的组件依赖 xf_init, 而 xf_init 不依赖需要自动初始化的组件".

修改 `examples/xf_init_config.h`:

```
#define XF_INIT_IMPL_METHOD                 XF_INIT_IMPL_BY_REGISTRY
//                                          XF_INIT_IMPL_BY_SECTION
//                                          XF_INIT_IMPL_BY_CONSTRUCTOR
//                                          XF_INIT_IMPL_BY_REGISTRY
```

对于相同的代码:

```c
int component1(void)
{
    printf("hello, I'm %s\n", __FUNCTION__);
    return 0;
}
XF_INIT_EXPORT_BOARD(component1);
```

其 `XF_INIT_EXPORT_BOARD(component1)` 部分展开如下所示:

```c
void __xf_init_registry_component1(void)
{
    static const xf_init_desc_t __xf_init_desc_component1 = {
        .func = (component1),
        .func_name = "component1",
    };
    static xf_init_desc_list_t __xf_init_desc_node_component1 = {
        .node = XF_LIST_HEAD_INIT(__xf_init_desc_node_component1.node),
        .p_desc = &__xf_init_desc_component1,
    };
    xf_init_list_register_board(&__xf_init_desc_node_component1);
}
```

相比使用 `constructor` 的情况只有函数名和函数属性不同, 而且由于该函数没有 `constructor` 属性, 不会被隐式调用, 需要显式调用该函数. 为了在 `xf_init` 中调用该函数, 需要使用注册表机制.

#### 注册表

注册表规则和注册表(registry)见:

1. 注册表规则: `src/xf_init_registry_rule.h`.
1. 注册表: `src/xf_init_registry.inc`.

注册表 `src/xf_init_registry.inc` 在 `src/xf_init.c` 实际上做的事是: 声明外部函数, 并调用他.

在 `src/xf_init.c` 中显式调用外部函数的部分是:

```c
static void xf_init_explicit_call_registry(void)
{
#define XF_INIT_REGISTRY_ACTION_DECLARE
#include "xf_init_registry.inc"
#define XF_INIT_REGISTRY_ACTION_CALL
#include "xf_init_registry.inc"
}
```

对于 `component1`, 以上代码展开为:

```c
static void xf_init_explicit_call_registry(void)
{
    extern void __xf_init_registry_component1(void);    /* 声明 */
    __xf_init_registry_component1();                    /* 调用 */
}
```

这就是 `xf_init` 会依赖外部需要自动初始化的组件的原因.

#### 注册表的使用方式

为了减少参考的变动, 注册表 `src/xf_init_registry.inc` 实际上包含的是用户注册表:

```
#if defined(XF_INIT_USER_REGISTRY_PATH)
#include XF_INIT_USER_REGISTRY_PATH
#endif
```

你需要在 `examples/xf_init_config.h` 内定义 `XF_INIT_USER_REGISTRY_PATH`, 并且路径需要定义为从 `src/xf_init_registry.inc` 路径出发, 到用户注册表的路径, 在示例中则为:

```c
#define XF_INIT_USER_REGISTRY_PATH          "../examples/my_registry.inc"
```

文件树如下:

```
📦xf_init
 ┣ 📂examples
 ┃ ┣ 📜my_registry.inc
 ┣ 📂src
 ┃ ┗ 📜xf_init_registry.inc
 ┗ ...
```

`my_registry.inc` 的内容如下, 根据所需等级填写即可:

```c
XF_INIT_REGISTER_BOARD(component1);
XF_INIT_REGISTER_BOARD(component2);
XF_INIT_REGISTER_PREV(component3);
XF_INIT_REGISTER_BOARD(component4);
XF_INIT_REGISTER_DEVICE(component5);
XF_INIT_REGISTER_BOARD(component6);
XF_INIT_REGISTER_BOARD(component7);
XF_INIT_REGISTER_PREV(component8);
XF_INIT_REGISTER_COMPONENT(component9);
XF_INIT_REGISTER_DEVICE(component10);
XF_INIT_REGISTER_ENV(component11);
XF_INIT_REGISTER_APP(component12);
```

### 优缺点

#### 优点

使用 `constructor` 或显式调用的话不需要了解链接脚本相关知识, 并且 `constructor` 实测基本所有平台都支持, 除了某些平台(如`ws63`)不使用 `constructor` 机制, 而是自行实现了自动初始化的机制.

#### 缺点

除了需要占用闪存以外, 还需要占用 ram 空间用作链表节点, 而且该空间在初始化后的阶段不会使用.
