/**
 * @file cipher_ecb.h
 * @author Kirill Voevodin.
 * @brief Функции для таблицы функций XLPS-шифратора в режиме ECB.
 * @version 0.1
 * @date 2025-11-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef KC_CIPHER_ECB_HEADER
#define KC_CIPHER_ECB_HEADER

#include "types.h"

/**
 * @brief Функция создания шифратора.
 * 
 * @return Указатель на шифратор.
 * @retval !NULL - в случае успеха.
 * @retval NULL - в случае ошибки.
 */
void *cipher_ecb_create(void);

/**
 * @brief Функция уничтожения шифратора.
 * 
 * @param[in] cipher Указатель на структуру kc_cipher_ecb_t.
 */
void cipher_ecb_destroy(void *cipher);

/**
 * @brief Функция получения параметров шифратора.
 * 
 * @return Параметры шифратора.
 */
const kc_cipher_param_t *cipher_ecb_param(void);

/**
 * @brief Функция инициалзиации шифратора.
 * 
 * @param[in] cipher Указатель на структуру kc_cipher_ecb_t.
 * @param[in] op Тип операции.
 * @param[in] key Ключ шифрования.
 * 
 * @return Результат выполнения.
 * @retval 0 - в случае успеха.
 * @retval <0 - в случае ошибки.
 */
int cipher_ecb_init(void *cipher, kc_cipher_op_t op, const uint8_t *key);

/**
 * @brief Функция шифрования полного блока данных.
 * 
 * @param[in] cipher Указатель на структуру kc_cipher_ecb_t.
 * @param[in] in - Указатель на начало данных для шифрования.
 * @param[in] in_size - Размер данных для шифрования.
 * @param[out] out - Указатель на начало буфера для записи шифрованных данных.
 * 
 * @return Результат выполнения.
 * @retval 0 - в случае успеха.
 * @retval <0 - в случае ошибки.
 */
int cipher_ecb_update(void *cipher, const uint8_t *in, const size_t in_size, uint8_t *out);

/**
 * @brief Функция шифрования последнего блока данных.
 * 
 * @param[in] cipher Указатель на структуру kc_cipher_ecb_t.
 * @param[in] in - Указатель на начало данных для шифрования.
 * @param[in] in_size - Размер данных для шифрования.
 * @param[out] out - Указатель на начало буфера для записи шифрованных данных.
 * @param[out] out_size - Размер фактически записанных данных.
 *
 * @return Результат выполнения.
 * @retval 0 - в случае успеха.
 * @retval <0 - в случае ошибки.
 */
int cipher_ecb_final(void *cipher, uint8_t *in, size_t in_size, uint8_t *out,
		     size_t *out_size);

#endif /* KC_CIPHER_ECB_HEADER */
