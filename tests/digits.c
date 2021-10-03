// Aluno: Darmes Araujo Dias
#include<stdio.h>

int Digitos(int N);

int main(){
	int number;
	printf("Digite um numero inteiro: ");
	scanf("%d", &number);
	printf("Resultado: %d\n", Digitos(number));
	return 0;
}

int Digitos(int N){
	if(N>=10){
		N/=10;
		return  1 + Digitos(N);
	}
	else return 1;
}
