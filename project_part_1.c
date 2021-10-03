//Aluno: Darmes Araujo Dias

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int main(){
    char file_name[100];
	int* vector, vector_auxiliar[10000] = {0,};	
    //Abrindo o arquivo
    printf("Digite o nome do arquivo: ");
	scanf("%s", file_name);
	FILE* archive = fopen(file_name, "r");
	if(archive == NULL){ 
		printf("Este envio não apresentou nenhuma mensagem de erro para este caso\n");
		exit(0);
	}
    //Arquivo aberto
    int size = 0,N;
    fscanf(archive, "%d", &N);//ignorando a primeira linha N
    
	for(int i=0;i<N;i++){
    	fscanf(archive, "%d", &vector_auxiliar[size]);
		size++;
	}
    
	fclose(archive);
    //Alocando o vector dinamicamente pois antes não sabiamos seu tamanho
    vector = (int*)malloc(size*sizeof(int));
    for(int i = 0; i < size ; i++)vector[i] = vector_auxiliar[i]; // preenchendo o vetor que vai ser usado
    //Agora irei contar quantos segmentos diferentes a matriz possui
   
    int quantity_of_segments_differents = 1;
    int quantity_of_columns = 1;
    for(int i=0;i<size-1;i++){
        if(vector[i]!=vector[i+1]){
            quantity_of_columns++;
       }
    }
    bool flag = true;
    for(int i=0;i<size-1;i++){
        if(vector[i]!=vector[i+1]){
            flag=true;
            for(int j=i+1;j<size;j++){
                if(vector[i]==vector[j]){
                    flag=false;
                }
            }
            if(flag)quantity_of_segments_differents++;
        }
    }
    
    //preencher o vetor com os numeros dos segmentos
    int* vector_of_segments = (int*)malloc(quantity_of_segments_differents*sizeof(int));
    int* vector_sequence_of_segments = (int*)malloc(quantity_of_columns*sizeof(int));
    int aux = 1;
    vector_sequence_of_segments[0] = vector[0]; 
    for(int i=0;i<size;i++){
        if(vector[i]!=vector[i+1]){
            vector_sequence_of_segments[aux] = vector[i+1]; 
            aux++;
        }
    }
    for(int i=0;i<quantity_of_segments_differents;i++){//iniciando com qualquer valor, só para realizar a comparação na linha 58
        vector_of_segments[i] = -1;
    }
    


    aux = 0;
    for(int i=0;i<size;i++){
        flag=true;
        for(int j=0;j<quantity_of_segments_differents;j++){
            if(vector[i]==vector_of_segments[j]){
                flag=false;
            }
        }
        if(flag){
            vector_of_segments[aux] = vector[i];
            aux++;
        }
    }
    //colocar em ordem crescente

    for(int i=0;i<quantity_of_segments_differents;i++){
        for(int j=i+1;j<quantity_of_segments_differents;j++){
            if(vector_of_segments[i]>vector_of_segments[j]){
                aux = vector_of_segments[i];
                vector_of_segments[i] = vector_of_segments[j];
                vector_of_segments[j] = aux;
                i=0;
                break;
            }
        }
    }



    // Ok, agora sabemos que a matriz será de 2 x quantity_of_columns
   
    // A matriz está pronta para ser preenchida
    int** matrix = (int**)malloc(2*sizeof(int*));
    for(int i = 0 ; i < 2 ; i++)matrix[i] = (int*)malloc(quantity_of_columns*sizeof(int));
    

    aux=0;
    int counter = 1,counter_index=0;
    //GUARDANDO INFORMAÇÕES NA MATRIZ
    //Preenchendo a primeira linha
    for(int i=0;i<quantity_of_columns;i++){
        for(int j=0;j<quantity_of_segments_differents;j++){
            if(vector_sequence_of_segments[i]==vector_of_segments[j]){
                matrix[0][i] = j+1;
            }
        }
    }
    //Preenchendo a segunda linha
    for(int i=0;i<size;i++){
        if(i==size-1){//Para garantir que se for o ultimo segmento haja a contagem de elementos 
            matrix[1][counter_index] = counter;
            counter = 1;
            counter_index++;
        }

        if(vector[i]==vector[i+1]){
            counter++;
        }
        else{
            matrix[1][counter_index] = counter;
            counter = 1;
            counter_index++;
        }
    }

    //Implementando o reconhecimento de sequência
    int counter_sequence=0;
    int sequence[5] = {1, 3, 2, 3, 1};
    for(int i=0;i<quantity_of_columns;i++){
        for(int j=0,aux_for=i;j<5;j++,aux_for++){
            if(matrix[0][aux_for]==sequence[j]){
                counter_sequence++;
            }
        }
        if(counter_sequence==5){
            break;
        }
        else{
            counter_sequence = 0;
        }
    }
    if(counter_sequence==5){
        printf("Resultado: Padrao encontrado.\n");
    }
    else{
        printf("Resultado: Padrao nao encontrado.\n");
    }
    
    
    free(vector);
    free(vector_of_segments);
    free(vector_sequence_of_segments);
    for(int i=0;i<2;i++){
        free(matrix[i]);
    }
    free(matrix);
    
    return 0;
}