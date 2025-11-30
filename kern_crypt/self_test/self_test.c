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