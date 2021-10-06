/*
 ============================================================================
 Name        : jogoVelha.c
 Author      : Luiz Henrique Vieira Steff
 Version     :
 Copyright   : Your copyright notice
 Description : Jogo da Velha. Jogo disputado por dois jogadores, com objetivo de formar uma linha horizontal,
 vertical ou diagonal de três xis ou círculos, numa das nove entrelinhas de uma figura de quatro
 linhas em forma de (#) cerquilha.
 Nesse exercício, você deve fazer um jogo da velha. Inicialmente, o programa deve guardar e escrever
 na tela um tabuleiro de jogo da velha. Depois, seu programa deve permitir que 2 jogadores humanos
 possam jogar um contra o outro. Finalmente, permita que o jogador humano possa jogar contra o
 computador.? O programa também deve permitir selecionar entre jogar contra um jogador humano ou o
 computador.
 Dica. Faça o programa perguntar qual a linha e coluna que o jogador que marcar. Não esqueça de validar
 o valor, ou seja, deve ser entre os limites da matriz.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define DIM 3

int linha, coluna,jogadas;

void mostrar_tabuleiro(char tabuleiro[DIM][DIM]);
int mostra_menu();
void jogada_do_computador(char tabuleiro[DIM][DIM]);
void multiplayer(char tabuleiro[DIM][DIM],int jogadas);
void singleplayer(char tabuleiro[DIM][DIM],char escolha);
int verifica_vitoria(char tabuleiro[DIM][DIM]);
int finalizar_game(char tabuleiro[DIM][DIM], int jogadas, int modo, int ganhou);
void validaJogada(char tabuleiro[DIM][DIM]);

int main(void) {
	setbuf(stdout, NULL);
	int jogando = 1, ganhou = 0, repetir = 1;
	do
	{
		jogadas = 0;
		ganhou = 0;
		jogando = 1;
		char tabuleiro[DIM][DIM] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
		int modo = mostra_menu();
		//roda o jogo inteiro em loop até acabar
		switch(modo){
		case (1):
			do
			{
				mostrar_tabuleiro(tabuleiro);
				multiplayer(tabuleiro,jogadas);
				jogadas++;
				ganhou = verifica_vitoria(tabuleiro);
				if(ganhou || jogadas == 8){
					repetir = finalizar_game(tabuleiro,jogadas,1,ganhou);
					jogando = 0;
				}
			}while(jogando);
			break;
		case (2):
			printf("Você pode escolher entre X ou O, insira abaixo: ");
			char escolha;
			scanf(" %c",&escolha);
			while(escolha != 'X' && escolha != 'O'){
					printf("Essa escolha não é válida!");
					scanf(" %c",&escolha);
			}
			do{
				mostrar_tabuleiro(tabuleiro);
				singleplayer(tabuleiro,escolha);
				jogadas++;
				ganhou = verifica_vitoria(tabuleiro);
				if(!(ganhou)){
					jogada_do_computador(tabuleiro);
					if(escolha == 'O'){
						tabuleiro[linha][coluna] = 'X';
					}else{
						tabuleiro[linha][coluna] = 'O';
					}
				}
				ganhou = verifica_vitoria(tabuleiro);
				if(ganhou || jogadas == 8){
					repetir = finalizar_game(tabuleiro,jogadas,2,ganhou);
					jogando = 0;
				}
			}while(jogando);
			break;
		default:
			printf("O modo selecionado não é válido!");
		}
	}
	while(repetir);
	return EXIT_SUCCESS;
}

void mostrar_tabuleiro(char tabuleiro[DIM][DIM]) {
	system("cls");
	for (int i = 0; i < DIM; i++) {
		printf("               ");
		printf("-------------------------\n                |");
		for (int j = 0; j < DIM; j++) {
			printf("   %c   |", tabuleiro[i][j]);
		}
		printf("\n");
	}
	printf("                ");
	printf("-------------------------\n");
}

int mostra_menu(){
	int modo = 0;
	printf("Olá bem vindo ao jogo da velha!\n Escolha um modo de jogo para continuar: \n");
	printf("Modo 1: Player vs Player\nModo 2: Player vs PC\n");
	scanf("%d",&modo);
	return modo;
}

void multiplayer(char tabuleiro[DIM][DIM],int jogadas){
	if(jogadas % 2 == 0){
		printf("Você é o jogador X selecione uma casa do tabuleiro para preencher, primeiro linha depois coluna: \n");
		validaJogada(tabuleiro);
		tabuleiro[linha][coluna] = 'X';
	}else{
		printf("Você é o jogador O selecione uma casa do tabuleiro para preencher, primeiro linha depois coluna: \n");
		validaJogada(tabuleiro);
		tabuleiro[linha][coluna] = 'O';
	}
}

int verifica_vitoria(char tabuleiro[DIM][DIM]){
	//verifica vitória na vertical
	for(int i = 0; i < 3; i++){
		if(tabuleiro[1][i] != ' ' && tabuleiro[1][i] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][0] && tabuleiro[i][1] == tabuleiro[i][2]){
					return 1;
		}
	}
	//verifica vitória na horizontal
	for(int i = 0; i < 3; i++)
		{
			if(tabuleiro[1][i] != ' ' && tabuleiro[1][i] == tabuleiro[0][i] && tabuleiro[0][i] == tabuleiro[2][i]){
				return 1;
		}
	}
	//verifica vitória na diagonal
	if(tabuleiro[1][1] != ' ' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]){
		return 1;
	}
	//verifica vitória na diagonal
	if(tabuleiro[1][1] != ' ' && tabuleiro[2][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[0][2]){
		return 1;
	}
	return 0;
}

int finalizar_game(char tabuleiro[DIM][DIM], int jogadas, int modo, int ganhou){
	int repetir;
	//mostra uma m0ensagem personalizada para o jogador que ganhou
	//caso singleplayer, ímpar é sempre o jogador, par é sempre o pc
	if(ganhou){
		if(modo == 1){
				if(!(jogadas % 2 == 0))
				{
					printf("Parabéns!! Você ganhou o jogo jogador X!!!");
					mostrar_tabuleiro(tabuleiro);
					Sleep(0.5);
					mostrar_tabuleiro(tabuleiro);
					Sleep(0.5);
					system("cls");
				}
				else
				{
					printf("Parabéns!! Você ganhou o jogo jogador O!!!");
					mostrar_tabuleiro(tabuleiro);
					Sleep(0.5);
					mostrar_tabuleiro(tabuleiro);
					Sleep(0.5);
					system("cls");
				}
			}else{
				if(!(jogadas % 2 == 0))
						{
							printf("Parabéns!! Você ganhou o jogo, jogador!!!");
							mostrar_tabuleiro(tabuleiro);
							Sleep(0.5);
							mostrar_tabuleiro(tabuleiro);
							Sleep(0.5);
							system("cls");
						}else{
							printf("Poxa que pena! Você perdeu!");
						}
			}
	}else{
		printf("Poxa que pena! Deu empate!");
	}
	//Volta ao menu principal ou encerra dependendo da escolha
	printf("Gostaria de jogar novamente?? Pressione 0 para sair ou qualquer número para continuar!");
	scanf(" %d",&repetir);
	if(repetir)
		return 1;
	return 0;
}
void validaJogada(char tabuleiro[DIM][DIM]){
	scanf(" %d %d",&linha,&coluna);
	//valida se o número é dentro dos limites
	while((linha > 2 || linha < 0) && (coluna > 2 || coluna < 0)){
		printf("Essa linha ou coluna não existe!");
		scanf(" %d %d",&linha,&coluna);
	}
	//valida se o campo já foi preenchido ou nao
	while(tabuleiro[linha][coluna] != ' '){
		printf("Esta casa do tabuleiro já está preenchida! Tente novamente!");
		scanf(" %d %d",&linha,&coluna);
	}
}

void singleplayer(char tabuleiro[DIM][DIM], char escolha){
	if(escolha == 'X'){
		printf("Você é o jogador X selecione uma casa do tabuleiro para preencher, primeiro linha depois coluna: \n");
		validaJogada(tabuleiro);
		tabuleiro[linha][coluna] = 'X';
	}else{
		printf("Você é o jogador O selecione uma casa do tabuleiro para preencher, primeiro linha depois coluna: \n");
		validaJogada(tabuleiro);
		tabuleiro[linha][coluna] = 'O';
		}
}

void jogada_do_computador(char tabuleiro[DIM][DIM]){
	srand(time(0));
	linha = rand() % 2;
	coluna = rand() % 2;
	while(tabuleiro[linha][coluna] != ' '){
		linha = rand() % 2;
		coluna = rand() % 2;
	}
}
