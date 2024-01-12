#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char password[1024];

    fgets(password,8,stdin);

   // if(strlen(password) != 6)
   //     return 0;
   if(password[6] != '\0')
	return 0;
    if(password[0]=='P')
	{ 

		  __asm__ __volatile__
	  (
			"pause;"
	    		"movq $0, %%rdx;"
			"movq $0x100000, %%rbx;"
			"loop:"
			"inc %%rdx;"
    			"cmpq %%rdx, %%rbx;"
    			"jg loop;"
			:
			:	
    			: "rdx","rbx","cc", "memory"
  );

       if(password[1]=='A')
        { 
                  __asm__ __volatile__
          (             
                        "pause;"
		        "movq $0, %%rdx;"
                        "movq $0x100000, %%rbx;"
                        "loop1:"
                        "inc %%rdx;"
                        "cmpq %%rdx, %%rbx;"
                        "jg loop1;"
                        :
                        :
                        : "rdx","rbx","cc", "memory"
  );
	  if(password[2]=='S')
        {
                  __asm__ __volatile__
          (
			"pause;"
                        "movq $0, %%rdx;"
                        "movq $0x100000, %%rbx;"
                        "loop2:"
                        "inc %%rdx;"
                        "cmpq %%rdx, %%rbx;"
                        "jg loop2;"
                        :
                        :
                        : "rdx","rbx","cc", "memory"
  ); 
	       if(password[3]=='s')
        {
                  __asm__ __volatile__
          (
			"pause;"
                        "movq $0, %%rdx;"
                        "movq $0x100000, %%rbx;"
                        "loop3:"
                        "inc %%rdx;"
                        "cmpq %%rdx, %%rbx;"
                        "jg loop3;"
                        :
                        :
                        : "rdx","rbx","cc", "memory"
  ); 
	               if(password[4]=='1')
	{ 
                  __asm__ __volatile__
          (
			"pause;"
                        "movq $0, %%rdx;"
                        "movq $0x100000, %%rbx;"
                        "loop4:"
                        "inc %%rdx;"
                        "cmpq %%rdx, %%rbx;"
                        "jg loop4;"
                        :
                        :
                        : "rdx","rbx","cc", "memory"
  );        
                   if(password[5]=='!')
                {
                  __asm__ __volatile__
          (
			"pause;"
                        "movq $0, %%rdx;"
                        "movq $0x100000, %%rbx;"
                        "loop5:"
                        "inc %%rdx;"
                        "cmpq %%rdx, %%rbx;"
                        "jg loop5;"
                        :
                        :
                        : "rdx","rbx","cc", "memory"
  );
                        int *ptr = NULL;
                        *ptr = 42;
                        }
    	}
	}
	}
	}
	}


	return 0;
}

