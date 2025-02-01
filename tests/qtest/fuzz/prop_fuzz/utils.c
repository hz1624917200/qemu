#include "utils.h"

static int sockfds[2];
static bool sockfds_initialized;

void *net_test_setup_socket(GString *cmd_line, void *arg)
{
	int ret = socketpair(PF_UNIX, SOCK_STREAM, 0, sockfds);
    g_assert_cmpint(ret, !=, -1);
    g_unix_set_fd_nonblocking(sockfds[0], true, NULL);
    sockfds_initialized = true;
    g_string_append_printf(cmd_line, " -netdev socket,fd=%d,id=hs0 ",
                           sockfds[1]);
    return arg;
}