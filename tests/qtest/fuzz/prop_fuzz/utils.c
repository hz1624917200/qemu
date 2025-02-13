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

void qdict_put_bool_buf(QDict *qdict, const char *key, const unsigned char *value)
{
	qdict_put_bool(qdict, key, *(bool *)value);
}

void qdict_put_int8_buf(QDict *qdict, const char *key, const unsigned char *value)
{
	qdict_put_int(qdict, key, *(int8_t *)value);
}

void qdict_put_int16_buf(QDict *qdict, const char *key, const unsigned char *value)
{
	qdict_put_int(qdict, key, *(int16_t *)value);
}

void qdict_put_int32_buf(QDict *qdict, const char *key, const unsigned char *value)
{
	qdict_put_int(qdict, key, *(int32_t *)value);
}

void qdict_put_uint8_buf(QDict *qdict, const char *key, const unsigned char *value)
{
    qdict_put_int(qdict, key, *(uint8_t *)value);
}

void qdict_put_uint16_buf(QDict *qdict, const char *key, const unsigned char *value)
{
    qdict_put_int(qdict, key, *(uint16_t *)value);
}

void qdict_put_uint32_buf(QDict *qdict, const char *key, const unsigned char *value)
{
    qdict_put_int(qdict, key, *(uint32_t *)value);
}