#include <planejamento.h>
#include <vector>

using namespace std;

Planejamento::Planejamento(ifstream &arquivoDeEntrada)
{

}

void Planejamento::insereEncomenda(int id, float custoMaterial, float valorDeVenda, int tempoDeFabricacao)
{
    Encomenda* encomenda = new Encomenda(id);
    encomenda->custoMaterial = custoMaterial;
    encomenda->valorDeVenda = valorDeVenda;
    encomenda->tempoDeFabricacao = tempoDeFabricacao;
}

// deve retorna um vetor contendo os valores das várias xi em ordem
void Planejamento::solveGlpk(ifstream &arquivoSaida)
{

    

    arquivoSaida << "==============================================" << endl;
    arquivoSaida << "Solução ótima para a base de dados apresentada" << endl;
    for(int i=0; i<this->getNumEncomendas(); i++){
        arquivoSaida << "x" << i+1 << ": " << resultado[i] << endl;
    }
    arquivoSaida << "==============================================" << endl;

}