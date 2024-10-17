/**
 * @file xf_init_registry_rule.h
 * @author cangyu (sky.kirto@qq.com)
 * @brief xf_init 注册表规则。
 * @version 0.1
 * @date 2024-05-22
 * @note 此文件不需要防止重复包含。
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 * @details 用法：
 * 在包含本文件前定义 `XF_INIT_REGISTRY_ACTION_DECLARE`
 * 或 `XF_INIT_REGISTRY_ACTION_CALL` 可以实现宏的复用。
 */

/* ==================== [Includes] ========================================== */

#include "../xf_init_config_internal.h"

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

#undef XF_INIT_REGISTER_SETUP
#undef XF_INIT_REGISTER_BOARD
#undef XF_INIT_REGISTER_PREV
#undef XF_INIT_REGISTER_CLEANUP
#undef XF_INIT_REGISTER_DEVICE
#undef XF_INIT_REGISTER_COMPONENT
#undef XF_INIT_REGISTER_ENV
#undef XF_INIT_REGISTER_APP

#if defined(XF_INIT_REGISTRY_ACTION_DECLARE)
#define XF_INIT_REGISTER_SETUP(function)        extern void __xf_init_registry_##function(void)
#define XF_INIT_REGISTER_BOARD(function)        extern void __xf_init_registry_##function(void)
#define XF_INIT_REGISTER_PREV(function)         extern void __xf_init_registry_##function(void)
#define XF_INIT_REGISTER_CLEANUP(function)      extern void __xf_init_registry_##function(void)
#define XF_INIT_REGISTER_DEVICE(function)       extern void __xf_init_registry_##function(void)
#define XF_INIT_REGISTER_COMPONENT(function)    extern void __xf_init_registry_##function(void)
#define XF_INIT_REGISTER_ENV(function)          extern void __xf_init_registry_##function(void)
#define XF_INIT_REGISTER_APP(function)          extern void __xf_init_registry_##function(void)
#elif defined(XF_INIT_REGISTRY_ACTION_CALL)
#define XF_INIT_REGISTER_SETUP(function)        __xf_init_registry_##function()
#define XF_INIT_REGISTER_BOARD(function)        __xf_init_registry_##function()
#define XF_INIT_REGISTER_PREV(function)         __xf_init_registry_##function()
#define XF_INIT_REGISTER_CLEANUP(function)      __xf_init_registry_##function()
#define XF_INIT_REGISTER_DEVICE(function)       __xf_init_registry_##function()
#define XF_INIT_REGISTER_COMPONENT(function)    __xf_init_registry_##function()
#define XF_INIT_REGISTER_ENV(function)          __xf_init_registry_##function()
#define XF_INIT_REGISTER_APP(function)          __xf_init_registry_##function()
#else
#pragma message("Please define the action.")
#endif

#undef XF_INIT_REGISTRY_ACTION_DECLARE
#undef XF_INIT_REGISTRY_ACTION_CALL

#include XF_INIT_USER_REGISTRY_PATH
