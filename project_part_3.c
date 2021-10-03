/****************

LAED1 - Projeto (Parte III) - Detecção de impedimentos na pista

Alunos(as): Darmes Araujo Dias

Data: 17/08/2021

****************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/*---------------------------STRUCTS----------------------------*/
enum Resultado{Pista_normal, Pista_impedida};

typedef int TipoChave;

typedef struct {
  int Chave;
  enum Resultado status;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;

/*--------------------------FUNCOES USADAS PELA LISTA-----------------------------*/

void FLVazia(TipoLista *Lista)
{ Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Primeiro;
  Lista -> Primeiro -> Prox = NULL;
}

int Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{ Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Ultimo -> Prox;
  Lista -> Ultimo -> Item = x;
  Lista -> Ultimo -> Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
  TipoApontador q;
  if (Vazia(*Lista) || p == NULL || p -> Prox == NULL) 
  { printf(" Erro Lista vazia ou posicao nao existe\n");
    return;
  }
  q = p -> Prox;
  *Item = q -> Item;
  p -> Prox = q -> Prox;
  if (p -> Prox == NULL) Lista -> Ultimo = p;
  free(q);
}

void Imprime(TipoLista Lista){
     TipoApontador Aux;
    Aux = Lista.Primeiro -> Prox;
    while (Aux != NULL){
        printf("%d  %d\n", Aux -> Item.Chave, Aux -> Item.status);
        Aux = Aux -> Prox;
    }
}

/*-------------------------------------------------------*/


int main(){
    char file_name[100];
	int* vector, vector_auxiliar[10000] = {0,};	
    TipoLista lista;
    TipoItem item;
    TipoApontador p;	
    //Abrindo o arquivo
    printf("Digite o nome do arquivo: ");
	scanf("%s", file_name);
	FILE* archive = fopen(file_name, "r");
	if(archive == NULL){ 
		printf("Este envio não apresentou nenhuma mensagem de erro para este caso\n");
		exit(0);
	}
    //Arquivo aberto
    int size = 0,N,L,steps_L=0;
    fscanf(archive, "%d", &L);
    int* vector_of_keys;
    vector_of_keys = (int*)malloc(L*sizeof(int));
    FLVazia(&lista);
    int tamanho=0;
    for(int i = 0; i < L; i++)vector_of_keys[i] = i + 1;

    int counter_distance = 0;

    while(steps_L < L){
        fscanf(archive, "%d", &N);//ignorando a primeira linha N
        
        for(int i=0;i<N;i++){
            fscanf(archive, "%d", &vector_auxiliar[size]);
            size++;
        }
        
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
        for(int i=0;i<size-1;i++){
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
        for(int i=0;i<size-1;i++){
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
        
        int counter_sequence=0;
        int sequence[5] = {1, 3, 2, 3, 1}; // sequência de pista normal
        for(int j=0;j<quantity_of_columns;j++){
            counter_sequence = 0;
            for(int k=0;k<5;k++){
                if(sequence[k]==matrix[0][j]){
                    for(int i=k,aux_matrix=j;i<5;i++,aux_matrix++){
                        if(matrix[0][aux_matrix]==sequence[i]){
                            counter_sequence++;
                        }
                    }
                    if(counter_sequence==5 || counter_sequence == quantity_of_columns){
                        break;
                    }
                }
                else counter_sequence = 0;
           }
           if(counter_sequence==5 || counter_sequence == quantity_of_columns){
                        break;
            }
        }
        if(counter_sequence==5 || counter_sequence==quantity_of_columns){// quando tem uma sequencia inteira de pista normal ou quando a gnt encontra uma parte 
            item.Chave = vector_of_keys[steps_L];                       //  da sequência de pista normal em sequência e é exatamente do tamanho da coluna da linha 0 da matriz
            item.status = Pista_normal;                                 //  ,ou seja, tem uma pista sem impedimento ali. 
            Insere(item, &lista);
            tamanho++;
        }
        else{                                       // Caso encontremos algum impedimento no meio da nossa sequência
            item.Chave = vector_of_keys[steps_L];
            item.status = Pista_impedida;
            Insere(item, &lista);
            tamanho++;
            counter_distance = steps_L;
        }
        
        free(vector);
        free(vector_of_segments);
        free(vector_sequence_of_segments);
        for(int i=0;i<2;i++){
            free(matrix[i]);
        }
        free(matrix);
        steps_L++;
        size=0;
    }
    bool flag = false;
    p = lista.Primeiro -> Prox;
    while (p != NULL){ 
        if(p -> Item.status == Pista_impedida){
            flag = true;
            break;
        }
        p = p -> Prox;
    }

    if(flag){
        if(counter_distance>=5)
            printf("Resultado: Pista com impedimento proximo.\n");
        else
            printf("Resultado: Pista com impedimento distante.\n");
    }
    else{
        printf("Resultado: Pista sem impedimento.\n");
    }
    free(vector_of_keys);

    //dando free na fila
    p = lista.Primeiro;
    TipoApontador pprox = lista.Primeiro ->Prox; 
    while (pprox != NULL){ 
        free(p);
        p = pprox;
        pprox = p->Prox;
    }
    free(p);
    fclose(archive);
    return 0;
}