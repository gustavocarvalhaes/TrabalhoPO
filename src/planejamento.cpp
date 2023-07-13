#include <glpk.h>
#include "planejamento.h"
#include <vector>
#include <iostream>

using namespace std;

// padrão arquivo de entrada:
// dias  numEncomendas
// tempoFabr custoMateriais ValorDeVenda
// tempoFabr custoMateriais ValorDeVenda
// tempoFabr custoMateriais ValorDeVenda
// tempoFabr custoMateriais ValorDeVenda
// tempoFabr custoMateriais ValorDeVenda

Planejamento::Planejamento(ifstream &arquivoEntrada)
{
    if (!arquivoEntrada.is_open())
    {
        cout << "ERRO: Arquivo não aberto corretamente!" << endl;
        return;
    }

 
    int diasDeTrabalho;
    int numEncomendas;
    int tempoDeFabricacao;
    float custoMateriais;
    float valorDeVenda;
    int i = 1;
    string leitor;

    arquivoEntrada >> diasDeTrabalho;
    arquivoEntrada >> numEncomendas;

    this->diasDeTrabalho = diasDeTrabalho;
    this->numEncomendas = numEncomendas;

    int encomendasVagas;
    encomendasVagas = 10 - numEncomendas;

    while (arquivoEntrada >> leitor >> tempoDeFabricacao >> custoMateriais >> valorDeVenda)
    {
        this->insereEncomenda(i, tempoDeFabricacao, custoMateriais, valorDeVenda);
        i++;
    }

    for (int i; i < encomendasVagas; i++)
    {
        this->insereEncomenda(i, 0, 0, 0);
    }
    int j=0;
    for(Encomenda* encomenda = this->primeiraEncomenda; encomenda!=nullptr; encomenda=encomenda->getProxEncomenda()){
        cout << "Encomenda: " << j+1 << " " << encomenda->tempoDeFabricacao << " " << encomenda->custoMaterial << " " << encomenda->valorDeVenda << endl;
        j++;
    }
}

void Planejamento::insereEncomenda(int id, int tempoDeFabricacao, float custoMaterial, float valorDeVenda)
{
    Encomenda *encomenda = new Encomenda(id);
    encomenda->custoMaterial = custoMaterial;
    encomenda->valorDeVenda = valorDeVenda;
    encomenda->tempoDeFabricacao = tempoDeFabricacao;
    if (this->primeiraEncomenda == nullptr) // se estiver vazio, insere no inicio
    {
        this->primeiraEncomenda = encomenda;
        this->ultimaEncomenda = encomenda;
    }
    else
    {
        this->ultimaEncomenda->proximaEncomenda = encomenda;
        this->ultimaEncomenda = encomenda;
    }
}

// atribuir no vetor resultado da classe planejamento os valores dos x
vector<double> Planejamento::solveGlpk()
{
    vector<Encomenda *> encomendas;
    Encomenda *encomenda = this->primeiraEncomenda;

    // colocando as encomendas em um vector para facilitar a manipulação dos dados
    while (encomenda->proximaEncomenda != nullptr)
    {
        encomendas.push_back(encomenda);
        encomenda = encomenda->proximaEncomenda;
    }

    // Criar o objeto de problema
    glp_prob *lp;
    lp = glp_create_prob();

    // Definir as variáveis
    glp_add_cols(lp, 10); // declara o número de variáveis

    // declara todas as variáveis
    // declara todas as variáveis
    glp_set_col_name(lp, 1, "x1");
    glp_set_col_kind(lp, 1, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 1, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 2, "x2");
    glp_set_col_kind(lp, 2, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 2, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 3, "x3");
    glp_set_col_kind(lp, 3, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 3, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 4, "x4");
    glp_set_col_kind(lp, 4, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 4, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 5, "x5");
    glp_set_col_kind(lp, 5, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 5, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 6, "x6");
    glp_set_col_kind(lp, 6, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 6, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 7, "x7");
    glp_set_col_kind(lp, 7, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 7, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 8, "x8");
    glp_set_col_kind(lp, 8, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 8, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 9, "x9");
    glp_set_col_kind(lp, 9, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 9, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 10, "x10");
    glp_set_col_kind(lp, 10, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 10, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    
     int tam = 10;
    // for (int i = 0; i < tam; i++)
    // {
    //     glp_set_col_name(lp, i + 1, "x" + to_string(i + 1));
    //     glp_set_col_kind(lp, i + 1, GLP_BV);           // Variável binária
    //     glp_set_col_bnds(lp, i + 1, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    // }

    // definindo os coeficientes para valorDeVenda
    for (int i = 0; i < tam; i++)
    {
        glp_set_obj_coef(lp, i, encomendas[i]->valorDeVenda);
    }

    // definindo os coeficientes de custoMaterial
    for (int i = 0; i < tam; i++)
    {
        glp_set_obj_coef(lp, i, -encomendas[i]->custoMaterial);
    }

    // Adicionar as restrições
    glp_add_rows(lp, 1); // Apenas uma restrição
    glp_set_row_name(lp, 1, "restricao1");

    // Definir os limites da restrição
    glp_set_row_bnds(lp, 1, GLP_UP, 0.0, this->diasDeTrabalho); // Limite superior é o número de dias previstos para trabalhar

    // Índices das variáveis envolvidas
    int ind[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 

    // Definir os coeficientes das variáveis na restrição
    double val[10]; // Coeficientes das variáveis
    for(int i = 1; i <= 10;i++){
        val[i-1]= encomendas[i-1]->tempoDeFabricacao;
    }
    glp_set_mat_row(lp, 1, 10, ind, val);
   
    // otimizar o problema
    glp_simplex(lp, NULL);

    // Obter o valor ótimo da função objetivo
    double objetivo = glp_get_obj_val(lp);

    // Obter os valores das variáveis ótimas
    vector<double> resultados;
    for (int i = 1; i <= tam; i++)
    {
        resultados.push_back(glp_get_col_prim(lp, i));
    }
    resultados.push_back(objetivo); // coloca a objetivo no final do vector

    /*
    // declara todas as variáveis
    glp_set_col_name(lp, 1, "x1");
    glp_set_col_kind(lp, 1, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 1, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 2, "x2");
    glp_set_col_kind(lp, 2, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 2, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 3, "x3");
    glp_set_col_kind(lp, 3, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 3, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 4, "x4");
    glp_set_col_kind(lp, 4, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 4, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 5, "x5");
    glp_set_col_kind(lp, 5, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 5, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 6, "x6");
    glp_set_col_kind(lp, 6, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 6, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 7, "x7");
    glp_set_col_kind(lp, 7, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 7, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 8, "x8");
    glp_set_col_kind(lp, 8, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 8, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 9, "x9");
    glp_set_col_kind(lp, 9, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 9, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1
    glp_set_col_name(lp, 10, "x10");
    glp_set_col_kind(lp, 10, GLP_BV);           // Variável binária
    glp_set_col_bnds(lp, 10, GLP_DB, 0.0, 1.0); // Limite inferior = 0, Limite superior = 1

    */

    // glp_set_obj_coef(lp, 2, encomendas[1]->valorDeVenda);
    // glp_set_obj_coef(lp, 3, encomendas[2]->valorDeVenda);
    // glp_set_obj_coef(lp, 4, encomendas[3]->valorDeVenda);
    // glp_set_obj_coef(lp, 5, encomendas[4]->valorDeVenda);
    // glp_set_obj_coef(lp, 6, encomendas[5]->valorDeVenda);
    // glp_set_obj_coef(lp, 7, encomendas[6]->valorDeVenda);
    // glp_set_obj_coef(lp, 8, encomendas[7]->valorDeVenda);
    // glp_set_obj_coef(lp, 9, encomendas[8]->valorDeVenda);
    // glp_set_obj_coef(lp, 10, encomendas[9]->valorDeVenda);
    // glp_set_obj_coef(lp, 10, encomendas[10]->valorDeVenda);

    return resultados;
}