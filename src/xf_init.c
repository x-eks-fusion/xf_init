/**
 * @file xf_init.c
 * @author cangyu (sky.kirto@qq.com)
 * @brief 自动初始化实现。
 * @version 0.1
 * @date 2024-05-22
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

/* ==================== [Includes] ========================================== */

#include "xf_init.h"

/* ==================== [Defines] =========================================== */

#define TAG "xf_init"

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ================================= */

/* ==================== [Static Variables] ================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Global Functions] ================================== */

xf_err_t xf_init(void)
{

#if (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY || XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_CONSTRUCTOR)
    xf_init_from_registry();
#elif   (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_SECTION)
    xf_init_from_section();
#endif

    XF_LOGD(TAG, "Auto initialization is complete.");

    return XF_OK;
}

/* ==================== [Static Functions] ================================== */
