#include <iostream>
#include <glpk.h>

int main()
{
    std::cout << "Oi Pancinha !!" << std::endl;

    glp_prob *lp;
    lp = glp_create_prob();

    glp_set_obj_dir(lp, GLP_MAX);

    int numVars = 2; // número de variáveis de decisão
    glp_add_cols(lp, numVars);
    for (int i = 1; i <= numVars; i++)
    {
        // Definir limites inferiores e superiores para as variáveis
        glp_set_col_bnds(lp, i, GLP_LO, 0.0, 0.0); // limite inferior = 0, limite superior = 0 (sem restrição)
        // Definir coeficientes da função objetivo
        glp_set_obj_coef(lp, i, 1.0); // coeficiente da variável na função objetivo
    }

    int numConstraints = 2; // número de restrições
    glp_add_rows(lp, numConstraints);
    for (int i = 1; i <= numConstraints; i++)
    {
        // Definir limites inferiores e superiores para as restrições
        glp_set_row_bnds(lp, i, GLP_UP, 0.0, 10.0); // limite inferior = 0, limite superior = 10
    }

    // Definir coeficientes da matriz das restrições
    int ia[3] = {1, 1, 2};                     // índices das linhas
    int ja[3] = {1, 2, 2};                     // índices das colunas
    double ar[3] = {1.0, 1.0, 1.0};            // valores dos coeficientes
    glp_set_mat_row(lp, 1, 2, ja, ar);         // atribuir a primeira linha da matriz das restrições
    glp_set_mat_row(lp, 2, 2, ja + 1, ar + 1); // atribuir a segunda linha da matriz das restrições

    glp_simplex(lp, NULL); // ou glp_intopt(lp, NULL) para programação inteira mista

    double z = glp_get_obj_val(lp); // obter o valor ótimo da função objetivo
    for (int i = 1; i <= numVars; i++)
    {
        double x = glp_get_col_prim(lp, i); // obter o valor ótimo da variável de decisão i
        // faça algo com os valores obtidos (ex.: imprimir)
        
    }

    glp_delete_prob(lp); // liberar o objeto de problema

    return 0;
}
