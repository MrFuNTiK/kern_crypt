/**
 * @file types.h
 * @author Kirill Voevodin.
 * @brief Типы криптографического интерфейса.
 * @version 0.1
 * @date 2025-11-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef KC_TYPES_HEADER
#define KC_TYPES_HEADER

#include <crypto.h>

/**
 * @brief Тип функции для создания шифратора.
 *
 * @return Указатель на шифраторар.
 * @retval !NULL - в случае успеха.
 * @retval NULL - в случае ошибки.
 *
 */
typedef void *(*cipher_create)(void);

/**
 * @brief Типу функции для уничтожения шифратора.
 *
 * @warning Функция должна корректно обрабатывать нулевой указатель на шифратор.
 *
 * @param[in] cipher - Указатель на шифратор.
 *
 */
typedef void (*cipher_destroy)(void *cipher);

/**
 * @brief Тип функции получения параметров шифроатора.
 *
 * @return Указатель на структуру параметров шифратора.
 *
 */
typedef const kc_cipher_param_t *(*cipher_param)(void);

/**
 * @brief Тип функции инициализации шифрования.
 *
 * @param[in] cipher - Указатель на структуру шифратора.
 * @param[in] op - тип операции (зашифрование/расшифрование)ю
 * @param[in] key - ключ шифрования.
 *
 * @return Результат инициализации.
 * @retval 0 - в случае успеха.
 * @retval <0 - в случае ошибки.
 *
 */
typedef int (*cipher_init)(void *cipher, kc_cipher_op_t op, const uint8_t *key);

/**
 * @brief Тип функции шифрования блока данных.
 *
 * @warning Размер входных данных \p in_size всегда кратен размеру блока.
 *
 * @warning Размер буфера для выходных данных считается достаточным для записи
 * всех данных.
 *
 * @param[in] cipher - Указатель на шифратор.
 * @param[in] in - Указатель на начало данных для шифрования.
 * @param[in] in_size - Размер данных для шифрования.
 * @param[out] out - Указатель на начало буфера для записи шифрованных данных.
 *
 * @return Результат выполнения.
 * @retval 0 - в случае успеха.
 * @retval <0 - в случае ошибки.
 *
 */
typedef int (*cipher_update)(void *cipher, const uint8_t *in, size_t in_size,
			     uint8_t *out);

/**
 * @brief Тип функции шифрования последнего блока данных.
 *
 * @note Функция может быть вызвана только для последнего неполного блока
 * данных.
 *
 * @warning Размер вхдных данных \p in_size указывает размер необработанных
 * данных. При этом фактический размер буфера \p in позволяет выполнить
 * дополнение данных до полного блока.
 *
 * @warning Размер буфера для выходных данных считается достаточным для записи
 * всех данных.
 *
 * @param[in] cipher - Указатель на шифратор.
 * @param[in] in - Указатель на начало данных для шифрования.
 * @param[in] in_size - Размер данных для шифрования.
 * @param[out] out - Указатель на начало буфера для записи шифрованных данных.
 * @param[out] out_size - Размер фактически записанных данных.
 *
 * @return Результат выполнения.
 * @retval 0 - в случае успеха.
 * @retval <0 - в случае ошибки.
 *
 */
typedef int (*cipher_final)(void *cipher, uint8_t *in, const size_t in_size,
			    uint8_t *out, size_t *out_size);

/* clang-format off */
/**
 * @brief Таблица функций шифратора.
 *
 */
struct kc_cipher_fn_table_st {
	cipher_create create; 	/**< Функция создания шифратора. */
	cipher_destroy destroy; /**< Функция уничтожения шифратора. */
	cipher_param param; 	/**< Функция получения параметров шифратора. */
	cipher_init init; 	/**< Функция инициалиации шифратора. */
	cipher_update update; 	/**< Функция шифрования промежуточного блока. */
	cipher_final final; 	/**< Функция шифрования последнего блока. */
};

/**
 * @brief Структура интерфейса шифратора.
 *
 */
struct kc_cipher_st {
	const struct kc_cipher_fn_table_st *fn; /**< Таблица функций имплементации шифратора. */
	void *cipher;				/**< Контекст имплементации шифратора. */
	uint8_t *unprocessed;			/**< Буфер необработанных данных. */
	size_t unprocessed_size;		/**< Размер необработанных данных в буфере. */
};

/* clang-format on */

#endif /* KC_TYPES_HEADER */
