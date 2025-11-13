#include <stdio.h>
#include <stdlib.h>

typedef struct matriz {
    int *dados;
    int *linha;
    int *coluna;
} *p_matriz;

p_matriz cria_matriz(int n){
    p_matriz matriz = (p_matriz) malloc(sizeof(p_matriz));
    matriz->dados = (int *) malloc(n * sizeof(int));
    matriz->linha = (int *) malloc(n * sizeof(int));
    matriz->coluna = (int *) malloc(n * sizeof(int));
    return matriz;
}

void destroi_matriz(p_matriz matriz){
    free(matriz->dados);
    free(matriz->linha);
    free(matriz->coluna);
    free(matriz);
}

int main() {
    int n;
    printf("Insira o número de elementos não nulos: ");
    scanf("%d", &n);
    p_matriz matriz = cria_matriz(n);
    for(int i = 0; i < n; i++) {
        scanf("%d %d %d", &matriz->dados[i], &matriz->linha[i], &matriz->coluna[i]);
    }
    for(int i = 0; i < n; i++) {
        printf("%d %d %d\n", matriz->dados[i], matriz->linha[i], matriz->coluna[i]);
    }
    return 0;
}
