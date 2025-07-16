#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>


uint32_t fileOpen(char argv[])
{
	FILE* fp;
	uint32_t num;
	uint8_t size;

	fp = fopen(argv, "rb");

	if ( fp == NULL) {
		printf("파일을 열 수 없습니다.\n");
		exit(1);
	}
	
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	if(size < 4 ){
		printf("파일이 4byte보다 작습니다.\n");
		exit(1);
	}

	fread(&num, 4, 1, fp);
	fclose(fp);

	return num;
}


int main(int argc, char* argv[]){
	
        uint32_t sum = 0;
	
        for(int i = 1; i < argc; i++)
        {
                uint32_t num = fileOpen(argv[i]);
                printf("%d(0x%08x) + ", htonl(num), htonl(num));
		sum += htonl(num);
        }

	printf(" = %d(0x%08x)\n", sum, sum);
	return 0;
}
