#include <stdio.h>
#include <stdlib.h>

#define FATOR 1000

typedef struct matriz {
    int *dados;
    int *linha;
    int *coluna;
} *p_matriz;

p_matriz cria_matriz(int k){
    int tamanho = (FATOR * k);
    p_matriz matriz = (p_matriz) malloc(sizeof(p_matriz));
    matriz->dados = (int *) malloc(tamanho * sizeof(int));
    matriz->linha = (int *) malloc(tamanho * sizeof(int));
    matriz->coluna = (int *) malloc(tamanho * sizeof(int));

    for (int i = 0; i < tamanho; i++) {
        matriz->dados[i] = -1;
        matriz->linha[i] = -1;
        matriz->coluna[i] = -1;
    }

    return matriz;
}

void destroi_matriz(p_matriz matriz){
    free(matriz->dados);
    free(matriz->linha);
    free(matriz->coluna);
    free(matriz);
}

int gera_hash(int i, int j, int k){
    return (((i * j)+(i + j))*1231) % (FATOR * k); // Pelos testes que eu fiz, parece ser uma boa função
}

void inserirOuAtualizar(p_matriz matriz, int valor, int linha, int coluna, int k){
    int posicao = gera_hash(linha, coluna, k);
    for (int i = posicao; i < (FATOR * k); i++){
        if (matriz->linha[i] == -1){
            matriz->dados[i] = valor;
            matriz->linha[i] = linha;
            matriz->coluna[i] = coluna;
            break;
        } else if (matriz->linha[i] == linha && matriz->coluna[i] == coluna){
            matriz->dados[i] = valor;
            break;
        }
    }
}

int acessar(p_matriz matriz, int linha, int coluna, int k) {
    int posicao = gera_hash(linha, coluna, k);
    for (int i = posicao; i < (FATOR * k); i++){
        if (matriz->linha[i] == linha && matriz->coluna[i] == coluna){
            return matriz->dados[i];
        }
        if (matriz->linha[i] == -1) return -1;
    }
    return -1;
}

int main() {
    int n;
    printf("Insira o número de elementos não nulos: \n");
    scanf("%d", &n);
    p_matriz matriz = cria_matriz(n);

    int dado = 0, linha = 0, coluna = 0;
    for(int i = 0; i < n + 1; i++) {
        scanf("%d %d %d", &dado, &linha, &coluna);
        inserirOuAtualizar(matriz, dado, linha, coluna, n);
    }
    
    for(int i = 0; i < FATOR * n; i++) {
        // if (matriz->dados[i] != -1)
            printf("%d %d %d\n", matriz->dados[i], matriz->linha[i], matriz->coluna[i]);
    }

    // para pesquisar os números na matriz
    for (int i = 0; i < 2; i++){
        scanf("%d %d", &linha, &coluna);
        printf("%d \n", acessar(matriz, linha, coluna, n));
    }
    return 0;
}
