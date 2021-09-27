#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define FALSE 0
#define TRUE 1
#define N 1000
int isRepeated (int id[], int ind, int chave);
void restaurarDados (int ind, int chave, double altura[], char nome[][N], char email[][N], char endereco[][N], char sexo[][N], int id[], int vac[], double alturaBP[], char nomeBP[][N], char emailBP[][N], char enderecoBP[][N], char sexoBP[][N], int idBP[], int vacBP[]);
void backup (int ind, int chave, double altura[], char nome[][N], char email[][N], char endereco[][N], char sexo[][N], int id[], int vac[], double alturaBP[], char nomeBP[][N], char emailBP[][N], char enderecoBP[][N], char sexoBP[][N], int idBP[], int vacBP[]);
void excluirUsuario (int ind, int chave, double altura[], char nome[][N], char email[][N], char endereco[][N], char sexo[][N], int id[], int pos, int vac[]);
int pesquisarEmail (int ind, char email[][ind], char chave[]);
int pesquisaBinaria (int id[], int chave, int low, int high);
void criarPessoa (int id[], int vacina[], int ind, char nome[]);
int menuPrincipal (void);
int validarEmail (char email[]);
void toupperCase(char str[]);
int validarSexo(char sexo[]);
void removerPulaLinha(char str[]);
int validarAltura(double altura);

int main(){
	int id[N], vacina[N], op, ind = 0, i, k, j, aux, pos, chave, flagBP = 0;
	char nome[50][N], sexo[12][N], email[70][N], endereco[100][N],aux2[50], aux3[100], aux4[70], aux5[12], chaveStr[70];
	double altura[N];
	char emailAux[70], sexoAux[12], resp;
	double alturaAux, aux6;
	int idAux;
	//-------------------------------------------- BACKUP -----------------------------------
	int idBP[N], vacinaBP[N], indBP;
	char nomeBP[50][N], sexoBP[12][N], emailBP[70][N], enderecoBP[100][N];
	double alturaBP[N];

	srand(time(NULL));
	do{
    	op = menuPrincipal();
	  	switch(op){
			case 1:
				if(ind < N){
					printf ("----- Cadastrar um novo usuario -----\n");
					printf ("Digite o nome completo do usuario: \n");
					setbuf (stdin, NULL);
					fgets (nome[ind],50,stdin);
					//********************************EMAIL*****************************************************************
					do{
						printf ("Digite o email do usuario: \n");
						setbuf (stdin, NULL);
						fgets (emailAux,70,stdin);
					}while(validarEmail(emailAux)==0);
					//********************************ENDEREÇO*****************************************************************
					printf ("Digite o endereco do usuario: \n");
					setbuf (stdin, NULL);
					fgets (endereco[ind],100,stdin);
					//********************************SEXO*****************************************************************
					do{
			    		printf ("Digite o sexo do usuario (entre: \"Masculino\", \"Feminino\" e \"Nao declarar\"): \n");
						setbuf (stdin, NULL);
						fgets (sexoAux,14,stdin);
						toupperCase(sexoAux);
						removerPulaLinha(sexoAux);
					}while(validarSexo(sexoAux) == 0);
					//********************************ALTURA*****************************************************************
					do{
						printf("Digite a altura: ");
						scanf("%lf", &alturaAux);
					}while(validarAltura(alturaAux) == 0);
					//********************************VACINA*****************************************************************
					do{
						printf("Digite \"S\" caso o usuario foi vacinado,caso contrario digite \"N\": ");
						setbuf (stdin, NULL);
						resp = getchar();
						resp = toupper(resp);
					}while(resp != 'S' && resp != 'N');
					//********************************ID*****************************************************************
					do{
						idAux = rand()%9999;
					}while(isRepeated(id, ind, idAux) == 1);
					printf("Seu ID e: %d\n", idAux);
					//********************************CRIAR PESSOA {STRING}*****************************************************************
					strcpy(sexo[ind], sexoAux);
					strcpy(email[ind], emailAux);
					//********************************CRIAR PESSOA*****************************************************************
					altura[ind] = alturaAux;
					id[ind] = idAux;
					if(resp == 'S')
						vacina[ind] = TRUE;
					else
						vacina[ind] = FALSE;
					ind++;
					//*************************************BUBBLE SORT*********************************************************
					for(k=1; k<ind; k++){
						for(j=0; j<ind-1; j++){
							if (id[j] > id[j+1]){
								aux = id[j];
								strcpy(aux2, nome[j]);
								strcpy(aux3, endereco[j]);
								strcpy(aux4, sexo[j]);
								strcpy(aux5, email[j]);
								aux6 = altura[j];
								id[j] = id[j+1];
								strcpy(nome[j], nome[j+1]);
								strcpy(endereco[j], endereco [j+1]);
								strcpy(sexo[j], sexo[j+1]);
								strcpy(email[j], email [j+1]);
								altura[j] = altura[j+1];
								id[j+1] = aux;
								strcpy(nome[j+1], aux2);
								strcpy(endereco[j+1], aux3);
								strcpy(sexo[j+1], aux4);
								strcpy(email[j+1], aux5);
								altura[j+1] = aux6;
								}
							}
						}
					}else
						printf("MEMORIA CHEIA! EXCLUA UM USUARIO PARA CONTINUAR!\n");
				break;
			case 2:
				printf("----- Editar um Usuario -----\n");
				printf("DIGITE O ID DO USUARIO QUE VAI SER EDITADO: ");
				scanf("%i", &chave);
                pos = pesquisaBinaria(id, chave, 0, ind);
				if (pos != -1){
					printf ("Digite o nome completo do usuario: \n");
				    setbuf (stdin, NULL);
				    fgets (nome[pos],50,stdin);

				do{
					printf ("Digite o novo email do usuario: \n");
					setbuf (stdin, NULL);
					fgets (email[pos],70,stdin);
				}while(validarEmail(email[pos])==0);

				do{
		    		printf ("Digite o sexo atualizado do usuario (entre: \"Masculino\", \"Feminino\" e \"Nao declarar\"): \n");
					setbuf (stdin, NULL);
					fgets (sexo[pos],14,stdin);
					toupperCase(sexo[pos]);
					removerPulaLinha(sexo[pos]);
				}while(validarSexo(sexo[pos]) == 0);

				    printf ("Digite o novo endereco do usuario: \n");
				    setbuf (stdin, NULL);
				    fgets (endereco[pos],100,stdin);

				do{
					printf("Digite a altura atualizada do usuario: ");
					scanf("%lf", &altura[pos]);
				}while(validarAltura(altura[pos]) == 0);

				do{
					printf("Digite \"S\" \"N\" em relacao a situacao de vacinacao do usuario: ");
					setbuf (stdin, NULL);
					resp = getchar();
					resp = toupper(resp);
				}while(resp != 'S' && resp != 'N');

                if(resp == 'S')
					vacina[pos] = TRUE;
				else
					vacina[pos] = FALSE;
				} else
					printf("\nID NAO ENCONTRADO\n!");
				break;
			case 3:
				printf("----- Excluir um Usuario pelo ID -----\n");
				printf("DIGITE O ID DO USUARIO QUE VAI SER EXCLUIDO: ");
				scanf("%i", &chave);
				pos = pesquisaBinaria(id, chave, 0, ind);
				if (pos != -1){
					excluirUsuario(ind, chave, altura, nome, email, endereco, sexo, id, pos, vacina);
					ind--;
				} else
					printf("ID NAO ENCONTRADO\n!");
				break;
			case 4:
				printf("----- Buscar Usuario por ID -----\n");
				printf("DIGITE O ID DO USUARIO QUE VAI SER FEITA A PESQUISA: ");
				scanf("%i", &chave);
				pos = pesquisaBinaria(id, chave, 0, ind);
				if (pos != -1){
					printf("id: %i\n", id[pos]);
					printf("Nome: %s", nome[pos]);
					printf("Email: %s", email[pos]);
					printf("Sexo: %s \n", sexo[pos]);
					printf("Endereco: %s", endereco[pos]);
					printf("Altura: %.2f\n", altura[pos]);
					if(vacina[pos] == TRUE)
						printf("Situcao: Vacinado\n");
					else
						printf("Situacao: Nao Vacinado\n");
				} else
					printf("ID NAO ENCONTRADO\n!");
				break;
			case 5:
				printf("----- Pesquisar Usuario pelo Email -----\n");
				printf("digite o email do usuario: ");
				setbuf (stdin, NULL);
				fgets (chaveStr, 70, stdin);
				pos = pesquisarEmail(ind, email, chaveStr);
				if (pos != -1){
					printf("id: %i\n", id[pos]);
					printf("Nome: %s", nome[pos]);
					printf("Email: %s", email[pos]);
					printf("Sexo: %s \n", sexo[pos]);
					printf("Endereco: %s", endereco[pos]);
					printf("Altura: %.2f\n", altura[pos]);
					if(vacina[pos] == TRUE)
						printf("Situcao: Vacinado\n");
					else
						printf("Situacao: Nao Vacinado\n");
				} else
					printf("EMAIL NAO ENCONTRADO\n!");
				
				break;
			case 6:
				system("cls");
				printf("----- Imprimir um Usuario -----\n");
				for(i = 0; i<ind; i++){
					printf("id: %i\n", id[i]);
					printf("Nome: %s", nome[i]);
					printf("Email: %s", email[i]);
					printf("Sexo: %s \n", sexo[i]);
					printf("Endereco: %s", endereco[i]);
					printf("Altura: %.2f\n", altura[i]);
					if(vacina[i] == TRUE)
						printf("Situcao: Vacinado\n");
					else
						printf("Situacao: Nao Vacinado\n");
					printf("---------------------------------------------------------\n");
				}
				break;
			case 7:
				printf("----- Fazer um Backup -----\n");
				indBP = ind;
				backup(ind, chave, altura, nome, email, endereco, sexo, id, vacina, alturaBP, nomeBP, emailBP, enderecoBP, sexoBP,idBP, vacinaBP);
				flagBP = 1;
				break;
			case 8:
				printf("----- Restaurar Dados -----\n");
				if(flagBP == 1){
				restaurarDados(indBP, chave, altura, nome, email, endereco, sexo, id, vacina, alturaBP, nomeBP, emailBP, enderecoBP, sexoBP,idBP, vacinaBP);
				ind = indBP;
				printf("BACKUP FEITO COM SUCESSO\n");
				}else
					printf("UM BACKUP E NECESSARIO PARA A RESTAURACAO DE DADOS!\n");
		}
}while(op != 0);





  return 0;
}
int menuPrincipal (void){
  int opc;

  printf ("--------- MENU PRINCIPAL ---------\n\n");
  printf ("1- Cadastrar um novo usuario\n");
  printf ("2- Editar um usuario\n");
  printf ("3- Excluir um usuario\n");
  printf ("4- Buscar um usuario pelo ID\n");
  printf ("5- Buscar um usuario pelo email\n");
  printf ("6- Imprimir todos os usuarios\n");
  printf ("7- Fazer backup de um usuario cadastrado\n");
  printf ("8- Restaurar dados\n");
  printf ("0- Sair\n");
  printf("Digite o numero correspondente da opcao desejada: ");
	scanf("%d",&opc);
	printf("\n");
	return opc;
}

int validarEmail (char email[]){
	int i;
	int	flag=0;

	for(i=0; email[i] != '\0'; i++)
		if(email[i] == '@')
			flag = 1;


	if (flag == 1)
		return 1;
	else
		return 0;
}

void toupperCase(char str[]){
	int i;

	for(i=0; str[i] != '\0'; i++)
		str[i] = toupper(str[i]);

}

void removerPulaLinha(char str[]){
	str[strlen(str)-1] = '\0';
}

int validarSexo(char sexo[]){

	if (strcmp(sexo,"MASCULINO") == 0)
		return 1;
	if(strcmp(sexo,"FEMININO") == 0)
		return 1;
	if (strcmp(sexo,"NAO DECLARAR") == 0)
		return 1;

	return 0;
}

int validarAltura(double altura){
	if(altura >= 1.0 && altura <= 2.0)
		return 1;

	return 0;
}

void criarPessoa (int id[], int vacina[], int ind, char nome[]){
	printf("");
}

int pesquisaBinaria (int id[], int chave, int low, int high){
	int mid;

	if (low > high)
		return -1;
	else{
		mid = (low+high)/2;
		if (chave == id[mid])
			return mid;
		else if (chave>id[mid])
			return pesquisaBinaria(id, chave, mid+1, high);
		else
			return pesquisaBinaria(id, chave, low, mid-1);
	}
}

int pesquisarEmail (int ind, char email[][ind], char chave[]){
	int i;
	
	for(i=0; i<ind; i++)
		if(strcmp(email[i], chave) == 0)
			return i;
	return -1;	
}

void excluirUsuario (int ind, int chave, double altura[], char nome[][N], char email[][N], char endereco[][N], char sexo[][N], int id[], int pos, int vac[]){
	int i;
	for(i=pos; i<(ind-1); i++){
		id[i] = id[i+1];
		vac[i] = vac[i+1];
		altura[i] = altura[i+1];
		strcpy(nome[i], nome[i+1]);
		strcpy(email[i], email[i+1]);
		strcpy(endereco[i], endereco[i+1]);
		strcpy(sexo[i], sexo[i+1]);
	}
}

void backup (int ind, int chave, double altura[], char nome[][N], char email[][N], char endereco[][N], char sexo[][N], int id[], int vac[], double alturaBP[], char nomeBP[][N], char emailBP[][N], char enderecoBP[][N], char sexoBP[][N], int idBP[], int vacBP[]){
	int i;
	for(i=0; i<ind; i++){
		idBP[i] = id[i];
		vacBP[i] = vac[i];
		alturaBP[i] = altura[i];
		strcpy(nomeBP[i], nome[i]);
		strcpy(emailBP[i], email[i]);
		strcpy(enderecoBP[i], endereco[i]);
		strcpy(sexoBP[i], sexo[i]);
	}
}

void restaurarDados (int ind, int chave, double altura[], char nome[][N], char email[][N], char endereco[][N], char sexo[][N], int id[], int vac[], double alturaBP[], char nomeBP[][N], char emailBP[][N], char enderecoBP[][N], char sexoBP[][N], int idBP[], int vacBP[]){
	int i;
	for(i=0; i<ind; i++){
		id[i] = idBP[i];
		vac[i] = vacBP[i];
		altura[i] = alturaBP[i];
		strcpy(nome[i], nomeBP[i]);
		strcpy(email[i], emailBP[i]);
		strcpy(endereco[i], enderecoBP[i]);
		strcpy(sexo[i], sexoBP[i]);
	}
}

int isRepeated (int id[], int ind, int chave){
	int i;
	
	for(i=0; i<ind; i++){
		if(chave < id[i])
			return 0;
		if(chave == id[i])
			return 1;

	}
	return 0;
}
