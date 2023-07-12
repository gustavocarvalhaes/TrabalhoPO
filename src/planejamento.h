#ifndef PLANEJAMENTO_H_INCLUDED
#define PLANEJAMENTO_H_INCLUDED
#include <iostream>
#include <fstream>
#include <encomenda.h>
#include <vector>


using namespace std;

class Planejamento
{
    private: 
        Encomenda* primeiraEncomenda;
        Encomenda* ultimaEncomenda;
        int numEncomendas;
        int diasDeTrabalho;
    
    public:
        //Leitura somente para o trabalho
        Planejamento(ifstream &arquivoEntrada);
        //Destrutor
        ~Planejamento();
        void insereEncomenda(int id, float custoMaterial, float valorDeVenda, int tempoDeFabricacao);
        void solveGlpk(ifstream &arquivoSaida);
        int getNumEncomendas(){return this->numEncomendas;};
};

#endif