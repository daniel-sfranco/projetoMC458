#include <stdio.h>
#include <stdlib.h>
#include "arvore_utils.c"


typedef struct matriz_composta *p_matriz;

struct matriz_composta {
    int n, m;
	p_no padrao, transposta;
};

p_matriz cria_matriz(int linhas, int colunas) {
    p_matriz matriz = (p_matriz) malloc(sizeof(struct matriz_composta));
    matriz->n = linhas;
	matriz->m = colunas;
	matriz->padrao = NULL;
    matriz->transposta = NULL;
    return matriz;
}

void destroi_matriz(p_matriz matriz){
    destroi_arvore(matriz->padrao);
    destroi_arvore(matriz->transposta);
    free(matriz);
}

void inserir_atualizar_matriz(p_matriz matriz, int dado, int linha, int coluna, int m) {
    matriz->padrao = inserir_atualizar(matriz->padrao, dado, linha, coluna, m);
    matriz->transposta = inserir_atualizar(matriz->transposta, dado, coluna, linha, m);
}

int acessa_posicao(p_matriz matriz, int linha, int coluna, int m) {
    return acessar(matriz->padrao, linha, coluna, m);
}

p_no retorna_transposta(p_matriz matriz){
    return matriz->transposta;
}

void multiplica_escalar_rec(p_no arvore, int escalar){
    if(arvore == NULL)
        return;
    arvore->dado = arvore->dado * escalar;
    multiplica_escalar_rec(arvore->direito, escalar);
    multiplica_escalar_rec(arvore->esquerdo, escalar);
}

void multiplica_escalar(p_matriz matriz, int escalar) {
    multiplica_escalar_rec(matriz->padrao, escalar);
    multiplica_escalar_rec(matriz->transposta, escalar);
}

int main() {
    int k, n, m;
    scanf("%d %d %d", &k, &n, &m);
    while(scanf("%d %d %d", &k, &n, &m) != EOF){
        p_matriz matriz = cria_matriz(n, m);
        
        int dado = 0, linha = 0, coluna = 0;
        for(int i = 0; i < k; i++) {
            scanf("%d %d %d", &dado, &linha, &coluna);
            inserir_atualizar_matriz(matriz, dado, linha, coluna, m);
        }

        /*
        for (int i = 0; i < 2; i++){
            scanf("%d %d", &linha, &coluna);
            printf("%d \n", acessar(matriz->padrao, linha, coluna, m));
        }
        */

        pre_ordem(matriz->padrao);
        printf("\n\n");

        multiplica_escalar(matriz, 3);
        pre_ordem(matriz->padrao);
        printf("\n\n");

        // printf("%d\n", acessa_posicao(matriz, 1, 2));

        destroi_matriz(matriz);
    }
    return 0;
}
