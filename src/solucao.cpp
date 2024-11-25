#include <iostream>

#include "solucao.h"

void exibirSolucao(Solucao &s)
{
    for(size_t i = 0; i < s.sequencia.size() - 1; i++)
        std::cout << s.sequencia[i] << " -> ";
    std::cout << s.sequencia.back() << std::endl;
}

void calcularValorObj (Solucao &s, double **matrizAdj)
{
    s.valorObj = 0;
    for(size_t i = 0; i < s.sequencia.size() - 1; i++)
    s.valorObj += matrizAdj[s.sequencia[i] - 1][s.sequencia[i+1] - 1];
}