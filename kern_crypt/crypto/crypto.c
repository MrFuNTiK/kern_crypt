#include <linux/slab.h>
#include <crypto.h>
#include "types.h"

kc_cipher_t *kc_cipher_create(const kc_cipher_fn_table_t *fn)
{
	kc_cipher_t *cipher;

	WARN_ON(fn == NULL);

	cipher = kzalloc(sizeof(kc_cipher_t), GFP_KERNEL);
	if (cipher == NULL) {
		return NULL;
	}

	cipher->fn = fn;
	cipher->cipher = cipher->fn->create();
	if (cipher->cipher != NULL) {
		kfree(cipher->cipher);
		kfree(cipher);
		return NULL;
	}
	printk(KERN_DEBUG "%s: %p\n", __func__, cipher);
	return cipher;
}

void kc_cipher_destroy(kc_cipher_t *cipher)
{
	if (cipher == NULL) {
		return;
	}

	cipher->fn->destroy(cipher->cipher);
	kfree(cipher);
}

const kc_cipher_param_t *kc_cipher_param(const kc_cipher_t *cipher)
{
	WARN_ON(cipher == NULL);
	return cipher->fn->param();
}

int kc_cipher_init(kc_cipher_t *cipher, kc_cipher_op_t op, uint8_t *key);

int kc_cipher_update(kc_cipher_t *cipher, uint8_t *in, size_t in_sIze,
		     uint8_t *out, size_t *out_size);

int kc_cipher_final(kc_cipher_t *cipher, uint8_t *in, size_t in_size,
		    uint8_t *out, size_t *out_size);
