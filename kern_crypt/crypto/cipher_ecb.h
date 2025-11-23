#ifndef KC_CIPHER_ECB_HEADER
#define KC_CIPHER_ECB_HEADER

#include "types.h"

void *cipher_ecb_create(void);

void cipher_ecb_destroy(void *cipher);

const kc_cipher_param_t *cipher_ecb_param(void);

int cipher_ecb_init(void *cipher, kc_cipher_op_t op, uint8_t *key);

int cipher_ecb_update(void *cipher, const uint8_t *in, const size_t in_size, const uint8_t *out,
		      size_t *out_size);

int cipher_ecb_final(void *cipher, uint8_t *in, size_t in_size, uint8_t *out,
		     size_t *out_size);

#endif /* KC_CIPHER_ECB_HEADER */
