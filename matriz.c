#include <stdio.h>
#include <stdlib.h>

int **cria_matriz(int n, int m){
    int **matriz = (int **) malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++){
        matriz[i] = (int *) malloc(m * sizeof(int));
        for(int j = 0; j < m; j++){
            matriz[i][j] = 0;
        }
    }
    return matriz;
}


void insere_matriz(int dado, int linha, int coluna, int **matriz){
    matriz[linha][coluna] = dado;
}


int acessa_matriz(int linha, int coluna, int **matriz){
    return matriz[linha][coluna];
}


int **retorna_transposta(int **matriz, int n, int m){
    int **transposta = cria_matriz(m, n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            transposta[j][i] = matriz[i][j];
        }
    }
    return transposta;
}


int **soma_matrizes(int **A, int **B, int linha_a, int linha_b, int coluna_a, int coluna_b){
    int linha = (linha_a > linha_b) ? linha_a : linha_b;
    int coluna = (coluna_a > coluna_b) ? coluna_a : coluna_b;
    int **C = cria_matriz(linha, coluna);
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            int dado = 0;
            if(i < linha_a && j < coluna_a)
                dado += A[i][j];
            if(i < linha_b && j < coluna_b)
                dado += B[i][j];
            C[i][j] = dado;
        }
    }
    return C;
}


void multiplica_escalar(int **matriz, int escalar, int n, int m){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            matriz[i][j] *= escalar;
}

int **multiplica_matrizes(int **A, int **B, int linha_a, int linha_b, int coluna_a, int coluna_b){
    if(coluna_a != linha_b)
        return NULL;
    int **C = cria_matriz(linha_a, coluna_b);
    for(int i = 0; i < linha_a; i++){
        for(int j = 0; j < coluna_b; j++){
            int dado = 0;
            for (int k = 0; k < coluna_a; k++){
                dado += A[i][k] * B[k][j];
            }
            C[i][j] = dado;
        }
    }
    return C;
}


int main(){
    int k, n, m;
    int **matriz;
    while(scanf("%d %d %d", &k, &n, &m) != EOF){
        int dado, linha, coluna;
        matriz = cria_matriz(n, m);
        for(int i = 0; i < k; i++){
            scanf("%d %d %d", &dado, &linha, &coluna);
            insere_matriz(dado, linha, coluna, matriz);
        }
    }
    return 0;
}
