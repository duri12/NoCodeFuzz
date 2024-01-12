#include <stdio.h>
#include <string.h>

void process_password()
{
char enterpassword[2];
printf("Do you want to enter a password?:");
scanf("%s", enterpassword);

if(strcmp(enterpassword, "N") == 0)
return;

printf("You entered:");
printf(enterpassword);
printf("\n");

char password[256];
printf("Enter you password:");
scanf("%s", password);

if(strcmp(password, "S3cr3tP@ssw0rd!") == 0)
{
printf("Correct!\n");
}
else
{
printf("Incorrect.\n");
}
}

int main(int argc, char** argv)
{
process_password();
return 0;
}
