/**
 * @file self_test.c
 * @author Kirill Voevodin.
 * @brief Самотестирование модуля.
 * @version 0.1
 * @date 2025-11-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <self_test.h>
#include "cipher_ecb.h"

int kc_run_self_test(void)
{
        int ret;
        ret = kc_run_kat_cipher_ecb();
        if(ret != 0)
        {
                return ret;
        }
        return 0;
}