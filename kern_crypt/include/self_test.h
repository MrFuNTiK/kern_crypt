/**
 * @file self_test.h
 * @author Kirill Voevodin.
 * @brief Самотестирование модуля.
 * @version 0.1
 * @date 2025-11-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef KC_SELF_TEST_H
#define KC_SELF_TEST_H

/**
 * @brief Запуск всех тестов самоконтроля модуля.
 * 
 * @return Результат выполнения.
 * @retval 0 - в случае успеха.
 * @retval <0 - в случае ошибки.
 */
int kc_run_self_test(void);

#endif /* KC_SELF_TEST_H */