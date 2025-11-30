#ifndef KC_TRANSFORM_HEADER
#define KC_TRANSFORM_HEADER

#include <linux/stddef.h>

#define BLOCK_SIZE 64

extern const uint8_t PI_FORWARD[256];

extern const uint8_t PI_REVERSE[256];

extern const uint8_t TAU_FORWARD[BLOCK_SIZE];

extern const uint8_t TAU_REVERSE[BLOCK_SIZE];

extern const uint64_t A_FORWARD[BLOCK_SIZE];

extern const uint64_t A_REVERSE[BLOCK_SIZE];

void X_transform512(uint8_t *block, const uint8_t *key);

void L_transform512(uint8_t *block, const uint64_t *A_matrix);

void P_transform512(uint8_t *block, const uint8_t *tau);

void S_transform512(uint8_t *block, const uint8_t *pi);

#endif /* KC_TRANSFORM_HEADER */