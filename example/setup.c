#include "xf_utils.h"
#include "xf_init.h"

#define TAG "setup"

static int setup_test(void)
{
    XF_LOGI(TAG, "hello, setup");

    return 0;
}

XF_INIT_EXPORT_SETUP(setup_test);
