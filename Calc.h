#include <stdbool.h>
#ifndef CALC_H
#define CALC_H
#define MAX_EXP_SIZE 100

typedef struct {
    char posFixa[512];
    char inFixa[512];
    float Valor;
} Expressao;

typedef struct {
    int topo;
    char *items[MAX_EXP_SIZE];
} Pilha;

char *getFormaInFixa(char *Str);
float getValor(char *Str);
void startPilha(Pilha *pilha);
int pilhaVazia(Pilha *pilha);
int pilhaCheia(Pilha *pilha);
void push(Pilha *pilha, char *item);
char *pop(Pilha *pilha);
bool isOper(char operador);
bool isFunc(char *funcao);
float evalPosfixa(char *posFixada);
char *getFormaInFixa(char *Str);
float getValor(char *Str);
#endif
