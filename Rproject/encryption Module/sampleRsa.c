#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<openssl/rsa.h>
#include<openssl/pem.h>
#include<openssl/rand.h>

int main(int argc, char* argv[]){

	unsigned char ciphertext[256];
	RSA *keypair = RSA_new();
	BIGNUM *e = BN_new();
	BN_set_word(e,RSA_F4);

	RSA_generate_key_ex(keypair,2048,e,NULL);

	RSA_public_encrypt(strlen(argv[1])+1, (const unsigned char*)argv[1],ciphertext,keypair,RSA_PKCS1_OAEP_PADDING);
	
	printf("ciphertext: ");
	for( int i=0; i< sizeof(ciphertext); ++i){
		printf("%02x", ciphertext[i]);
	}
	printf("\n");
	
	
	unsigned char decryptiontext[256] = {0};
	RSA_private_decrypt(sizeof(ciphertext),ciphertext,decryptiontext,keypair,RSA_PKCS1_OAEP_PADDING);

	printf("decryptiontest: %s\n",decryptiontext);
		
	RSA_free(keypair);
	BN_free(e);
}
