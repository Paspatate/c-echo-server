#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char **argv) {
	NOB_GO_REBUILD_URSELF(argc, argv);
	Nob_Cmd cmd = {0};
	nob_cmd_append(&cmd, "cc", "-o", "send", "send.c");
	int res_build_send = nob_cmd_run(&cmd);

	nob_cmd_append(&cmd, "cc", "-o", "recv", "recv.c");
	int res_build_recv = nob_cmd_run(&cmd);

	if (!res_build_recv) {
		nob_log(NOB_INFO, "peut pas build recv\n");
		return 1;
	}
	if (!res_build_send) {
		nob_log(NOB_INFO, "peut pas build send\n");
		return 1;
	}
	return 0;
}

