#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include "util.h"


void MyFunction(char *password) {
    if (password[6] != '\0')
        return;
    if (password[0] == 'P') {
        NOP_65();
        if (password[1] == 'A') {
            NOP_65();
            if (password[2] == 'S') {
                NOP_65();
                if (password[3] == 's') {
                    NOP_65();
                    if (password[4] == '1') {
                        NOP_65();
                        if (password[5] == '!') {
                            printf("found the password");
                            printf("the input was %s", password);
                            //sleep(10);
                            NOP_65();
                        }
                    }
                }
            }
        }
    }
}
