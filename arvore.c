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


void inserir_soma_matriz(p_matriz matriz, int dado, int linha, int coluna, int m) {
    matriz->padrao = soma_no(matriz->padrao, dado, linha, coluna, m);
    matriz->transposta = soma_no(matriz->transposta, dado, coluna, linha, m);
}


int acessa_posicao(p_matriz matriz, int linha, int coluna, int m) {
    return acessar(matriz->padrao, linha, coluna, m);
}


void inserir_atualizar_matriz(p_matriz matriz, int dado, int linha, int coluna, int m) {
    matriz->padrao = inserir_atualizar(matriz->padrao, dado, linha, coluna, m);
    matriz->transposta = inserir_atualizar(matriz->transposta, dado, coluna, linha, m);
}


p_no retorna_transposta(p_matriz matriz){
    return matriz->transposta;
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


void busca_linha_B(p_no noB, int linha_B, p_no noA, p_matriz resultado) {
    if(noB == NULL)
        return;

    int tamanho_min = linha_B * resultado->m;
    int tamanho_max = tamanho_min + resultado->m - 1;
    if (noB->chave > tamanho_min){
        busca_linha_B(noB->esquerdo, linha_B, noA, resultado);
    } 
    if (noB->chave < tamanho_max){
        busca_linha_B(noB->direito, linha_B, noA, resultado);
    }
    if (noB->linha == linha_B ){
        int dado_C = noA->dado * noB->dado;
        inserir_soma_matriz(resultado, dado_C, noA->linha, noB->coluna, resultado->m);
    }

}


void recursivo_multiplicar_A(p_no noA, p_matriz B, p_matriz resultado) {
    if(noA == NULL)
        return;

    recursivo_multiplicar_A(noA->esquerdo, B, resultado);
    int linha_B = noA->coluna;
    busca_linha_B(B->padrao, linha_B, noA, resultado);
    recursivo_multiplicar_A(noA->direito, B, resultado);
}


p_matriz multiplicar_matrizes(p_matriz A, p_matriz B) {
    p_matriz resultado = cria_matriz(A->n, B->m);
    recursivo_multiplicar_A(A->padrao, B, resultado);
    return  resultado;
}


int main() {
    int k, n, m;
    while(scanf("%d %d %d", &k, &n, &m) != EOF){
        printf("Iniciando iteração com matriz com %d elementos e tamanho %dx%d\n", k, n, m);
        p_matriz matriz = cria_matriz(n, m);
        int dado = 0, linha = 0, coluna = 0;
        for(int i = 0; i < k; i++) {
            scanf("%d %d %d", &dado, &linha, &coluna);
            inserir_atualizar_matriz(matriz, dado, linha, coluna, m);
            acessa_posicao(matriz, linha, coluna, m);
        }

        p_matriz transposta = cria_matriz(m, n);
        transposta->padrao = retorna_transposta(matriz);
        transposta->transposta = matriz->padrao;

        p_matriz soma_simetrica = soma_matrizes(matriz, transposta);

        multiplica_escalar(matriz, 2);
        multiplica_escalar(transposta, 2);

        p_matriz mult_simetrica = multiplicar_matrizes(matriz, transposta);

        destroi_matriz(matriz);
        free(transposta);
        destroi_matriz(soma_simetrica);
        destroi_matriz(mult_simetrica);
        printf("Matriz com %d elementos e tamanho %dx%d terminada\n", k, n, m);
    }
    return 0;
}
