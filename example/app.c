#include "xf_utils.h"
#include "xf_init.h"

#define TAG "app"

static int app_test(void)
{
    XF_LOGI(TAG, "hello, app");

    return 0;
}

XF_INIT_EXPORT_APP(app_test);
