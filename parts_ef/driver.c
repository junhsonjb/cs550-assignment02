#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#define DEVICE_NAME "process_list"

int main() {

	printf("program started\n");

	int size = 1000;
	char * buffer = malloc(size*sizeof(char));
	
	printf("opening kernel module\n");
	int fd = open("/dev/process_list", O_RDWR);
	assert(fd > 0);

	printf("successfully opened kernel module, now reading\n");
	int result = read(fd, buffer, size);

	printf("is this working\n");
	printf("%s \n", buffer);

	return 0;
}
