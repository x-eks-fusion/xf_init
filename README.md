# xf_init

## xf_init 特点
1. 支持 section 自动初始化方式，通用性更强
2. 支持 constructor 自动初始化方式，移植更简单
3. 支持注册表手动初始化方式，可读性和通用性更高。
4. 仅依赖[xf_utils](https://github.com/x-eks-fusion/xf_utils),可移植性强。
5. 占用低，解耦性强。除了.h文件，仅仅只有一个300行不到的.c文件

## 文件夹介绍

```shell
.
├── config_template                     # xf_init 配置模板
├── examples                            # linux 例程
├── linker                              # 各个平台的链接脚本（持续更新）
├── src                                 # xf_init 源代码
│  ├── xf_init.c                        # 实现 xf_init 相关收集函数
│  ├── xf_init.h                        # 对外调用头文件
│  ├── xf_init_config_internal.h        # 内部依赖的配置文件
│  ├── xf_init_impl_by_constructor.h    # constructor 自动初始化实现
│  ├── xf_init_impl_by_registry.h       # 注册表初始化的实现
│  ├── xf_init_impl_by_section.h        # section 初始化的实现
│  ├── xf_init_registry.inc             # 内部注册表（在注册表模式下使用）
│  ├── xf_init_registry_rule.h          # 注册表规则实现
│  └── xf_init_types.h                  # 相关类型头文件
├── DETAILS.md                          # 自动初始化原理说明
├── README.md                           # 仓库说明文档
└── xmake.lua                           # xmake 构建脚本
```

## 实现方式

自动初始化实现库. 内含三种实现方式:

1. 需要自动初始化的函数的符号导出到段, 实现依赖倒置(见 `xf_init_impl_by_section.h`).
1. 需要自动初始化的函数的符号, 通过 `constructor` 挂载到内置初始化链表, 实现在调用时初始化(延迟初始化), 同时也实现依赖倒置(见 `xf_init_impl_by_constructor.h`).
1. 显式调用注册函数, 此时需要手动修改注册表(见 `xf_init_impl_by_registry.h`), 此时 `xf_init` 也会依赖需要初始化的组件, 通常不推荐使用.

切换这三种实现方式时, 需要自动初始化的代码无需改动, 只需使用对应的宏即可, 如 `XF_INIT_EXPORT_DEVICE`.
使用示例如下:

```c
int component5(void)
{
    printf("hello, I'm %s\n", __FUNCTION__);
    return __COUNTER__;
}
XF_INIT_EXPORT_DEVICE(component5);
```

但是, 如果使用的是显式调用注册函数, 记得在注册表中添加需要自动初始化的函数, 如 `examples/my_registry.inc` 所示.

```c
XF_INIT_REGISTER_BOARD(component1);
// ...
XF_INIT_REGISTER_DEVICE(component5);
// ...
XF_INIT_REGISTER_APP(component12);
```

注册表使用方式见 `src/xf_init_registry.inc` 内的注释.

# 快速入门

1. 安装 xmake.

   [安装 - xmake](https://xmake.io/#/zh-cn/guide/installation)

1. 克隆 xf_utils.

   ```bash
   # 克隆本仓库, 略
   cd xf_init
   # 获取 xf_utils
   git clone https://github.com/x-eks-fusion/xf_utils.git
   ```

1. 修改日志等级.

   ```c
   // xf_utils/src/xf_log/xf_log_config.h
   #   define XF_LOG_LOCAL_LEVEL XF_LOG_INFO
   // 修改为 👇
   #   define XF_LOG_LOCAL_LEVEL XF_LOG_VERBOSE
   ```

1. 运行 linux 示例.

   ```bash
   cd examples/
   clear; xmake clean linux; xmake build linux; xmake run linux
   ```

1. 测试其他初始化方式.

   ```c
   // 修改 examples/xf_init_config.h
   /**
   * @brief 选择自动初始化的实现方式.
   */
   #define XF_INIT_IMPL_METHOD                 XF_INIT_IMPL_BY_REGISTRY
   //                                          XF_INIT_IMPL_BY_SECTION
   //                                          XF_INIT_IMPL_BY_CONSTRUCTOR
   //                                          XF_INIT_IMPL_BY_REGISTRY
   ```

# 详细说明

见 《[详细说明](DETAILS.md)》.
