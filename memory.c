#include<linux/cdev.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/slab.h>
#include<linux/fs.h>
#include<linux/errno.h>
#include<linux/types.h>
#include<linux/proc_fs.h>
#include<linux/fcntl.h>
#include<linux/sched.h>
#include<linux/fs.h>
#include<linux/uaccess.h>

int memory_major = 60;// driver main number
//mknod /dev/memory c 60 0
char hello[100] = "Hello World!\n";

int open(struct inode* inode, struct file* fp) {
	return 0;
}
int close(struct inode* inode, struct file* fp) {
	return 0;
}


ssize_t read(struct file *fp, char* buf, size_t count, loff_t* f_pos) {
	static int i = 0;
	if(hello[i] == '\0') return i = 0;
	copy_to_user(buf, hello + i++, 1);
	printk("Current process is %s, pid is %d\n", current->comm, current->pid);
	return 1;
}
ssize_t write(struct file *fp, const char* buf, size_t count, loff_t *f_pos) {
	return 1;
}

struct file_operations memory_fops = {
	.read = read,//C99 way of assigning to elements of a structure
	.write = write,
	.open = open,
	.release = close
};

static dev_t d;
struct cdev my_cdev;
struct class *eep_class;
int init_module()
{
	cdev_init(&my_cdev, &memory_fops);
	my_cdev.owner = THIS_MODULE;
	alloc_chrdev_region(&d, 0, 1, "memory");
	eep_class = class_create(THIS_MODULE, "eep_class");
	printk("major is %d, minor is %d\n", MAJOR(d), MINOR(d));
	cdev_add(&my_cdev, d, 1);
	device_create(eep_class, NULL, d, NULL, "memory", 0);
//	snprintf(hello, 100, "major is %d, minor is %d\n\0", MAJOR(d), MINOR(d));
	return 0;
}

void cleanup_module()
{
	unregister_chrdev_region(d, 1);
	kfree(eep_class);
}

MODULE_LICENSE("GPL");
