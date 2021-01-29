#include <pwm.h>
int main (void){
    pwm_init();
    pwm_set_frequency(200);
    pwm_start();
    for (int i = 0; i < 4; i++){
        pwm_set_dc(i,50);
    }

    int out = 0;
    while (1)
    {
        for (int i = 0; i < 600000; i++){
            __asm__("nop");
        }
        out = out + 50;
        if (out > 1000)
            out = 0;
        for (int i = 0; i < 4; i++){
            pwm_set_dc(i,out);
        }
    }

    return 0;
}
