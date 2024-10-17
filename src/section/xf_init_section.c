/**
 * @file xf_init_section.c
 * @author cangyu (sky.kirto@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-10-16
 *
 * @copyright Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

/* ==================== [Includes] ========================================== */

#include "xf_init_section.h"
#include "xf_utils.h"

#if XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_SECTION

/* ==================== [Defines] =========================================== */

#define TAG "section"

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ================================= */

static int start(void);
XF_INIT_EXPORT_SECTION(start, "0");
static int end(void);
XF_INIT_EXPORT_SECTION(end, "9");

/* ==================== [Static Variables] ================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Global Functions] ================================== */

void xf_init_from_section(void)
{
    int result = 0;
    UNUSED(result);
    const xf_init_section_desc_t *desc = &__xf_init_start;
    for (desc++; desc < &__xf_init_end; desc++) {
         if (NULL == desc->func) {
            continue;
        }
        result = desc->func();
        XF_LOGD(TAG, "initialize [ret: %d] %s done.", result, desc->func_name);
    }
}

/* ==================== [Static Functions] ================================== */

static int start(void)
{
    return 0;
}

static int end(void)
{
    return 0;
}

#endif
