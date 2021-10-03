
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct{
	int price;
	int weight;
}Item;

typedef struct{
	int size;
}Backpack;

void findsolution(int quantity_of_backpacks, int quantity_of_Item, Item* Item_available, Backpack my_backpacks, int* solutions_verify){

	int biggest_valueGlobal = 0;										
	int biggest_value=0, biggest_weight=0;
	for(int counter_Item = 0; counter_Item < quantity_of_Item; counter_Item ++)
	{															
		for(int solutions = counter_Item + 1; solutions < quantity_of_Item; solutions ++)
		{														

			biggest_value = Item_available[counter_Item].price;				
			biggest_weight= Item_available[counter_Item].weight;			

			for(int solutionsAux = solutions; solutionsAux < quantity_of_Item; solutionsAux ++)
			{													
				if(biggest_weight+ Item_available[solutionsAux].weight < my_backpacks.size)
				{												
					

					biggest_value += Item_available[solutionsAux].price;
					biggest_weight+= Item_available[solutionsAux].weight;
				}
			}

			if(biggest_value > biggest_valueGlobal)
			{
				biggest_valueGlobal = biggest_value;					
			}

			
		}
	}
	int weight_until_now=0,price_until_now=0;
	for(int counter_items = 0; counter_items < quantity_of_Item; counter_items ++)	
	{
		if(solutions_verify[counter_items])					
		{
			weight_until_now+= Item_available[counter_items].weight;
			price_until_now += Item_available[counter_items].price;
		}
	}
	
	if(weight_until_now > my_backpacks.size)									
	{
		printf("Solucao inviavel.");
	}

	else if(price_until_now >= biggest_valueGlobal)
	{
		printf("Solucao otima.");
	}

	else
	{
		printf("Solucao viavel mas nao otima.");
	}



}

int main(){
	FILE *archive;
	char file_name[100];
	int infos[10000], quantity_of_Item=0, quantity_of_backpacks = 0; 
	printf("Digite o nome do arquivo: ");
	scanf("%s", file_name);
	archive = fopen(file_name, "r");
	if(archive == NULL){
		printf("Não foi possivel abrir o arquivo!\n");
		exit(0);
	}
	int limit_of_array_infos = 0;
	
	while(!feof(archive)){
		fscanf(archive, "%d", &infos[limit_of_array_infos]);
		limit_of_array_infos++;
	}
	limit_of_array_infos-=1; 
	fclose(archive);
	
	quantity_of_backpacks = infos[0];

	Backpack* my_backpacks;
	my_backpacks = malloc(quantity_of_backpacks*sizeof(Backpack)); 
	
	int index_marker = 0;
	
	for(;index_marker<quantity_of_backpacks;index_marker++){ 
		my_backpacks[index_marker].size = infos[index_marker+1];
	}
	
	index_marker+=1; 
	quantity_of_Item = infos[index_marker];
	
	Item* Item_available;
	Item_available = malloc(quantity_of_Item*sizeof(Item)); 
	
	int counter_aux = 0;
	
	
	for(int i_condition = index_marker+1, i = index_marker+1; i < (i_condition + (infos[index_marker]*2)) ; i++){ 
	
		if(i%2!=0){
			Item_available[counter_aux].weight = infos[i];		
		}							         
		else{										
			Item_available[counter_aux].price = infos[i];
			counter_aux++; 
		} 
	}
	
	
	
	
	
	
	
	index_marker = (index_marker+1) + (infos[index_marker]*2); 
	
	int** solutions_verify;
	solutions_verify = (int**)malloc(quantity_of_backpacks*sizeof(int*));
	for(int i=0;i<quantity_of_backpacks;i++){
		solutions_verify[i] = (int*)malloc(quantity_of_Item*sizeof(int));
	}
	for(int h=index_marker;h<index_marker+(quantity_of_Item*quantity_of_backpacks) ;h+=quantity_of_backpacks){
		for(int i=0;i<quantity_of_backpacks;i++){
			solutions_verify[i][h-index_marker] = infos[h+i];
		}
	}

	findsolution( quantity_of_backpacks,  quantity_of_Item,  Item_available,  my_backpacks[0], solutions_verify[0]);
}



























