#include <iostream>
#include <vector>
#include <ctime>
#include <limits>
#include <chrono>
#include <iomanip>

#include "solucao.h"
#include "subsequence.h"
#include "construcao.h"
#include "subseqLS.h"
#include "perturbacao.h"

int ILS(double **matrizAdj, int dimensao)
{
   int maxIterIls, maxIter = 50;
   if (dimensao >= 150){
      maxIterIls = dimensao/2;
   } else {maxIterIls = dimensao;}

   float avarageScore = 0;
   
   for (int a = 0; a < 10; a++){
      //inicio do ILS
      Solucao bestOfAll;
      std::vector<std::vector<Subsequence>> subseq_matrix_BOA(dimensao+1, std::vector<Subsequence>(dimensao+1)); // criar matriz de subsequencias
      subseq_matrix_BOA[0][dimensao].C = std::numeric_limits<double>::max();

      for (int i = 0; i < maxIter; i++){
         Solucao s = criarSolucao (matrizAdj, dimensao);
         std::vector<std::vector<Subsequence>> subseq_matrix(dimensao+1, std::vector<Subsequence>(dimensao+1));
         UpdateAllSubseq(s, subseq_matrix, matrizAdj);
         Solucao best = s;
         std::vector<std::vector<Subsequence>> subseq_matrix_best = subseq_matrix;

         int iterIls = 0;

         while (iterIls <= maxIterIls){
            rvnd(matrizAdj, s, subseq_matrix, dimensao);
            if (subseq_matrix[0][dimensao].C < subseq_matrix_best[0][dimensao].C){
               best = s;
               subseq_matrix_best =subseq_matrix;
               iterIls = 0;
            }
            
            s = best;
            subseq_matrix = subseq_matrix_best;
            perturbacao(s, subseq_matrix, matrizAdj);
            iterIls++;
         }
         if (subseq_matrix_best[0][dimensao].C < subseq_matrix_BOA[0][dimensao].C){
            bestOfAll = best;
            subseq_matrix_BOA = subseq_matrix_best;
         }
      }
      avarageScore += subseq_matrix_BOA[0][dimensao].C;
   }
   avarageScore /= 10;

   return avarageScore;
}