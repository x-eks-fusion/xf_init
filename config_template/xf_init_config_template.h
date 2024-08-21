/**
 * @file xf_init_config_template.h
 * @author catcatBlue (catcatblue@qq.com)
 * @brief xf_init 配置文件模板.
 * @version 1.0
 * @date 2024-08-06
 * 
 * Copyright (c) 2024, CorAL. All rights reserved.
 * 
 */

/**
 * @brief 使用说明.
 *
 * 1. 复制该文件到工程目录, 并重命名为 `xf_init_config.h`.
 * 2. 打开本文件(`#if 0` 改为 `#if 1`, 或删除 `#if 0` 和对应的 `#endif`).
 *
 */

#if 0

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
#define XF_INIT_IMPL_METHOD                 XF_INIT_IMPL_BY_SECTION
//                                          XF_INIT_IMPL_BY_CONSTRUCTOR
//                                          XF_INIT_IMPL_BY_REGISTRY

/**
 * @brief 自动初始化注册表文件路径.
 */
// #define XF_INIT_USER_REGISTRY_PATH          "/path/to/your/registry.inc"

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* __XF_INIT_CONFIG_H__ */

#endif /* if 0 */