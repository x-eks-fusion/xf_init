/**
 * @file xf_init_impl_by_constructor.h
 * @author catcatBlue (catcatblue@qq.com)
 * @brief 使用构造器属性实现自动初始化。
 *        ctors 缩写来源: https://gcc.gnu.org/onlinedocs/gccint/Initialization.html
 * @version 1.0
 * @date 2024-07-02
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

#ifndef __XF_INIT_IMPL_BY_CONSTRUCTOR_H__
#define __XF_INIT_IMPL_BY_CONSTRUCTOR_H__

/* ==================== [Includes] ========================================== */

#include "xf_init_impl_by_registry.h"

/**
 * @ingroup group_xf_init_internal
 * @defgroup group_xf_init_internal_impl_by_constructor constructor
 * @brief 基于构造器属性实现自动初始化。
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

#if !defined(__GNUC__)
#   error "constructor 需要启用 GNU 特性"
#endif

#if !defined(__constructor)
#   define __constructor               __attribute__((constructor))
#endif

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

/**
 * @brief 导出板级初始化函数, constructor 实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_BOARD.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_CONSTRUCTOR_BOARD(function) \
    void __used __constructor __xf_init_ctors_##function(void) { \
        XF_INIT_DESC_DEFINE(function); \
        XF_INIT_DESC_NODE_DEFINE(function); \
        xf_init_list_register_board(&XF_INIT_DESC_NODE_NAME(function)); \
    }

/**
 * @brief 导出组件预初始化函数, constructor 实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_PREV.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_CONSTRUCTOR_PREV(function) \
    void __used __constructor __xf_init_ctors_##function(void) { \
        XF_INIT_DESC_DEFINE(function); \
        XF_INIT_DESC_NODE_DEFINE(function); \
        xf_init_list_register_prev(&XF_INIT_DESC_NODE_NAME(function)); \
    }

/**
 * @brief 导出设备初始化函数, constructor 实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_DEVICE.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_CONSTRUCTOR_DEVICE(function) \
    void __used __constructor __xf_init_ctors_##function(void) { \
        XF_INIT_DESC_DEFINE(function); \
        XF_INIT_DESC_NODE_DEFINE(function); \
        xf_init_list_register_device(&XF_INIT_DESC_NODE_NAME(function)); \
    }

/**
 * @brief 导出组件初始化函数, constructor 实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_COMPONENT.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_CONSTRUCTOR_COMPONENT(function) \
    void __used __constructor __xf_init_ctors_##function(void) { \
        XF_INIT_DESC_DEFINE(function); \
        XF_INIT_DESC_NODE_DEFINE(function); \
        xf_init_list_register_component(&XF_INIT_DESC_NODE_NAME(function)); \
    }

/**
 * @brief 导出环境初始化函数, constructor 实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_ENV.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_CONSTRUCTOR_ENV(function) \
    void __used __constructor __xf_init_ctors_##function(void) { \
        XF_INIT_DESC_DEFINE(function); \
        XF_INIT_DESC_NODE_DEFINE(function); \
        xf_init_list_register_env(&XF_INIT_DESC_NODE_NAME(function)); \
    }

/**
 * @brief 导出应用初始化函数, constructor 实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_APP.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_CONSTRUCTOR_APP(function) \
    void __used __constructor __xf_init_ctors_##function(void) { \
        XF_INIT_DESC_DEFINE(function); \
        XF_INIT_DESC_NODE_DEFINE(function); \
        xf_init_list_register_app(&XF_INIT_DESC_NODE_NAME(function)); \
    }

#ifdef __cplusplus
} /*extern "C"*/
#endif

/**
 * End of group_xf_init_internal_impl_by_constructor
 * @}
 */

#endif /* __XF_INIT_IMPL_BY_CONSTRUCTOR_H__ */
