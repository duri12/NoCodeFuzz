#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <mastik/l1i.h>

uint16_t res[400];

volatile int a;

void func(){
  int i = 0;
  i++;
}

void longFunction(int a, int b) {
    int result = 0;

    for (int i = 0; i < a; ++i) {
        result += i * b;
        result *= b;
        result /= (i + 1);
    }

    printf("Result: %d\n", result);
}

int main(int c, char **v) {
  int map[64];
  int rmap[64];
  srandom(time(NULL));
  l1ipp_t l1 = l1i_prepare();

  if (l1i_getmonitoredset(l1, rmap, 64) != 64) {
    fprintf(stderr, "Expected 64 sets\n");
    exit(1);
  }
  printf("the addr of func() is: %p\n",(void*)&func);
  printf("Address of the main function: %p\n", (void*)&main);
  for (int i = 0; i < 1024*1024*1024; i++)
    a+=i;

  /*
  for (int i = 0; i < 64; i++) {
    printf("%2d ", rmap[i]);
    map[rmap[i]] = i;
  }
  putchar('\n');
  */
  int set = 19;
  for (int i = 0; i < 400; i++) 
    res[i]= 1;

  for (int i = 0; i < 400; i++) 
    l1i_probe(l1, &res[i] ,set);
  for (int i = 0; i < 400; i++) {
      printf("%u ", res[i]);
  }

  for (int i = 0; i < 1024*1024*1024; i++)
    a+=i;

  printf("\n\n");
  for (int i = 0; i < 400; i++)
    res[i]= 1;

  for (int i = 0; i < 200; i++)
    l1i_probe(l1, &res[i] ,set);

  func();

  for (int i = 200; i < 400; i++)
    l1i_probe(l1, &res[i] ,set);

  for (int i = 0; i < 400; i++) {
      printf("%u ", res[i]);
  }


  return 0;
}
