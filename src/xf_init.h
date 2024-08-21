/**
 * @file xf_init.h
 * @author catcatBlue (catcatblue@qq.com)
 * @brief 自动初始化。
 * @version 1.0
 * @date 2024-07-02
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

/**
 * @defgroup group_xf_init xf_init
 * @brief xf_init 实现自动初始化。
 *
 * 基于段的自动初始化机制可以实现：
 * 需要初始化的组件依赖 xf_init, 而 xf_init 不依赖这些组件。
 *
 */

/**
 * @ingroup group_xf_init
 * @defgroup group_xf_init_user 用户接口
 * @brief 不同等级的自动初始化宏。
 *
 * xfusion 用户使用 xf_init 时只需 `#include "xf_init.h"` 即可。
 *
 */

/**
 * @ingroup group_xf_init
 * @defgroup group_xf_init_port 移植接口
 * @brief 调用 xf_init 运行自动初始化的接口。
 */

/**
 * @ingroup group_xf_init
 * @defgroup group_xf_init_internal 内部接口
 * @brief 不同初始化方式的实现。用户不一定需要。
 */

#ifndef __XF_INIT_H__
#define __XF_INIT_H__

/* ==================== [Includes] ========================================== */

#include "xf_init_types.h"

#if     (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_SECTION)
#   include "xf_init_impl_by_section.h"
#elif   (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_CONSTRUCTOR)
#   include "xf_init_impl_by_constructor.h"
#elif   (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY)
#   include "xf_init_impl_by_registry.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ================================= */

/**
 * @ingroup group_xf_init_port
 * @{
 */

/**
 * @brief xf 初始化.
 *
 * @param p_ops 提供给 xf_init 调用的预初始化函数.
 * @return xf_err_t
 *      - XF_ERR_INVALID_ARG        参数错误
 *      - XF_FAIL                   失败
 *      - XF_OK                     成功
 */
xf_err_t xf_init(const xf_init_preinit_ops_t *const p_ops);

/**
 * End of group_xf_init_port
 * @}
 */

/**
 * @ingroup group_xf_init_user
 * @{
 */


/* ==================== [Macros] ============================================ */

#if     defined(__DOXYGEN__)
/* 此处仅用于生成 doxygen 注释 */
/**
 * @brief 板级初始化.
 *
 * 根据实际配置见:
 * - @ref XF_INIT_EXPORT_SECTION_BOARD
 * - @ref XF_INIT_EXPORT_CONSTRUCTOR_BOARD
 * - @ref XF_INIT_EXPORT_REGISTRY_BOARD
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_BOARD(function)
/**
 * @brief 组件预初始化 (pure software initialization).
 *
 * 根据实际配置见:
 * - @ref XF_INIT_EXPORT_SECTION_PREV
 * - @ref XF_INIT_EXPORT_CONSTRUCTOR_PREV
 * - @ref XF_INIT_EXPORT_REGISTRY_PREV
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_PREV(function)
/**
 * @brief 设备初始化.
 *
 * 根据实际配置见:
 * - @ref XF_INIT_EXPORT_SECTION_DEVICE
 * - @ref XF_INIT_EXPORT_CONSTRUCTOR_DEVICE
 * - @ref XF_INIT_EXPORT_REGISTRY_DEVICE
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_DEVICE(function)
/**
 * @brief 组件初始化 (dfs, lwip, ...).
 *
 * 根据实际配置见:
 * - @ref XF_INIT_EXPORT_SECTION_COMPONENT
 * - @ref XF_INIT_EXPORT_CONSTRUCTOR_COMPONENT
 * - @ref XF_INIT_EXPORT_REGISTRY_COMPONENT
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_COMPONENT(function)
/**
 * @brief 环境初始化 (mount disk, ...).
 *
 * 根据实际配置见:
 * - @ref XF_INIT_EXPORT_SECTION_ENV
 * - @ref XF_INIT_EXPORT_CONSTRUCTOR_ENV
 * - @ref XF_INIT_EXPORT_REGISTRY_ENV
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_ENV(function)
/**
 * @brief 应用程序初始化 (gui application etc ...).
 *
 * 根据实际配置见:
 * - @ref XF_INIT_EXPORT_SECTION_APP
 * - @ref XF_INIT_EXPORT_CONSTRUCTOR_APP
 * - @ref XF_INIT_EXPORT_REGISTRY_APP
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_APP(function)
#elif     (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_SECTION)
/**
 * @brief 板级初始化.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_BOARD(function)          XF_INIT_EXPORT_SECTION_BOARD(function)
/**
 * @brief 组件预初始化 (pure software initialization)
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_PREV(function)           XF_INIT_EXPORT_SECTION_PREV(function)
/**
 * @brief 设备初始化.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_DEVICE(function)         XF_INIT_EXPORT_SECTION_DEVICE(function)
/**
 * @brief 组件初始化 (dfs, lwip, ...).
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_COMPONENT(function)      XF_INIT_EXPORT_SECTION_COMPONENT(function)
/**
 * @brief 环境初始化 (mount disk, ...).
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_ENV(function)            XF_INIT_EXPORT_SECTION_ENV(function)
/**
 * @brief 应用程序初始化 (gui application etc ...).
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_APP(function)            XF_INIT_EXPORT_SECTION_APP(function)
#elif   (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_CONSTRUCTOR)
/**
 * @brief 板级初始化.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_BOARD(function)          XF_INIT_EXPORT_CONSTRUCTOR_BOARD(function)
/**
 * @brief 组件预初始化 (pure software initialization).
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_PREV(function)           XF_INIT_EXPORT_CONSTRUCTOR_PREV(function)
/**
 * @brief 设备初始化.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_DEVICE(function)         XF_INIT_EXPORT_CONSTRUCTOR_DEVICE(function)
/**
 * @brief 组件初始化 (dfs, lwip, ...).
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_COMPONENT(function)      XF_INIT_EXPORT_CONSTRUCTOR_COMPONENT(function)
/**
 * @brief 环境初始化 (mount disk, ...).
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_ENV(function)            XF_INIT_EXPORT_CONSTRUCTOR_ENV(function)
/**
 * @brief 应用程序初始化 (gui application etc ...).
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_APP(function)            XF_INIT_EXPORT_CONSTRUCTOR_APP(function)
#elif   (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY)
/**
 * @brief 板级初始化.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_BOARD(function)          XF_INIT_EXPORT_REGISTRY_BOARD(function)
/**
 * @brief 组件预初始化 (pure software initialization)
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_PREV(function)           XF_INIT_EXPORT_REGISTRY_PREV(function)
/**
 * @brief 设备初始化.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_DEVICE(function)         XF_INIT_EXPORT_REGISTRY_DEVICE(function)
/**
 * @brief 组件初始化 (dfs, lwip, ...).
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_COMPONENT(function)      XF_INIT_EXPORT_REGISTRY_COMPONENT(function)
/**
 * @brief 环境初始化 (mount disk, ...).
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_ENV(function)            XF_INIT_EXPORT_REGISTRY_ENV(function)
/**
 * @brief 应用程序初始化 (gui application etc ...).
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_APP(function)            XF_INIT_EXPORT_REGISTRY_APP(function)
#endif

/**
 * End of group_xf_init_user
 * @}
 */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* __XF_INIT_H__ */
