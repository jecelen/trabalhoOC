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
	char bindesc[10]; //dados sem utilizade para o objetivo do programa

	struct dirent *_dir;	
		
	/*buscar por arquivo .dir no diretorio*/
	dir = opendir(".");
	if(dir != NULL){
		while((_dir = readdir(dir)) != NULL){
			if(strstr(_dir->d_name, ".din") != NULL){
				strcpy(nomeArq, _dir->d_name);
				printf("%s\n", nomeArq);
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
		fscanf(ptrarq, " %[^\n]", bindesc);
		*n = 1;
		
		while(result!=EOF){
			novo = (din*)malloc(sizeof(din));
			result = fscanf(ptrarq, "%d", &novo->instrucao);
			novo->prox = NULL;
			p->prox = novo;
			p = p->prox;
			fscanf(ptrarq, " %[^\n]", bindesc);
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




int main(){

	din *file, *p;

	file = NULL;
	int n = 0;

	file = abrirArq(file, &n);
	printf("Foram lidar %d instruções.\n",n);
	/*conrfimar valores*/
	p = file;
	while(p != NULL){
		printf("%d\n",p->instrucao);
		p = p->prox;

	



	}
}