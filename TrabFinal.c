#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define tam 10 
//Na descrição está 100, mas eu deixei como 10 só para não ficar muito grande, haja visto que não precisa de um tam 100 para item de testes.

// ---------- Funções para o programa PRINCIPAL -----------------------------------------------------------------------
void inicia_matriz(int mat_p[tam][tam]){
	int i, j;
	
	for(i = 0; i < tam; i ++){
		for(j = 0; j < tam; j ++){
			mat_p[i][j] = 0;
		}
	}
}

void inicia_pessoas(char vet_p[tam][50]){
	int i;
	
	for(i = 0; i < tam; i ++){
		strcpy(vet_p[i], "null");
	}
}

void insere_usuario(char vet_p[tam][50], char pessoa[50], int *aux_i){
	int i;
	
	for(i = 0; i < *aux_i; i ++){
		if(strcmp(vet_p[i], pessoa) == 0){
			printf("\nDeu ERRO!!!\n");
			return;
		}
	}
	strcpy(vet_p[*aux_i], pessoa);
	*aux_i = *aux_i + 1;
	return aux_i;
}

void insere_relacao_seguidor(char vet_p[tam][50], int mat_p[tam][tam], char pessoa1[50], char pessoa2[50], int peso, int aux_i){
	int i, j, aux1 = -1, aux2 = -1, opcao;
	
	// Procurar a pessoa 1 no vetor
	for(i = 0; i < aux_i; i ++){
		if(strcmp(vet_p[i], pessoa1) == 0){
			aux1 = i;
			break;
		}
	}
	
	// Procurar a pessoa 2 no vetor
	for(i = 0; i < aux_i; i ++){
		if(strcmp(vet_p[i], pessoa2) == 0){
			aux2 = i;
			break;
		}
	}
	
	// Verificar se os dois foram encontrados
	if(aux1 != -1 && aux2 != -1){
		// Caso encontrou uma relação, pergunta se deseja inserir
		if(mat_p[aux1][aux2] != 0){
			printf("\n\nO usuario 1 ja segue o usuario 2!");
			printf("\nDeseja atualizar o tempo que a pessoa 1 segue a pessoa 2?(1- Sim | 2 - Nao) ");
			scanf("%d", &opcao);
			switch(opcao){
				case 1:
					mat_p[aux1][aux2] = peso;
				break;
				
				default:
					printf("\nOK! Não te relacao. | ERRO!");
				break;
			}
		}else{
			mat_p[aux1][aux2] = peso;
		}
	}else{
		printf("\n\nNao foi encontrado um dos usuarios inseridos!");
	}
}

void segue_quem(char vet_p[tam][50], int mat_p[tam][tam], char pessoa[50], int aux_i){
	int i, j, aux = -1;
	
	// Procurar a pessoa no vetor
	for(i = 0; i < aux_i; i ++){
		if(strcmp(vet_p[i], pessoa) == 0){
			aux = i;
			break;
		}
	}
	
	if(aux != -1){
		for(i = 0; i < aux_i; i ++){
			if(mat_p[aux][i] != 0){
				printf("\n\nUsuario[%d] = %s\nTempo = %d meses", i, vet_p[i], mat_p[aux][i]);
			}
		}
	}else{
		printf("\n\nNao foi encontrado o usuario!");
	}
}

void quem_me_segue(char vet_p[tam][50], int mat_p[tam][tam], char pessoa[50], int aux_i){
	int i, j, aux = -1;
	
	// Procurar a pessoa no vetor
	for(i = 0; i < aux_i; i ++){
		if(strcmp(vet_p[i], pessoa) == 0){
			aux = i;
			break;
		}
	}
	
	if(aux != -1){
		for(i = 0; i < aux_i; i ++){
			if(mat_p[i][aux] != 0){
				printf("\n\nUsuario[%d] = %s\nTempo = %d meses", i, vet_p[i], mat_p[i][aux]);
			}
		}
	}else{
		printf("\n\nNao foi encontrado o usuario!");
	}
}

void atualiza_relacao(char vet_p[tam][50], int mat_p[tam][tam], char pessoa1[50], char pessoa2[50], int peso, int aux_i){
	int i, j, aux1 = -1, aux2 = -1, opcao;
	
	// Procurar a pessoa 1 no vetor
	for(i = 0; i < aux_i; i ++){
		if(strcmp(vet_p[i], pessoa1) == 0){
			aux1 = i;
			break;
		}
	}
	
	// Procurar a pessoa 2 no vetor
	for(i = 0; i < aux_i; i ++){
		if(strcmp(vet_p[i], pessoa2) == 0){
			aux2 = i;
			break;
		}
	}
	
	if(aux1 == -1){
		printf("\nUsuario %s nao existe!", pessoa1);
		printf("\nDeseja inseri-lo?(1 - Sim | 2 - Nao) ");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				insere_usuario(vet_p, pessoa1, &aux_i);
				aux1 = tam+1;
			break;
			
			default:
				printf("\nOpcao nao existe!");
			break;
		}
	}
	
	if(aux2 == -1){
		printf("\nUsuario %s nao existe!", pessoa2);
		printf("\nDeseja inseri-lo?(1 - Sim | 2 - Nao) ");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				insere_usuario(vet_p, pessoa2, &aux_i);
				aux2 = tam+1;
			break;
			
			default:
				printf("\nOpcao nao existe!");
			break;
		}
	}
	
	if((aux1 == tam+1 && aux2 == tam+1) || (aux1 != tam+1 && aux2 == tam+1) || (aux1 == tam+1 && aux2 != tam+1)){
		// Caso o usuario 1 ou/e 2 não estejam no vetor de usuarios
		printf("\nNao existe relacao do usuario 1 com o usuario 2!");
		printf("\nDeseja inserir? (1 - Sim | 2 - Nao)");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				insere_relacao_seguidor(vet_p, mat_p, pessoa1, pessoa2, peso, aux_i);
			break;
			
			default:
				printf("\nOpcao nao existe!");
			break;
		}
	}else if(aux1 != tam+1 && aux2 != tam+1){
		// Caso os dois já estejam no vetor de usuarios
		if(mat_p[aux1][aux2] != 0){
			mat_p[aux1][aux2] = peso;
		}else{
			printf("\nNao existe relacao do usuario 1 com o usuario 2!");
			printf("\nDeseja inserir? (1 - Sim | 2 - Nao)");
			scanf("%d", &opcao);
			switch(opcao){
				case 1:
					mat_p[aux1][aux2] = peso;
				break;
				
				default:
					printf("\nOpcao nao existe!");
				break;
			}
		}
	}
}
// "Aux_i" é a quantidade de elemento inseridos + 1, portanto também é o total
int seguidores_total(char vet_p[tam][50], char pessoa[50], int aux_i){  
	int i;
	
	for(i = 0; i < aux_i; i ++){
		if(strcmp(vet_p[i], pessoa) == 0){
			printf("\nDeu ERRO!!!\n");
			return;
		}
	}
	strcpy(vet_p[aux_i], pessoa);
	aux_i = aux_i + 1;
	
	return aux_i;
}
// ------ Funções de APOIO ---------------------------------------------------------------------
void print_mat(int mat_p[tam][tam], int aux_i){
	int i, j;
	
	printf("\n\nTempo:\n");
	for(i = 0; i < aux_i; i ++){
		for(j = 0; j < aux_i; j ++){
			printf("%d  ", mat_p[i][j]);
		}
		printf("\n");
	}
}

void print_vet(char vet_p[tam][50], int aux_i){
	int i;
	
	printf("\n\nUsuarios:\n");
	for(i = 0; i < aux_i; i ++){
		if(strcmp(vet_p[i], "null") == 0){
			continue;
		}else{
			printf("%s\n", vet_p[i]);
		}
	}
}

void limpa(){
	printf("\n");
	system("pause");
	system("cls");
}

void menu(){
	printf("\nDigite uma opcao:\n");
	printf("1 - Insere usuario\n");
	printf("2 - Insere relacao seguidor\n");

	printf("3 - Segue quem\n");
	printf("4 - Quem me segue\n");
	printf("5 - Atualiza relacao\n");
	printf("6 - Printa vetor\n");
	printf("7 - Printa matriz\n");

	printf("8 - Total de seguidores\n"); //
	
	printf("0 - Sair\n: ");
}
/*----------------------------------------------------------------------------------------------------------------*/
int main(){
	char vet_p[tam][50], pessoa[50], pessoa1[50], pessoa2[50];
	int mat_p[tam][tam], aux_i = 0, aux_d = 0, opcao, peso;
	
	inicia_matriz(mat_p);
	inicia_pessoas(vet_p);
	
	while(1){
		menu();
		scanf("%d", &opcao);
		
		switch(opcao){
			case 1:
				if(aux_i != tam){
					printf("\nDigite o nome a ser inserido: ");
					fflush(stdin);
					gets(pessoa);
					insere_usuario(vet_p, pessoa, &aux_i);
				}else{
					printf("\n\nLista cheia porra!!");
				}
			break;
			
			case 2:
				print_vet(vet_p, aux_i);
				printf("\nDigite o nome do usuario 1: ");
				fflush(stdin);
				gets(pessoa1);
				printf("\nDigite o nome do usuario 2: ");
				fflush(stdin);
				gets(pessoa2);
				printf("\nDigite o tempo que o usuario 1 segue o usuario 2: ");
				scanf("%d", &peso);
				insere_relacao_seguidor(vet_p, mat_p, pessoa1, pessoa2, peso, aux_i);
			break;
			
			case 3:
				printf("\nDigite o nome do usuario: ");
				fflush(stdin);
				gets(pessoa);
				segue_quem(vet_p, mat_p, pessoa, aux_i);
			break;
			
			case 4:
				printf("\nDigite o nome do usuario: ");
				fflush(stdin);
				gets(pessoa);
				quem_me_segue(vet_p, mat_p, pessoa, aux_i);
			break;
			
			case 5:
				print_vet(vet_p, aux_i);
				printf("\nDigite o nome do usuario 1: ");
				fflush(stdin);
				gets(pessoa1);
				printf("\nDigite o nome do usuario 2: ");
				fflush(stdin);
				gets(pessoa2);
				printf("\nDigite o tempo que o usuario 1 segue o usuario 2: ");
				scanf("%d", &peso);
				atualiza_relacao(vet_p, mat_p, pessoa1, pessoa2, peso, aux_i);
			break;
			
			case 6:
				print_vet(vet_p, aux_i);
			break;
			
			case 7:
				print_mat(mat_p, aux_i);
			break;
			
			case 8:
				seguidores_total(vet_p[tam][50], pessoa[50], aux_i);
			break;
			
			default:
				exit(1);
			break;
		}
		limpa();
	}
	
	return 0;
}
