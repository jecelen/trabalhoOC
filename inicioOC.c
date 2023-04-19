#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>


typedef struct arquivo
{
	int instrucao;
	struct arquivo *prox;
}din;

din *abrirArq(din *file, int *n){
	FILE *ptrarq;
	DIR *dir;
	int result;
	char nomeArq[50];
	char enddesc[10]; //dados sem utilizade para o objetivo do programa

	struct dirent *_dir;	
		
	/*buscar por arquivo .dir no diretorio*/
	dir = opendir(".");
	if(dir != NULL){
		while((_dir = readdir(dir)) != NULL){
			if(strstr(_dir->d_name, ".din") != NULL){
				strcpy(nomeArq, _dir->d_name);
				printf("Arquivo %s localizado no diretório.\n\n", nomeArq);
			}
		}
	}	
	/*abrir arquivo .dir*/
	ptrarq = fopen(nomeArq, "r");
	if(ptrarq == NULL){
		printf("Falha ao abrir o arquivo .din.\n");
		return file;
		}
	
	else{
		din *p, *novo;
		
		novo = (din*)malloc(sizeof(din));
		result = fscanf(ptrarq, "%d", &novo->instrucao);
		novo->prox = NULL;
		file = novo;
		p = file;
		fscanf(ptrarq, " %[^\n]", enddesc);
		*n = 1;
		
		while(result!=EOF){
			novo = (din*)malloc(sizeof(din));
			result = fscanf(ptrarq, "%d", &novo->instrucao);
			novo->prox = NULL;
			p->prox = novo;
			p = p->prox;
			fscanf(ptrarq, " %[^\n]", enddesc);
			*n+=1;
			if(feof(ptrarq)){
				break;
				}	
			}
		fclose(ptrarq);
		}

	closedir(dir);
	
	return file;
	}

void contaComando(din *file){
	din *p; 
	p = file;
	int le, busca, escreve;
	le = busca = escreve = 0;

	while(p!=NULL){
		if(p->instrucao==0){
			le+=1;
		}
		else if(p->instrucao==1){
			escreve+=1;
		}
		else{
			busca+=1;
		}
	p=p->prox;
	}
	printf("Foram realizados %d acessos às instruções, %d acessos aos dados, %d leituras de dados e %d escritas de dados.\n", busca, le+escreve, le, escreve);
}


int main(){

	din *file, *p;

	file = NULL;
	int n = 0;

	file = abrirArq(file, &n);
	printf("Foram realizados %d acessos à memória.\n",n);

	contaComando(file);
	
}