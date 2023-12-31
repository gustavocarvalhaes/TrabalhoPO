#ifndef PLANEJAMENTO_H_INCLUDED
#define PLANEJAMENTO_H_INCLUDED
#include <iostream>
#include <fstream>
#include "encomenda.h"
#include <vector>
/*
TRABALHO DE PESQUISA OPERACIONAL - 2023
ALUNOS: Gustavo Carvalhaes da Fonseca Ferreira - 202065522B
        Daniel Freitas Pereira - 202065118A
*/

using namespace std;

class Planejamento
{
    private: 
        Encomenda* primeiraEncomenda;
        Encomenda* ultimaEncomenda;
        int numEncomendas;
        double diasDeTrabalho;

    public:
        //Leitura somente para o trabalho
        Planejamento(ifstream &arquivoEntrada);
        //Destrutor
        ~Planejamento();
        void insereEncomenda(int id, int tempoDeFabricacao, float custoMaterial, float valorDeVenda);
        vector<double> solveGlpk();
        int getNumEncomendas(){return this->numEncomendas;};
        int resultado[6];
};

#endif