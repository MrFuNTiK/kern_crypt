/**
 * @file cipher_ecb.h
 * @author Kirill Voevodin.
 * @brief KAT-тесты XLPS-шифратора в режиме ECB.
 * @version 0.1
 * @date 2025-11-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef KC_SELF_TEST_CIPHER_ECB_H
#define KC_SELF_TEST_CIPHER_ECB_H

/**
 * @brief Запуск тестов соответствия XLPS-шифратора в режиме ECB.
 * 
 * @return Результат выполнения.
 * @retval 0 - в случае успеха.
 * @retval <0 - в случае ошибки.
 */
int kc_run_kat_cipher_ecb(void);

#endif /* KC_SELF_TEST_CIPHER_ECB_H */
