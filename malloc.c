#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **dados;
    int inicio;     
    int fim;     
    int tamanho;   
    int capacidade;  
} Fila;


Fila* criarFila(int capacidadeInicial) {
    Fila *fila = (Fila *) malloc(sizeof(Fila));
    if (fila == NULL) return NULL;  

    fila->dados = (void **) malloc(sizeof(void*) * capacidadeInicial);
    if (fila->dados == NULL) {
        free(fila);
        return NULL; 
    }

    fila->inicio = 0;
    fila->fim = -1;
    fila->tamanho = 0;
    fila->capacidade = capacidadeInicial;

    return fila;
}


int enfileirar(Fila *fila, void *elemento) {
    if (fila->tamanho == fila->capacidade) {
        
        void **novaFila = (void **) realloc(fila->dados, sizeof(void*) * fila->capacidade * 2);
        if (novaFila == NULL) return 0; 
        fila->dados = novaFila;
        fila->capacidade *= 2;
    }

    
    fila->fim = (fila->fim + 1) % fila->capacidade;
    fila->dados[fila->fim] = elemento;
    fila->tamanho++;
    return 1; 
}


void* desenfileirar(Fila *fila) {
    if (fila->tamanho == 0) return NULL; 

    void *elementoRemovido = fila->dados[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->capacidade;
    fila->tamanho--;

    return elementoRemovido;
}

int estaVazia(Fila *fila) {
    return (fila->tamanho == 0);
}


void* primeiro(Fila *fila) {
    if (fila->tamanho == 0) return NULL;
    return fila->dados[fila->inicio];
}


void limparFila(Fila *fila) {
    if (fila != NULL) {
        free(fila->dados);  
        free(fila);         
    }
}

int main() {
    Fila *fila = criarFila(2);
    if (fila == NULL) {
        printf("Erro ao criar a fila.\n");
        return 1;
    }

    int a = 1, b = 2, c = 3;

    enfileirar(fila, &a);
    enfileirar(fila, &b);
    enfileirar(fila, &c); 
    int *primeiroElemento = (int *) desenfileirar(fila);
    if (primeiroElemento != NULL) {
        printf("Elemento removido: %d\n", *primeiroElemento);
    }

    primeiroElemento = (int *) primeiro(fila);
    if (primeiroElemento != NULL) {
        printf("Primeiro elemento na fila: %d\n", *primeiroElemento);
    }

    limparFila(fila);
    return 0;
}
