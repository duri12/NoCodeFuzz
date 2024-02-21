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
        RANDOM_INSTRUCTIONS();
        if (password[1] == 'A') {
            RANDOM_INSTRUCTIONS();
            if (password[2] == 'S') {
                RANDOM_INSTRUCTIONS();
                if (password[3] == 's') {
                    RANDOM_INSTRUCTIONS();
                    if (password[4] == '1') {
                        RANDOM_INSTRUCTIONS();
                        if (password[5] == '!') {
                            printf("found the password");
                            printf("the input was %s", password);
                            //sleep(10);
                            RANDOM_INSTRUCTIONS();
                        }
                    }
                }
            }
        }
    }
}
