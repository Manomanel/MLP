#include <iostream>
#include <vector>
#include <ctime>

#include "Data.h"
#include "construcao.h"
#include "solucao.h"
#include "subsequence.h"

void perturbacao (Solucao &s, std::vector<std::vector<Subsequence>> &subseq_matrix,double** matrizAdj)
{
    
   int pos_i, pos_j, tam_i, tam_j;
   int tam_max = ceil(s.sequencia.size() / 10.);

   if (tam_max <= 2){
      tam_i = 2;
      tam_j = 2;
   } else {
      tam_i = rand() % (tam_max-2)+2;
      tam_j = rand() % (tam_max-2)+2;
   }
    
   pos_i = rand() % (s.sequencia.size()-tam_i-1) + 1;

   do{
      pos_j = rand() % (s.sequencia.size()-tam_j-1) + 1;
   } while (!(pos_j + tam_j < pos_i) && !(pos_j > pos_i + tam_i));

   std::vector<int> aux;

   if (pos_i < pos_j){
      //colocar no vetor auxiliar os valores de J
      for (int j = 0; j < tam_j; j++){
         aux.push_back(s.sequencia[pos_j]);
         s.sequencia.erase(s.sequencia.begin()+pos_j);
      }
      //colocar na posicao de J os valores de I
      for (int i = 0; i < tam_i; i++){
         s.sequencia.insert(s.sequencia.begin()+pos_j, s.sequencia[pos_i]);
         s.sequencia.erase(s.sequencia.begin()+pos_i);
      }
      //insere os valores do vetor aux na solucao na posicao I
      while (!aux.empty()){
         s.sequencia.insert(s.sequencia.begin()+pos_i, aux.back());
         aux.pop_back();
      }
   } else { //para casos em que o vetor J vem antes de I
      for (int i = 0; i < tam_i; i++){
         aux.push_back(s.sequencia[pos_i]);
         s.sequencia.erase(s.sequencia.begin()+pos_i);
      }
      for (int j = 0; j < tam_j; j++){
         s.sequencia.insert(s.sequencia.begin()+pos_i, s.sequencia[pos_j]);
         s.sequencia.erase(s.sequencia.begin()+pos_j);
      }
      while (!aux.empty()){
         s.sequencia.insert(s.sequencia.begin()+pos_j, aux.back());
         aux.pop_back();
      }
   }
   UpdateAllSubseq(s, subseq_matrix, matrizAdj); //substituir pra o especifico
}