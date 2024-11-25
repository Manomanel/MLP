#include <iostream>
#include <vector>
#include <ctime>

#include "solucao.h"
#include "subsequence.h"

Subsequence Concatenate(double **matrizAdj, Subsequence &sigma_1, Subsequence &sigma_2)
   {
      Subsequence sigma;
      double temp = matrizAdj[sigma_1.last - 1][sigma_2.first - 1];
      sigma.W = sigma_1.W + sigma_2.W;
      sigma.T = sigma_1.T + temp + sigma_2.T;
      sigma.C = sigma_1.C + sigma_2.W * (sigma_1.T + temp) + sigma_2.C;
      sigma.first = sigma_1.first;
      sigma.last = sigma_2.last;
 
      return sigma;
   }

// depois da soluao incial
void UpdateAllSubseq (Solucao &s, std::vector<std::vector<Subsequence>> &subseq_matrix, double** matrizAdj)
{
   int n = s.sequencia.size();

   // subsequencias de um unico no
   for (int i = 0; i < n; i++){
      int v = s.sequencia[i];
      subseq_matrix[i][i].W = (i > 0);
      subseq_matrix[i][i].C = 0;
      subseq_matrix[i][i].T = 0;
      subseq_matrix[i][i].first = s.sequencia[i];
      subseq_matrix[i][i].last = s.sequencia[i];
   }
   
   for (int i = 0; i < n; i++)
      for (int j = i+1; j < n; j++)
         subseq_matrix[i][j] = Concatenate(matrizAdj, subseq_matrix[i][j-1], subseq_matrix[j][j]);

   // subsequencias invertidas para o 2-opt   
   for (int i = n - 1; i >= 0; i--)
      for (int j = i - 1; j >= 0; j--)
         subseq_matrix[i][j] = Concatenate(matrizAdj, subseq_matrix[i][j+1], subseq_matrix[j][j]);
   
}