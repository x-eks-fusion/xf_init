/**
 * @file xf_init_registry.h
 * @author catcatBlue (catcatblue@qq.com)
 * @brief 使用注册表实现初始化。
 * @version 1.0
 * @date 2024-07-02
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

#ifndef __XF_INIT_REGISTRY_H__
#define __XF_INIT_REGISTRY_H__

/* ==================== [Includes] ========================================== */

#include "../xf_init_config_internal.h"
#include "xf_utils.h"

#if XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY || XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_CONSTRUCTOR

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

#if defined(__GNUC__) && !defined(__constructor) && XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_CONSTRUCTOR
#   define __constructor               __attribute__((constructor))
#else
#   define __constructor
#endif

/* ==================== [Typedefs] ========================================== */

/**
 * @brief 初始化功能类型。
 */
typedef enum _xf_init_registry_type_t {
    XF_INIT_REGISTRY_TYPE_SETUP = 0x00,      /*!< 板级 */
    XF_INIT_REGISTRY_TYPE_BOARD,             /*!< 板级 */
    XF_INIT_REGISTRY_TYPE_PREV,              /*!< 组件级预初始化 */
    XF_INIT_REGISTRY_TYPE_CLEANUP,              /*!< 组件级预初始化 */
    XF_INIT_REGISTRY_TYPE_DEVICE,            /*!< 设备级 */
    XF_INIT_REGISTRY_TYPE_COMPONENT,         /*!< 组件级 */
    XF_INIT_REGISTRY_TYPE_ENV,               /*!< 环境级 */
    XF_INIT_REGISTRY_TYPE_APP,               /*!< 应用程序级 */

    XF_INIT_REGISTRY_TYPE_MAX,
} xf_init_registry_type_t;

/**
 * @brief 初始化函数类型.
 *
 * @return int
 *      - 0             无异常
 *      - (OTHER)       错误码见 @ref xf_err_code_t.
 */
typedef int (*xf_init_fn_t)(void);

/**
 * @brief 初始化函数详情结构体.
 *
 * desc: description.
 *
 * @note 基于 section 初始化时用.
 */
typedef struct _xf_init_registry_desc_t {
    const xf_init_fn_t func;            /*!< 初始化函数 */
    const char *func_name;              /*!< 初始化函数的函数名 */
} xf_init_registry_desc_t;

/**
 * @brief 初始化函数链表结构体.
 *
 * @note 基于 registry 初始化时用.
 */
typedef struct _xf_init_registry_desc_node_t {
    xf_list_t node;
    const xf_init_registry_desc_t *const p_desc;
} xf_init_registry_desc_node_t;

/* ==================== [Global Prototypes] ================================= */

/**
 * @brief （内部函数）注册初始化函数，无需直接调用，使用宏调用
 * 
 * @param p_desc_node 函数详情结构体
 * @param type 注册初始化函数的类型
 */
void xf_init_registry_register_desc_node(xf_init_registry_desc_node_t *p_desc_node, xf_init_registry_type_t type);

/**
 * @brief 注册函数收集后，统一在此调用初始化函数
 * 
 */
void xf_init_from_registry(void);

/* ==================== [Macros] ============================================ */

/**
 * @ingroup group_xf_init_internal
 * @defgroup group_xf_init_internal_registry registry
 * @brief 基于注册表实现初始化。
 * @{
 */

#define XF_INIT_EXPORT_REGISTRY(type, function) \
    void __used __constructor __xf_init_registry_##function(void) { \
        static const xf_init_registry_desc_t CONCAT(__xf_init_desc_, function) = { \
            .func       = (function), \
            .func_name  = XSTR(function), \
        };\
        static xf_init_registry_desc_node_t CONCAT(__xf_init_desc_node_, function) = { \
            .node       = XF_LIST_HEAD_INIT(CONCAT(__xf_init_desc_node_, function).node), \
            .p_desc     = &CONCAT(__xf_init_desc_, function), \
        };\
        xf_init_registry_register_desc_node(&CONCAT(__xf_init_desc_node_, function), XF_INIT_REGISTRY_TYPE_##type); \
    }


/**
 * @brief 导出板级初始化函数, 全局函数实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_BOARD.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_REGISTRY_SETUP(function) XF_INIT_EXPORT_REGISTRY(SETUP, function)

/**
 * @brief 导出板级初始化函数, 全局函数实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_BOARD.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_REGISTRY_BOARD(function) XF_INIT_EXPORT_REGISTRY(BOARD, function)

/**
 * @brief 导出板级初始化函数, 全局函数实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_PREV.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_REGISTRY_PREV(function) XF_INIT_EXPORT_REGISTRY(PREV, function)

/**
 * @brief 导出板级初始化函数, 全局函数实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_BOARD.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_REGISTRY_CLEANUP(function) XF_INIT_EXPORT_REGISTRY(CLEANUP, function)

/**
 * @brief 导出板级初始化函数, 全局函数实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_DEVICE.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_REGISTRY_DEVICE(function) XF_INIT_EXPORT_REGISTRY(DEVICE, function)

/**
 * @brief 导出板级初始化函数, 全局函数实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_COMPONENT.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_REGISTRY_COMPONENT(function) XF_INIT_EXPORT_REGISTRY(COMPONENT, function)

/**
 * @brief 导出板级初始化函数, 全局函数实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_ENV.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_REGISTRY_ENV(function) XF_INIT_EXPORT_REGISTRY(ENV, function)

/**
 * @brief 导出板级初始化函数, 全局函数实现.
 *
 * @attention 不要直接使用该宏. 请使用 @ref XF_INIT_EXPORT_APP.
 *
 * @param function 初始化函数.
 */
#define XF_INIT_EXPORT_REGISTRY_APP(function) XF_INIT_EXPORT_REGISTRY(APP, function)


#ifdef __cplusplus
} /* extern "C" */
#endif

/**
 * End of group_xf_init_internal_registry
 * @}
 */

#endif

#endif /* __XF_INIT_REGISTRY_H__ */
