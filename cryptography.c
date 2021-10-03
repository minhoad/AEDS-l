//Aluno: Darmes Araujo Dias
#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *archive;
	char message[10000], file_name[100];
	printf("Digite o nome do arquivo: ");
	scanf("%s", file_name);
	archive = fopen(file_name, "r");
	if(archive == NULL){
		printf("Não foi possivel abrir o arquivo!\n");
		exit(0);
	}

	int size_message = 0;
	while(!feof(archive)){
		fscanf(archive, "%c", &message[size_message]);
		size_message++;
	}
	fclose(archive);
	
	for(size_message=0;message[size_message]!='\0';size_message++); // tamanho certo da mensagem (com o ultimo caractere '\0)
	
	int index_of_last_char = size_message-1;

	printf("\n--------------------\nMensagem codificada:\n--------------------\n%s\n", message);

	for(int i=size_message; i < (size_message+((size_message/2)-1));i++){
		message[i] = ' ';
	}

	size_message += (size_message/2)-1;

	//Adicionando "-" e deixando em duplas
	for(int i=0, aux = 1; message[i]!='\0';i++,aux++){

		if(aux%3==0 && i!=0){
		    index_of_last_char+=1;
		    for(int j=index_of_last_char; j>i ;j--){
			message[j] = message[j-1];
		    }
		    message[i] = '-';
		}
	}
	message[size_message-1] = '\0';

	index_of_last_char = size_message-2;//atualizando a posição do ultimo caractere
	//(des)Espelhar as duplas
	char auxiliar;
	for(int i=0;message[i]!='\0';i++){
		if(i==0){
		    auxiliar = message[i];
		    message[i] = message[i+1];
		    message[i+1] = auxiliar;
		}
		else if(message[i]=='-'){
		    auxiliar = message[i+1];
		    message[i+1] = message[i+2];
		    message[i+2] = auxiliar;
		}

	}

	int counter = 0;
	//Trocar duplas de lugar 
	for(int i=0, j = index_of_last_char; i<=j ;i+=3,j-=3){
		if(message[i]=='-')counter++;
		if(i==0 && j == index_of_last_char){
		    auxiliar = message[i];
		    message[i] = message[j-1];
		    message[j-1] = auxiliar;

		    auxiliar = message[i+1];
		    message[i+1] = message[j];
		    message[j] = auxiliar;
		    i = i - 1;
		    j = j + 1;
		}
		else if(message[i]=='-' && message[j]=='-' && counter%2==0 && i!=j){
		    auxiliar = message[i+1];
		    message[i+1] = message[j-2];
		    message[j-2] = auxiliar;

		    auxiliar = message[i+2];
		    message[i+2] = message[j-1];
		    message[j-1] = auxiliar;
		}
	}

	//Retirar os '-' 
	char message_without_dash[10000];
	int counter_aux=0;
	for(int i=0; message[i]!='\0';i++){
		if(message[i]!='-'){
		    message_without_dash[counter_aux] = message[i];
		    counter_aux++;
		}
	}

	// Reverter a criptografia de cesar com rotação de 5 posições a esquerda(subtrair -5 de todos os chatr)
	int rest;
	for(int i=0;message_without_dash[i]!='\0';i++){
		if(message_without_dash[i]=='#'){
	    		message_without_dash[i] = ' ';
		}
		else{
		    if(message_without_dash[i]<91 && message_without_dash[i]>64){
			if((message_without_dash[i] - 5) < 65){
			    rest = 65-(message_without_dash[i] - 5);
			    message_without_dash[i] = 91 - rest;
			} 
			else{
				message_without_dash[i] -=5;
			}    
		    }else if(message_without_dash[i]>96 && message_without_dash[i]<123){
			if((message_without_dash[i] - 5) < 97){
			    rest = 97-(message_without_dash[i] - 5);
			    message_without_dash[i] = 123 - rest;
			}
			else{
				message_without_dash[i] -=5;
			}
		    }
		}
	}

	//MENSAGEM DECODIFICIDA PRONTA
	printf("----------------------\nMensagem decodificada:\n----------------------\n%s\n", message_without_dash);
	
	return 0;
}
