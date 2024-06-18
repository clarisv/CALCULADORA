#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include "calc.h"

#define MAX_EXP_SIZE 100
#define OPERATORS "+-*/^"

void startPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int pilhaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

int pilhaCheia(Pilha *pilha) {
    return pilha->topo == MAX_EXP_SIZE - 1;
}

void push(Pilha *pilha, char *item) {
    if (pilhaCheia(pilha)) {
        printf("Pilha esta cheia\n");
        exit(1);
    }
    pilha->items[++(pilha->topo)] = strdup(item);
}

char *pop(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        printf("Pilha esta vazia\n");
        exit(1);
    }
    return pilha->items[(pilha->topo)--];
}

bool isOper(char operador) {
    return strchr(OPERATORS, operador) != NULL;
}

bool isFunc(char *funcao) {
    return (strcmp(funcao, "sen") == 0 || strcmp(funcao, "cos") == 0 ||
            strcmp(funcao, "tan") == 0 || strcmp(funcao, "log") == 0);
}

float evalPosfixa(char *posFixada) {
    Pilha pilha;
    startPilha(&pilha);
    char *token = strtok(posFixada, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&pilha, token);
        }
        else if (isOper(token[0]) && strlen(token) == 1) {
            float b = atof(pop(&pilha));
            float a = atof(pop(&pilha));
            float result;
            switch (token[0]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
                case '^':
                    result = powf(a, b);
                    break;
                default:
                    result = 0.0;
                    break;
            }
            char resultStr[32];
            snprintf(resultStr, sizeof(resultStr), "%f", result);
            push(&pilha, resultStr);
        } else if (isFunc(token)) {
            float valor = atof(pop(&pilha));
            float result;
            float rad = valor * (3.141592 / 180);
            if (strcmp(token, "sen") == 0) {
                result = sinf(rad);
            } else if (strcmp(token, "cos") == 0) {
                result = cosf(rad);
            } else if (strcmp(token, "tan") == 0) {
                result = tanf(rad);
            } else if (strcmp(token, "log") == 0) {
                result = log10f(valor);
            } else {
                result = 0.0;
            }
            char resultStr[32];
            snprintf(resultStr, sizeof(resultStr), "%f", result);
            push(&pilha, resultStr);
        }
        token = strtok(NULL, " ");
    }
    return atof(pop(&pilha));
}

char *getFormaInFixa(char *Str) {
    static char infix[512];
    Pilha pilha;
    startPilha(&pilha);

    char *token = strtok(Str, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&pilha, token);
        } else if (isOper(token[0]) && strlen(token) == 1) {
            char *b = pop(&pilha);
            char *a = pop(&pilha);
            char expr[512];
            snprintf(expr, sizeof(expr), "(%s %c %s)", a, token[0], b);
            push(&pilha, expr);
            free(a);
            free(b);
        } else if (isFunc(token)) {
            char *a = pop(&pilha);
            char expr[512];
            snprintf(expr, sizeof(expr), "%s(%s)", token, a);
            push(&pilha, expr);
            free(a);
        }
        token = strtok(NULL, " ");
    }
    strcpy(infix, pop(&pilha));
    return infix;
}

float getValor(char *Str) {
    char postfix[512];
    strcpy(postfix, Str);  // Copiando a string para não modificar o argumento original
    return evalPosfixa(postfix);
}
#define MAX_EXP_SIZE 100
#define OPERADORES "+-*/^"

int main() {

    // Mudar a expressão
    char entryPosfixada[] = "0.5 45 sen 2 ^ +";

    Expressao exp;

    strcpy(exp.posFixa, entryPosfixada);
    exp.Valor = getValor(exp.posFixa);
    strcpy(exp.inFixa, getFormaInFixa(exp.posFixa));

    printf("\nExpressao no formato posfixado: %s\n", entryPosfixada);
    printf("Expressao no formato infixado: %s\n", exp.inFixa);
    printf("Valor final da expressao: %.2f\n", exp.Valor);

    printf("\n\t\tPara altera os valores das entradas pos fixas, altere na função main\n\n");

    return 0;
}
