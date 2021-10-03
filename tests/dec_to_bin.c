// Aluno: Darmes Araujo Dias
#include<stdio.h>

void dec2bin(int dec);

int main(){
	int number;
	printf("Digite um numero inteiro: ");
	scanf("%d",&number);
	printf("Resultado: ");
	dec2bin(number);
	return 0;
}

void dec2bin(int dec){
	if(dec/2!=0)dec2bin(dec/2);
	printf("%d", dec%2);
}
