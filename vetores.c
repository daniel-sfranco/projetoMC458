#include <stdio.h>
#include <stdlib.h>


#define FATOR 50


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
    
    long long teste = (((long long)i * (long long)j) + ((long long)i + (long long)j)) * 1231;
    
    int resultado = (int)(teste % (long long)(FATOR * k));
    
    return resultado;
}


int acessar(p_matriz matriz, int linha, int coluna, int k) {
    long int posicao = gera_hash(linha, coluna, k);
    for (long int i = posicao; i < (FATOR * k); i++){
        if (matriz->linha[i] == linha && matriz->coluna[i] == coluna){
            return matriz->dados[i];
        }
        if (matriz->linha[i] == -1) return -1;
    }
    return -1;
}


void inserirOuAtualizar(p_matriz matriz, int valor, int linha, int coluna, int k){
    int posicao = gera_hash(linha, coluna, k);
    int inserido = 0;
    for (int i = posicao; i < (FATOR * k); i++){
        if (matriz->linha[i] == -1){
            matriz->dados[i] = valor;
            matriz->linha[i] = linha;
            matriz->coluna[i] = coluna;
            inserido = 1;
            break;
        } else if (matriz->linha[i] == linha && matriz->coluna[i] == coluna){
            matriz->dados[i] = valor;
            inserido = 1;
            break;
        }
    }
    if(inserido == 0){
        for (int i = 0; i < posicao; i++){
            if (matriz->linha[i] == -1){
                matriz->dados[i] = valor;
                matriz->linha[i] = linha;
                matriz->coluna[i] = coluna;
                inserido = 1;
                break;
            } else if (matriz->linha[i] == linha && matriz->coluna[i] == coluna){
                matriz->dados[i] = valor;
                inserido = 1;
                break;
            }
        }
    }
}


p_matriz retorna_transposta(p_matriz matriz){
    p_matriz transposta = (p_matriz) malloc(sizeof(struct matriz));
    transposta->tamanho = matriz->tamanho;
    transposta->dados = matriz->dados;
    transposta->linha = matriz->coluna;
    transposta->coluna = matriz->linha;
    return transposta;
}


p_matriz soma_matrizes(p_matriz A, p_matriz B){
    p_matriz C = cria_matriz((A->tamanho + B->tamanho)/FATOR);
    int k = C->tamanho / FATOR;
    for(int i = 0; i < A->tamanho; i++)
        if(A->linha[i] >= 0)
            inserirOuAtualizar(C, A->dados[i], A->linha[i], A->coluna[i], k);
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

void multiplica_escalar(p_matriz matriz, int escalar){
    for (int i = 0; i < matriz->tamanho; i++)
        if (matriz->linha[i] >= 0)
            matriz->dados[i] *= escalar;
}


void inserir_somando(p_matriz matriz, int valor, int linha, int coluna, int k){
    int posicao = gera_hash(linha, coluna, k);
    for (int i = posicao; i < matriz->tamanho; i++){
        if (matriz->linha[i] == -1){
            matriz->dados[i] = valor;
            matriz->linha[i] = linha;
            matriz->coluna[i] = coluna;
            break;
        } else if (matriz->linha[i] == linha && matriz->coluna[i] == coluna){
            matriz->dados[i] += valor;
            if (matriz->dados[i] == 0){
                matriz->linha[i]  = -1;
                matriz->coluna[i] = -1;
            }
            break;
        }
    }
}
 


p_matriz multiplicar_matrizes(p_matriz A, p_matriz B){
    if (A->coluna != B->linha){
        printf("O número de COlunas de A deve ser igual ao de Linhas de B\n");
        return NULL;
    }
    
    int tamanho_c = (A->tamanho + B->tamanho)/FATOR; // ka+kb
    p_matriz resultado = cria_matriz(tamanho_c);

    for (int i=0; i<A->tamanho; i++){
        if (A->linha[i] != -1){
            for (int j=0; j<B->tamanho; j++){
                if (B->linha[j] != -1){
                    if (A->coluna[i] == B->linha[j]){
                        inserir_somando(resultado,(A->dados[i] * B->dados[j]), A->linha[i], B->coluna[j], tamanho_c);
                        
                    }
                }

            }
        }
    }

    return resultado;
}


int main() {
    int k, n, m;
    while(scanf("%d %d %d", &k, &n, &m) != EOF){
        printf("Iniciando iteração com matriz com %d elementos e tamanho %dx%d\n", k, n, m);
        p_matriz matriz = cria_matriz(k);

        int dado = 0, linha = 0, coluna = 0;
        for(int i = 0; i < k; i++) {
            scanf("%d %d %d", &dado, &linha, &coluna);
            inserirOuAtualizar(matriz, dado, linha, coluna, k);
            acessar(matriz, linha, coluna, k);
        }
        
        p_matriz transposta = retorna_transposta(matriz);

        p_matriz soma_simetrica = soma_matrizes(matriz, transposta);

        destroi_matriz(matriz);
        destroi_matriz(soma_simetrica);
        free(transposta);
        printf("Matriz com %d elementos e tamanho %dx%d terminada\n", k, n, m);
    }
    return 0;
}
