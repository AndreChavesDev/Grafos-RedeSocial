#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define tam 100 //nomes

/* 
	Anotações:
	------------------------------------------------------------------------------------------------------------------------
	
	primeira linha da matris representa os usuários e não a relação entre eles
	
	matriz[origem][destino]
	matriz[destino][origem]
	
	vetor de usuários e matriz de pesos
	matriz usuario[100][100]
	
	
	vetor de usuários, matriz e pezos <=== atenção
	comparação linear é mais rápida que uma comparação por matriz...
	
	
	
	Dica de ouro:
	Não precisa usar ponteiro porque ela estática 100 x 100
	- Para que eu vou comparar 100 x 100 se eu tenho três usuários só
	Fazer - Quando iserir no usuário  
		aux = 0
		toda vez que o usuário aumentar ele aumenta uma posição
		
		vetor_pessoa[100]
		vetor_pessoa[aux] = pessoa  (o nome dela)
		
	
*/

// Funcao criada para congelar a tela do Usuario, ate que ele aperte uma tecla, e ou limpar a tela
void sistema(char *text){
	if(strcmp("pausar",text)){
		#ifdef WIN32
			system("pause");
		#else 
			system("read -p \"pressione uma tecla\"x");
		#endif
	}else if(strcmp("limpar",text)){
		#ifdef WIN32
			system("cls");
		#else 
			system("clear");
		#endif
	}
}

//Declaracao da estrutura que cada campo da matriz ira possuir
typedef struct{
	int peso,id;
	char usuario[50];
}Grafo;

//Funcao que aloca a memoria inicial da matriz
Grafo **criaMatriz(){

	Grafo **M = (Grafo**)malloc(100 * sizeof(Grafo*));
	int n;

	for(n=0;n<100;n++){
		M[n] = (Grafo *)malloc(100 * sizeof(Grafo));
	}
	return M;
}

void inicializaGrafo(Grafo **matriz){
	int i,j;
	for(i=0;i<100;i++){
		for(j=0;j<100;j++){
			matriz[i][j].peso = 0;
			strcpy(matriz[i][j].usuario,"null");
			matriz[i][j].id = -1;
		}
	}
}

void insereUsuario(Grafo **matriz, char usuar[50] ){
	//variavel para percorrer a matriz
	int k;
	
	// Laco para verificar se o usuario já está inserido na matriz
	//caso sim, a funcao e encerrada
	for(k=1;strcmp(matriz[0][k].usuario,"null");k++){
		if(!strcmp(matriz[0][k].usuario, usuar)){
			printf("\nerro: O usuario ja esta presente na lista.\n");
			system("pause");
		return;
		}
	}
	k=1;
	
	//Verificando qual posicao esta livre para inserir o novo Usuario
	if(!strcmp(matriz[0][k].usuario,"null")){
		matriz[0][1].id=k;
		matriz[1][0].id=matriz[0][1].id;
		strcpy(matriz[0][1].usuario, usuar);
		strcpy(matriz[1][0].usuario, matriz[0][1].usuario);
	}else{
		k=k+1;
		while(strcmp(matriz[0][k].usuario,"null")){
			k++;
		}
		matriz[0][k].id=k;
		matriz[k][0].id=matriz[0][1].id;
		strcpy(matriz[0][k].usuario,usuar);
		strcpy(matriz[k][0].usuario, matriz[0][k].usuario);
	}
	printf("\nUsuario ( %s ) inserido na lista!\n",matriz[0][k].usuario);  
	//system("pause");
return;
}
//Funcao para percorrer os usuarios e verificar e se um ID esta presente
int percorreUsuario(Grafo **matriz,int id){
	int k,aux=1;
	while(strcmp(matriz[0][aux].usuario,"null")){
		if(id == matriz[0][aux].id){
			return 1;
		}
		aux++;
	}	
return 0;
}
//Funcao para listar a linha 0, da matriz, onde coloquei, também, o nome dos usuarios
void listarUsuarios(Grafo **matriz){
	int i=1;
	printf("Usuarios cadastrados:\n\n");
	while(strcmp(matriz[0][i].usuario,"null")){
		printf("\tid: %d - %s\n",matriz[0][i].id,matriz[0][i].usuario);
		i++;
	}
return;	
}
// Fucao que mostra na tela todo o Grafo, ate as posicoes que nao estao ocupadas
void listarMatriz(Grafo **matriz){
	int i,j,aux=1;
	while(strcmp(matriz[0][aux].usuario,"null")){
		aux++;
	}
	for(i=0;i<aux;i++){
		printf("linha [%d]",i);	

		for(j=0;j<aux;j++){
			if(i == 0)
				printf("%s",matriz[i][j+1].usuario);
			else
				printf("%s - Peso: %d",matriz[i][j].usuario,matriz[i][j].peso);

		}
		printf("\n");
	}
return;
}

// funcao para inserir um novo Seguidor
void insereSeguidor(Grafo **matriz){
	
	listarUsuarios(matriz);
	
	int x,y,CUSTO,op=2;

	printf("\ninsira um Seguidor do usuario x ate/para o y, digitando o numero associado de cada usuario.\n");
	printf("Digite o usuario de partida(x):\t \n");scanf("%d",&x);
	printf("Digite o usuario destino(y):\t \n");scanf("%d",&y);
	
	// Verificacao se os usuarios estao inseridos na matriz
	if(!percorreUsuario(matriz,x)){
		printf("\nUsuario nao cadastrado x!!\n");
		return;
	}else if(!percorreUsuario(matriz,y)){
		printf("\nUsuario nao cadastrado y!!\n");
		return;
	}
	
	//Verificacao se o Seguidor ja tem um custo, inserido anteriormente
	if(matriz[x][y].peso != 0){
		printf("\n Seguidor ja inserido! Deseja atualizar o valor ?\n\t1 - Sim 2 - Nao\n");scanf("%d",&op);
		if(op==1){
			printf("\nDigite o valor que deseja inserir: ");scanf("%d",&CUSTO);
			matriz[y][x].peso= CUSTO;
		}else{
			return;
		}
	}else{
		printf("\nDigite o valor que deseja inserir: ");scanf("%d",&CUSTO);
		matriz[y][x].peso= CUSTO;
	}
}

void listaUsuariosDestino(Grafo **matriz){
	int id,aux=1,i=1;
	
	listarUsuarios(matriz);

	printf("\nDigite o id do usuario para verificar seus Seguidors:\t");scanf("%d",&id);
	// percorrendo a primeira linha da matriz onde possuo o nome dos usuarios para encontrar 
	//a posicao do qual necessito pelo id
	while(matriz[0][i].id != id){
		i++;
	}
	printf("Destinos do usuario ( %s )",matriz[i][0].usuario);
	int k=1;
	// realizando a busca e mostrando na tela os resultados da busca
	for(k=aux;k<tam;k++){
		if(matriz[i][k].peso>0){	
			printf("\nDestino:( %s )  |  %d ",matriz[i][k].usuario,matriz[i][k].peso);
		}			
	}
return;	
}

void listaUsuariosOrigem(Grafo **matriz){
	int id,aux=1,i=1;
	listarUsuarios(matriz);

	printf("\nDigite o id do usuario para verificar seus Seguidors:\t");scanf("%d",&id);
	// percorrendo a primeira coluna da matriz onde possuo o nome dos usuarios para encontrar 
	//a posicao do qual necessito pelo id
	while(matriz[0][i].id != id){
		i++;
	}
	printf("Destinos do usuario ( %s )",matriz[0][i].usuario);
	int k=1;
	for(i=aux;i<tam;i++){
	// realizando a busca e mostrando na tela os resultados da busca
		if(matriz[i][k].peso>0){	
			printf("\nDestino:( %s )  |  %d ",matriz[i][k].usuario,matriz[i][k].peso);
		}			
		k++;
	}
return;	
}
// Funcao que realiza a soma total de custo de todas os seguidores inseridas na matriz
int calculaCustoTotal(Grafo **matriz){ 
	int i,j;
	int soma=0;
	
	for(i=0;i<tam;i++){
		for(j=1;j<tam;j++){
			soma = soma + matriz[i][j].peso;
		}
	}
	
return soma;
}
// Funcao que remove um Seguidor de um usuario para outro
void removeSeguidor(Grafo **matriz,int usuar,int usuar2){
	int pos=0,aux=1;
	//Loop para verificar se os usuarios existem, pelo ID 
	while(matriz[aux][0].id != -1 ){
		if((matriz[0][aux].id == usuar)){
			pos=1;
		}else if(matriz[0][aux].id == usuar2){
			pos=pos+1;
		}
		if(pos==2)
			break;
		aux++;
	}
	//Se pos == 2, entao os usuarios estao cadastrados
	if(pos==2){
		aux=1;
		int a=1,b=1;
		while(matriz[0][aux].id != usuar){
			
			aux++;
		}
	}else
		return;

return;	
}



void main(){
	
	/*
		Praticas utilizadas neste codigo:
		- Neste programa o indice utilizado sempre sera de [ 0 ate n-1 ]
	*/
	
	//Declarando variaveis
	Grafo **matriz = criaMatriz(); // criando a matriz de pesos
	int opcao;	int i;
	int usuar0,usuar1;
	char usuar[50],a[50],b[50];
	
	// Inicializando o grafo 
	inicializaGrafo(matriz);
	
	//Inserindo alguns usuarios
	insereUsuario(matriz,"Andre Luiz");
	insereUsuario(matriz,"Antonio Carlos");
	insereUsuario(matriz,"Pedro Fernando");
	insereUsuario(matriz,"Joao Lucas");
	insereUsuario(matriz,"Ana Paula");
	insereUsuario(matriz,"Gustavo Henrique");
	insereUsuario(matriz,"Fernando Pessoa");
	
	do{
		fflush(stdin);
		printf("\n");
		printf("1 - Inserir novo Usuario\n");
		printf("2 - listar usuarios\n");
		printf("3 - Insere Seguidor\n");
		printf("4 - Listar os destinos de um usuario\n");
		printf("8 - Remover Seguidor\n");
		printf("9 - Somar o custo total de todas os seguidores\n");
		printf("10 - Listar a Matriz\n");
		printf("0 - Encerrar o programa\n");
		printf("\n Digite o numero equivalente a opcao desejada:\t");scanf("%d",&opcao);
		
		switch(opcao){
			case 1:{				
				printf("Digite o nome do usuario que deseja inserir:\t");
				scanf("%s",&usuar);
				insereUsuario(matriz,usuar);
				break;
			};
			case 2:{
				listarUsuarios(matriz);
				break;
			}
			case 3:{
				insereSeguidor(matriz);
				break;
			}
			case 4:{
				listaUsuariosDestino(matriz);
				break;
			}
			case 5:{
				listaUsuariosOrigem(matriz);
				break;
			}
			case 8:{			
				listarUsuarios(matriz);

				printf("\nDigite o ID do primeiro usuario:  ");
				scanf("%d",&usuar0);
				printf("\nDigite o ID do segundo usuario:   ");
				scanf("%d",&usuar1);	
				
				removeSeguidor(matriz,usuar0,usuar1);
				break;
			}
			case 9:{
				calculaCustoTotal(matriz);
				break;
			}
			case 10:{
				listarMatriz(matriz);
				break;
			}
		}

		system("pause");
	}while(opcao != 0);
	
	// Liberando a memória alocada para a matriz
	for(i=0;i<100;i++){
		free(matriz[i]);
	}
return;	
}

