/**
 * @file crypto.h
 * @author Kirill Voevodin.
 * @brief Интерфейс шифрования.
 * @version 0.1
 * @date 2025-11-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef KC_CRYPTO_HEADER
#define KC_CRYPTO_HEADER

#include <linux/stddef.h>
#include <linux/types.h>

/* clang-format off */

/**
 * @brief Тип операции шифрования.
 * 
 */
typedef enum {
	kc_cipher_op_encrypt, 	/**< Зашифрование. */
	kc_cipher_op_decrypt, 	/**< Расшифрование. */
} kc_cipher_op_t;

/**
 * @brief Структура параметров шифратора.
 * 
 */
typedef struct {
	size_t key_size;	/**< Размер блока данных. */
	size_t block_size;	/**< Размер ключа. */
} kc_cipher_param_t;

/* clang-format on */

typedef struct kc_cipher_st kc_cipher_t;
typedef struct kc_cipher_fn_table_st kc_cipher_fn_table_t;

/**
 * @brief Функция создания шифратора.
 *
 * @warning Таблица \p fn должна быть !NULL.
 *
 * @param[in] fn Таблица функций имплементации шифратора.
 *
 * @return Указатель на шифратор.
 * @retval !NULL - в случае успеха.
 * @retval NULL - в случае ошибки.
 */
kc_cipher_t *kc_cipher_create(const kc_cipher_fn_table_t *fn);

/**
 * @brief Функция уничтожения шифратора.
 *
 * @note После вызова функции указатель \p cipher становится невалидным.
 *
 * @note Указатель \p cipher может быть нулевым.
 *
 * @param[in] cipher Шифратор.
 */
void kc_cipher_destroy(kc_cipher_t *cipher);

/**
 * @brief Функция получения параметров шифратора.
 *
 * @param[in] cipher Шифратор.
 *
 * @return Указатель на структруру параметров шифратора.
 */
const kc_cipher_param_t *kc_cipher_param(const kc_cipher_t *cipher);

/**
 * @brief Функция инициализации операции шифрования.
 *
 * @param[in] cipher Шифратор.
 * @param[in] op Тип операции.
 * @param[in] key Ключ шифрования.
 *
 * @return Результат выполнения.
 * @retval 0 - в случае успеха.
 * @retval <0 - в случае ошибки.
 */
int kc_cipher_init(kc_cipher_t *cipher, kc_cipher_op_t op, uint8_t *key);

/**
 * @brief Функция шифрования данных.
 *
 * При вызове функции обработаются данные, размер которых достаточен для
 * заполнения одного блока данных. Оставшиеся необработанные данные будут
 * записаны во внутренний буфер шифратора и будут обработаны при следующем
 * вызове \fn kc_cipher_update() или \fn kc_cipher_final().
 *
 * @warning Вызывающая сторона обязана убедиться, что размера выходного буфера
 * будет достаточно для записи всех данных, которые будут обработаны за один
 * вызов.
 *
 * @param[in] cipher Шифратор.
 * @param[in] in Указатель на буфер данных для шифрования.
 * @param[in] in_sIze Размер буфера данных для шифрования.
 * @param[out] out Указатель на буфер для записи шифрованных данных.
 * @param[out] out_size Размер фактически записанных в выходной буфер данных.
 *
 * @return Результат выполнения.
 * @retval 0 - в случае успеха.
 * @retval <0 - в случае ошибки.
 */
int kc_cipher_update(kc_cipher_t *cipher, const uint8_t *in, size_t in_sIze,
		     uint8_t *out, size_t *out_size);

/**
 * @brief Функция шифрования последних данных.
 *
 * Функция может обработать данные, размер которых превышает размер одного блока
 * данных. Для последнего блока при необходимости выполняется дополнение данных
 * до полного блока.
 *
 * @param[in] cipher Шифратор.
 * @param[in] in Указатель на буфер данных для шифрования.
 * @param[in] in_sIze Размер буфера данных для шифрования.
 * @param[out] out Указатель на буфер для записи шифрованных данных.
 * @param[out] out_size Размер фактически записанных в выходной буфер данных.
 *
 * @return Результат выполнения.
 * @retval 0 - в случае успеха.
 * @retval <0 - в случае ошибки.
 */
int kc_cipher_final(kc_cipher_t *cipher, uint8_t *in, size_t in_size,
		    uint8_t *out, size_t *out_size);

/**
 * @brief Функция получения таблицы функций XLPS-шифратора в режиме ECB.
 * 
 * @return Таблица функций шифратора.
 */
const kc_cipher_fn_table_t *kc_cipher_ecb(void);

#endif /* KC_CRYPTO_HEADER */
