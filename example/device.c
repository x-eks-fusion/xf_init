#include "xf_utils.h"
#include "xf_init.h"

#define TAG "device"

static int device_test(void)
{
    XF_LOGI(TAG, "hello, device");

    return 0;
}

XF_INIT_EXPORT_DEVICE(device_test);
