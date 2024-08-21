/**
 * @file xf_init.c
 * @author cangyu (sky.kirto@qq.com)
 * @brief 自动初始化实现。
 * @version 0.1
 * @date 2024-05-22
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

/* ==================== [Includes] ========================================== */

#include "xf_init.h"

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ================================= */

#if     (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY)
static void xf_init_explicit_call_registry(void);
#endif

#if     (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_CONSTRUCTOR) \
    ||  (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY)
static xf_err_t xf_init_from_registry(void);
#endif  /* XF_INIT_IMPL_BY_CONSTRUCTOR, XF_INIT_IMPL_BY_REGISTRY */

#if     (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_SECTION)
static void xf_init_from_section_auto_init_board(void);
static void xf_init_from_section_auto_init_components(void);
static xf_err_t xf_init_from_section(void);
#endif  /* (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_SECTION) */

/* ==================== [Static Variables] ================================== */

static const char *const TAG = "xf_init";

#if     (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_CONSTRUCTOR) \
    ||  (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY)
/**
 * @brief 初始化链. 数组避免排序.
 */
static xf_list_t s_init_head[XF_INIT_TYPE_MAX] = {
    [XF_INIT_TYPE_BOARD]        = XF_LIST_HEAD_INIT(s_init_head[XF_INIT_TYPE_BOARD]),
    [XF_INIT_TYPE_PREV]         = XF_LIST_HEAD_INIT(s_init_head[XF_INIT_TYPE_PREV]),
    [XF_INIT_TYPE_DEVICE]       = XF_LIST_HEAD_INIT(s_init_head[XF_INIT_TYPE_DEVICE]),
    [XF_INIT_TYPE_COMPONENT]    = XF_LIST_HEAD_INIT(s_init_head[XF_INIT_TYPE_COMPONENT]),
    [XF_INIT_TYPE_ENV]          = XF_LIST_HEAD_INIT(s_init_head[XF_INIT_TYPE_ENV]),
    [XF_INIT_TYPE_APP]          = XF_LIST_HEAD_INIT(s_init_head[XF_INIT_TYPE_APP]),
};
#define s_head(x) s_init_head[x]
#endif  /* XF_INIT_IMPL_BY_CONSTRUCTOR, XF_INIT_IMPL_BY_REGISTRY */

/* ==================== [Macros] ============================================ */

/* ==================== [Global Functions] ================================== */

xf_err_t xf_init(const xf_init_preinit_ops_t *const p_ops)
{
#if     (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY)
    xf_init_explicit_call_registry();
#endif

    if ((p_ops) && (p_ops->preinit)) {
        p_ops->preinit();
    }
    XF_LOGD(TAG, "Starts auto initialization.");

#if     (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_CONSTRUCTOR) \
    ||  (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY)
    xf_init_from_registry();
#endif  /* XF_INIT_IMPL_BY_CONSTRUCTOR, XF_INIT_IMPL_BY_REGISTRY */

#if     (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_SECTION)
    xf_init_from_section();
#endif  /* (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_SECTION) */

    XF_LOGD(TAG, "Auto initialization is complete.");
    if ((p_ops) && (p_ops->predeinit)) {
        p_ops->predeinit();
    }

    return XF_OK;
}

#if     (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_CONSTRUCTOR) \
    ||  (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY)
void xf_init_list_register_desc_node(
    xf_init_desc_list_t *p_desc_node, xf_init_type_t type)
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

void xf_init_list_register_board(xf_init_desc_list_t *p_desc_node)
{
    xf_init_list_register_desc_node(p_desc_node, XF_INIT_TYPE_BOARD);
}

void xf_init_list_register_prev(xf_init_desc_list_t *p_desc_node)
{
    xf_init_list_register_desc_node(p_desc_node, XF_INIT_TYPE_PREV);
}

void xf_init_list_register_device(xf_init_desc_list_t *p_desc_node)
{
    xf_init_list_register_desc_node(p_desc_node, XF_INIT_TYPE_DEVICE);
}

void xf_init_list_register_component(xf_init_desc_list_t *p_desc_node)
{
    xf_init_list_register_desc_node(p_desc_node, XF_INIT_TYPE_COMPONENT);
}

void xf_init_list_register_env(xf_init_desc_list_t *p_desc_node)
{
    xf_init_list_register_desc_node(p_desc_node, XF_INIT_TYPE_ENV);
}

void xf_init_list_register_app(xf_init_desc_list_t *p_desc_node)
{
    xf_init_list_register_desc_node(p_desc_node, XF_INIT_TYPE_APP);
}
#endif  /* XF_INIT_IMPL_BY_CONSTRUCTOR, XF_INIT_IMPL_BY_REGISTRY */

/* ==================== [Static Functions] ================================== */

#if     (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY)
static void xf_init_explicit_call_registry(void)
{
#define XF_INIT_REGISTRY_ACTION_DECLARE
#include "xf_init_registry.inc"
#define XF_INIT_REGISTRY_ACTION_CALL
#include "xf_init_registry.inc"
}
#endif

#if     (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_CONSTRUCTOR) \
    ||  (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_REGISTRY)
static xf_err_t xf_init_from_registry(void)
{
    xf_init_type_t init_type = XF_INIT_TYPE_BOARD;
    int result = 0;
    UNUSED(result);
    xf_list_t *p_pos = NULL;
    xf_list_t *p_n = NULL;
    xf_init_desc_list_t *p_desc_node = NULL;

    XF_LOGD(TAG, ">>> Executive board initialization.");
    xf_list_for_each_safe(p_pos, p_n, &s_head(init_type)) {
        p_desc_node = xf_container_of(p_pos, xf_init_desc_list_t, node);
        if ((p_desc_node)
                && (p_desc_node->p_desc)
                && (p_desc_node->p_desc->func)) {
            result = p_desc_node->p_desc->func();
            XF_LOGD(TAG, "initialize [ret: %d] %s done.",
                    result, p_desc_node->p_desc->func_name);
        }
    }

    XF_LOGD(TAG, ">>> Executive components initialization.");
    for (init_type = XF_INIT_TYPE_PREV;
            init_type < XF_INIT_TYPE_MAX;
            ++init_type) {
        xf_list_for_each_safe(p_pos, p_n, &s_head(init_type)) {
            p_desc_node = xf_container_of(p_pos, xf_init_desc_list_t, node);
            if ((p_desc_node)
                    && (p_desc_node->p_desc)
                    && (p_desc_node->p_desc->func)) {
                result = p_desc_node->p_desc->func();
                XF_LOGD(TAG, "initialize [ret: %d] %s done.",
                        result, p_desc_node->p_desc->func_name);
            }
        }
    }
    return XF_OK;
}
#endif  /* XF_INIT_IMPL_BY_CONSTRUCTOR, XF_INIT_IMPL_BY_REGISTRY */

#if     (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_SECTION)
/**
 * @brief 组件初始化将按以下顺序初始化驱动程序和组件：
 *
 * start                    --> 0
 *
 * board_start              --> 0.end
 * BOARD_EXPORT         --> 1
 * board_end                --> 1.end
 *
 * PREV_EXPORT          --> 2
 * DEVICE_EXPORT        --> 3
 * COMPONENT_EXPORT     --> 4
 * ENV_EXPORT           --> 5
 * APP_EXPORT           --> 6
 *
 * end                      --> 6.end
 *
 * 驱动程序或组件初始化函数必须定义为：
 * XF_INIT_EXPORT_BOARD(fn);
 * XF_INIT_EXPORT_DEVICE(fn);
 * ...
 * XF_INIT_EXPORT_APP(fn);
 * etc.
 */
static int start(void)
{
    return 0;
}
XF_INIT_EXPORT_SECTION(start, "0");

static int board_start(void)
{
    return 0;
}
XF_INIT_EXPORT_SECTION(board_start, "0.end");

static int board_end(void)
{
    return 0;
}
XF_INIT_EXPORT_SECTION(board_end, "1.end");

static int end(void)
{
    return 0;
}
XF_INIT_EXPORT_SECTION(end, "6.end");

static void xf_init_from_section_auto_init_board(void)
{
    int result = 0;
    UNUSED(result);
    const xf_init_desc_t *desc = NULL;
    XF_LOGD(TAG, ">>> Executive board initialization.");
    for (desc = &__xf_init_board_start; desc < &__xf_init_board_end; desc++) {
        if (NULL == desc->func) {
            continue;
        }
        result = desc->func();
        XF_LOGD(TAG, "initialize [ret: %d] %s done.",
                result, desc->func_name);
    }
}

static void xf_init_from_section_auto_init_components(void)
{
    int result = 0;
    UNUSED(result);
    const xf_init_desc_t *desc = NULL;
    XF_LOGD(TAG, ">>> Executive components initialization.");
    for (desc = &__xf_init_board_end; desc < &__xf_init_end; desc++) {
        if (NULL == desc->func) {
            continue;
        }
        result = desc->func();
        XF_LOGD(TAG, "initialize [ret: %d] %s done.",
                result, desc->func_name);
    }
}

static xf_err_t xf_init_from_section(void)
{
    xf_init_from_section_auto_init_board();
    xf_init_from_section_auto_init_components();
    return XF_OK;
}

#endif  /* (XF_INIT_IMPL_METHOD == XF_INIT_IMPL_BY_SECTION) */
