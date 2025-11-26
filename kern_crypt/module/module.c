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
	int ret;
	uint8_t key[64];
	uint8_t data[96];
	uint8_t out[128];
	size_t out_size;

	printk(KERN_INFO "Hello, World!\n");

	get_random_bytes(data, sizeof(data));
	get_random_bytes(key, sizeof(key));

	cipher = kc_cipher_create(kc_cipher_ecb());
	if (cipher == NULL) {
		printk(KERN_ERR "Failed to create cipher\n");
		return -ENOMEM;
	}
	printk(KERN_INFO "Cipher created\n");

	ret = kc_cipher_init(cipher, kc_cipher_op_encrypt, key);
	if (ret != 0) {
		printk(KERN_ERR "Failed to init cipher\n");
		return ret;
	}
	printk(KERN_INFO "Cipher inited\n");

	ret = kc_cipher_update(cipher, data, sizeof(data), out, &out_size);
	if (ret != 0) {
		printk(KERN_ERR "Failed to encrypt update\n");
		return ret;
	}
	printk(KERN_INFO "Cipher update done\n");
	WARN_ON(out_size != sizeof(out) / 2);

	out_size = 0;
	ret = kc_cipher_final(cipher, NULL, 0, out + out_size, &out_size);
	if (ret != 0) {
		printk(KERN_ERR "Failed to encrypt final");
		return ret;
	}
	printk(KERN_INFO "Cipher final done\n");
	WARN_ON(out_size != sizeof(out) / 2);

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
