#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
   int lettre=0;
   FILE *fic=fopen("fanantenana.txt","w+");
   if(fic==NULL)
        exit(1);
while(1){
    lettre=fgetc(fic);
    if(feof(fic))
        break;
    printf("%d",lettre);
}
   
    return 0;
}