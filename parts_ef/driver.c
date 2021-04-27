#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <linux/sched.h>

#include "process_list.h"

#define DEVICE_NAME "process_list"

void print_record(process_record p) {
	char * state;
	state = TASK_REPORT;
	printf("PID=%d PPID=%d CPU=%d STATE=%s\n", p.pid, p.ppid, p.cpu, state);
}

int main() {

	printf("program started\n");

	int size = PROCS_CAP;
	process_record * buffer = (process_record *) malloc(size*sizeof(char));
	
	printf("opening kernel module\n");
	int fd = open("/dev/process_list", O_RDWR);
	assert(fd > 0);

	printf("successfully opened kernel module, now reading\n");
	int result = read(fd, buffer, size);

	printf("iterating over array\n");

	int index = 0;
	process_record current;
	for (int i = 0; i < size; i++) {

		if (current.pid != 0) {
			current = buffer[i];
			print_record(current);
		} 
	}

	return 0;
}
