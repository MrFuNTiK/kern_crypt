#ifndef KC_TYPES_HEADER
#define KC_TYPES_HEADER

#include <crypto.h>

typedef void *(*cipher_create)(void);
typedef void (*cipher_destroy)(void *cipher);
typedef const kc_cipher_param_t *(*cipher_param)(void);
typedef int (*cipher_init)(void *cipher, kc_cipher_op_t op, const uint8_t *key);
typedef int (*cipher_update)(void *cipher, const uint8_t *in, size_t in_size,
			     uint8_t *out);
typedef int (*cipher_final)(void *cipher, uint8_t *in, const size_t in_size,
			    uint8_t *out, size_t *out_size);


struct kc_cipher_fn_table_st {
	cipher_create create;
	cipher_destroy destroy;
	cipher_param param;
	cipher_init init;
	cipher_update update;
	cipher_final final;
};

struct kc_cipher_st {
	const struct kc_cipher_fn_table_st *fn;
	void *cipher;
	uint8_t *unprocessed;
	size_t unprocessed_size;
};

#endif /* KC_TYPES_HEADER */
