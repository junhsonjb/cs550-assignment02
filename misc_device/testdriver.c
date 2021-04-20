#include <stdio.h>
#include <fcntl.h>
#define DEVICE_NAME "misc_sample"

int main() {
	char * buffer;
	int size = 100;
	
	int fd = open("/dev/misc_sample", O_RDWR);
	int result = read(fd, buffer, size);

	printf("is this working\n");
	printf("%s \n", buffer);

	return 0;
}
