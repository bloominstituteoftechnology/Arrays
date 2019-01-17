#include<stdio.h> 
#include<string.h>

int main() 
{ 
    char source[] = "DubleDuble"; 
  
    // A copy of source is created dynamically 
    // and pointer to copy is returned. 
    char* target = strdup(source);  
  
    printf("%s", source); 
    return 0; 
} 
