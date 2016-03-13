#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#ifdef linux
    #define LIMPA system("clear")
#else
    #define LIMPA system("cls")
#endif
void mostraAjuda(char **argv);
void geraMelhor(int quantidade, int *lista);
void geraAleatorio(int qunatidade, int *lista);
void geraPior(int quantidade, int *lista);
int main(int argc, char **argv){
    setlocale(LC_ALL, "ptb");
    LIMPA;
    srand(time(NULL));
	int i, quantidade, opcao, tipoLista, *lista = NULL, retorno;
	char *nomeLista = NULL, tipoListaS[10];
    while((opcao = getopt(argc, argv, "hl:t:q:")) > 0){
		switch(opcao){
			case 't':
                if(strncmp(optarg, "aleatorio", 9) == 0){
                    tipoLista = 0;
                    strncpy(tipoListaS, "aleatorio", 9);
                    break;
                }
                if(strncmp(optarg, "melhor", 6) == 0){
                    tipoLista = 1;
                    strncpy(tipoListaS, "melhor", 6);
                    break;
                }
                if(strncmp(optarg, "pior", 4) == 0){
                    tipoLista = 2;
                    strncpy(tipoListaS, "pior", 4);
                    break;
                }
                printf("[%s] - Argumento inválido!\n", optarg);
                exit(1);
			break;
			case 'l':
				nomeLista = optarg;
			break;
			case 'q':
				quantidade = atoi(optarg);
			break;
            case 'h':
                mostraAjuda(argv);
            break;
			default:
				printf("Opção invalida!\n");
				return 1;
			break;
		}
    }
	lista = calloc(quantidade, sizeof(int));
	switch(tipoLista){
		case 0:
			geraAleatorio(quantidade, lista);
		break;
		case 1:
			geraMelhor(quantidade, lista);
		break;
		case 2:
			geraPior(quantidade, lista);
		break;
	}
	FILE *arquivo = NULL;
	arquivo = fopen(nomeLista, "w");
	if(arquivo == NULL){
		printf("Erro ao salvar a lista!\n");
		exit(1);
	}
	for(i = 0;i < quantidade;i++){
		fprintf(arquivo, "%d\n", lista[i]);
	}
	free(lista);
    printf("Nome da lista gerada:\t%s\n", nomeLista);
    printf("Quantidade:\t\t%d\n", quantidade);
    printf("Tipo de lista:\t\t%s\n", tipoListaS);
    printf("Para mais informções utilize a opção -h\n");
	if(retorno != EOF){
		fclose(arquivo);
	}
	else{
		printf("Erro ao salvar a lista!\n");
		fclose(arquivo);
		exit(1);
	}
    return 0;
}

void mostraAjuda(char **argv){
    printf("Modos de uso:\n");
    printf("\t-h\t\t\t\tMostra essa tela.\n");
    printf("\t-t aleatorio|melhor|pior\tTipo da lista a ser gerada.\n");
    printf("\t-l nomeLista.txt\t\tDefinir o nome do aquivo da lista a ser gerada.\n");
    printf("\t-q QUANTIDADE\t\t\tDefinir a quantidade de numeros gerados.\n");
    printf("exemplo de uso:\n");
    printf("talyson@XPS:~$ %s -t aleatorio -q 10000 -l lista_10k.txt\n", argv[0]);
    printf("\n\nVersão 0.1 - Gerador de lista para materia de Pesquisa e Odernação de Dados UTFPR-MD.\n");
    printf("Devevolvido por Talyson Rodrigues 13/02/2016.\nContato:t4lyson[at]gmail[dot]com.\n");
    printf("Compilação: %s, %s.\n", __DATE__, __TIME__);
    exit(1);
}

void geraAleatorio(int quantidade, int *lista){
    int i, aux, pos1, pos2;
    for(i = 0;i < quantidade;i++){
        lista[i] = i;
    }
    for(i = 0;i <= quantidade;i++){
        pos1 = rand() % quantidade;
        pos2 = rand() % quantidade;
        aux = lista[pos1];
        lista[pos1] = lista[pos2];
        lista[pos2] = aux;
    }
}

void geraMelhor(int quantidade, int *lista){
	int i;
	for(i = 0;i < quantidade;i++){
		lista[i] = i;
	}
}

void geraPior(int quantidade, int *lista){
	int i;

	for(i = quantidade -1 ;i >= 0;i--){
		lista[i] = quantidade - 1 - i;
	}
}
