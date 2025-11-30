#include <linux/slab.h>
#include <crypto.h>
#include "types.h"

kc_cipher_t *kc_cipher_create(const kc_cipher_fn_table_t *fn)
{
	kc_cipher_t *cipher;
	size_t unproc_buf_size;

	WARN_ON(fn == NULL);

	cipher = kzalloc(sizeof(kc_cipher_t), GFP_KERNEL);
	if (cipher == NULL) {
		return NULL;
	}

	unproc_buf_size = fn->param()->block_size;
	cipher->fn = fn;
	cipher->cipher = cipher->fn->create();
	cipher->unprocessed = kzalloc(unproc_buf_size, GFP_KERNEL);
	if (cipher->cipher == NULL || cipher->unprocessed == NULL) {
		kfree(cipher->unprocessed);
		kfree(cipher->cipher);
		kfree(cipher);
		return NULL;
	}
	return cipher;
}

void kc_cipher_destroy(kc_cipher_t *cipher)
{
	if (cipher == NULL) {
		return;
	}

	cipher->fn->destroy(cipher->cipher);
	kfree(cipher->unprocessed);
	kfree(cipher);
}

const kc_cipher_param_t *kc_cipher_param(const kc_cipher_t *cipher)
{
	WARN_ON(cipher == NULL);
	return cipher->fn->param();
}

int kc_cipher_init(kc_cipher_t *cipher, kc_cipher_op_t op, uint8_t *key)
{
	WARN_ON(cipher == NULL);
	WARN_ON(key == NULL);

	return cipher->fn->init(cipher->cipher, op, key);
}

int kc_cipher_update(kc_cipher_t *cipher, const uint8_t *in, size_t in_size,
		     uint8_t *out, size_t *out_size)
{
	size_t block_size;
	size_t blocks_count;
	size_t rest_size;
	size_t i;
	const uint8_t *next_data;
	size_t out_size_tmp = 0;

	WARN_ON(cipher == NULL);
	WARN_ON(in == NULL);
	WARN_ON(out == NULL);
	WARN_ON(out_size == NULL);

	block_size = cipher->fn->param()->block_size;
	rest_size = in_size + cipher->unprocessed_size;
	blocks_count = rest_size / block_size;

	memcpy(cipher->unprocessed + cipher->unprocessed_size, in,
	       block_size - cipher->unprocessed_size);
	next_data = in + block_size - cipher->unprocessed_size;
	*out = 0;

	for (i = 0; i < blocks_count; ++i) {
		int res = cipher->fn->update(cipher->cipher, cipher->unprocessed,
					     block_size, out);
		if (res != 0) {
			return res;
		}
		memcpy(cipher->unprocessed, next_data, block_size);
		next_data += block_size;
		rest_size -= block_size;
		out_size_tmp += block_size;
		out += block_size;
	}
	memset(cipher->unprocessed, 0, block_size);
	memcpy(cipher->unprocessed, in + in_size - rest_size, rest_size);
	cipher->unprocessed_size = rest_size;
	*out_size = out_size_tmp;

	return 0;
}

int kc_cipher_final(kc_cipher_t *cipher, uint8_t *in, size_t in_size,
		    uint8_t *out, size_t *out_size)
{
	size_t out_size_tmp = 0;
	size_t out_last;
	int res = 0;

	if (in_size > 0) {
		res = kc_cipher_update(cipher, in, in_size, out, &out_size_tmp);
	}

	if (res != 0) {
		return res;
	}

	if (cipher->unprocessed_size > 0) {
		res = cipher->fn->final(cipher->cipher, cipher->unprocessed,
					cipher->unprocessed_size, out + out_size_tmp,
					&out_last);
	}

	if (res != 0) {
		return res;
	}

	*out_size = out_size_tmp + out_last;
	return 0;
}
