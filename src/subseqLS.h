#ifndef SUBSEQLS_H
#define SUBSEQLS_H

#include "solucao.h"
#include "subsequence.h"
#include "subseqLS.h"

bool Swap (double** matrizAdj, Solucao &s, std::vector<std::vector<Subsequence>> &subseq_matrix, int n);
bool two_opt (double** matrizAdj, Solucao &s, std::vector<std::vector<Subsequence>> &subseq_matrix, int n);
bool reinsertion (double** matrizAdj, Solucao &s, std::vector<std::vector<Subsequence>> &subseq_matrix, int n, int choice);
void rvnd (double **matrizAdj, Solucao &s, std::vector<std::vector<Subsequence>> &subseq_matrix, int n);

#endif