/**
 * @file xf_init_config_internal.h
 * @author catcatBlue (catcatblue@qq.com)
 * @brief xf_init 模块内部配置总头文件。
 *        确保 xf_init_config.h 的所有定义都有默认值。
 * @version 1.0
 * @date 2024-07-02
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

#ifndef __XF_INIT_CONFIG_INTERNAL_H__
#define __XF_INIT_CONFIG_INTERNAL_H__

/* ==================== [Includes] ========================================== */

#include "xf_init_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

#define XF_INIT_IMPL_BY_SECTION         0
#define XF_INIT_IMPL_BY_CONSTRUCTOR     1
#define XF_INIT_IMPL_BY_REGISTRY        2

/* Implementation method */
#if !defined(XF_INIT_IMPL_METHOD)
#   define XF_INIT_IMPL_METHOD          XF_INIT_IMPL_BY_SECTION
#endif

#if XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY && !defined(XF_INIT_USER_REGISTRY_PATH)
#error "when XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY, you must define XF_INIT_USER_REGISTRY_PATH"
#endif

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __XF_INIT_CONFIG_INTERNAL_H__
