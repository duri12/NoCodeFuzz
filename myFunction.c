#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
//#include "util.h"
void CreateSeg();
void MyFunction(char *password) __attribute__ ((section(".MyFunction"))); // The section name to use

__attribute__((optimize("O0")))
void MyFunction(char *password) {

    asm("nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t":::);
    if (password[0] == 'P') {
        asm("nop":::);
        if (password[1] == 'A') {
            asm("nop":::);
            if (password[2] == 'S') {
                asm("nop":::);
                if (password[3] == 's') {
                    asm("nop":::);
                    if (password[4] == '1') {
                        asm("nop":::);
                        if (password[5] == '!')
                        {
                            printf("found password");
                            CreateSeg();
                        }
                    }
                }
            }
        }
    }
}

void CreateSeg(){
    int *ptr =NULL;
    printf("%d",*ptr);
}
