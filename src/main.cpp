#include <iostream>
#include <vector>
#include <ctime>
#include <limits>
#include <chrono>
#include <iomanip>

#include "Data.h"
#include "solucao.h"
#include "construcao.h"
#include "subsequence.h"
#include "subseqLS.h"

using namespace std;

int main(int argc, char** argv)
{
   srand(time(NULL));
   auto data = Data(argc,  argv[1]);
   data.read();
   int n = data.getDimension();
   double **matrizAdj = data.getMatrixCost();

   Solucao s = criarSolucao(matrizAdj, n); //cria a solucao inicial da mesma maneira do TSP
   
   std::vector<std::vector<Subsequence>> subseq_matrix(n+1, std::vector<Subsequence>(n+1)); // criar matriz de subsequencias

   UpdateAllSubseq (s, subseq_matrix, matrizAdj);

   cout << subseq_matrix[0][n].C << "\n";

   rvnd(matrizAdj, s, subseq_matrix, n);

   cout << subseq_matrix[0][n].C;
   
   return 0;
}