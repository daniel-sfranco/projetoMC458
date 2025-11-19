#include <stdio.h>
#include <stdlib.h>

typedef struct no *p_no;

struct no {
    int chave, altura;
    int dado, linha, coluna;
    p_no esquerdo, direito;
};

int calcula_chave(int linha, int coluna, int m) {
    return (linha * m) + coluna;
}

p_no cria_no(int dado, int linha, int coluna, int m){
    p_no no = (p_no) malloc(sizeof(struct no));
    no->esquerdo = NULL;
    no->direito = NULL;
    no->altura = 1;
    no->dado = dado;
    no->linha = linha;
    no->coluna = coluna;
    no->chave = calcula_chave(linha, coluna, m);
    return no;
}

void destroi_arvore(p_no no) {
    if (no != NULL) {
        destroi_arvore(no->esquerdo);
        destroi_arvore(no->direito);
        free(no);
    }
}

int mede_altura(p_no no){
    if (no == NULL) return 0;
    return no->altura;
}

p_no rotaciona_direita(p_no no) {
    p_no es = no->esquerdo;
    p_no es_dir = es->direito;

    es->direito = no;
    no->esquerdo = es_dir;
    
    no->altura = ((mede_altura(no->esquerdo) > mede_altura(no->direito)) ?
        mede_altura(no->esquerdo) : mede_altura(no->direito)) + 1;

    es->altura = ((mede_altura(es->esquerdo) > mede_altura(es->direito)) ?
        mede_altura(es->esquerdo) : mede_altura(es->direito)) + 1;

    return es;
}

p_no rotaciona_esquerda(p_no no) {
    p_no dir = no->direito;
    p_no dir_es = dir->esquerdo;

    dir->esquerdo = no;
    no->direito = dir_es;

    no->altura = ((mede_altura(no->esquerdo) > mede_altura(no->direito)) ?
        mede_altura(no->esquerdo) : mede_altura(no->direito)) + 1;

    dir->altura = ((mede_altura(dir->esquerdo) > mede_altura(dir->direito)) ?
        mede_altura(dir->esquerdo) : mede_altura(dir->direito)) + 1;

    return dir;
}

p_no inserir_atualizar(p_no no, int dado, int linha, int coluna, int m) {
    if (no == NULL) {
        p_no novo = cria_no(dado, linha, coluna, m);
        return novo;
    }

    int chave = calcula_chave(linha, coluna, m);

    if (chave == no->chave && no->linha == linha && no->coluna == coluna){
        no->dado = dado;
        return no;
    } else if (chave < no->chave)
        no->esquerdo = inserir_atualizar(no->esquerdo, dado, linha, coluna, m);
    else if (chave > no->chave)
        no->direito = inserir_atualizar(no->direito, dado, linha, coluna, m);

    no->altura = ((mede_altura(no->esquerdo) > mede_altura(no->direito)) ?
        mede_altura(no->esquerdo) : mede_altura(no->direito)) + 1;
    
    int fator_b = 0;
    if (no != NULL)
        fator_b = mede_altura(no->esquerdo) - mede_altura(no->direito);

    if (fator_b > 1 && chave < no->esquerdo->chave)
        return rotaciona_direita(no);
    if (fator_b < -1 && chave > no->direito->chave)
        return rotaciona_esquerda(no);
    if (fator_b > 1 && chave > no->esquerdo->chave) {
        no->esquerdo = rotaciona_esquerda(no->esquerdo);
        return rotaciona_direita(no);
    }
    if (fator_b < -1 && chave < no->direito->chave){
        no->direito = rotaciona_direita(no->direito);
        return rotaciona_esquerda(no);
    }

    return no;
}


int acessar(p_no no, int linha, int coluna, int m) {
    if (no == NULL)
        return 0;
    if (no->linha == linha && no->coluna == coluna)
        return no->dado;
    int chave = calcula_chave(linha, coluna, m);
    if (chave < no->chave) {
        return acessar(no->esquerdo, linha, coluna, m);
    } else {
        return acessar(no->direito, linha, coluna, m);
    }
}

void pre_ordem(p_no no) {
    if(no != NULL) {
        printf("%d ", no->dado);
        pre_ordem(no->esquerdo);
        pre_ordem(no->direito);
    }
}

