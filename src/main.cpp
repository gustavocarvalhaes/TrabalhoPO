#include <iostream>
#include <glpk.h>
#include <fstream>
#include "planejamento.h"
#include <vector>

/*
TRABALHO DE PESQUISA OPERACIONAL - 2023
ALUNOS: Gustavo Carvalhaes da Fonseca Ferreira - 202065522B
        Daniel Freitas Pereira - 202065118A
*/

/*
    -Para compilar use:
    g++ main.cpp -o <nome_Programa> -lglpk
    -Para executar use:
    ./<nome_Programa> <arquivoDeEntrada> <arquivoDeSaida>
*/

using namespace std;

int main(int argc, char const *argv[]){
    // Verificando os parâmetros do programa
    if (argc != 3) 
    {
        cout << "ERRO: Esperado: ./<nome_Programa> <arquivoDeEntrada> <arquivoDeSaida>" << endl;
        return 1;
    }

    ifstream arquivoEntrada;
    ofstream arquivoSaida;

    arquivoEntrada.open(argv[1], ios::in);
    arquivoSaida.open(argv[2], ios::out | ios::app);
    Planejamento* planejamento = new Planejamento(arquivoEntrada);
    vector<double> resultado = planejamento->solveGlpk();

    arquivoSaida << "==============================================" << endl;
    arquivoSaida << "Solução ótima para a base de dados apresentada" << endl;
    arquivoSaida << "Valor da função objetivo: " << resultado[10] << endl;
    arquivoSaida << "Valores das variáveis de decisão x" << endl;
    for(int i=0; i<planejamento->getNumEncomendas(); i++){
        arquivoSaida << "x" << i+1 << ": " << resultado[i] << endl;
    }
    arquivoSaida << "==============================================" << endl;
    return 0;
}

