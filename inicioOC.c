#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct arquivo
{
	int instrucao;
	struct arquivo *prox;
}din;

din *abrirArq(din *file, int *n){
	FILE *ptrarq;
	int result;
	char nomeArq[50];
	char enddesc[10]; //dados sem utilizade para o objetivo do programa

	printf("Digite o nome e extensão do arquivo: ");
	scanf(" %[^\n]", nomeArq);

	ptrarq = fopen(nomeArq, "r");
	if(ptrarq == NULL){
		printf("Falha ao abrir o arquivo .din.\n");
		file->instrucao = -1;
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

	if(file->instrucao != -1){
		printf("Foram realizados %d acessos à memória.\n",n);
		contaComando(file);
	}
	
}
