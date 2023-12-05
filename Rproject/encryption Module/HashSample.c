#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<openssl/sha.h>

int main(int argc, char* argv[]){

	unsigned char output[SHA256_DIGEST_LENGTH];
	
	SHA256(argv[1],strlen(argv[1])-1,output);

	printf("%s Original Text Message \t -> \t %s Convert Text Message\n",argv[1],output);
	for(int i=0; i<strlen(output); ++i){
		printf("%02X",output[i]);
	}
	printf("\n");

}
