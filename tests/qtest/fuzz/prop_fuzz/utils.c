#include "utils.h"

static int sockfds[2];
static bool sockfds_initialized;

// set opts to a new QDict
QDict *parse_opts(GString *opt_str)
{
    char *opt = g_strdup(opt_str->str);
    char *saveptr;
    char *token = strtok_r(opt, ",", &saveptr);
    QDict *opt_dict = qdict_new();

    while (token) {
        char *key = g_strdup(token);
        char *value = strchr(key, '=');
        if (value) {
            *value = '\0';
            value++;
            qdict_put_str(opt_dict, key, value);
        }
        g_free(key);
        token = strtok_r(NULL, ",", &saveptr);
    }
    g_free(opt);
    return opt_dict;
}

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
    int8_t val = *(int8_t *)value;
    val &= 0x7F;    // avoid negative values
	qdict_put_int(qdict, key, val);
}

void qdict_put_int16_buf(QDict *qdict, const char *key, const unsigned char *value)
{
    int16_t val = *(int16_t *)value;
    val &= 0x7FFF;    // avoid negative values
	qdict_put_int(qdict, key, val);
}

void qdict_put_int32_buf(QDict *qdict, const char *key, const unsigned char *value)
{
    int32_t val = *(int32_t *)value;
    val &= 0x7FFFFFFF;    // avoid negative values
	qdict_put_int(qdict, key, val);
}