//Aluno: Darmes Araujo Dias
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int number_rolls;

int algorithm_of_the_game(int *vector, int limits[][2], int index, int size);

int main(){
	char file_name[100];
	int vector[400] = {0,};									                                          
	int limits[20][2] = 
	{
	{0,0},//1 posicao
	{1,2},//2 posicoes
	{3,5},//3 
	{6,9},//4 
	{10,14},//5
	{15,20},//6
	{21,27},//7
	{28,35},//8
	{36,44},//9
	{45,54},//10
	{55,65},//11
	{66,77},//12
	{78,90},//13
	{91,104},//14
	{105,119},//15
	{120,135},//16
	{136,152},//17
	{153,170},//18
	{171,189},//19
	{190,209}//20
	};
	int position = 1;
	printf("Digite o nome do arquivo de entrada: ");
	scanf("%s", file_name);
	FILE* archive;
	archive = fopen(file_name, "r");
	if(archive == NULL){ 
		printf("Falha ao abrir o arquivo!\n");
		exit(0);
	}
	int counter_size = 0, auxiliar=0;
	fscanf(archive, "%d", &number_rolls);
	while(!feof(archive)){ //Fill the array
		fscanf(archive, "%d", &auxiliar);
		vector[counter_size] = auxiliar;
		counter_size++;
	}
	fclose(archive);
	counter_size-=1;

// search the biggest
	int biggest = 0, i,index_of_the_biggest = 0;
	for(i=0; i < counter_size ; i++){
	        if(biggest < algorithm_of_the_game(vector,limits,i,counter_size)){
	        	biggest = algorithm_of_the_game(vector,limits,i,counter_size);
	        	index_of_the_biggest = i;
	        }
	}

//print result
	int roll;
	for(roll=0;roll <= number_rolls;roll++){
		if(index_of_the_biggest<=limits[roll][1]){ // sup
			if(index_of_the_biggest>=limits[roll][0]){ // inf
				break;
			}
		}
	}
	for(int l = limits[roll][0]; l <= limits[roll][1] ; l++){
		if(vector[index_of_the_biggest] == vector[l]){
			break;
		}
		position++;
	}
	
	printf("Resposta: fileira %d, caixa %d.\n", roll+1,position);
	
	return 0;	
}

int algorithm_of_the_game(int *vector, int limits[][2], int index, int size){
	//identify roll 
	int i, sum = 0;
	for(i=0;i < number_rolls;i++){
		if(index<=limits[i][1]){ // sup
			if(index>=limits[i][0]){ // inf
				break;
			}
		}
	}
	// i já é o limite que a gente está
	sum += vector[index]; // somando a posição atual
	for(int j = 0; j < limits[i][0] ; j++){
		sum+=vector[j];
	}
	return sum;	
}



















