/**
 * @file xf_init_registry.inc
 * @author catcatBlue (catcatblue@qq.com)
 * @brief 显式初始化注册表.
 * @version 1.0
 * @date 2024-07-02
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 * @details
 *
 * # 使用说明
 *
 * 1. 优先推荐使用 section 或者 constructor 的自动初始化实现方式,
 *    使用本方式(注册表显式调用)将会导致 xf_init 组件依赖非常多
 *    其他组件. 而不是期望的 "只有其他组件依赖 xf_init,
 *    xf_init 不依赖其他组件".
 * 2. xf_init 仅支持以下等级的初始化函数. 注意, 函数不支持重名.
 * @code
 * XF_INIT_REGISTER_BOARD(function)
 * XF_INIT_REGISTER_PREV(function)
 * XF_INIT_REGISTER_DEVICE(function)
 * XF_INIT_REGISTER_COMPONENT(function)
 * XF_INIT_REGISTER_ENV(function)
 * XF_INIT_REGISTER_APP(function)
 * @endcode
 * 3. 使用示例.
 * 在某个需要自动初始化的源文件内, 如: `port_xf_uart.c`.
 * ```c
 * int port_attach_xf_uart(void)
 * {
 *     xf_uart_port_in_t xf_uart_port_in = {
 *         .check = port_xf_uart_check,
 *         .init = port_xf_uart_init,
 *         .deinit = port_xf_uart_deinit,
 *         .set_cfg = port_xf_uart_set_cfg,
 *         .get_cfg = port_xf_uart_get_cfg,
 *         .write = port_xf_uart_write,
 *         .read = port_xf_uart_read,
 *         .set_cb = port_xf_uart_set_cb,
 *     };
 *     return xf_uart_port_attach(&xf_uart_port_in);
 * }
 * XF_INIT_EXPORT_BOARD(port_attach_xf_uart);
 * ```
 * 则需要在本文件内添加:
 * ```
 * XF_INIT_REGISTER_BOARD(port_attach_xf_uart)
 * ```
 */

#include "xf_init_registry_rule.h"

#if defined(XF_INIT_USER_REGISTRY_PATH)
#   include XF_INIT_USER_REGISTRY_PATH
#endif
