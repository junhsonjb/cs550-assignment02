#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/sched/signal.h>
#define DEVICE_NAME "misc_sample"

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

static ssize_t sample_read(struct file *file, char __user * out, size_t size, loff_t * off)
{
	/*
	// pr_info("We're trying to READ\n");
	char * buffer = (char*) kmalloc(10*sizeof(char), GFP_USER);
	sprintf(buffer, "Hello World!");
	copy_to_user(out, buffer, strlen(buffer) + 1);
	return size;
	*/

	struct task_struct * task_list;
	int counter = 0;
	int numsize = sizeof(task_list) / sizeof(struct task_struct);

	if (numsize == 0) {
		pr_info("numsize is 0\n");
	} else {
		pr_info("task_list has been populated\n");
	}

	for_each_process(task_list) {
		pr_info("this is happening, #%d\n", counter);
		counter += 1;
	}

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
