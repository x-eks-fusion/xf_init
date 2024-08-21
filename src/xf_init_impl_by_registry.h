/**
 * @file xf_init_impl_by_registry.h
 * @author catcatBlue (catcatblue@qq.com)
 * @brief 使用注册表实现初始化。
 * @version 1.0
 * @date 2024-07-02
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

#ifndef __XF_INIT_IMPL_BY_REGISTRY_H__
#define __XF_INIT_IMPL_BY_REGISTRY_H__

/* ==================== [Includes] ========================================== */

#include "xf_init_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ================================= */

/**
 * @ingroup group_xf_init_internal
 * @{
 */

/**
 * @brief 向 xf_init 内部初始化链表数组注册一个节点.
 *
 * @attention 不要直接使用该函数.
 *
 * @param p_desc_node 包含初始化描述体与链表节点的初始化节点.
 * @param type 初始化功能类型.
 */
void xf_init_list_register_desc_node(
    xf_init_desc_list_t *p_desc_node, xf_init_type_t type);

/**
 * @brief 注册一个板级初始化函数.
 *
 * @attention 不要直接使用该函数.
 *
 * @param p_desc_node 包含初始化描述体与链表节点的初始化节点.
 */
void xf_init_list_register_board(xf_init_desc_list_t *p_desc_node);

/**
 * @brief 注册一个组件预初始化函数.
 *
 * @attention 不要直接使用该函数.
 *
 * @param p_desc_node 包含初始化描述体与链表节点的初始化节点.
 */
void xf_init_list_register_prev(xf_init_desc_list_t *p_desc_node);

/**
 * @brief 注册一个设备级初始化函数.
 *
 * @attention 不要直接使用该函数.
 *
 * @param p_desc_node 包含初始化描述体与链表节点的初始化节点.
 */
void xf_init_list_register_device(xf_init_desc_list_t *p_desc_node);

/**
 * @brief 注册一个组件级初始化函数.
 *
 * @attention 不要直接使用该函数.
 *
 * @param p_desc_node 包含初始化描述体与链表节点的初始化节点.
 */
void xf_init_list_register_component(xf_init_desc_list_t *p_desc_node);

/**
 * @brief 注册一个环境级初始化函数.
 *
 * @attention 不要直接使用该函数.
 *
 * @param p_desc_node 包含初始化描述体与链表节点的初始化节点.
 */
void xf_init_list_register_env(xf_init_desc_list_t *p_desc_node);

/**
 * @brief 注册一个应用级初始化函数.
 *
 * @attention 不要直接使用该函数.
 *
 * @param p_desc_node 包含初始化描述体与链表节点的初始化节点.
 */
void xf_init_list_register_app(xf_init_desc_list_t *p_desc_node);

/* ==================== [Macros] ============================================ */

/**
 * @brief 并接为 xf_init_desc_t 变量名.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_DESC_NAME(function)         CONCAT(__xf_init_desc_, function)

/**
 * @brief 并接为 xf_init_desc_list_t 变量名.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_DESC_NODE_NAME(function)    CONCAT(__xf_init_desc_node_, function)

/**
 * @brief 定义包含初始化函数、初始化函数的函数名的常量初始化描述体.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_DESC_DEFINE(function) \
    static const xf_init_desc_t XF_INIT_DESC_NAME(function) = { \
        .func       = (function), \
        .func_name  = XSTR(function), \
    }

/**
 * @brief 定义包含初始化描述体与链表节点的初始化变量.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_DESC_NODE_DEFINE(function) \
    static xf_init_desc_list_t XF_INIT_DESC_NODE_NAME(function) = { \
        .node       = XF_LIST_HEAD_INIT(XF_INIT_DESC_NODE_NAME(function).node), \
        .p_desc     = &XF_INIT_DESC_NAME(function), \
    }

/**
 * End of group_xf_init_internal
 * @}
 */

/**
 * @ingroup group_xf_init_internal
 * @defgroup group_xf_init_internal_impl_by_registry registry
 * @brief 基于注册表实现初始化。
 * @{
 */

/**
 * @brief 导出板级初始化函数, 全局函数实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_BOARD.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_REGISTRY_BOARD(function) \
    void __xf_init_registry_##function(void) { \
        XF_INIT_DESC_DEFINE(function); \
        XF_INIT_DESC_NODE_DEFINE(function); \
        xf_init_list_register_board(&XF_INIT_DESC_NODE_NAME(function)); \
    }

/**
 * @brief 导出板级初始化函数, 全局函数实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_PREV.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_REGISTRY_PREV(function) \
    void __xf_init_registry_##function(void) { \
        XF_INIT_DESC_DEFINE(function); \
        XF_INIT_DESC_NODE_DEFINE(function); \
        xf_init_list_register_prev(&XF_INIT_DESC_NODE_NAME(function)); \
    }

/**
 * @brief 导出板级初始化函数, 全局函数实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_DEVICE.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_REGISTRY_DEVICE(function) \
    void __xf_init_registry_##function(void) { \
        XF_INIT_DESC_DEFINE(function); \
        XF_INIT_DESC_NODE_DEFINE(function); \
        xf_init_list_register_device(&XF_INIT_DESC_NODE_NAME(function)); \
    }

/**
 * @brief 导出板级初始化函数, 全局函数实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_COMPONENT.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_REGISTRY_COMPONENT(function) \
    void __xf_init_registry_##function(void) { \
        XF_INIT_DESC_DEFINE(function); \
        XF_INIT_DESC_NODE_DEFINE(function); \
        xf_init_list_register_component(&XF_INIT_DESC_NODE_NAME(function)); \
    }

/**
 * @brief 导出板级初始化函数, 全局函数实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_ENV.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_REGISTRY_ENV(function) \
    void __xf_init_registry_##function(void) { \
        XF_INIT_DESC_DEFINE(function); \
        XF_INIT_DESC_NODE_DEFINE(function); \
        xf_init_list_register_env(&XF_INIT_DESC_NODE_NAME(function)); \
    }

/**
 * @brief 导出板级初始化函数, 全局函数实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_APP.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_REGISTRY_APP(function) \
    void __xf_init_registry_##function(void) { \
        XF_INIT_DESC_DEFINE(function); \
        XF_INIT_DESC_NODE_DEFINE(function); \
        xf_init_list_register_app(&XF_INIT_DESC_NODE_NAME(function)); \
    }

#ifdef __cplusplus
} /* extern "C" */
#endif

/**
 * End of group_xf_init_internal_impl_by_registry
 * @}
 */

#endif /* __XF_INIT_IMPL_BY_REGISTRY_H__ */
