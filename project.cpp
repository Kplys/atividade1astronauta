#include <iostream>
#include "astronautasprojeto.h"

using namespace std;

int acharAstronauta(const vector<Astronauta>& astronautas, const string& cpf) {
    for (int i = 0; i < (int)astronautas.size(); i++) {
        if (astronautas[i].cpf == cpf) return i;
    }
    return -1;
}

int acharVoo(const vector<Voo>& voos, int codigo) {
    for (int i = 0; i < (int)voos.size(); i++) {
        if (voos[i].codigovoo == codigo) return i;
    }
    return -1;
}

bool cpfNoVoo(const Voo& voo, const string& cpf) {
    for (int i = 0; i < (int)voo.listacpf.size(); i++) {
        if (voo.listacpf[i] == cpf) return true;
    }
    return false;
}

bool vooFoiLancado(const Voo& voo) {
    return voo.estadovoo != "planejado";
}

void listarVoos(const vector<Astronauta>& astronautas, const vector<Voo>& voos) {
    string estados[] = {
        "planejado",
        "em curso",
        "finalizado com sucesso",
        "finalizado com explosao"
    };

    for (int e = 0; e < 4; e++) {
        cout << "=== " << estados[e] << " ===" << endl;

        bool achou = false;

        for (int i = 0; i < (int)voos.size(); i++) {
            if (voos[i].estadovoo == estados[e]) {
                achou = true;
                cout << "Voo " << voos[i].codigovoo << endl;
                cout << "Estado: " << voos[i].estadovoo << endl;
                cout << "Astronautas:" << endl;

                if (voos[i].listacpf.empty()) {
                    cout << "nenhum" << endl;
                } else {
                    for (int j = 0; j < (int)voos[i].listacpf.size(); j++) {
                        int ia = acharAstronauta(astronautas, voos[i].listacpf[j]);
                        cout << voos[i].listacpf[j] << " - ";
                        if (ia != -1) {
                            cout << astronautas[ia].nome << endl;
                        } else {
                            cout << "desconhecido" << endl;
                        }
                    }
                }

                cout << endl;
            }
        }

        if (!achou) {
            cout << "Nenhum voo nesta categoria." << endl << endl;
        }
    }
}

void listarMortos(const vector<Astronauta>& astronautas, const vector<Voo>& voos) {
    cout << "=== astronautas mortos ===" << endl;

    bool achou = false;

    for (int i = 0; i < (int)astronautas.size(); i++) {
        if (!astronautas[i].vivo) {
            achou = true;
            cout << astronautas[i].cpf << " - " << astronautas[i].nome << endl;
            cout << "Voos: ";

            bool primeiro = true;

            for (int j = 0; j < (int)voos.size(); j++) {
                if (vooFoiLancado(voos[j]) && cpfNoVoo(voos[j], astronautas[i].cpf)) {
                    if (!primeiro) cout << ", ";
                    cout << voos[j].codigovoo;
                    primeiro = false;
                }
            }

            if (primeiro) {
                cout << "nenhum";
            }

            cout << endl << endl;
        }
    }

    if (!achou) {
        cout << "Nenhum astronauta morto." << endl;
    }
}

int main() {
    vector<Astronauta> astronautas;
    vector<Voo> voos;

    string comando;

    while (cin >> comando) {
        if (comando == "FIM") {
            break;
        }

        if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;

            cin >> cpf >> idade;
            getline(cin >> ws, nome);

            if (acharAstronauta(astronautas, cpf) != -1) {
                cout << "Recusado: CPF " << cpf << " ja cadastrado." << endl;
            } else {
                astronautas.push_back(Astronauta(cpf, nome, idade));
                cout << "Astronauta cadastrado: " << cpf << " - " << nome << endl;
            }
        }

        else if (comando == "CADASTRAR_VOO") {
            int codigo;
            cin >> codigo;

            if (acharVoo(voos, codigo) != -1) {
                cout << "Recusado: voo " << codigo << " ja cadastrado." << endl;
            } else {
                voos.push_back(Voo(codigo));
                cout << "Voo cadastrado: " << codigo << endl;
            }
        }

        else if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;

            int ia = acharAstronauta(astronautas, cpf);
            int iv = acharVoo(voos, codigo);

            if (ia == -1) {
                cout << "Recusado: astronauta " << cpf << " nao cadastrado." << endl;
            } else if (iv == -1) {
                cout << "Recusado: voo " << codigo << " nao cadastrado." << endl;
            } else if (voos[iv].estadovoo != "planejado") {
                cout << "Recusado: voo " << codigo << " nao esta planejado." << endl;
            } else if (!astronautas[ia].vivo) {
                cout << "Recusado: astronauta " << cpf << " esta morto." << endl;
            } else if (cpfNoVoo(voos[iv], cpf)) {
                cout << "Recusado: astronauta " << cpf << " ja esta nesse voo." << endl;
            } else {
                voos[iv].listacpf.push_back(cpf);
                cout << "Astronauta " << cpf << " adicionado ao voo " << codigo << endl;
            }
        }

        else if (comando == "REMOVER_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;

            int ia = acharAstronauta(astronautas, cpf);
            int iv = acharVoo(voos, codigo);

            if (ia == -1) {
                cout << "Recusado: astronauta " << cpf << " nao cadastrado." << endl;
            } else if (iv == -1) {
                cout << "Recusado: voo " << codigo << " nao cadastrado." << endl;
            } else if (voos[iv].estadovoo != "planejado") {
                cout << "Recusado: voo " << codigo << " nao esta planejado." << endl;
            } else if (!cpfNoVoo(voos[iv], cpf)) {
                cout << "Recusado: astronauta " << cpf << " nao esta no voo." << endl;
            } else {
                vector<string> novaLista;
                for (int i = 0; i < (int)voos[iv].listacpf.size(); i++) {
                    if (voos[iv].listacpf[i] != cpf) {
                        novaLista.push_back(voos[iv].listacpf[i]);
                    }
                }
                voos[iv].listacpf = novaLista;
                cout << "Astronauta " << cpf << " removido do voo " << codigo << endl;
            }
        }

        else if (comando == "LANCAR_VOO") {
            int codigo;
            cin >> codigo;

            int iv = acharVoo(voos, codigo);

            if (iv == -1) {
                cout << "Recusado: voo " << codigo << " nao cadastrado." << endl;
            } else if (voos[iv].estadovoo != "planejado") {
                cout << "Recusado: voo " << codigo << " nao esta planejado." << endl;
            } else if (voos[iv].listacpf.empty()) {
                cout << "Recusado: voo " << codigo << " nao tem astronautas." << endl;
            } else {
                bool ok = true;

                for (int i = 0; i < (int)voos[iv].listacpf.size(); i++) {
                    int ia = acharAstronauta(astronautas, voos[iv].listacpf[i]);
                    if (ia == -1 || !astronautas[ia].vivo || !astronautas[ia].disponivel) {
                        ok = false;
                    }
                }

                if (!ok) {
                    cout << "Recusado: existe astronauta morto ou indisponivel no voo." << endl;
                } else {
                    voos[iv].estadovoo = "em curso";

                    for (int i = 0; i < (int)voos[iv].listacpf.size(); i++) {
                        int ia = acharAstronauta(astronautas, voos[iv].listacpf[i]);
                        astronautas[ia].disponivel = false;
                    }

                    cout << "Voo " << codigo << " lancado com sucesso." << endl;
                }
            }
        }

        else if (comando == "EXPLODIR_VOO") {
            int codigo;
            cin >> codigo;

            int iv = acharVoo(voos, codigo);

            if (iv == -1) {
                cout << "Recusado: voo " << codigo << " nao cadastrado." << endl;
            } else if (voos[iv].estadovoo != "em curso") {
                cout << "Recusado: voo " << codigo << " nao esta em curso." << endl;
            } else {
                voos[iv].estadovoo = "finalizado com explosao";

                for (int i = 0; i < (int)voos[iv].listacpf.size(); i++) {
                    int ia = acharAstronauta(astronautas, voos[iv].listacpf[i]);
                    if (ia != -1) {
                        astronautas[ia].vivo = false;
                        astronautas[ia].disponivel = false;
                    }
                }

                cout << "Voo " << codigo << " explodiu." << endl;
            }
        }

        else if (comando == "FINALIZAR_VOO") {
            int codigo;
            cin >> codigo;

            int iv = acharVoo(voos, codigo);

            if (iv == -1) {
                cout << "Recusado: voo " << codigo << " nao cadastrado." << endl;
            } else if (voos[iv].estadovoo != "em curso") {
                cout << "Recusado: voo " << codigo << " nao esta em curso." << endl;
            } else {
                voos[iv].estadovoo = "finalizado com sucesso";

                for (int i = 0; i < (int)voos[iv].listacpf.size(); i++) {
                    int ia = acharAstronauta(astronautas, voos[iv].listacpf[i]);
                    if (ia != -1 && astronautas[ia].vivo) {
                        astronautas[ia].disponivel = true;
                    }
                }

                cout << "Voo " << codigo << " finalizado com sucesso." << endl;
            }
        }

        else if (comando == "LISTAR_VOOS") {
            listarVoos(astronautas, voos);
        }

        else if (comando == "LISTAR_MORTOS") {
            listarMortos(astronautas, voos);
        }

        else {
            cout << "Comando desconhecido: " << comando << endl;
        }
    }

    return 0;
}