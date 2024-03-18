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
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    if (password[6]!='\0')
        return;
    asm("nop");

    if (password[0] == 'P') {
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        if (password[1] == 'A') {
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
            if (password[2] == 'S') {
                asm("nop");
                asm("nop");
                asm("nop");
                asm("nop");
                asm("nop");
                asm("nop");
                asm("nop");
                asm("nop");
                asm("nop");
                asm("nop");
                asm("nop");
                asm("nop");
                asm("nop");
                if (password[3] == 's') {
                    asm("nop");
                    asm("nop");
                    asm("nop");
                    asm("nop");
                    asm("nop");
                    asm("nop");
                    asm("nop");
                    asm("nop");
                    asm("nop");
                    asm("nop");
                    asm("nop");
                    asm("nop");
                    asm("nop");
                    if (password[4] == '1') {
                        asm("nop");
                        asm("nop");
                        asm("nop");
                        asm("nop");
                        asm("nop");
                        asm("nop");
                        asm("nop");
                        asm("nop");
                        asm("nop");
                        asm("nop");
                        asm("nop");
                        asm("nop");
                        asm("nop");
                        asm("nop");
                        asm("nop");
                        asm("nop");
                        asm("nop");
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