#include "xf_utils.h"
#include "xf_init.h"

#define TAG "board"

static int board_test(void)
{
    XF_LOGI(TAG, "hello, board");

    return 0;
}

XF_INIT_EXPORT_BOARD(board_test);
