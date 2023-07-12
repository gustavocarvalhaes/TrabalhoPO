#ifndef ENCOMENDA_H_INCLUDED
#define ENCOMENDA_H_INCLUDED
#include <fstream>
#include <vector>


using namespace std;

class Encomenda
{

friend class Planejamento;
    private:
        Encomenda* proximaEncomenda;
        int id;
        float custoMaterial;
        float valorDeVenda;
        int tempoDeFabricacao;
        
    public:
        //Destrutor
        ~Encomenda();
        Encomenda(int id){
            this->id=id;
            this->proximaEncomenda = nullptr;
            this->custoMaterial = 0;
            this->valorDeVenda = 0;
            this->tempoDeFabricacao = 0;
        };
        Encomenda* getProxEncomenda(){
            return this->proximaEncomenda;
        };
};

#endif // ENCOMENDA_H_INCLUDED