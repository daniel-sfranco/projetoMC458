#include <stdio.h>
#include <stdlib.h>

#define FATOR 1000

typedef struct matriz {
    int tamanho;
    int *dados;
    int *linha;
    int *coluna;
} *p_matriz;

p_matriz cria_matriz(int k){
    int tamanho = (FATOR * k);
    p_matriz matriz = (p_matriz) malloc(sizeof(struct matriz));
    matriz->dados = (int *) malloc(tamanho * sizeof(int));
    matriz->linha = (int *) malloc(tamanho * sizeof(int));
    matriz->coluna = (int *) malloc(tamanho * sizeof(int));
    matriz->tamanho = tamanho;

    for (int i = 0; i < tamanho; i++) {
        matriz->dados[i] = 0;
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
    for (int i = posicao; i < matriz->tamanho; i++){
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

p_matriz retorna_transposta(p_matriz matriz){
    p_matriz transposta = (p_matriz) malloc(sizeof(struct matriz));
    transposta->tamanho = matriz->tamanho;
    transposta->dados = matriz->dados;
    transposta->linha = matriz->coluna;
    transposta->coluna = matriz->linha;
    return transposta;
}

void multiplica_escalar(p_matriz matriz, int escalar){
    for (int i = 0; i < matriz->tamanho; i++)
        if (matriz->linha[i] >= 0)
            matriz->dados[i] *= escalar;
}

p_matriz soma_matrizes(p_matriz A, p_matriz B){
    p_matriz C = cria_matriz((A->tamanho + B->tamanho)/FATOR);
    int k = C->tamanho / FATOR;
    for(int i = 0; i < A->tamanho; i++)
        if(A->linha[i] >= 0)
            inserirOuAtualizar(C, A->dados[i], A->linha[i], A->coluna[i], k);
    printf("\n");
    for(int i = 0; i < C->tamanho; i++)
        if (C->linha[i] != -1)
            printf("%d %d %d %d\n", i, C->dados[i], C->linha[i], C->coluna[i]);
    for(int i = 0; i < B->tamanho; i++){
        if(B->linha[i] != -1){
            int posicao = gera_hash(B->linha[i], B->coluna[i], k);
            for(int j = posicao; j < C->tamanho; j++){
                if(C->linha[j] == -1){
                    C->dados[j] = B->dados[i];
                    C->linha[j] = B->linha[i];
                    C->coluna[j] = B->coluna[i];
                    break;
                } else if (C->linha[j] == B->linha[i] && C->coluna[j] == B->coluna[i]){
                    C->dados[j] += B->dados[i];
                    break;
                }
            }
        }
    }
    return C;
}

int main() {
    int n;
    printf("Insira o número de elementos não nulos: \n");
    while(scanf("%d", &n) != EOF){
        p_matriz matriz = cria_matriz(n);

        int dado = 0, linha = 0, coluna = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d %d %d", &dado, &linha, &coluna);
            inserirOuAtualizar(matriz, dado, linha, coluna, n);
        }
        
        p_matriz transposta = retorna_transposta(matriz);

        printf("\n");
        for(int i = 0; i < matriz->tamanho; i++)
            if (matriz->linha[i] != -1)
                printf("%d %d %d\n", matriz->dados[i], matriz->linha[i], matriz->coluna[i]);

        printf("\n");
        for(int i = 0; i < transposta->tamanho; i++)
            if (transposta->linha[i] != -1)
                printf("%d %d %d\n", transposta->dados[i], transposta->linha[i], transposta->coluna[i]);

        p_matriz soma_simetrica = soma_matrizes(matriz, transposta);

        printf("\n");
        for(int i = 0; i < soma_simetrica->tamanho; i++)
            if (soma_simetrica->linha[i] != -1)
                printf("%d %d %d %d\n", i, soma_simetrica->dados[i], soma_simetrica->linha[i], soma_simetrica->coluna[i]);

        /*
        for (int i = 0; i < 2; i++){
            scanf("%d %d", &linha, &coluna);
            printf("%d \n", acessar(matriz, linha, coluna, n));
        }
        */

        /*
        p_matriz transposta = retorna_transposta(matriz);
        for(int i = 0; i < FATOR * n; i++) {
            if(transposta->linha[i] != -1) {
                printf("%d %d %d\n", transposta->dados[i], transposta->linha[i], transposta->coluna[i]);
            }
        }
        */
        destroi_matriz(matriz);
        destroi_matriz(soma_simetrica);
        free(transposta);
        printf("Insira o número de elementos não nulos: \n");
    }
    return 0;
}
