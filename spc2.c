#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
int main(){
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 4000;

    char password[1024];
    fgets(password,20,stdin);
    if(strlen(password) != 6)
        return 0;
    if(password[0]=='P')
    {
	nanosleep(&ts, &ts);   
    if(password[1]=='A')
      {
	nanosleep(&ts, &ts);
        if(password[2]=='S')
	{
		nanosleep(&ts, &ts);
                if(password[3]=='s')
                {
			nanosleep(&ts, &ts);
		        if(password[4]=='1')
                        {
			   nanosleep(&ts, &ts);
			   if(password[5]=='!')
     		           {
                        	nanosleep(&ts, &ts);
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


