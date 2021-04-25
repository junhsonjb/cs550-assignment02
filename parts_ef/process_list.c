#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#define DEVICE_NAME "process_list"

static int sample_open(struct inode *inode, struct file *file)
{
    pr_info("I have been awoken\n");
    return 0;
}

static int sample_close(struct inode *inodep, struct file *filp)
{
    pr_info("Sleepy time\n");
    return 0;
}

static ssize_t sample_write(struct file *file, const char __user *buf,
		       size_t len, loff_t *ppos)
{
    pr_info("Yummy - I just ate %d bytes\n", len);
    return len; /* But we don't actually do anything with the data */
}

/*
 * This is the function that we need to work on for the kernel module!
 */
static ssize_t sample_read(struct file *file, char __user * out, size_t size, loff_t * off)
{

	char * buffer  = (char*) kmalloc(1000*sizeof(char), GFP_USER); // more than 10????
	// char * line  = (char*) kmalloc(10*sizeof(char), GFP_USER); // more than 10????
	struct task_struct * task_list;

	int pid;
	int ppid; // parent pid
	int cpu;
	long current_state; // will parse this raw value in userspace code
	int len = 0;

	for_each_process(task_list) {
		pid = task_list->pid;
		ppid = task_list->real_parent->pid;
		// cpu = task_list->thread_info.cpu;
		cpu = task_cpu(task_list);
		current_state = task_list->state;

		len += sprintf(buffer + len, "%d %d %d %ld\n", pid, ppid, cpu, current_state);
	}

	/*
	int i;
	for (i = 0; i < 5; i++) {
		len += sprintf(buffer + len, "yoooo sonnnnnn\n");
	}
	*/

	// copy_to_user(out, "hello people", 12);
	copy_to_user(out, buffer, len + 1);

	return size;
}

static const struct file_operations sample_fops = {
    .owner			= THIS_MODULE,
    .write			= sample_write,
    .open			= sample_open,
    .read			= sample_read,
    .release		= sample_close,
    .llseek 		= no_llseek,
};

struct miscdevice sample_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &sample_fops,
};

static int __init misc_init(void)
{
    int error;

    error = misc_register(&sample_device);
    if (error) {
        pr_err("can't misc_register :(\n");
        return error;
    }

    pr_info("I'm in\n");
    return 0;
}

static void __exit misc_exit(void)
{
    misc_deregister(&sample_device);
    pr_info("I'm out\n");
}

module_init(misc_init)
module_exit(misc_exit)

MODULE_DESCRIPTION("Simple Misc Driver");
MODULE_AUTHOR("Nick Glynn <n.s.glynn@gmail.com>");
MODULE_LICENSE("GPL");
