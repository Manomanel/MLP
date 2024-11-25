#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <vector>

typedef struct solucao {
	std::vector<int> sequencia;
	double valorObj;
} Solucao;

void exibirSolucao(Solucao &s);
void calcularValorObj (Solucao &s, double **matrizAdj);

#endif