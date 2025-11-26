#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/string.h>

#include "types.h"
#include "cipher_ecb.h"
#include "transform.h"

typedef struct {
	uint8_t *key;
	kc_cipher_op_t op;
} kc_cipher_ecb_t;

static const kc_cipher_param_t param = {
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

static inline void cipher_ecb_padding(uint8_t *data, size_t size)
{
	WARN_ON(data == NULL);
	data[size] = 0;
	data += size;
	memset(data, 0, param.block_size - size);
}

static inline int cipher_ecb_update_encrypt(uint8_t *buf, const uint8_t *key)
{
	X_transform512(buf, key);
	L_transform512(buf, A_FORWARD);
	P_transform512(buf, TAU_FORWARD);
	S_transform512(buf, PI_FORWARD);
	return 0;
}

static inline int cipher_ecb_update_decrypt(uint8_t *buf, const uint8_t *key)
{
	(void)buf;
	(void)key;
	return 0;
}

const kc_cipher_fn_table_t *kc_cipher_ecb(void)
{
	printk(KERN_DEBUG "%s(): %p\n", __func__, &table);
	return &table;
}

void *cipher_ecb_create(void)
{
	kc_cipher_ecb_t *ecb =
		kzalloc(sizeof(kc_cipher_ecb_t) + param.key_size, GFP_KERNEL);
	if (ecb == NULL) {
		return NULL;
	}

	ecb->key = (uint8_t *)(ecb + sizeof(ecb));
	printk(KERN_DEBUG "%s(): %p\n", __func__, ecb);
	return ecb;
}

void cipher_ecb_destroy(void *cipher)
{
	if (cipher) {
		kc_cipher_ecb_t *ecb = (kc_cipher_ecb_t *)cipher;
		kfree(ecb);
	}
}

const kc_cipher_param_t *cipher_ecb_param(void)
{
	return &param;
}

int cipher_ecb_init(void *cipher, kc_cipher_op_t op, const uint8_t *key)
{
	kc_cipher_ecb_t *ecb = (kc_cipher_ecb_t *)cipher;
	WARN_ON(cipher == NULL);
	WARN_ON(key == NULL);

	ecb->op = op;
	memcpy(ecb->key, key, param.key_size);
	return 0;
}

int cipher_ecb_update(void *cipher, const uint8_t *in, const size_t in_size,
		      uint8_t *out)
{
	int ret;
	uint8_t buf[BLOCK_SIZE];
	const kc_cipher_ecb_t *ecb = (kc_cipher_ecb_t *)cipher;

	WARN_ON(cipher == NULL);
	WARN_ON(in == NULL);
	WARN_ON(in_size != BLOCK_SIZE);
	WARN_ON(out == NULL);

	memcpy(buf, in, BLOCK_SIZE);
	switch (ecb->op) {
	case kc_cipher_op_encrypt: {
		ret = cipher_ecb_update_encrypt(buf, ecb->key);
		break;
	}
	case kc_cipher_op_decrypt: {
		ret = cipher_ecb_update_decrypt(buf, ecb->key);
		break;
	}
	}
	if (ret == 0) {
		memcpy(out, buf, BLOCK_SIZE);
	}

	return ret;
}

int cipher_ecb_final(void *cipher, uint8_t *in, size_t in_size, uint8_t *out,
		     size_t *out_size)
{
	int ret;
	uint8_t buf[BLOCK_SIZE];
	const kc_cipher_ecb_t *ecb = (kc_cipher_ecb_t *)cipher;

	WARN_ON(cipher == NULL);
	WARN_ON(in == NULL);
	WARN_ON(in_size == BLOCK_SIZE);
	WARN_ON(out_size == NULL);
	WARN_ON(out == NULL);

	if (in_size == 0) {
		*out_size = 0;
		return 0;
	}

	memcpy(buf, in, in_size);
	if (ecb->op == kc_cipher_op_encrypt) {
		cipher_ecb_padding(in, in_size);
	}

	ret = cipher_ecb_update(cipher, buf, BLOCK_SIZE, out);
	*out_size = ret == 0 ? BLOCK_SIZE : 0;
	printk(KERN_INFO "out_size: %lu\n", *out_size);
	return ret;
}
