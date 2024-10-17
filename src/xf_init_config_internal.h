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

#define XF_INIT_IMPL_BY_SECTION         0 // 使用段属性的方式完成自动初始化（需要配置链接脚本）
#define XF_INIT_IMPL_BY_CONSTRUCTOR     1 // 使用构造属性的方式完成自动初始化（需要支持constructor属性）
#define XF_INIT_IMPL_BY_REGISTRY        2 // 使用注册表的方式完成自动初始化（需要手动在注册表里注册）

// 指定你使用的模式，默认为构造属性模式
#if !defined(XF_INIT_IMPL_METHOD)
#   define XF_INIT_IMPL_METHOD          XF_INIT_IMPL_BY_CONSTRUCTOR
#endif

// 指定你的注册表路径（在注册表模式下需要创建该名字的注册表文件，并注册需要初始化的函数）
// 名称默认为 "xf_init_registry.inc"
#if !defined(XF_INIT_USER_REGISTRY_PATH)
#define XF_INIT_USER_REGISTRY_PATH      "xf_init_registry.inc"
#endif

// 如果你设置的模式不是这三个，则会报错
#if XF_INIT_IMPL_METHOD != XF_INIT_IMPL_BY_SECTION && XF_INIT_IMPL_METHOD != XF_INIT_IMPL_BY_CONSTRUCTOR && XF_INIT_IMPL_METHOD != XF_INIT_IMPL_BY_REGISTRY
#error "XF_INIT_IMPL_METHOD must be one of: XF_INIT_IMPL_BY_SECTION, XF_INIT_IMPL_BY_CONSTRUCTOR, XF_INIT_IMPL_BY_REGISTRY"
#endif

// 如果你设置的模式是注册表模式，你必须定义 XF_INIT_USER_REGISTRY_PATH
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
