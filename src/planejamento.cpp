#include <glpk.h>
#include "planejamento.h"
#include <vector>
#include <iostream>

using namespace std;

/*
TRABALHO DE PESQUISA OPERACIONAL - 2023
ALUNOS: Gustavo Carvalhaes da Fonseca Ferreira - 202065522B
        Daniel Freitas Pereira - 202065118A
*/

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


    for (int i = 0; i < numEncomendas; i++)
    {
        arquivoEntrada >> tempoDeFabricacao >> custoMateriais >> valorDeVenda;
        this->insereEncomenda(i + 1, tempoDeFabricacao, custoMateriais, valorDeVenda);
    }

    for (int i = numEncomendas + 1; i <= 10; i++)
    {
        this->insereEncomenda(i, 0, 0, 0);
    }
    int j = 0;
    for (Encomenda *encomenda = this->primeiraEncomenda; encomenda != nullptr; encomenda = encomenda->getProxEncomenda())
    {
        cout << "Encomenda: " << j + 1 << " " << encomenda->tempoDeFabricacao << " " << encomenda->custoMaterial << " " << encomenda->valorDeVenda << endl;
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
    while (encomenda != nullptr)
    {
        encomendas.push_back(encomenda);
        encomenda = encomenda->proximaEncomenda;
    }

    // Criar o objeto de problema
    glp_prob *lp;
    lp = glp_create_prob();

    glp_set_obj_dir(lp, GLP_MAX); // maximizar
    // Definir as variáveis
    glp_add_cols(lp, 10); // declara o número de variáveis

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
    // definindo os coeficientes para valorDeVenda
    double coef = 0.0;
    for (int i = 1; i <= tam; i++)
    {
        coef = encomendas[i - 1]->valorDeVenda - encomendas[i - 1]->custoMaterial;
        glp_set_obj_coef(lp, i, coef);
    }

    // Adicionar as restrições
    glp_add_rows(lp, 1); // Apenas uma restrição
    glp_set_row_name(lp, 1, "restricao1");

    // Definir os limites da restrição
    glp_set_row_bnds(lp, 1, GLP_UP, 0.0, this->diasDeTrabalho); // Limite superior é o número de dias previstos para trabalhar


    // Índices das variáveis envolvidas
    int ind[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Definir os coeficientes das variáveis na restrição
    double val[11]; // Coeficientes das variáveis
    for (int i = 1; i <= 10; i++)
    {
        ind[i] = i; // Ajuste para o índice correto
        val[i] = encomendas[i - 1]->tempoDeFabricacao;
    }

    glp_set_mat_row(lp, 1, 10, ind, val);
    // otimizar o problema
    glp_iocp parm;
    glp_init_iocp(&parm);
    parm.presolve = GLP_ON;
    glp_intopt(lp, &parm);

    // Obter o valor ótimo da função objetivo
    double objetivo = glp_mip_obj_val(lp);

    // Obter os valores das variáveis ótimas
    vector<double> resultados;
    for (int i = 1; i <= tam; i++)
    {
        resultados.push_back(glp_mip_col_val(lp, i));
    }

    resultados.push_back(objetivo); // coloca a objetivo no final do vector

    glp_delete_prob(lp);

    return resultados;
}