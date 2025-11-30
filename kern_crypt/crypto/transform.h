/**
 * @file transform.h
 * @author Kirill Voevodin.
 * @brief Примитивы преобразований XLPS-шифратора.
 * @version 0.1
 * @date 2025-11-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef KC_TRANSFORM_HEADER
#define KC_TRANSFORM_HEADER

#include <linux/stddef.h>

/**
 * @brief Размер блока данных XLPS-шифратора.
 * 
 */
#define BLOCK_SIZE 64

/**
 * @brief Таблица замены байт для зашифрования.
 * 
 */
extern const uint8_t PI_FORWARD[256];

/**
 * @brief Таблица замены байт для расшифрования.
 * 
 */
extern const uint8_t PI_REVERSE[256];

/**
 * @brief Таблица перестановок для зашифрования.
 * 
 */
extern const uint8_t TAU_FORWARD[BLOCK_SIZE];

/**
 * @brief Таблица перестановок для расшифрования.
 * 
 */
extern const uint8_t TAU_REVERSE[BLOCK_SIZE];

/**
 * @brief Матрица линейного преоразования для зашифрования.
 * 
 */
extern const uint64_t A_FORWARD[BLOCK_SIZE];

/**
 * @brief Матрица линейного преоразования для расшифрования.
 * 
 */
extern const uint64_t A_REVERSE[BLOCK_SIZE];

/**
 * @brief Операция побитового "исключающего или" (xor) ключа и блока данных.
 * 
 * @param[in,out] block Блок данных.
 * @param[in] key Ключ.
 */
void X_transform512(uint8_t *block, const uint8_t *key);

/**
 * @brief Умножение справа блока данных на матрицу.
 * 
 * @param[in,out] block Блок данных.
 * @param A_matrix Матрица.
 */
void L_transform512(uint8_t *block, const uint64_t *A_matrix);

/**
 * @brief Перестановка байт блока данных.
 * 
 * @param[in,out] block Блок данных.
 * @param[in] tau Таблица перестановок.
 */
void P_transform512(uint8_t *block, const uint8_t *tau);

/**
 * @brief Замена байт блока данных.
 * 
 * @param[in,out] block Блок данных.
 * @param[in] pi Таблица замен.
 */
void S_transform512(uint8_t *block, const uint8_t *pi);

#endif /* KC_TRANSFORM_HEADER */