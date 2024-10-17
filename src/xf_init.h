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

#include "xf_init_config_internal.h"
#include "xf_utils.h"

#include "section/xf_init_section.h"
#include "registry/xf_init_registry.h"

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
 * @brief xf 初始化. 所有使用宏收集的初始化函数，将会在这里统一调用
 *
 * @return xf_err_t
 *      - XF_FAIL                   失败
 *      - XF_OK                     成功
 */
xf_err_t xf_init(void);

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
 * @brief 基础配置初始化. 主要用于初始化 log 等功能。
 *
 * @attention 此宏一般用于系统初始化，不推荐应用层调用。
 *
 * 根据实际配置见:
 * - @ref XF_INIT_EXPORT_SECTION_SETUP
 * - @ref XF_INIT_EXPORT_REGISTRY_SETUP
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_SETUP(function)

/**
 * @brief 板级初始化.初始化和开发板相关内容，如 heap，sys 等功能。
 *
 * @attention 此宏一般用于系统初始化，不推荐应用层调用。
 *
 * 根据实际配置见:
 * - @ref XF_INIT_EXPORT_SECTION_BOARD
 * - @ref XF_INIT_EXPORT_REGISTRY_BOARD
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_BOARD(function)

/**
 * @brief 抽象层预初始化，初始化 HAL NAL 等抽象层.
 *
 * @attention 此宏一般用于系统初始化，不推荐应用层调用。
 *
 * 根据实际配置见:
 * - @ref XF_INIT_EXPORT_SECTION_PREV
 * - @ref XF_INIT_EXPORT_REGISTRY_PREV
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_PREV(function)

/**
 * @brief 设置清除初始化，对应 SETUP 这里用于反初始化一些应用层不需要的操作.
 *
 * @attention 此宏一般用于系统初始化，不推荐应用层调用。
 *
 * 根据实际配置见:
 * - @ref XF_INIT_EXPORT_SECTION_CLEANUP
 * - @ref XF_INIT_EXPORT_REGISTRY_CLEANUP
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_CLEANUP(function)

/**
 * @brief 设备初始化. 应用层初始化外设使用
 *
 * 根据实际配置见:
 * - @ref XF_INIT_EXPORT_SECTION_DEVICE
 * - @ref XF_INIT_EXPORT_REGISTRY_DEVICE
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_DEVICE(function)

/**
 * @brief 组件初始化. 应用层初始化一些外部组件使用
 *
 * 根据实际配置见:
 * - @ref XF_INIT_EXPORT_SECTION_COMPONENT
 * - @ref XF_INIT_EXPORT_REGISTRY_COMPONENT
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_COMPONENT(function)

/**
 * @brief 环境初始化. 应用层初始化环境（如文件系统）
 *
 * 根据实际配置见:
 * - @ref XF_INIT_EXPORT_SECTION_ENV
 * - @ref XF_INIT_EXPORT_REGISTRY_ENV
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_ENV(function)

/**
 * @brief 应用程序初始化. 如
 *
 * 根据实际配置见:
 * - @ref XF_INIT_EXPORT_SECTION_APP
 * - @ref XF_INIT_EXPORT_REGISTRY_APP
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_APP(function)

#elif     (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_SECTION)

#define XF_INIT_EXPORT_SETUP(function)          XF_INIT_EXPORT_SECTION_SETUP(function)

#define XF_INIT_EXPORT_BOARD(function)          XF_INIT_EXPORT_SECTION_BOARD(function)

#define XF_INIT_EXPORT_PREV(function)           XF_INIT_EXPORT_SECTION_PREV(function)

#define XF_INIT_EXPORT_CLEANUP(function)        XF_INIT_EXPORT_SECTION_CLEANUP(function)

#define XF_INIT_EXPORT_DEVICE(function)         XF_INIT_EXPORT_SECTION_DEVICE(function)

#define XF_INIT_EXPORT_COMPONENT(function)      XF_INIT_EXPORT_SECTION_COMPONENT(function)

#define XF_INIT_EXPORT_ENV(function)            XF_INIT_EXPORT_SECTION_ENV(function)

#define XF_INIT_EXPORT_APP(function)            XF_INIT_EXPORT_SECTION_APP(function)

#elif   (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY || XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_CONSTRUCTOR)

#define XF_INIT_EXPORT_SETUP(function)          XF_INIT_EXPORT_REGISTRY_SETUP(function)

#define XF_INIT_EXPORT_BOARD(function)          XF_INIT_EXPORT_REGISTRY_BOARD(function)

#define XF_INIT_EXPORT_PREV(function)           XF_INIT_EXPORT_REGISTRY_PREV(function)

#define XF_INIT_EXPORT_CLEANUP(function)        XF_INIT_EXPORT_REGISTRY_CLEANUP(function)

#define XF_INIT_EXPORT_DEVICE(function)         XF_INIT_EXPORT_REGISTRY_DEVICE(function)

#define XF_INIT_EXPORT_COMPONENT(function)      XF_INIT_EXPORT_REGISTRY_COMPONENT(function)

#define XF_INIT_EXPORT_ENV(function)            XF_INIT_EXPORT_REGISTRY_ENV(function)

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
