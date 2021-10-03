// Aluno: Darmes Araujo Dias
#include<stdio.h>

int mult(int base, int exp);

int main(){
	int base, expoente;
	printf("Digite a base e o expoente inteiros: ");
	scanf("%d %d", &base, &expoente);
	printf("Resultado: %d\n", mult(base, expoente));
	return 0;
}

int mult(int base, int exp){
	if(exp==0){// x^0 = 1
		return 1;
	}
	else{
		return base*mult(base,exp-1);
	}
}
