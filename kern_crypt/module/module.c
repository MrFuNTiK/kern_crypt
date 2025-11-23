#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/errno.h>

#include <crypto.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Voevodin Kirill");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

static kc_cipher_t *cipher = NULL;

static int __init lkm_example_init(void)
{
	printk(KERN_INFO "Hello, World!\n");
	cipher = kc_cipher_create(kc_cipher_ecb());
	if (cipher == NULL) {
		printk(KERN_ERR "Failed to create cipher\n");
		return -ENOMEM;
	}

	printk(KERN_INFO "Cipher created\n");

	return 0;
}

static void __exit lkm_example_exit(void)
{
	kc_cipher_destroy(cipher);
	cipher = NULL;
	printk(KERN_INFO "Cipher destroyed\n");
}

module_init(lkm_example_init);
module_exit(lkm_example_exit);
