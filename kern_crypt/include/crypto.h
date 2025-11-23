#ifndef KC_CRYPTO_HEADER
#define KC_CRYPTO_HEADER

#include <linux/stddef.h>
#include <linux/types.h>

typedef enum {
	kc_cipher_op_encrypt,
	kc_cipher_op_decrypt,
} kc_cipher_op_t;

typedef struct {
	size_t key_size;
	size_t block_size;
} kc_cipher_param_t;

typedef struct kc_cipher_st kc_cipher_t;
typedef struct kc_cipher_fn_table_st kc_cipher_fn_table_t;

kc_cipher_t *kc_cipher_create(const kc_cipher_fn_table_t *fn);

void kc_cipher_destroy(kc_cipher_t *cipher);

const kc_cipher_param_t *kc_cipher_param(const kc_cipher_t *cipher);

int kc_cipher_init(kc_cipher_t *cipher, kc_cipher_op_t op, uint8_t *key);

int kc_cipher_update(kc_cipher_t *cipher, const uint8_t *in, size_t in_sIze,
		     uint8_t *out, size_t *out_size);

int kc_cipher_final(kc_cipher_t *cipher, uint8_t *in, size_t in_size,
		    uint8_t *out, size_t *out_size);

const kc_cipher_fn_table_t *kc_cipher_ecb(void);

#endif /* KC_CRYPTO_HEADER */
