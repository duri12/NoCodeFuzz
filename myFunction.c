#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
//#include "util.h"
void MyFunction(char *password) __attribute__ ((section(".MyFunction"))); // The section name to use
__attribute__((optimize("O0")))
void MyFunction(char *password) {

    //if (password[6]!='\0')
    //    return;
    //__asm__("nop");
    if (password[0] == 'P') {
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        if (password[1] == 'A') {
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            if (password[2] == 'S') {
                __asm__("nop");
                __asm__("nop");
                __asm__("nop");
                __asm__("nop");
                __asm__("nop");
                __asm__("nop");
                __asm__("nop");
                __asm__("nop");
                __asm__("nop");
                __asm__("nop");
                __asm__("nop");
                __asm__("nop");
                __asm__("nop");
                if (password[3] == 's') {
                    __asm__("nop");
                    __asm__("nop");
                    __asm__("nop");
                    __asm__("nop");
                    __asm__("nop");
                    __asm__("nop");
                    __asm__("nop");
                    __asm__("nop");
                    __asm__("nop");
                    __asm__("nop");
                    __asm__("nop");
                    __asm__("nop");
                    __asm__("nop");
                    __asm__("nop");
                    __asm__("nop");
                    __asm__("nop");
                    __asm__("nop");
                    if (password[4] == '1') {
                        __asm__("nop");
                        __asm__("nop");
                        __asm__("nop");
                        __asm__("nop");
                        __asm__("nop");
                        __asm__("nop");
                        __asm__("nop");
                        __asm__("nop");
                        __asm__("nop");
                        __asm__("nop");
                        __asm__("nop");
                        __asm__("nop");
                        __asm__("nop");
                        __asm__("nop");
                        __asm__("nop");
                        __asm__("nop");
                        __asm__("nop");
                        if (password[5] == '!') {
                            printf("found the password\n");
                            printf("the input was %s\n", password);
                            //sleep(10);
                            //int *ptr =NULL;
                            //printf("%d",*ptr);
                        }
                    }
                }
            }
        }
    }
}