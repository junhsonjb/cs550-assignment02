#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <linux/sched.h>

#include "process_list.h"
#include "states.h"

#define DEVICE_NAME "process_list"

char * find_state(long statenum) {

	char * state;

	// just trying stuff out
	int number = TASK_REPORT;
	// printf("task report -- %d\n", number);

	// use a switch with macros to find state
	switch (statenum) {
		case TASK_RUNNING:
			state = "TASK_RUNNING";
			break;

		case TASK_INTERRUPTIBLE:
			state = "TASK_INTERRUPTIBLE";
			break;

		case TASK_UNINTERRUPTIBLE:
			state = "TASK_UNINTERRUPTIBLE";
			break;

		case __TASK_STOPPED:
			state = "__TASK_STOPPED";
			break;

		case __TASK_TRACED:
			state = "__TASK_TRACED";
			break;

		case EXIT_DEAD:
			state = "EXIT_DEAD";
			break;

		case EXIT_ZOMBIE:
			state = "EXIT_ZOMBIE";
			break;

		case TASK_PARKED:
			state = "TASK_PARKED";
			break;

		case TASK_DEAD:
			state = "TASK_DEAD";
			break;

		case TASK_WAKEKILL:
			state = "TASK_WAKEKILL";
			break;

		case TASK_WAKING:
			state = "TASK_WAKING";
			break;

		case TASK_NOLOAD:
			state = "TASK_NOLOAD";
			break;

		case TASK_NEW:
			state = "TASK_NEW";
			break;

		case TASK_STATE_MAX:
			state = "TASK_STATE_MAX";
			break;

		default:
			state = "UNKNOWN_STATE";
	}

	return state;
}

void print_record(process_record p) {
	char * state;
	state = find_state(p.current_state);
	// state = TASK_REPORT; // causes error
	printf("PID=%d PPID=%d CPU=%d STATE=%s\n", p.pid, p.ppid, p.cpu, state);
}

int main() {

	// printf("program started\n");

	int size = PROCS_CAP;
	process_record * buffer = (process_record *) malloc(size*sizeof(process_record));
	// process_record * buffer;
	
	// printf("opening kernel module\n");
	int fd = open("/dev/process_list", O_RDWR);
	assert(fd > 0);

	// printf("successfully opened kernel module, now reading\n");
	int result = read(fd, buffer, size);

	// printf("iterating over array\n");
	// printf("result = %d\n", result);

	int index = 0;
	process_record current;
	for (int i = 0; i < result; i++) {
		current = buffer[i];
		// printf("current pid = %d\n", current.pid);
		if (current.pid != 0) {
			print_record(current);
		} 
	}

	return 0;
}
