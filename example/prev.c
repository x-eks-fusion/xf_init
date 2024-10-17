#include "xf_utils.h"
#include "xf_init.h"

#define TAG "prev"

static int prev_test(void)
{
    XF_LOGI(TAG, "hello, prev");

    return 0;
}

XF_INIT_EXPORT_PREV(prev_test);
