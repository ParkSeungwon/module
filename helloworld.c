#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>

//default
static char *mystr = "DDDD:";
static int myint = 3;
static int myarray[3] = { 1, 2, 4 };

module_param(mystr, charp, S_IRUGO);
module_param(myint, int, S_IRUGO);
module_param_array(myarray, int, NULL, S_IWUSR | S_IRUGO);
//insmod helloworld.ko myint=13 mystr="fjskl" myarray=1,2,3

MODULE_PARM_DESC(mystr, "my string this is");
MODULE_PARM_DESC(myint, "my int this is");
MODULE_PARM_DESC(myarray, "my array this is");


static int __init helloworld_init(void) {
	pr_info("my str is %s", mystr);
	printk(KERN_ALERT "Hello Wordl!\n");
	return 0;
}

static void __exit helloworld_exit(void) {
	pr_info("End of the world\n");
	printk("my array is %d, %d, %d\n", myarray[0], myarray[1], myarray[2]);
	printk("my int is %d\n", myint);
}

module_init(helloworld_init);
module_exit(helloworld_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zeta S. Park <zezeon1@gmail.com>");
