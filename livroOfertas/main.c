#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int posicao;
    float valor;
    int quantidade;
    struct oferta *prox;
} oferta;

typedef struct {
    int posicao;
    int acao;
    float valor;
    int quantidade;
} input_acao;

typedef struct {
    oferta *inicio;
}Lista;

void inserir_lista_oferta(Lista *lista, oferta of){
    oferta *novo = (oferta*) malloc(sizeof(of));
    novo->posicao = of.posicao;
    novo->valor = of.valor;
    novo->quantidade = of.quantidade;
    novo->prox = NULL;

    if(lista->inicio == NULL){
        lista->inicio = novo;
    }else{
        oferta *fim = lista->inicio;
        while(fim->prox != NULL){
            fim = fim->prox;
        }
        fim->prox = novo;
    }
}
void imprimir(Lista *lista){
    oferta *inicio = lista->inicio;
    while(inicio != NULL){
        printf("%d, %.2f, %d\n", inicio->posicao, inicio->valor, inicio->quantidade);
        inicio = inicio->prox;
    }
}

void ordenar_ofertar_por_posicao_asc(Lista *lista) {
    oferta *inicio = lista->inicio;
    while(inicio != NULL){
        oferta *proximo = inicio->prox;
        while(proximo != NULL){
            if(inicio->posicao > proximo->posicao){
                int posicao = inicio->posicao;
                float valor = inicio->valor;
                int quantidade = inicio->quantidade;

                inicio->posicao = proximo->posicao;
                inicio->valor = proximo->valor;
                inicio->quantidade = proximo->quantidade;

                proximo->posicao = posicao;
                proximo->valor = valor;
                proximo->quantidade = quantidade;
            }
            proximo = proximo->prox;       
        }
        inicio = inicio->prox;
    }   
}
void adicionar_oferta(Lista **lista, input_acao acao, int posicao_anterior){
    oferta *aux ,*novo = (oferta*) malloc(sizeof(oferta));
    if(novo){
        novo->posicao = acao.posicao;
        novo->valor = acao.valor;
        novo->quantidade = acao.quantidade;
        if(*lista == NULL){
            novo->prox = NULL;
            *lista = novo;
        }else{
            aux = *lista;
            if(posicao_anterior == 0){
                novo->prox = aux;
                *lista = novo;
            while (novo->prox != NULL){
                oferta *proximo = novo->prox;
                proximo->posicao++;
                novo = proximo;
                }
                return;
            }
            if(posicao_anterior == -1){
                while(aux->prox != NULL){
                    aux = aux->prox;
                }
                novo->posicao = aux->posicao + 1;
                inserir_lista_oferta(*&lista, *novo);
                return;
            }
            while(aux->posicao != posicao_anterior && aux->prox != NULL){
                aux = aux->prox;
            }
            novo->prox = aux->prox;
            aux->prox = novo;
            while (novo->prox != NULL)
            {
                oferta *proximo = novo->prox;
                proximo->posicao++;
                novo = proximo;
            }
            
        }

    }else{
        printf("Erro ao alocar memoria\n");
    }
    
}
void modificar_oferta(Lista *lista, input_acao acao){
    oferta *inicio = lista->inicio;
    while(inicio != NULL){
        if(inicio->posicao == acao.posicao){
            if(acao.valor > 0){
                inicio->valor = acao.valor;
            }
            if(acao.quantidade > 0){
                inicio->quantidade = acao.quantidade;
            }
        }
        inicio = inicio->prox;
    }
}
int buscar_oferta_por_posicao(Lista **lista, int posicao){
    oferta *aux = *lista;
    oferta *oferta_encontrada = NULL;
    if(posicao == 0){
        return 0;
    }
    while(aux != NULL){
        if(aux->posicao == posicao){
            oferta_encontrada = aux;
            return oferta_encontrada->posicao;
        }
        aux = aux->prox;
    }
    return -1;
}

oferta* remover_oferta(Lista **lista, int posicao){
    oferta *aux = *lista;
    oferta *oferta_removida = NULL;

    if(aux->posicao == posicao){
        oferta_removida = aux;
        *lista = oferta_removida->prox;
        oferta *proximo = aux->prox;
        while(proximo != NULL){
            if(proximo->posicao > posicao){
                proximo->posicao--;
            }
            proximo = proximo->prox;
        }
    }else{
        aux = *lista;
        oferta *proximo = aux->prox;
        while(aux->prox != NULL &&  proximo->posicao != posicao){
            aux = aux->prox;
            proximo = aux->prox;
        }
        if(proximo){
            oferta_removida = proximo;
            aux->prox = proximo->prox;
        }
        while(proximo != NULL){
            if(proximo->posicao > posicao){
                proximo->posicao--;
            }
            proximo = proximo->prox;
        }
    }
    return oferta_removida;
}

void recebe_input_nmro_notificoes(int* nmro_notificacoes){
    int input_nmro_notificacoes = 0;
    scanf("%d", &input_nmro_notificacoes);
    while(input_nmro_notificacoes <= 0){
        printf("Digite um numero de notificacoes maior que 0\n");
        scanf("%d", &input_nmro_notificacoes);
    }
    *nmro_notificacoes = input_nmro_notificacoes;
}
void recebe_input_acao(input_acao* acao){
    int input_posicao = 0;
    int input_acao = 0;
    float input_valor = 0;
    int input_quantidade = 0;
    scanf("%d, %d, %f, %d", &input_posicao, &input_acao, &input_valor, &input_quantidade);
    (*acao).acao = input_acao;
    (*acao).posicao = input_posicao;
    (*acao).valor = input_valor;
    (*acao).quantidade = input_quantidade;
}
int main(void){

    oferta livro_de_ofertas[9] = {
        {.posicao = 1, .valor= 15.4, .quantidade = 50 },
        {.posicao = 2, .valor= 15.4, .quantidade = 10 },
        {.posicao = 3, .valor= 15.9, .quantidade = 20 },
        {.posicao = 4, .valor= 16.1, .quantidade = 100 },
        {.posicao = 5, .valor= 16.20, .quantidade = 20 },
        {.posicao = 6, .valor= 16.43, .quantidade = 30 },
        {.posicao = 7, .valor= 17.20, .quantidade = 70 },
        {.posicao = 8, .valor= 17.35, .quantidade = 80 },
        {.posicao = 9, .valor= 17.50, .quantidade = 200 },
};

    int input_nmro_notificacoes = 0;
    recebe_input_nmro_notificoes(&input_nmro_notificacoes);
    input_acao acoes[input_nmro_notificacoes];
    for(int i = 0; i < input_nmro_notificacoes; i++){
        recebe_input_acao(&acoes[i]);
    }
    // Cria lista de ofertas e insere as ofertas
    Lista lt_ofertas;
    lt_ofertas.inicio = NULL;

    for(int i = 0; i < 9; i++){
        inserir_lista_oferta(&lt_ofertas, livro_de_ofertas[i]);
    }
    for(int i = 0; i < input_nmro_notificacoes; i++){
        if(acoes[i].acao == 0 && (acoes[i].posicao == 0 || acoes[i].quantidade == 0 || acoes[i].valor == 0)){
            continue;
        }
        oferta of = {acoes[i].posicao, acoes[i].valor, acoes[i].quantidade};

        switch (acoes[i].acao){
        case 0:
            int of_anterior = buscar_oferta_por_posicao(&lt_ofertas, acoes[i].posicao - 1);
            adicionar_oferta(&lt_ofertas, acoes[i], of_anterior);
            ordenar_ofertar_por_posicao_asc(&lt_ofertas);
            continue;
        case 1:
            modificar_oferta(&lt_ofertas, acoes[i]);
            ordenar_ofertar_por_posicao_asc(&lt_ofertas);
            continue;

        case 2:
            oferta *oferta_removida = remover_oferta(&lt_ofertas, acoes[i].posicao);
            free(oferta_removida);
            ordenar_ofertar_por_posicao_asc(&lt_ofertas);
            continue;
        default:
            continue;
        }
    
    }

    imprimir(&lt_ofertas);
    return 0;
}