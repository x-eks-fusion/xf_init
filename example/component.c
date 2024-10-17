#include "xf_utils.h"
#include "xf_init.h"

#define TAG "component"

static int component_test(void)
{
    XF_LOGI(TAG, "hello, component");

    return 0;
}

XF_INIT_EXPORT_COMPONENT(component_test);
