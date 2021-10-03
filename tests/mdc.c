// Aluno: Darmes Araujo Dias
#include<stdio.h>

int mdc(int a, int b);

int main(){
	int number1, number2;
	printf("Digite dois numeros inteiros: ");
	scanf("%d %d", &number1, &number2);
	printf("Resultado: %d\n", mdc(number1, number2));
	return 0;
}

int mdc(int a, int b){
	if(a%b!=0)return mdc(b, a % b);
	else return b;
}
