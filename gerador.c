#include <stdio.h>
#include <stdlib.h>

void gerar_matriz(int dimensao, double esparsidade){
    FILE *arquivo;
    char nome_arquivo[30];
    sprintf(nome_arquivo, "entrada_%d_%.8lf.in", dimensao, esparsidade);
    arquivo = fopen(nome_arquivo, "w");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo.");
        return;
    }
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
        int linha = rand() % tamanho_max;
        int coluna = rand() % tamanho_max;
        fprintf(arquivo, "%d %d %d\n", dado, linha, coluna);
    }
    fprintf(arquivo, "\n");
    printf("Matriz com dimensão %d e esparsidade %lf inserida corretamente no arquivo.\n",dimensao, esparsidade);
    fclose(arquivo);
}

int main(){
    gerar_matriz(2, 0.01);
    gerar_matriz(2, 0.05);
    gerar_matriz(2, 0.1);
    gerar_matriz(2, 0.2);
    gerar_matriz(3, 0.01);
    gerar_matriz(3, 0.05);
    gerar_matriz(3, 0.1);
    gerar_matriz(3, 0.2);
    double esparsidade = 1.0 / (10.0 * 10.0 * 10.0 * 10.0);
    for(int i = 4; i < 7; i++){
        gerar_matriz(i, esparsidade);
        gerar_matriz(i, esparsidade / 10);
        gerar_matriz(i, esparsidade / 100);
        esparsidade /= 10;
    } 
    return 0;
}
