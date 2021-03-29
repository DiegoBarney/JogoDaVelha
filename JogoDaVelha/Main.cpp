#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define linhas 3
#define colunas 3

#define tamLinhasInterface 5
#define tamColunasInterface 3

struct dados_jogador
{
	char nome[50];
	char pecaJogador;
	bool vencedor = false;
};

void jogoDaVelhaUserIterface(char** matrizJogoPreenchida) {
	int descontoInterfaceVsMatriz = 0;
	system("cls");

	for (int linhasInterface = 1; linhasInterface <= tamLinhasInterface; linhasInterface++) {

		printf("\n");

		if (linhasInterface % 2 == 0)
		{
			printf("________________________\n");
		}
		else {
			descontoInterfaceVsMatriz++;
			for (int colunasInterface = 0; colunasInterface < tamColunasInterface; colunasInterface++)
			{
				printf("  %c   ", matrizJogoPreenchida[linhasInterface - descontoInterfaceVsMatriz][colunasInterface]);

				if (colunasInterface < 2) {
					printf("|");
				}

				printf("   ");
			}
		}
	}
	printf("\n");
}

char** iniciaJogada() {
	char** matriz = NULL;

	matriz = (char**)malloc(linhas * sizeof(char*));

	for (int i = 0; i < linhas; ++i)
		matriz[i] = (char*)malloc(colunas * sizeof(char));


	for (size_t i = 0; i < linhas; i++)
	{
		for (size_t a = 0; a < colunas; a++)
		{
			matriz[i][a] = ' ';
		}
	}

	return matriz;
}

dados_jogador* carregaDadosDosJogadores()
{
	dados_jogador* dadosJogadores = (dados_jogador*)malloc(2 * sizeof(dados_jogador));
	memset(dadosJogadores, NULL, sizeof(dados_jogador));

	int numeroPeca;

	for (int i = 0; i < 2;	i++) {
		printf("\n Digite o nome do %d jogador: ", i);
		fflush(stdin);
		fgets(dadosJogadores[i].nome, 40, stdin);
		dadosJogadores[i].vencedor = false;
	}

	printf("\nJogador %s, digite 1 para jogar com X ou 0 para jogar com O: ", dadosJogadores[0].nome);
	scanf_s("%d", &numeroPeca);


	if (numeroPeca)
	{
		dadosJogadores[0].pecaJogador = 'X';
		dadosJogadores[1].pecaJogador = 'O';
	}
	else
	{
		dadosJogadores[0].pecaJogador = 'O';
		dadosJogadores[1].pecaJogador = 'X';
	}

	return dadosJogadores;
}

void fazjogada(dados_jogador* jogador, char** matriz) {
	int posicaoDaJogada = 0;
	char peca;

	printf("%s, Escolha um numero do teclado para a jogada e aperte ENTER: ", jogador->nome);
	scanf_s("%d", &posicaoDaJogada);

	switch (posicaoDaJogada)
	{
	case 1:
		matriz[2][0] = jogador->pecaJogador;
		break;
	case 2:
		matriz[2][1] = jogador->pecaJogador;
		break;
	case 3:
		matriz[2][2] = jogador->pecaJogador;
		break;
	case 4:
		matriz[1][0] = jogador->pecaJogador;
		break;
	case 5:
		matriz[1][1] = jogador->pecaJogador;
		break;
	case 6:
		matriz[1][2] = jogador->pecaJogador;
		break;
	case 7:
		matriz[0][0] = jogador->pecaJogador;
		break;
	case 8:
		matriz[0][1] = jogador->pecaJogador;
		break;
	case 9:
		matriz[0][2] = jogador->pecaJogador;
	default:
		break;
	}
}

bool analisaVencedorOuEmpate(dados_jogador* jogador, char** matriz) {

	char pecasParaAvaliar[2] = { 'X','O' };

	for (int i = 0; i < 2; i++)
	{
		//DIAGONAIS
		if (matriz[0][0] == pecasParaAvaliar[i] && matriz[1][1] == pecasParaAvaliar[i] && matriz[2][2] == pecasParaAvaliar[i] ||
			matriz[0][2] == pecasParaAvaliar[i] && matriz[1][1] == pecasParaAvaliar[i] && matriz[2][0] == pecasParaAvaliar[i])
		{
			jogador->vencedor = true;
		}

		//COLUNAS
		if (matriz[0][0] == pecasParaAvaliar[i] && matriz[1][0] == pecasParaAvaliar[i] && matriz[2][0] == pecasParaAvaliar[i] ||
			matriz[0][1] == pecasParaAvaliar[i] && matriz[1][1] == pecasParaAvaliar[i] && matriz[2][1] == pecasParaAvaliar[i] ||
			matriz[0][2] == pecasParaAvaliar[i] && matriz[1][2] == pecasParaAvaliar[i] && matriz[2][2] == pecasParaAvaliar[i])
		{
			jogador->vencedor = true;
		}

		//LINHAS
		if (matriz[0][0] == pecasParaAvaliar[i] && matriz[0][1] == pecasParaAvaliar[i] && matriz[0][2] == pecasParaAvaliar[i] ||
			matriz[1][0] == pecasParaAvaliar[i] && matriz[1][1] == pecasParaAvaliar[i] && matriz[1][2] == pecasParaAvaliar[i] ||
			matriz[2][0] == pecasParaAvaliar[i] && matriz[2][1] == pecasParaAvaliar[i] && matriz[2][2] == pecasParaAvaliar[i])
		{
			jogador->vencedor = true;
		}
	}

	if (jogador->vencedor) {
		printf("\n\nParabens %s, Voce foi o(a) vencedor(a)!!!\n\n\n", jogador->nome);
		return true;
	}
	else {

		for (size_t i = 0; i < linhas; i++)
		{
			for (size_t a = 0; a < colunas; a++)
			{
				if (matriz[i][a] == ' ')
					return false;
			}
		}

		printf("\n\nJogo empatado!!!\n\n\n");
		return true;
	}

	return false;
}

void gameplay(dados_jogador jogador, char** matriz) {
	jogoDaVelhaUserIterface(matriz);
	fazjogada(&jogador, matriz);
	jogoDaVelhaUserIterface(matriz);
}

int main()
{
	char** matriz = NULL;
	dados_jogador* dadosJogadores = (dados_jogador*)malloc(2 * sizeof(dados_jogador));
	bool finalizaJogo = false;
	int jogadas = 0;

	matriz = iniciaJogada();
	dadosJogadores = carregaDadosDosJogadores();
	do {
		dados_jogador jogadorAtual = dadosJogadores[jogadas%2];
		gameplay(jogadorAtual, matriz);
		finalizaJogo = analisaVencedorOuEmpate(&jogadorAtual, matriz);

		jogadas++;

	} while (finalizaJogo == false);

	system("pause");
}
