#ifndef PERTURBACAO_H
#define PERTURBACAO_H

#include "subsequence.h"
#include "solucao.h"

void perturbacao (Solucao &s, std::vector<std::vector<Subsequence>> &subseq_matrix, double** matrizAdj);

#endif