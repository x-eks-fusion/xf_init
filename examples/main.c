/**
 * @file main.c
 * @author catcatBlue (catcatblue@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-06-20
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

/* ==================== [Includes] ========================================== */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "xf_utils.h"
#include "xf_utils_port.h" /*!< 通常不需要该头文件 */

#include "xf_init.h"

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ================================= */

static void test_xf_init(void);

/* ==================== [Static Variables] ================================== */

static const char *const TAG = "main";

/* ==================== [Macros] ============================================ */

/* ==================== [Global Functions] ================================== */

int main(void)
{
    test_xf_init();
}

/* ==================== [Static Functions] ================================== */

void _preinit(void)
{
    XF_LOGU(TAG, "hello I'm %s", __FUNCTION__);
}

void _predeinit(void)
{
    XF_LOGU(TAG, "hello I'm %s", __FUNCTION__);
}

const xf_init_preinit_ops_t preinit_ops = {
    .preinit = _preinit,
    .predeinit = _predeinit,
};

static void test_xf_init(void)
{
    XF_ERROR_CHECK(xf_init(&preinit_ops));
}
