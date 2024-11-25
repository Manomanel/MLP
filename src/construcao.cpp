#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>//find e sort

#include "Data.h"
#include "construcao.h"
#include "solucao.h"

double valoresAlpha[25] = {
	0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07,
	0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14,
	0.15, 0.16, 0.17, 0.18, 0.19, 0.20, 0.21,
	0.22, 0.23, 0.24, 0.25
};

typedef struct insercao {
    int verticeSelecionado;
    int verticeRemovido;
    double custoInsecao;
} insercao;

void prepararSolucao (Solucao &s, std::vector<int> &candidatos, double **matrizAdj, int dimensao);
void criarInsercoes (Solucao &s, std::vector<int> &candidatos, double **matrizAdj, std::vector<insercao> &lista);
void ordenarLista (std::vector<insercao> &lista);

Solucao criarSolucao (double **matrizAdj, int dimensao)
{
    Solucao s;
    std::vector<int> candidatos;
    //criar a lista de candidatos completa
    for (int i = 2; i <= dimensao; i++){
        candidatos.push_back(i);
    }
    //criar uma solucao parcial com 3 elementos
    prepararSolucao(s, candidatos, matrizAdj, dimensao);
    //lista de possiveis insercoes
    std::vector<insercao> lista;
    //criar e inserir um elemento ate acabar a lista de candidatos
    while (!candidatos.empty()){
        lista.clear();
        criarInsercoes(s, candidatos, matrizAdj, lista);
    }
    calcularValorObj(s, matrizAdj);
    return s;
}

void prepararSolucao (Solucao &s, std::vector<int> &candidatos, double **matrizAdj, int dimensao)
{
    s.sequencia.push_back(1);//inicia e termina com o elemento 1
    for (int i = 0; i < 3; i++){//escolhe 3 candidatos aleatorios
        int rnd = rand() % candidatos.size();
        s.sequencia.push_back(candidatos[rnd]);
        candidatos.erase(candidatos.begin()+rnd);
    }
    s.sequencia.push_back(1);
}

void criarInsercoes (Solucao &s, std::vector<int> &candidatos, double **matrizAdj, std::vector<insercao> &lista)
{
    for (size_t i = 0; i < s.sequencia.size()-1; i++){//cada vertice de S'
        for (size_t j = 0; j < candidatos.size(); j++){//para cada candidato
        
        insercao possivelInsercao;
        int elemento = candidatos[j];
        possivelInsercao.verticeSelecionado = elemento;

        possivelInsercao.custoInsecao = matrizAdj[s.sequencia[i]-1][elemento-1] + matrizAdj[elemento-1][s.sequencia[i+1]-1] - matrizAdj[s.sequencia[i]-1][s.sequencia[i+1]-1];
        possivelInsercao.verticeRemovido = i+1;
        lista.push_back(possivelInsercao);
        }
    }
    ordenarLista(lista);

    double alpha = valoresAlpha[rand() % 25];//escolhe um valor de alpha
    int selecionado = rand() % ((int) ceil(alpha * lista.size()));//escolhe uma insercao dos candidatos grasp

    s.sequencia.emplace(s.sequencia.begin()+lista[selecionado].verticeRemovido, lista[selecionado].verticeSelecionado);//insere a escolhida
    auto iter = std::find(candidatos.begin(), candidatos.end(), lista[selecionado].verticeSelecionado);//procura e remove o elemento selecionado da CL
    candidatos.erase(iter);
}

void ordenarLista (std::vector<insercao> &lista)
{
    std::sort(lista.begin(), lista.end(), [](const insercao& a, const insercao& b) {
    return a.custoInsecao < b.custoInsecao;
    });
}