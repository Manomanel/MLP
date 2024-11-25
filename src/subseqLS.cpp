#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>//reverse

#include "Data.h"
#include "solucao.h"
#include "subsequence.h"

bool Swap (double** matrizAdj, Solucao &s, std::vector<std::vector<Subsequence>> &subseq_matrix, int n)
{ //swap   [1][i-1]  [j][j] [i+1][j-1] [i][i] [j+1][n]

   double best_delta = 0;
   int best_i, best_j;

   for (int i = 1; i < n; i++){
      for (int j = i+1; j < n; j++){

         Subsequence sigma1 = Concatenate(matrizAdj, subseq_matrix[0][i-1], subseq_matrix[j][j]);
         Subsequence sigma2 = Concatenate(matrizAdj, sigma1, subseq_matrix[i+1][j-1]);
         Subsequence sigma3 = Concatenate(matrizAdj, sigma2, subseq_matrix[i][i]);
         Subsequence sigma4 = Concatenate(matrizAdj, sigma3, subseq_matrix[j+1][n]);

         //Verificação
         if(sigma4.C - subseq_matrix[0][n].C < best_delta){
            best_delta = sigma4.C - subseq_matrix[0][n].C;
            best_i = i;
            best_j = j;
         }
      }
   }
   
   if(best_delta < 0){
      std::swap(s.sequencia[best_i], s.sequencia[best_j]);
      UpdateAllSubseq(s,subseq_matrix, matrizAdj);
      return true;
   }

   return false;
}

bool two_opt (double** matrizAdj, Solucao &s, std::vector<std::vector<Subsequence>> &subseq_matrix, int n)
{ //2-opt  [1][i-1] [j][i] [j+1][n]

   double best_delta = 0;
   int best_i, best_j;   

   for (int i = 1; i < n; i++){
      for (int j = i+1; j < n; j++){

         Subsequence sigma1 = Concatenate(matrizAdj, subseq_matrix[0][i-1], subseq_matrix[j][i]);
         Subsequence sigma2 = Concatenate(matrizAdj, sigma1, subseq_matrix[j+1][n]);

         if(sigma2.C - subseq_matrix[0][n].C < best_delta){
            best_delta = sigma2.C - subseq_matrix[0][n].C;
            best_i = i;
            best_j = j;
         }
      }
   }

   if(best_delta < 0){
      std::reverse(s.sequencia.begin()+best_i, s.sequencia.begin()+best_j+1);
      UpdateAllSubseq(s,subseq_matrix, matrizAdj);
      return true;
   }

   return false;
}

/*
reinsertion if i < j  [1][i-choice] [i+1][j] [i][i+choice-1] [j+1][n]

reinsertion if j < i  [1][j] [i][i+choice-1] [j+1][i-1] [i+choice][n]
*/
bool reinsertion (double** matrizAdj, Solucao &s, std::vector<std::vector<Subsequence>> &subseq_matrix, int n, int choice)
{

   double best_delta = 0;
   int best_i, best_j;   

   for (int i = 1; i < n - 1; i++){
      if ((choice >= 2 && i == n - 2) || (choice == 3 && n - 3))continue;

      for (int j = 0; j < n - 1; j++){
         if (j == i-1 || j == i || (j == i+1 && choice >= 2) || (j == i+2 && choice == 3))continue;

         if (i < j){
            Subsequence sigma1 = Concatenate(matrizAdj, subseq_matrix[0][i-1], subseq_matrix[i+choice][j]);
            Subsequence sigma2 = Concatenate(matrizAdj, sigma1, subseq_matrix[i][i+choice-1]);
            Subsequence sigma3 = Concatenate(matrizAdj, sigma2, subseq_matrix[j+1][n]);
            
            if(sigma3.C - subseq_matrix[0][n].C < best_delta){
               best_delta = sigma3.C - subseq_matrix[0][n].C;
               best_i = i;
               best_j = j;
            }
         }  else {
            Subsequence sigma1 = Concatenate(matrizAdj, subseq_matrix[0][j], subseq_matrix[i][i+choice-1]);
            Subsequence sigma2 = Concatenate(matrizAdj, sigma1, subseq_matrix[j+1][i-1]);
            Subsequence sigma3 = Concatenate(matrizAdj, sigma2, subseq_matrix[i+choice][n]);
            
            if(sigma3.C - subseq_matrix[0][n].C < best_delta){
               best_delta = sigma3.C - subseq_matrix[0][n].C;
               best_i = i;
               best_j = j;
            }
         }
      }
   }
    
   if(best_delta < 0){
      for (int n = 0; n < choice; n++){
         if (best_i < best_j){
            s.sequencia.insert(s.sequencia.begin() + best_j+1, s.sequencia[best_i]);
            s.sequencia.erase(s.sequencia.begin() + best_i);
         } else {
            int teste = s.sequencia[best_i + n];
            s.sequencia.erase(s.sequencia.begin() + best_i + n);
            s.sequencia.insert(s.sequencia.begin() + best_j+1 + n, teste);
         }
      }
      UpdateAllSubseq(s,subseq_matrix, matrizAdj);
      return true;
   }
   return false;
}

void rvnd (double **matrizAdj, Solucao &s, std::vector<std::vector<Subsequence>> &subseq_matrix, int n)
{

   std::vector<int> NL = {1, 2, 3, 4, 5};
   bool improved = false;

   while (NL.empty() == false)
   {
      int k = rand() % NL.size();
      switch (NL[k])
      {
      case 1:
         improved = Swap(matrizAdj, s, subseq_matrix, n);
         break;
      case 2:
         improved = reinsertion(matrizAdj, s, subseq_matrix, n, 1);
         break;
      case 3:
         improved = reinsertion(matrizAdj, s, subseq_matrix, n, 2);
         break;
      case 4:
         improved = reinsertion(matrizAdj, s, subseq_matrix, n, 3);
         break;
      case 5:
         improved = two_opt(matrizAdj, s, subseq_matrix, n);
         break;
      }
      if (improved)
         NL = {1, 2, 3, 4, 5};
      else
         NL.erase(NL.begin() + k);
   }
}