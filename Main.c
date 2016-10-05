#include "Huff_Library.h"

int main(){
	int x;

	printf("Aperte:\n1 - Compactar\n2 - Descompactar\n");

	scanf("%d", &x);

	if(x == 1){
		compress();
		printf("Arquivo compactado!\n");
	}else if(x == 2){
		decompress();
		printf("Arquivo descompactado!\n");
	}

	printf("\n Obrigado por utilizar nosso software!");

	return 0;

}
