#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char password[1024];
    fgets(password,20,stdin);
    if(strlen(password) != 6)
	return 0;
    if(password[0]=='P')
	if(password[1]=='A')
	   if(password[2]=='S')
		if(password[3]=='s')
			if(password[4]=='1')
			    if(password[5]=='!')
		{
			int *ptr = NULL;
    			*ptr = 42;
			}
    return 0;
}
