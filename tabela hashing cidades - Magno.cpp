#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

char cidades[30][40] = {"Aracaju", "Arapongas", "Astorga", "Barueri", "Blumenau", "Campinas", "Castro", "Cianorte", "Curitiba", "Diamante do Norte", "Engenheiro Beltrao", "Florai", "Floriano", "Goiania", "Goioere", "Hortolandia", "Itapemirim", "Ivaipora", "Jundiai", "Jussara", "Mandaguacu", "Marialva", "Maringa", "Natal", "Sinop", "Sorocaba", "Suzano", "Ubatuba", "Vitoria", "Volta Redonda"};

typedef struct tipoCidade 
{
	char nomeCidade[40];
	struct tipoCidade *proximo;
}TCidade;

typedef struct tipoLista 
{
	TCidade *inicio;
	TCidade *fim;
}TLista;

TLista tabelaHashing[62]; //Escolhi o tamanho 62 para que o ultimo indice seja um numero primo (61), o que ajuda a evitar colisões na dispersão dos dados.

void inicializar()
{
	int i;
	for (i=0; i<62; i++)
	{
		tabelaHashing[i].inicio = NULL;
		tabelaHashing[i].fim = NULL;
	}
}

int hash(int soma)
{
		return soma % 61;
}

void executar()
{
	int quantasLetras;
	int i;
	int j = 0;
	printf("\n Informe o numero de letras que serao utilizadas para o calculo do hash: ");
	scanf("%d", &quantasLetras);
	
	do {	
		int soma = 0;
		for (i=0; i<quantasLetras && cidades[j][i] != '\0'; i++)
		{
			soma = soma + cidades[j][i];
		}
		int indice = hash(soma);
	
		TCidade *novaCidade;
		novaCidade = new TCidade;
		strcpy (novaCidade->nomeCidade, cidades[j]);
		novaCidade->proximo = NULL;
	
	
		if(tabelaHashing[indice].inicio == NULL)
		{
			tabelaHashing[indice].inicio = novaCidade;
			tabelaHashing[indice].fim = novaCidade ;
		}
		else
		{
			tabelaHashing[indice].fim->proximo = novaCidade;
			tabelaHashing[indice].fim = novaCidade;
		}
		j++;
	} while (j<30);
}

void apresentar()
{
	TCidade *aux;
	int i;
	
	for (i = 0; i < 62; i++) //para percorrer a tabela hashing
	{
		TCidade *aux;
		aux = tabelaHashing[i].inicio;
		if (aux != NULL)
		{
			printf("\n Indice: %d - ", i);
			while (aux != NULL) //para percorrer as listas encadeadas
			{
				printf("%s | ", aux->nomeCidade);
				aux = aux->proximo;
			}
		}
		else
		{
			printf("\n Indice: %d  - / ", i);
		}	
	}
	printf("\n ");
}

void discussao() //função para imprimir o número de colisões e numero de indices ocupados
{
	int i;
	int indicesUtilizados = 0;
	int tamanhoLista = 0;
	int indicesComColisoes = 0;
	
	for (i=0; i<62; i++)
	{
		if (tabelaHashing[i].inicio != NULL)
		{
			indicesUtilizados += 1;
		}
		if (tabelaHashing[i].inicio != tabelaHashing[i].fim && tabelaHashing[i].inicio != NULL)
		{
			indicesComColisoes += 1;
			TCidade *aux;
			aux = tabelaHashing[i].inicio;
			while (aux != NULL) {	
				aux = aux->proximo;
				tamanhoLista += 1; 
			}
		}
	}
	printf("\n Numero de indices ocupados: %d", indicesUtilizados);
	printf("\n Numero de colisoes: %d \n", tamanhoLista - indicesComColisoes);
}



int main(void) 
{
	int opcao;
	inicializar();
	
	do
	{
		printf("\n 1 - Executar hash");
		printf("\n 2 - Apresentar tabela hashing");
		printf("\n 3 - Apresentar discussao");
		printf("\n 4 - Limpar tabela");
		printf("\n 0 - Sair");
		printf("\n Escolha uma opcao: ");
		scanf("%d", &opcao);
		switch(opcao)
		{
			case 1: executar(); break;
			case 2: apresentar(); break;
			case 3: discussao(); break;
			case 4: inicializar(); system("cls"); break;
		}
	}while (opcao != 0);
	
	
	
	
	
	return 0;
}
