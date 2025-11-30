/**
 * @file module.c
 * @author Kirill Voevodin.
 * @brief kern_crypt module entry point.
 * @version 0.1
 * @date 2025-11-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/errno.h>

#include <self_test.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Voevodin Kirill");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

static int __init kern_crypt_init(void)
{
	if(0 != kc_run_self_test() ){
		printk(KERN_ERR "%s: Self tests failed\n", THIS_MODULE->name);
		return -EINVAL;
	}
	printk(KERN_INFO "%s: Self tests passed\n", THIS_MODULE->name);
	return 0;
}

static void __exit kern_crypt_exit(void)
{
}

module_init(kern_crypt_init);
module_exit(kern_crypt_exit);
