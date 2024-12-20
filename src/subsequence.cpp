#include <iostream>
#include <vector>
#include <ctime>
#include <cassert>

#include "solucao.h"
#include "subsequence.h"

void Concatenate(double **matrizAdj, Subsequence &sigma_1, Subsequence &sigma_2, Subsequence &sigma)
{
   double temp = matrizAdj[sigma_1.last - 1][sigma_2.first - 1];
   double T = sigma_1.T;
   sigma.W = sigma_1.W + sigma_2.W;
   sigma.T = T + temp + sigma_2.T;
   sigma.C = sigma_1.C + sigma_2.W * (T + temp) + sigma_2.C;
   sigma.first = sigma_1.first;
   sigma.last = sigma_2.last;
}

// depois da soluao incial
void UpdateAllSubseq (Solucao &s, std::vector<std::vector<Subsequence>> &subseq_matrix, double** matrizAdj)
{
   int n = s.sequencia.size();

   // subsequencias de um unico no
   for (int i = 0; i < n; i++){
      subseq_matrix[i][i].W = (i > 0);
      subseq_matrix[i][i].C = 0;
      subseq_matrix[i][i].T = 0;
      subseq_matrix[i][i].first = s.sequencia[i];
      subseq_matrix[i][i].last = s.sequencia[i];
   }

   for (int i = 0; i < n; i++)
      for (int j = i+1; j < n; j++)
         Concatenate(matrizAdj, subseq_matrix[i][j-1], subseq_matrix[j][j], subseq_matrix[i][j]);

   // subsequencias invertidas para o 2-opt   
   for (int i = n - 1; i >= 0; i--)
      for (int j = i - 1; j >= 0; j--)
         Concatenate(matrizAdj, subseq_matrix[i][j+1], subseq_matrix[j][j], subseq_matrix[i][j]);
   
}

// atualiza somente as subsequencias necessarias depois de uma mudança da solução
/*void partSubseqUpdate (std::vector<std::vector<Subsequence>> &subseq_matrix, double** matrizAdj, int k, int l, int n, Solucao &s)
{

   //printf(" K: %d e L: %d\n", k, l);

   for (int i = k; i <= l; i++){
      subseq_matrix[i][i].W = (i > 0);
      subseq_matrix[i][i].C = 0;
      subseq_matrix[i][i].T = 0;
      subseq_matrix[i][i].first = s.sequencia[i];
      subseq_matrix[i][i].last = s.sequencia[i];
      //printf("oi 1\n");
   }

   for (int i = 0; i < k; i++)
      for (int j = k; j < n; j++){
         subseq_matrix[i][j] = Concatenate(matrizAdj, subseq_matrix[i][j-1], subseq_matrix[j][j]);
         //printf("oi 2\n");
      }

   for (int i = k; i <= l; i++)
      for (int j = i + 1; j < n; j++){
         subseq_matrix[i][j] = Concatenate(matrizAdj, subseq_matrix[i][j-1], subseq_matrix[j][j]);
         //printf("oi 3\n");
      }

   for (int i = k; i <= l; i++)
      for (int j = i - 1; j >= 0; j--){
         subseq_matrix[i][j] = Concatenate(matrizAdj, subseq_matrix[i][j+1], subseq_matrix[j][j]);
         //printf("oi 4\n");
      }
         
   for (int i = n - 1; i > l; i--)
      for (int j = l; j >= 0; j--){
         subseq_matrix[i][j] = Concatenate(matrizAdj, subseq_matrix[i][j+1], subseq_matrix[j][j]);
         //printf("oi 5\n");
      }
         
}*/