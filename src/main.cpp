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
#include "ILS.h"

using namespace std;

int main(int argc, char** argv)
{
   srand(time(NULL));
   auto data = Data(argc,  argv[1]);
   data.read();

   auto before = std::chrono::high_resolution_clock::now();

   int n = data.getDimension();
   double **matrizAdj = data.getMatrixCost();
   
   float resultado = ILS(matrizAdj, n);

   auto after = std::chrono::high_resolution_clock::now();
   cout << (std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() /10) << "\n";
   cout << setprecision(8) << resultado << "\n";
   
   return 0;
}