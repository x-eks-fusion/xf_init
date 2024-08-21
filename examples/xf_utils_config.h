/**
 * @file xf_utils_config.h
 * @author cangyu (sky.kirto@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-07-01
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

#ifndef __XF_UTILS_CONFIG_H__
#define __XF_UTILS_CONFIG_H__

/* ==================== [Includes] ========================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

/**
 * @brief 是否使用标准库的类型定义(uint32_t 之类).
 */
#define XF_STDDEF_ENABLE                (1)

/**
 * @brief 是否使能错误码值到字符串的查找表(`XF_OK`->"XF_OK").
 */
#define XF_COMMON_ERR_TO_NAME_LOOKUP_DISABLE     (1)

/**
 * @brief 获取文件名。
 * __FILENAME__ 定义于 xf_def.h，需要 gcc 编译器支持。
 * 如果不支持，__FILENAME__ == __FILE__。
 */
#define XF_LOG_FILE_NAME                    (__FILENAME__)

/**
 * @brief 新行符。
 */
#define XF_LOG_NEWLINE                      "\n"

/**
 * @brief 日志动态栈数组缓存大小。
 */
#define XF_LOG_BUF_SIZE                     (64U)

/**
 * @brief 时间戳样式。二选一.
 */
#define XF_LOG_TIMESTAMP_TIME_MS            (1)

/**
 * @brief 默认日志等级。 见 @ref xf_log_types.h
 */
#define XF_LOG_DEFAULT_LEVEL                (XF_LOG_LVL_INFO)

/**
 * @brief 是否使用彩色 log。
 */
#define XF_LOG_COLORS_ENABLE                    (1)

/**
 * @brief 是否使用 xf_printf() 替代 printf()
 */
#define XF_PRINTF_OVERRIDE_STD_ENABLE            (0)

/**
 * @brief 是否使用 xf_printf.
 */
#define XF_PRINTF_CUSTOM_PRINTF_ENABLE            (1)

/**
 * @brief 'ntoa' 转换缓冲区大小，必须足够大才能容纳一个转换后的缓冲区
 * 包含填充零的数字（在堆栈上动态创建）
 * 默认值：32 字节
 */
#define PRINTF_NTOA_BUFFER_SIZE             32U

/**
 * @brief 'ftoa' 转换缓冲区大小，必须足够大才能容纳转换后的数据
 * 包含填充零的浮点数（在堆栈上动态创建）
 * 默认值：32 字节
 */
#define PRINTF_FTOA_BUFFER_SIZE             32U

/**
 * @brief 支持浮点类型（%f）
 */
#define PRINTF_SUPPORT_FLOAT                1

/**
 * @brief 支持指数浮点表示法 (%e/%g)
 */
// #define PRINTF_DISABLE_SUPPORT_EXPONENTIAL   1
#define PRINTF_SUPPORT_EXPONENTIAL           1

/**
 * @brief 定义默认浮点精度
 */
#define PRINTF_DEFAULT_FLOAT_PRECISION       6U

/**
 * @brief 定义适合用 %f 打印的最大浮点数
 */
#define PRINTF_MAX_FLOAT                     1e9

/**
 * @brief 支持 long long 类型（%llu 或 %p）
 */
#define PRINTF_SUPPORT_LONG_LONG             1

/**
 * @brief 支持 ptrdiff_t 类型 (%t)
 * ptrdiff_t 通常在 <stddef.h> 中定义为 long 或 long long 类型
 */
#define PRINTF_SUPPORT_PTRDIFF_T             1

#define XF_LOCK_EN                       1


/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __XF_UTILS_CONFIG_H__
