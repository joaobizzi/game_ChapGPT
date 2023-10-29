#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para imprimir o tabuleiro
void imprimirTabuleiro(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se alguém venceu
int verificarVitoria(char tabuleiro[3][3], char jogador) {
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) {
            return 1; // Linha
        }
        if (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador) {
            return 1; // Coluna
        }
    }
    if (tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) {
        return 1; // Diagonal principal
    }
    if (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador) {
        return 1; // Diagonal secundária
    }
    return 0;
}

// Função para verificar se o tabuleiro está cheio (empate)
int tabuleiroCheio(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == ' ')
                return 0; // Ainda há espaços vazios
        }
    }
    return 1; // O tabuleiro está cheio
}

// Função para a jogada do jogador
void jogadaJogador(char tabuleiro[3][3], char jogador) {
    int linha, coluna;
    printf("Sua vez, jogador %c!\n", jogador);
    do {
        printf("Informe a linha (0, 1 ou 2) e a coluna (0, 1 ou 2) separadas por um espaço: ");
        scanf("%d %d", &linha, &coluna);
    } while (linha < 0 || linha > 2 || coluna < 0 || coluna > 2 || tabuleiro[linha][coluna] != ' ');
    tabuleiro[linha][coluna] = jogador;
}

// Função para a jogada do computador (jogador 'O')
void jogadaComputador(char tabuleiro[3][3], char jogador) {
    printf("Vez do computador (O)...\n");
    int linha, coluna;

    // Lógica do computador para a jogada
    // Verifica se pode ganhar
    for (linha = 0; linha < 3; linha++) {
        for (coluna = 0; coluna < 3; coluna++) {
            if (tabuleiro[linha][coluna] == ' ') {
                tabuleiro[linha][coluna] = jogador;
                if (verificarVitoria(tabuleiro, jogador)) {
                    return; // O computador pode ganhar
                }
                tabuleiro[linha][coluna] = ' ';
            }
        }
    }

    // Verifica se o jogador pode ganhar e bloqueia
    for (linha = 0; linha < 3; linha++) {
        for (coluna = 0; coluna < 3; coluna++) {
            if (tabuleiro[linha][coluna] == ' ') {
                tabuleiro[linha][coluna] = (jogador == 'X') ? 'O' : 'X';
                if (verificarVitoria(tabuleiro, (jogador == 'X') ? 'O' : 'X')) {
                    tabuleiro[linha][coluna] = 'O';
                    return; // Bloqueia o jogador
                }
                tabuleiro[linha][coluna] = ' ';
            }
        }
    }

    // Caso contrário, joga aleatoriamente
    do {
        linha = rand() % 3;
        coluna = rand() % 3;
    } while (tabuleiro[linha][coluna] != ' ');

    tabuleiro[linha][coluna] = 'O';
}

int main() {
    char tabuleiro[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    char jogador, oponente;

    // Escolha quem começa primeiro
    int inicio;
    printf("Escolha quem começa primeiro:\n");
    printf("1. Jogador\n");
    printf("2. Computador\n");
    scanf("%d", &inicio);

    if (inicio == 1) {
        jogador = 'X';
        oponente = 'O';
    } else {
        jogador = 'O';
        oponente = 'X';
    }

    int vezDoJogador = 1; // Variável para alternar entre jogador e computador

    srand(time(NULL)); // Inicializa a semente para geração de números aleatórios

    printf("Bem-vindo ao Jogo da Velha!\n");

    while (1) {
        imprimirTabuleiro(tabuleiro);

        if (vezDoJogador) {
            jogadaJogador(tabuleiro, jogador);
            if (verificarVitoria(tabuleiro, jogador)) {
                imprimirTabuleiro(tabuleiro);
                printf("Parabéns! O jogador %c venceu!\n", jogador);
                break;
            }
        } else {
            jogadaComputador(tabuleiro, oponente);
            if (verificarVitoria(tabuleiro, oponente)) {
                imprimirTabuleiro(tabuleiro);
                printf("O computador venceu!\n");
                break;
            }
        }

        if (tabuleiroCheio(tabuleiro)) {
            imprimirTabuleiro(tabuleiro);
            printf("O jogo terminou em empate!\n");
            break;
        }

        vezDoJogador = !vezDoJogador;
    }

    return 0;
}
