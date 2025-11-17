#include <stdio.h>
#include <stdlib.h>
#include "arvore_utils.c"


typedef struct matriz_composta *p_matriz;

struct matriz_composta {
    p_no padrao, transposta;
};

p_matriz cria_matriz() {
    p_matriz matriz = (p_matriz) malloc(sizeof(struct matriz_composta));
    matriz->padrao = NULL;
    matriz->transposta = NULL;
    return matriz;
}

void destroi_matriz(p_matriz matriz){
    destroi_arvore(matriz->padrao);
    destroi_arvore(matriz->transposta);
    free(matriz);
}

void inserir_atualizar_matriz(p_matriz matriz, int dado, int linha, int coluna) {
    matriz->padrao = inserir_atualizar(matriz->padrao, dado, linha, coluna);
    matriz->transposta = inserir_atualizar(matriz->transposta, dado, coluna, linha);
}

void pre_ordem(p_no no)
{
    if(no != NULL)
    {
        printf("%d ", no->dado);
        pre_ordem(no->esquerdo);
        pre_ordem(no->direito);
    }
}

int main(){
    p_matriz matriz = cria_matriz();
    int k;
    scanf("%d", &k);
    
    int dado = 0, linha = 0, coluna = 0;
    for(int i = 0; i < k + 1; i++) {
        scanf("%d %d %d", &dado, &linha, &coluna);
        inserir_atualizar_matriz(matriz, dado, linha, coluna);
    }

    for (int i = 0; i < 2; i++){
        scanf("%d %d", &linha, &coluna);
        printf("%d \n", acessar(matriz->padrao, linha, coluna));
    }



    pre_ordem(matriz->padrao);
    printf("\n");

    destroi_matriz(matriz);
    return 0;
}