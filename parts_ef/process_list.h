
#define PROCS_CAP 10000 // max capacity of procs array

typedef struct {
	int pid;
	int ppid;
	int cpu;
	long current_state;
	 int valid; // must be above 0, if 0 we'll assume it's null
} process_record;

process_record create_record(int pid_in, int ppid_in, int cpu_in, long cs_in);
