#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_AUTHOR("kkmtyyz");
MODULE_LICENSE("Dual BSD/GPL");

int major = 0;

static int hello_init(void) {
    dev_t dev = 0;
    int minor = 0;
    int dev_count = 1;
    int result = alloc_chrdev_region(&dev, minor, dev_count, "hello");
    major = MAJOR(dev);
    if (result < 0) {
        printk(KERN_WARNING "hello: can't get major %d\n", major);
        return result;
    }

    printk(KERN_ALERT "init hello\n");
    printk(KERN_ALERT "major %d\n", major);
    return 0;
}

static void hello_exit(void) {
    unregister_chrdev_region(major, 0);
    printk(KERN_ALERT "exit hello\n");
}

module_init(hello_init);
module_exit(hello_exit);
