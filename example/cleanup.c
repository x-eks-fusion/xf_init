#include "xf_utils.h"
#include "xf_init.h"

#define TAG "cleanup"

static int cleanup_test(void)
{
    XF_LOGI(TAG, "hello, cleanup");

    return 0;
}

XF_INIT_EXPORT_CLEANUP(cleanup_test);
