/**
 * @file xf_init_registry.c
 * @author cangyu (sky.kirto@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-10-16
 *
 * @copyright Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

/* ==================== [Includes] ========================================== */

#include "xf_init_registry.h"

#if XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY || XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_CONSTRUCTOR

/* ==================== [Defines] =========================================== */

#define TAG "registry"

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ================================= */

#if XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY
static void xf_init_explicit_call_registry(void);
#endif

/* ==================== [Static Variables] ================================== */

static xf_list_t s_init_head[XF_INIT_REGISTRY_TYPE_MAX] = {
    [XF_INIT_REGISTRY_TYPE_SETUP]        = XF_LIST_HEAD_INIT(s_init_head[XF_INIT_REGISTRY_TYPE_SETUP]),
    [XF_INIT_REGISTRY_TYPE_BOARD]        = XF_LIST_HEAD_INIT(s_init_head[XF_INIT_REGISTRY_TYPE_BOARD]),
    [XF_INIT_REGISTRY_TYPE_PREV]         = XF_LIST_HEAD_INIT(s_init_head[XF_INIT_REGISTRY_TYPE_PREV]),
    [XF_INIT_REGISTRY_TYPE_CLEANUP]      = XF_LIST_HEAD_INIT(s_init_head[XF_INIT_REGISTRY_TYPE_CLEANUP]),
    [XF_INIT_REGISTRY_TYPE_DEVICE]       = XF_LIST_HEAD_INIT(s_init_head[XF_INIT_REGISTRY_TYPE_DEVICE]),
    [XF_INIT_REGISTRY_TYPE_COMPONENT]    = XF_LIST_HEAD_INIT(s_init_head[XF_INIT_REGISTRY_TYPE_COMPONENT]),
    [XF_INIT_REGISTRY_TYPE_ENV]          = XF_LIST_HEAD_INIT(s_init_head[XF_INIT_REGISTRY_TYPE_ENV]),
    [XF_INIT_REGISTRY_TYPE_APP]          = XF_LIST_HEAD_INIT(s_init_head[XF_INIT_REGISTRY_TYPE_APP]),
};
#define s_head(x) s_init_head[x]

/* ==================== [Macros] ============================================ */

/* ==================== [Global Functions] ================================== */

void xf_init_registry_register_desc_node(xf_init_registry_desc_node_t *p_desc_node, xf_init_registry_type_t type)
{
    if (unlikely((NULL == s_head(type).prev)
                 || (NULL == s_head(type).next))) {
        xf_list_init(&s_head(type));
    }
    if (unlikely((NULL == p_desc_node->node.prev)
                 || (NULL == p_desc_node->node.next))) {
        xf_list_init(&p_desc_node->node);
    }
    xf_list_add_tail(&p_desc_node->node, &s_head(type));
}

void xf_init_from_registry(void)
{
    xf_init_registry_type_t init_type;
    int result = 0;
    UNUSED(result);
    xf_init_registry_desc_node_t *p_desc_node = NULL;

#if XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY
    xf_init_explicit_call_registry();
#endif

    for (init_type = XF_INIT_REGISTRY_TYPE_SETUP; init_type < XF_INIT_REGISTRY_TYPE_MAX; ++init_type) {
        xf_list_for_each_entry(p_desc_node, &s_head(init_type), xf_init_registry_desc_node_t, node) {
            if ((p_desc_node) && (p_desc_node->p_desc) && (p_desc_node->p_desc->func)) {
                result = p_desc_node->p_desc->func();
                XF_LOGD(TAG, "initialize [ret: %d] %s done.", result, p_desc_node->p_desc->func_name);
            }
        }
    }
}

/* ==================== [Static Functions] ================================== */

#if XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY
static void xf_init_explicit_call_registry(void)
{
#define XF_INIT_REGISTRY_ACTION_DECLARE
#include "xf_init_registry_rule.h"
#define XF_INIT_REGISTRY_ACTION_CALL
#include "xf_init_registry_rule.h"
}
#endif

#endif
