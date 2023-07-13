#include <iostream>
#include <glpk.h>
#include <fstream>
#include "planejamento.h"
#include <vector>

/*
    -Para compilar use:
    g++ main.cpp -o trabalhopo -lglpk
    -Para executar use:
    ./trabalhopo <input_file>
*/

using namespace std;

struct Problema {
    int NumVarDec;
    int NumVarProd;
    int NumConstraints;
};


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

    // solveGlpk(readFile(input_file));
    
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


void solveGlpk(Problema prob){
    glp_prob *lp;
    lp = glp_create_prob();
    glp_set_obj_dir(lp, GLP_MAX); // Direção da função objetivo

    // Definir limites inferiores e superiores para as variáveis
    glp_add_cols(lp, prob.NumVarDec);

    // Definir coeficientes da função objetivo
    for (int i = 1; i <= prob.NumVarDec; i++)
    {
        glp_set_col_bnds(lp, i, GLP_LO, 0.0, 0.0); // limite inferior = 0, limite superior = 0 (sem restrição)
        glp_set_obj_coef(lp, i, 1.0); // coeficiente da variável na função objetivo
    }
    // Definir limites inferiores e superiores para as restrições
    glp_add_rows(lp, prob.NumConstraints);
    for (int i = 1; i <= prob.NumConstraints; i++)
    {
        glp_set_row_bnds(lp, i, GLP_UP, 0.0, 10.0); // limite inferior = 0, limite superior = 10
    }

    // Definir coeficientes da matriz das restrições
    
}

Problema readFile(string inputFile){
    Problema problema;
    ifstream file(inputFile);
    string line;
    int lineCount = 0;
    while (getline(file, line))
    {
        if (lineCount == 0)
        {
            problema.NumVarDec = stoi(line);
        }
        else if (lineCount == 1)
        {
            problema.NumVarProd = stoi(line);
        }
        else if (lineCount == 2)
        {
            problema.NumConstraints = stoi(line);
        }
        else
        {
            break;
        }
        lineCount++;
    }
    return problema;
}