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
   int n = data.getDimension();
   double **matrizAdj = data.getMatrixCost();
   
   int resultado = ILS(matrizAdj, n);

   cout << resultado;
   
   return 0;
}