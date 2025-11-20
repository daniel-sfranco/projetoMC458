#include <stdio.h>
#include <stdlib.h>

void gerar_matriz(int dimensao, double esparsidade, FILE *arquivo){
    int tamanho_max = 1;
    for(int i = 0; i < dimensao; i++)
        tamanho_max *= 10;
    tamanho_max /= 100;
    esparsidade *= 10000;
    long int elementos_totais = tamanho_max * tamanho_max;
    int numero_elementos = elementos_totais * esparsidade;
    tamanho_max *= 100;
    esparsidade /= 10000;
    fprintf(arquivo, "%d %d %d\n", numero_elementos, tamanho_max, tamanho_max);
    for(long int i = 0; i < numero_elementos; i++){
        int dado = rand() + 1;
        int linha = rand() % tamanho_max + 1;
        int coluna = rand() % tamanho_max + 1;
        fprintf(arquivo, "%d %d %d\n", dado, linha, coluna);
    }
    fprintf(arquivo, "\n");
    printf("Matriz com dimensão %d e esparsidade %lf inserida corretamente no arquivo.\n",dimensao, esparsidade);
}

int main(){
    FILE *arquivo;
    arquivo = fopen("entrada.in", "w");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo.");
        return 1;
    }
    gerar_matriz(2, 0.01, arquivo);
    gerar_matriz(2, 0.05, arquivo);
    gerar_matriz(2, 0.1, arquivo);
    gerar_matriz(2, 0.2, arquivo);
    gerar_matriz(3, 0.01, arquivo);
    gerar_matriz(3, 0.05, arquivo);
    gerar_matriz(3, 0.1, arquivo);
    gerar_matriz(3, 0.2, arquivo);
    double esparsidade = 1.0 / (10.0 * 10.0 * 10.0 * 10.0);
    for(int i = 4; i < 7; i++){
        gerar_matriz(i, esparsidade, arquivo);
        gerar_matriz(i, esparsidade / 10, arquivo);
        gerar_matriz(i, esparsidade / 100, arquivo);
        esparsidade /= 10;
    }
    fclose(arquivo);
    return 0;
}
