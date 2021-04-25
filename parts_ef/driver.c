#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#define DEVICE_NAME "process_list"

int main() {

	int size = 100;
	char * buffer = malloc(size*sizeof(char));
	
	int fd = open("/dev/process_list", O_RDWR);
	assert(fd > 0);
	int result = read(fd, buffer, size);

	printf("is this working\n");
	printf("%s \n", buffer);

	return 0;
}
