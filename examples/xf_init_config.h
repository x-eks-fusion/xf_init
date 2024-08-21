/**
 * @file xf_init_config.h
 * @author cangyu (sky.kirto@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-07-01
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

#ifndef __XF_INIT_CONFIG_H__
#define __XF_INIT_CONFIG_H__

/* ==================== [Includes] ========================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

/**
 * @brief 选择自动初始化的实现方式.
 */
#define XF_INIT_IMPL_METHOD                 XF_INIT_IMPL_BY_REGISTRY
//                                          XF_INIT_IMPL_BY_SECTION
//                                          XF_INIT_IMPL_BY_CONSTRUCTOR
//                                          XF_INIT_IMPL_BY_REGISTRY

/**
 * @brief 自动初始化的注册表路径。
 */
#define XF_INIT_USER_REGISTRY_PATH          "my_registry.inc"

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __XF_INIT_CONFIG_H__
