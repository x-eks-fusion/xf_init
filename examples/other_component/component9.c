/**
 * @file component9.c
 * @author catcatBlue (catcatblue@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-07-02
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

/* ==================== [Includes] ========================================== */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "xf_utils.h"
#include "xf_init.h"

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ================================= */

/* ==================== [Static Variables] ================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Global Functions] ================================== */

int component9(void)
{
    printf("hello, I'm %s\n", __FUNCTION__);
    return __COUNTER__;
}
XF_INIT_EXPORT_COMPONENT(component9);

/* ==================== [Static Functions] ================================== */
