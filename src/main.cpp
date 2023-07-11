#include <iostream>
#include <glpk.h>
#include <fstream>
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

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return -1;
    }
    string input_file = argv[1];


    solveGlpk(readFile(input_file));

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