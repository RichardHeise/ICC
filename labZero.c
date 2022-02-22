#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

int main () {

    // leitura de dados
    Polinomio entrada;
    double x = 0, x_inicial = 0, x_final = 0;
    int iteracoes = 0;

    printf("Digite o grau do polinomio: ");
    scanf("%d", &entrada.grau);

    entrada.p = malloc(sizeof(double) * (entrada.grau+1));

    for (int i = entrada.grau; i >= 0; i--) {
      printf("Digite o valor do coeficiente %d\n", entrada.grau-i+1);
      scanf("%lf", &entrada.p[i]);
    }

    printf("Digite o x_inicial do intervalo: ");
    scanf("%lf", &x_inicial);

    printf("Digite o x_final para o intervalo: ");
    scanf("%lf", &x_final);

    // ---------------------------------------------------------------------------------- //

    double tempo;

    // ---------------------------------------------------------------------------------- //

    printf("\n===================================================================\n");
    printf("Resumo de execução do método da bisseccao\n\n");

    tempo = timestamp();
    printf("O erro é de : %.15lf\n", bisseccao(entrada, x_inicial, x_final, EPS, &iteracoes, &x) );
    printf("raiz: %.15lf\n", x);
    printf("interações: %d\n", iteracoes);
    tempo = timestamp() - tempo;
    printf("Duração: %lf\n\n\n", tempo);
    iteracoes = 0;


    // ---------------------------------------------------------------------------------- //

    printf("\n===================================================================\n");
    printf("Resumo de execução do método de newthonRaphson\n\n");
    
    tempo = timestamp();
    printf("O erro é de : %.15lf\n", newtonRaphson(entrada, x_inicial, EPS, &iteracoes, &x) );
    printf("raiz: %.15lf\n", x);
    printf("interações: %d\n\n\n", iteracoes);
    tempo = timestamp() - tempo;
    printf("Duração: %lf\n\n\n", tempo);
    iteracoes = 0;

    // ---------------------------------------------------------------------------------- //

    printf("\n===================================================================\n");
    printf("Resumo de execução do método da secante\n\n");

    tempo = timestamp();
    printf("O erro é de : %.15lf\n", secante(entrada, x_inicial, x_final, EPS, &iteracoes, &x) );
    printf("raiz: %.15lf\n", x);
    printf("interações: %d\n\n\n", iteracoes);
    tempo = timestamp() - tempo;
    printf("Duração: %lf\n\n\n", tempo);

    printf("\n===================================================================\n");

    // ---------------------------------------------------------------------------------- //

    return 0;

}

