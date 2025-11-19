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


p_no soma_matrizes_rec(p_no no1, p_no resultado, int m) {
	if (no1 == NULL) return NULL;
	resultado = inserir_somar(resultado, no1->dado, no1->linha, no1->coluna, m);
    soma_matrizes_rec(no1->esquerdo, resultado, m);
    soma_matrizes_rec(no1->direito, resultado, m);
	return resultado;
}

p_matriz soma_matrizes(p_matriz matriz1, p_matriz matriz2) {
	p_matriz matriz3 = cria_matriz(matriz1->n, matriz1->m);
	matriz3->padrao = soma_matrizes_rec(matriz1->padrao, matriz3->padrao, matriz3->m);
	matriz3->padrao = soma_matrizes_rec(matriz2->padrao, matriz3->padrao, matriz3->m);

	matriz3->transposta = soma_matrizes_rec(matriz1->transposta, matriz3->transposta, matriz3->m);
	matriz3->transposta = soma_matrizes_rec(matriz2->transposta, matriz3->transposta, matriz3->m);

	return matriz3;
}

int main() {
    int k, n, m;
    scanf("%d %d %d", &k, &n, &m);
    p_matriz matriz1 = cria_matriz(n, m);
    
    int dado = 0, linha = 0, coluna = 0;
    for(int i = 0; i < k; i++) {
        scanf("%d %d %d", &dado, &linha, &coluna);
        inserir_atualizar_matriz(matriz1, dado, linha, coluna, m);
    }

    scanf("%d", &k);
    p_matriz matriz2 = cria_matriz(n, m);
    for(int i = 0; i < k; i++) {
        scanf("%d %d %d", &dado, &linha, &coluna);
        inserir_atualizar_matriz(matriz2, dado, linha, coluna, m);
    }

    pre_ordem(matriz1->padrao);
    printf("\n\n");
    pre_ordem(matriz2->padrao);
    printf("\n\n");
	
	p_matriz matriz3 = soma_matrizes(matriz1, matriz2);
    pre_ordem(matriz3->padrao);
    printf("\n\n");

    destroi_matriz(matriz1);
    destroi_matriz(matriz2);
    destroi_matriz(matriz3);
    
	return 0;
}
