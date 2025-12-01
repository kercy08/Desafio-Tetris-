#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ALTURA 20
#define LARGURA 10

// Função para inicializar o campo com pontos '.'
void inicializarCampo(char campo[ALTURA][LARGURA]) {
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            campo[i][j] = '.';
        }
    }
}

// Função para imprimir o campo
void imprimirCampo(char campo[ALTURA][LARGURA]) {
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            printf("%c ", campo[i][j]);
        }
        printf("\n");
    }
}

// Estrutura para representar uma peça
struct Peca {
    int tipo;    // 0 = I, 1 = O
    int altura;  // altura da peça
    int largura; // largura da peça
    char forma[4][4];
};

// Inicializa as formas I e O
void criarPeca(struct Peca *p) {
    int tipo = rand() % 2;
    p->tipo = tipo;

    // Limpa a matriz interna da peça
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            p->forma[i][j] = '.';

    if (tipo == 0) {  
        // Peça I (vertical)
        p->altura = 4;
        p->largura = 1;
        for (int i = 0; i < 4; i++)
            p->forma[i][0] = '#';
    } else {         
        // Peça O (quadrado)
        p->altura = 2;
        p->largura = 2;
        p->forma[0][0] = '#';
        p->forma[0][1] = '#';
        p->forma[1][0] = '#';
        p->forma[1][1] = '#';
    }
}

// Verifica se a peça pode cair (checa colisão)
int podeCair(char campo[ALTURA][LARGURA], struct Peca p, int linha, int coluna) {
    for (int i = 0; i < p.altura; i++) {
        for (int j = 0; j < p.largura; j++) {

            if (p.forma[i][j] == '#') {
                int novaLinha = linha + i + 1;
                int novaColuna = coluna + j;

                // Bateu no chão
                if (novaLinha >= ALTURA)
                    return 0;

                // Bateu em outra peça
                if (campo[novaLinha][novaColuna] == '#')
                    return 0;
            }
        }
    }
    return 1;
}

// "Desenha" a peça no campo
void fixarPeca(char campo[ALTURA][LARGURA], struct Peca p, int linha, int coluna) {
    for (int i = 0; i < p.altura; i++) {
        for (int j = 0; j < p.largura; j++) {
            if (p.forma[i][j] == '#') {
                campo[linha + i][coluna + j] = '#';
            }
        }
    }
}

int main() {
    srand(time(NULL));

    char campo[ALTURA][LARGURA];
    inicializarCampo(campo);

    printf("=== Desafio Tetris Stack Intermediario ===\n");

    // Rodar 5 peças caindo
    for (int rodada = 1; rodada <= 5; rodada++) {
        printf("\n--- Rodada %d ---\n", rodada);

        struct Peca p;
        criarPeca(&p);

        int coluna = rand() % (LARGURA - p.largura);
        int linha = 0;

        // Queda da peça
        while (podeCair(campo, p, linha, coluna)) {
            linha++;
        }

        // Fixar peça no campo
        fixarPeca(campo, p, linha, coluna);

        printf("Campo apos a queda:\n");
        imprimirCampo(campo);
    }

    return 0;
}
