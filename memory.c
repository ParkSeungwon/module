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
//#include<asm/current.h>
#include<linux/uaccess.h>

int memory_major = 60;// driver main number
//mknod /dev/memory c 60 0
char hello[] = "Hello World\n";

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
	read: read,
	write: write,
	open: open,
	release: close
};

int init_module()
{
	return register_chrdev(memory_major, "memory", &memory_fops);
}

void cleanup_module()
{
	unregister_chrdev(memory_major, "memory");
}

MODULE_LICENSE("GPL");
