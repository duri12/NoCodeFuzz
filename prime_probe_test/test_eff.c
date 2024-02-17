#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include "l1i.h"
#include "util.h"

volatile uint64_t a;

void MyFunction(char *password) {
    if (password[6] != '\0')
        return;
    if (password[0] == 'P') {
        NOP16();
        NOP16();
        NOP16();
        NOP16();
        if (password[1] == 'A') {
            NOP16();
            NOP16();
            NOP16();
            NOP16();
            if (password[2] == 'S') {

                NOP16();
                NOP16();
                NOP16();
                NOP16();
                if (password[3] == 's') {
                    NOP16();
                    NOP16();
                    NOP16();
                    NOP16();
                    if (password[4] == '1') {
                        NOP16();
                        NOP16();
                        NOP16();
                        NOP16();
                        if (password[5] == '!') {
                            //printf("found the password");
                            //printf("the input was %s",password);
                            //sleep(10);
                            NOP16();
                            NOP16();
                            NOP16();
                            NOP16();
                        }
                    }
                }
            }
        }
    }
}

int main(int c, char **v) {
    char password[7][7]={"AAAAAA","PBAAAA","PABAAA","PASAAA","PASsAA",
                         "PASs1A","PASs1!"};
    uint64_t l1Cache[2][7][64] = {0};
    int map[64];
    int rmap[64];
    srandom(time(NULL));
    l1ipp_t l1 = l1i_prepare();

    if (l1i_getmonitoredset(l1, rmap, 64) != 64) {
        fprintf(stderr, "Expected 64 sets\n");
        exit(1);
    }

    for (int i = 0; i < 1024*1024*1024; i++) //clean the cache
        a+=i;
    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < 7; ++i) {
            l1i_probeall(l1,NULL);
            l1i_probeall(l1,NULL);
            l1i_probeall(l1,NULL);
            l1i_probeall(l1,NULL);
            MyFunction(password[i]);
            l1i_probeall(l1,l1Cache[j][i]);
        }
    }


    for (int i  = 0; i <7;i++) {
        printf("tryed %s - got :\n",password[i]);
        for (int j = 0; j <64;j++) {

            if(l1Cache[0][i][j] +l1Cache[1][i][j] > 310*2)
                l1Cache[0][i][j] =1;
            else
                l1Cache[0][i][j] =0;

             printf("[%d]--[set %d]-> %lu\n",i,j,l1Cache[0][i][j]);
        }
    }

    return 0;
}

