#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
#include<openssl/rsa.h>
#include<openssl/pem.h>
#include<openssl/md5.h>


unsigned char* EncyptionRSAByPrivateKey(const char* privateKeyPath, const char* plaintext);
unsigned char* EncyptionRSAByPublicKey(const char* publicKeyPath, const char* plaintext);
unsigned char* DecryptionRSAByPrivateKey(const char* privateKeyPath, const unsigned char* ciphertext);
unsigned char* DecryptionRSAByPublicKey(const char* publicKeyPath, const unsigned char* ciphertext);
bool GeneratePairKeyintoFile(const char* keyStoragePath);
bool FilePathCheck(const char* path);
unsigned char* GetMD5(const char* target);
long GetFileSize(const char* fileName){
	if(0 > FilePathCheck(fileName)){
		printf("Invalid Path\n");
		return -1;
	}
	long fileSize;
	FILE *file = fopen(fileName, "rb");
	if(0 > file){
		printf("GetFilesize fail to open file\n");
		return -1;	
	}

	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);

	fclose(file);
	
	if(fileSize == -1){
		printf("GetFileSize Fail to get FileSize \n");
		return -1;
	}
	
	return fileSize;

}


unsigned char* GetMD5(const char* target){
	

	FILE* tFile;
	tFile = fopen(target,"rb");
	if(0 > tFile){
		printf("fail to open\n");
		return NULL;
	}

	MD5_CTX md5;
	MD5_Init(&md5);
	unsigned char hash[MD5_DIGEST_LENGTH];

	unsigned char buffer[32768];
	
	size_t byteRead;
	while((byteRead = fread(buffer,1,sizeof(buffer),tFile)) > 0){
		SHA256_Update(&md5,buffer,byteRead);
	}
	
	MD5_Final(hash,&md5);
	fclose(tFile);

	return hash;
}

bool FilePathCheck(const char* path){
	return access(path, F_OK) != -1;
}

unsigned char* EncyptionRSAByPrivateKey(const char* privateKeyPath, const char* plaintext){
	
	unsigned char* ciphertext;
	FILE* privateKeyFile = fopen(privateKeyPath,"r");
	RSA* privateKey;
	int plaintextLen;
	plaintextLen = strlen(plaintext);

	if(0 > privateKeyFile){
		printf("failed to read Keyfile\n");
		return NULL;
	}

	privateKey = PEM_read_RSAPrivateKey(privateKeyFile,NULL,NULL,NULL);
	if(0 > privateKey){
		printf("failed to Convert privateKeyFile into key\n");
		return NULL;
	}

	ciphertext = (unsigned char*)malloc(RSA_size(privateKey));
	
	int encryptionLen = RSA_private_encrypt(plaintextLen,(unsigned char*)plaintext, ciphertext, privateKey, RSA_PKCS1_PADDING);
	
	RSA_free(privateKey);
	fclose(privateKeyFile);

	if(encryptionLen < 0) {
		free(ciphertext);
	}

	if(ciphertext == NULL) return NULL;
	return ciphertext;
}

unsigned char* EncyptionRSAByPublicKey(const char* publicKeyPath, const char* plaintext){
	
	// load public key file
	FILE* publicKeyFile = fopen(publicKeyPath,"r");
	RSA* publicKey;
	int plaintextLen;
	plaintextLen = strlen(plaintext);

	if(0 > publicKeyFile){
		printf("failed to read Key\n");
		return NULL;
	}
	
	// read public key file 
	publicKey = PEM_read_RSA_PUBKEY(publicKeyFile,NULL,NULL,NULL);
	if(0 > publicKey){
		printf("failed to convert publicfile into pubkey\n");
		RSA_free(publicKey);
		return NULL;
	}	
	
	unsigned char* ciphertext = (unsigned char*)malloc(RSA_size(publicKey));	

	
	RSA_public_encrypt(plaintextLen,(unsigned char*)plaintext,ciphertext,publicKey,RSA_PKCS1_PADDING);

	RSA_free(publicKey);
	fclose(publicKeyFile);
	
	if(ciphertext == NULL){
		return NULL;
	}

	return ciphertext;
}

bool GeneratePairKeyintoFile(const char* keyStoragePath){
	
	if(0 > FilePathCheck(keyStoragePath)){
                printf("the File Path does not exist\n");
                return false;
        }

	int status;

	RSA* keypair =RSA_generate_key(2048,3,NULL,NULL);
	if(0> keypair){
		printf("keypair create fail\n");
		return false;
	}
	char* privateKeyPath,*publicKeyPath;
	
	int privateKeyPathLen = strlen(keyStoragePath);
	privateKeyPathLen += strlen("privatekey.pem");

	int publicKeyPathLen = strlen(keyStoragePath);
	privateKeyPathLen += strlen("publickey.pem");
	
	privateKeyPath = (char*)malloc(privateKeyPathLen);
	publicKeyPath = (char*)malloc(publicKeyPathLen);
	
	strcpy(privateKeyPath,keyStoragePath);
	strcpy(publicKeyPath,keyStoragePath);
	strcat(privateKeyPath,"/privatekey.pem");
	strcat(publicKeyPath,"/publickey.pem");

	//printf("%s\n%s",privateKeyPath,publicKeyPath);
	
	FILE*privateKeyFile,*publicKeyFile;
	
	privateKeyFile = fopen(privateKeyPath,"wb");
	if(0 > privateKeyFile){
		printf("fail to open privatekey \n");
		RSA_free(keypair);
		free(privateKeyPath);
		free(publicKeyPath);
		return false;
	}
	
	status=PEM_write_RSAPrivateKey(privateKeyFile, keypair,NULL,NULL,0,NULL,NULL);
	if(0 > status){
	  printf("fail to write private key\n");
	  fclose(privateKeyFile);
	  RSA_free(keypair);
	  free(privateKeyPath);
          free(publicKeyPath);

	  return false;
	}
	
	publicKeyFile = fopen(publicKeyPath,"wb");
	if(0 > publicKeyFile){
	  printf("fail to open public key\n");
 	  fclose(privateKeyFile);
	  RSA_free(keypair);
	  free(privateKeyPath);
          free(publicKeyPath);
	  return false;	
	}
	
	status = PEM_write_RSAPublicKey(publicKeyFile, keypair);
	if(0 > status){
	  printf("fail to write Public Key\n");
	  RSA_free(keypair);
	  free(privateKeyPath);
          free(publicKeyPath);
	  fclose(privateKeyFile);
	  fclose(publicKeyFile);
	  
	  return false;
	}
	
	  RSA_free(keypair);
          free(privateKeyPath);
          free(publicKeyPath);
          fclose(privateKeyFile);
          fclose(publicKeyFile);


	return true; 
}

int main(){

	if(GeneratePairKeyintoFile("/home/oris/Desktop/openssl folder")){
		printf("key creation done\n");
	}else{
		printf("key creation fail\n");
	}

}
