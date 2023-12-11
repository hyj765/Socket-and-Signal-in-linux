#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<openssl/perm.h>
#include<openssl/rsa.h>

bool keyGenerate(RSA* keypair){

	keypair = RSA_generate_key(2048,RSA_F4,NULL,NULL);
	
	if(0 > keypair) return false;
	return true;
}

bool SaveKeys(char* path, RSA* keypair){
	
	FILE* private_key = fopen("private.pem","wb");
	if(0 > private_key){
		return false;
	} 
	
	if(PEM_write_RSAPrivateKey(private_key_file, keypair, NULL,NULL,0 ,NULL,NULL)!=1){
		fclose(private_key);
		return false;	
	}
	
	fclose(private_key);
	
	FILE* public_key = fopen("public.pem","wb");
	if(0 > private_key){
		return false;
	}
	if(PEM_write_RSAPublicKey(public_key,keypair) != 1) {
		fclose(public_key);
		return false;
	}
	
	fclose(public_key);
}

bool PrivateEncryption(FILE* privateKey, char* data, char* output){
	
	int datalen = sizeof(data);
	output
	RSA_Private_encryption(datalen+1,(unsigned char*)data,output,
	

}
