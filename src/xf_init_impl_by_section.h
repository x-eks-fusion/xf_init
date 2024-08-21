/**
 * @file xf_init_impl_by_section.h
 * @author catcatBlue (catcatblue@qq.com)
 * @brief 使用段属性实现自动初始化。
 * @version 1.0
 * @date 2024-07-02
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

#ifndef __XF_INIT_IMPL_BY_SECTION_H__
#define __XF_INIT_IMPL_BY_SECTION_H__

/* ==================== [Includes] ========================================== */

#include "xf_init_types.h"

/**
 * @ingroup group_xf_init_internal
 * @defgroup group_xf_init_internal_impl_by_section section
 * @brief 基于段属性实现自动初始化。
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

#if !defined(__GNUC__)
#   error "section 需要启用 GNU 特性"
#endif

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

/**
 * @brief 导出初始化函数到段.
 *
 * @attention 不要直接使用该宏, 也不要使用 `XF_INIT_EXPORT_SECTION_BOARD`,
 * 请用之后定义 `XF_INIT_*` 宏, 如 `XF_INIT_EXPORT_BOARD`.
 *
 * @param function 初始化函数. 类型见 @ref xf_init_fn_t.
 * @param level 字符串等级. 范围: "1" ~ "6".
 */
#define XF_INIT_EXPORT_SECTION(function, level) \
    __used __section(".xf_auto_init." level) \
    const xf_init_desc_t __xf_init_##function = { \
        .func       = (function), \
        .func_name  = XSTR(function), \
    }

/**
 * @brief 板级初始化.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_BOARD.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_SECTION_BOARD(function)      XF_INIT_EXPORT_SECTION(function, "1")

/**
 * @brief 组件预初始化 (pure software initialization).
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_PREV.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_SECTION_PREV(function)       XF_INIT_EXPORT_SECTION(function, "2")

/**
 * @brief 设备初始化.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_DEVICE.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_SECTION_DEVICE(function)     XF_INIT_EXPORT_SECTION(function, "3")

/**
 * @brief 组件初始化 (dfs, lwip, ...).
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_COMPONENT.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_SECTION_COMPONENT(function)  XF_INIT_EXPORT_SECTION(function, "4")

/**
 * @brief 环境初始化 (mount disk, ...).
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_ENV.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_SECTION_ENV(function)        XF_INIT_EXPORT_SECTION(function, "5")

/**
 * @brief 应用程序初始化 (gui application etc ...).
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_APP.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_SECTION_APP(function)        XF_INIT_EXPORT_SECTION(function, "6")

#ifdef __cplusplus
} /* extern "C" */
#endif

/**
 * End of group_xf_init_internal_impl_by_section
 * @}
 */

#endif /* __XF_INIT_IMPL_BY_SECTION_H__ */

