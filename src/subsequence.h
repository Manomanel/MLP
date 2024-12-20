#ifndef SUBSEQUENCE_H
#define SUBSEQUENCE_H

typedef struct t_subsequence {
   double T, C;
   int W;
   int first, last;
} Subsequence;

void Concatenate(double **matrizAdj, Subsequence &sigma_1, Subsequence &sigma_2, Subsequence &sigma);
void UpdateAllSubseq (Solucao &s, std::vector<std::vector<Subsequence>> &subseq_matrix, double** matrizAdj);
void partSubseqUpdate (std::vector<std::vector<Subsequence>> &subseq_matrix, double** matrizAdj, int k, int l, int n, Solucao &s);

#endif