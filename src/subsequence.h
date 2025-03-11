#ifndef SUBSEQUENCE_H
#define SUBSEQUENCE_H

typedef struct t_subsequence {
   double T, C;
   int W;
   int first, last;
} Subsequence;

inline void Concatenate(double **matrizAdj, Subsequence &sigma_1, Subsequence &sigma_2, Subsequence &sigma)
{
   double temp = matrizAdj[sigma_1.last - 1][sigma_2.first - 1];
   double T = sigma_1.T;
   sigma.W = sigma_1.W + sigma_2.W;
   sigma.T = T + temp + sigma_2.T;
   sigma.C = sigma_1.C + sigma_2.W * (T + temp) + sigma_2.C;
   sigma.first = sigma_1.first;
   sigma.last = sigma_2.last;
}
void UpdateAllSubseq (Solucao &s, std::vector<std::vector<Subsequence>> &subseq_matrix, double** matrizAdj);
void partSubseqUpdate (std::vector<std::vector<Subsequence>> &subseq_matrix, double** matrizAdj, int k, int l, int n, Solucao &s);

#endif