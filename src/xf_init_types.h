/**
 * @file xf_init_types.h
 * @author catcatBlue (catcatblue@qq.com)
 * @brief xf_init 类型定义。
 * @version 1.0
 * @date 2024-07-02
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

#ifndef __XF_INIT_TYPES_H__
#define __XF_INIT_TYPES_H__

/* ==================== [Includes] ========================================== */

#include "xf_init_config_internal.h"

#include "xf_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/**
 * @ingroup group_xf_init_user
 * @{
 */

/**
 * @brief 初始化函数类型.
 *
 * @return int
 *      - 0             无异常
 *      - (OTHER)       错误码见 @ref xf_err_code_t.
 */
typedef int (*xf_init_fn_t)(void);

/**
 * End of group_xf_init_user
 * @}
 */

/**
 * @ingroup group_xf_init_internal
 * @{
 */

/**
 * @brief 初始化功能类型。
 */
typedef enum _xf_init_type_t {
    XF_INIT_TYPE_BOARD = 0x00,      /*!< 板级 */
    XF_INIT_TYPE_PREV,              /*!< 组件级预初始化 */
    XF_INIT_TYPE_DEVICE,            /*!< 设备级 */
    XF_INIT_TYPE_COMPONENT,         /*!< 组件级 */
    XF_INIT_TYPE_ENV,               /*!< 环境级 */
    XF_INIT_TYPE_APP,               /*!< 应用程序级 */

    XF_INIT_TYPE_MAX,
} xf_init_type_t;

/**
 * @brief 初始化函数详情结构体.
 *
 * desc: description.
 *
 * @note 基于 section 初始化时用.
 */
typedef struct _xf_init_desc_t {
    const xf_init_fn_t func;            /*!< 初始化函数 */
    const char *func_name;              /*!< 初始化函数的函数名 */
} xf_init_desc_t;

/**
 * @brief 初始化函数链表结构体.
 *
 * @note 基于 constructor 初始化时用.
 */
typedef struct _xf_init_desc_list_t {
    xf_list_t node;
    const xf_init_desc_t *const p_desc;
} xf_init_desc_list_t;

/**
 * End of group_xf_init_internal
 * @}
 */

/**
 * @ingroup group_xf_init_port
 * @{
 */

/**
 * @brief xf_init 预初始化函数类型.
 */
typedef struct _xf_init_preinit_ops_t {
    /**
     * @brief 预初始化.
     * 主要完成调试串口的初始化以及日志输出函数的设置.
     * 也可以忽略该参数, 在调用 `xf_init` 前初始化.
     */
    void (*preinit)(void);

    /**
     * @brief 反预初始化.
     * 主要完成反初始化调试串口.
     */
    void (*predeinit)(void);
} xf_init_preinit_ops_t;

/**
 * End of group_xf_init_port
 * @}
 */

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* __XF_INIT_TYPES_H__ */
