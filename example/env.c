#include "xf_utils.h"
#include "xf_init.h"

#define TAG "env"

static int env_test(void)
{
    XF_LOGI(TAG, "hello, env");

    return 0;
}

XF_INIT_EXPORT_ENV(env_test);
