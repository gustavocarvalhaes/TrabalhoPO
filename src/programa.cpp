#include <iostream>
#include <glpk.h>

int main() {
    glp_prob *lp;
    lp = glp_create_prob();

    // Definir a direção da otimização (MIN)
    glp_set_obj_dir(lp, GLP_MIN);

    // Adicionar as variáveis de decisão
    int numVars = 12; // uma variável para cada mês
    glp_add_cols(lp, numVars);
    for (int i = 1; i <= numVars; i++) {
        // Definir limites inferiores e superiores para as variáveis
        glp_set_col_bnds(lp, i, GLP_LO, 0.0, 0.0); // limite inferior = 0, limite superior = 0 (sem restrição)
        // Definir coeficientes da função objetivo (custo de manter estoque)
        glp_set_obj_coef(lp, i, 8.0); // custo de manter estoque por tapete por mês = $8.00
    }

    // Adicionar a restrição do estoque final
    glp_add_rows(lp, 1);
    glp_set_row_bnds(lp, 1, GLP_FX, 0.0, 0.0); // estoque final igual a zero

    // Definir a matriz das restrições (tapetes produzidos por mês)
    int *ia = new int[numVars + 1];
    int *ja = new int[numVars + 1];
    double *ar = new double[numVars + 1];
    for (int i = 1; i <= numVars; i++) {
        ia[i] = 1;
        ja[i] = i;
        ar[i] = 1.0;
    }
    glp_set_mat_row(lp, 1, numVars, ja, ar);

    // Resolver o problema
    glp_simplex(lp, NULL);

    // Verificar o status da solução
    int status = glp_get_status(lp);
    if (status == GLP_OPT) {
        double custoTotal = glp_get_obj_val(lp);
        std::cout << "Custo total: $" << custoTotal << std::endl;
    } else {
        std::cout << "Não foi encontrada uma solução ótima." << std::endl;
    }

    // Liberar recursos
    glp_delete_prob(lp);
    delete[] ia;
    delete[] ja;
    delete[] ar;

    return 0;
}
