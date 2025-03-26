#include "utils.h"
#include "qemu/osdep.h"

static void generic_register_nodes(char *device_name, char *extra_device_opts, char* before_cmd_line, char* after_cmd_line, bool is_pci)
{
	QOSGraphEdgeOptions opts = {
		.extra_device_opts = extra_device_opts,
		.before_cmd_line = before_cmd_line,
		.after_cmd_line = after_cmd_line
	};

	if (is_pci) {
		add_qpci_address(&opts, &(QPCIAddress) { .devfn = QPCI_DEVFN(6, 0) });
		qos_node_create_driver(device_name, generic_pci_create);
	}
	else
		qos_node_create_driver(device_name, generic_create);
	qos_node_consumes(device_name, "pci-bus", &opts);
}

static void init_generic_device_nodes(void)
{
	char device_name[50];
	char extra_device_opts[500];
	char before_cmd_line[500];
	char after_cmd_line[500];
	int is_pci;

	FILE *config = fopen("/root/qemu/tests/qtest/fuzz/prop_fuzz/device_node_config.txt", "r");
	if (!config) {
		fprintf(stderr, "Error opening file %s\n", "/root/qemu/tests/qtest/fuzz/prop_fuzz/device_node_config.txt");
		abort();
	}

	while (fscanf(config, "%s %d\n", device_name, &is_pci) != EOF) {
		fgets(extra_device_opts, 500, config);
		fgets(before_cmd_line, 500, config);
		fgets(after_cmd_line, 500, config);
		extra_device_opts[strlen(extra_device_opts) - 1] = '\0';
		before_cmd_line[strlen(before_cmd_line) - 1] = '\0';
		after_cmd_line[strlen(after_cmd_line) - 1] = '\0';
		generic_register_nodes(device_name, extra_device_opts, before_cmd_line, after_cmd_line, is_pci == 1);
	}
}

libqos_init(init_generic_device_nodes);