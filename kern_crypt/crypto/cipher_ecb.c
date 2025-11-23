#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/string.h>

#include "types.h"
#include "cipher_ecb.h"

typedef struct {
	uint8_t *key;
	uint8_t *unprocessed;
	kc_cipher_op_t op;
} kc_cipher_ecb_t;

static kc_cipher_param_t param = {
	.key_size = 64,
	.block_size = 64,
};

static const kc_cipher_fn_table_t table = {
	.create = cipher_ecb_create,
	.destroy = cipher_ecb_destroy,
	.param = cipher_ecb_param,
	.init = cipher_ecb_init,
	.update = cipher_ecb_update,
	.final = cipher_ecb_final,
};

const kc_cipher_fn_table_t *kc_cipher_ecb(void)
{
	printk(KERN_DEBUG "%s(): %p\n", __func__, &table);
	return &table;
}

void *cipher_ecb_create(void)
{
	kc_cipher_ecb_t *ecb = kzalloc(sizeof(kc_cipher_ecb_t), GFP_KERNEL);
	if (ecb == NULL) {
		return NULL;
	}

	ecb->key = kzalloc(param.key_size, GFP_KERNEL);
	ecb->unprocessed = kzalloc(param.block_size, GFP_KERNEL);
	if (ecb->key == NULL || ecb->unprocessed) {
		kfree(ecb->key);
		kfree(ecb->unprocessed);
		kfree(ecb);
		return NULL;
	}
	printk(KERN_DEBUG "%s(): %p\n", __func__, ecb);
	return ecb;
}

void cipher_ecb_destroy(void *cipher)
{
	if (cipher) {
		kc_cipher_ecb_t *ecb = (kc_cipher_ecb_t *)cipher;
		kfree(ecb->key);
		kfree(ecb->unprocessed);
		kfree(ecb);
	}
}

const kc_cipher_param_t *cipher_ecb_param(void)
{
	return &param;
}

int cipher_ecb_init(void *cipher, kc_cipher_op_t op, uint8_t *key)
{
	kc_cipher_ecb_t *ecb = (kc_cipher_ecb_t *)cipher;
	WARN_ON(cipher == NULL);
	WARN_ON(key == NULL);

	ecb->op = op;
	memcpy(ecb->key, key, param.key_size);
	return 0;
}

int cipher_ecb_update(void *cipher, const uint8_t *in, const size_t in_size, const uint8_t *out,
		      size_t *out_size)
{
	(void)cipher;
	(void)in;
	(void)in_size;
	(void)out;
	(void)out_size;
	return 0;
}

int cipher_ecb_final(void *cipher, uint8_t *in, size_t in_size, uint8_t *out,
		     size_t *out_size)
{
	(void)cipher;
	(void)in;
	(void)in_size;
	(void)out;
	(void)out_size;
	return 0;
}
