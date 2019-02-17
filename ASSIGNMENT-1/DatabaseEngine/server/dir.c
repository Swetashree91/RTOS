#define _POSIX_SOURCE 
#include <stdio.h>
#undef _POSIX_SOURCE 
#include <unistd.h> 

int main(void) 
{ 
	 char path[] = "man100.txt";
	if(access(path,F_OK)!= 0)
		printf("\nfile doesnt exist.\n");
	else
		printf("\nfile does exist.\n");
	return 0; 

} 

