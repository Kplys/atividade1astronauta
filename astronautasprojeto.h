#ifndef ASTRONAUTASPROJETO_H
#define ASTRONAUTASPROJETO_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Astronauta {
public:
    string cpf;
    string nome;
    int idade;
    bool vivo;
    bool disponivel;

    Astronauta(string cpf, string nome, int idade) {
        this->cpf = cpf;
        this->nome = nome;
        this->idade = idade;
        this->vivo = true;
        this->disponivel = true;
    }
};

class Voo {
public:
    int codigovoo;
    vector<string> listacpf;
    string estadovoo;

    Voo(int codigovoo) {
        this->codigovoo = codigovoo;
        this->estadovoo = "planejado";
    }
};

int acharAstronauta(const vector<Astronauta>& astronautas, const string& cpf);
int acharVoo(const vector<Voo>& voos, int codigo);
bool cpfNoVoo(const Voo& voo, const string& cpf);
bool vooFoiLancado(const Voo& voo);
void listarVoos(const vector<Astronauta>& astronautas, const vector<Voo>& voos);
void listarMortos(const vector<Astronauta>& astronautas, const vector<Voo>& voos);

#endif