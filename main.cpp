#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <ctime>
#include <cstdlib>

using namespace std;

#include "Utils.h"
#include "Data.h"
#include "Pessoa.h"
#include "Titular.h"
#include "Conta.h"
#include "ContaSimples.h"
#include "ContaEspecial.h"
#include "ContaPoupanca.h"

// variáveis globais
set<Titular*> vTitular;
set<Conta*> vConta;
fstream arqTitular;
fstream arqConta;

/* -------------------------------------------------------------------------- */

void lerArquivoTitular();
void lerArquivoConta();
void atualizarArquivoTitular();
void atualizarArquivoConta();
void cadastrarTitular(string nome, char sexo, int dia, int mes, int ano, string cpf, float dinheiro);
void abrirConta(short int tipoConta, string numero, string agencia, string cpf);
void acessarConta(string numero, string cpf);
string criarNumeroConta();
Conta* obterContaPelaChavePix(string chavePix);
bool isChaveRepetida(string chavePix);

/* -------------------------------------------------------------------------- */

int main() {
    short int menu; // variável de controle do sistema bancário

    // variáveis auxiliares para cadastro e acesso de titular
    string nome;
    char sexo;
    int dia, mes, ano; // variáveis para data de nascimento
    string cpf;
    float dinheiro;

    // variáveis auxiliares para abertura e acesso de conta
    short int tipoConta;
    string numero, agencia;

    // carrega os dados salvos
    lerArquivoTitular();
    lerArquivoConta();

    do {
        cout << "\n" << "--------------------" << "\n";
        cout << "\n" << "Digite a operacao que desejar realizar no sistema:" << "\n";
        cout << "1: cadastro de titular" << "\n";
        cout << "2: abertura de conta" << "\n";
        cout << "3: acessar conta" << "\n";
        cout << "0: fechar o sistema" << "\n";

        cout << "\n" << "Operacao: ";
        cin >> menu;

        if (menu == 1) {
            cout << "\n" << "Para cadastrar um titular digite as seguintes informacoes:" << "\n";

            cin.ignore();

            do {
                cout << "\n" << "Nome completo (sem acento):" << "\n";
                
                getline(cin, nome);

                if (Utils::validarNome(nome))
                    break;
                else
                    cout << "O nome informado nao e valido" << "\n";
            } while (1);

            do {
                cout << "\n" << "Sexo (M ou F): ";
                cin >> sexo;

                if (Utils::validarSexo(sexo))
                    break;
                else
                    cout << "O sexo informado nao e valido" << "\n";
            } while (1);

            do {
                cout << "\n" << "Para a data de nascimento:" << "\n";
                cout << "Dia (DD): ";
                cin >> dia;
                cout << "Mes (MM): ";
                cin >> mes;
                cout << "Ano (AAAA): ";
                cin >> ano;

                if (Utils::validarDataDeNascimento(dia, mes, ano))
                    break;
                else
                    cout << "A data inserida nao e valida" << "\n";
            } while (1);

            do {  
                cout << "\n" << "Cpf (sem pontuacao): ";
                cin >> cpf;
            
                if (Utils::validarCpf(cpf))
                    break;
                else
                    cout << "O CPF inserido nao e valido" << "\n";
            } while (1);

            do {  
                cout << "\n" << "Dinheiro atual na carteira: ";
                cin >> dinheiro;
            
                if (Utils::validarDinheiro(dinheiro))
                    break;
                else
                    cout << "O dinheiro informado nao e valido" << "\n";
            } while (1);

            try {
                cadastrarTitular(nome, sexo, dia, mes, ano, cpf, dinheiro);
                cout << "\n" << "Titular cadastrado" << "\n";
            } catch (bad_alloc) {
                cout << "Nao e possivel cadastrar novos titulares" << "\n";
            } catch (...) {
                cout << "Erro ao cadastrar titular" << "\n";
            }
        } else if (menu == 2) {
            cout << "\n" << "Para abrir uma conta digite o tipo dela:" << "\n";
            cout << "1: conta simples" << "\n";
            cout << "2: conta especial" << "\n";
            cout << "3: conta poupanca" << "\n";

            do {
                cout << "\n" << "Tipo da conta: ";
                cin >> tipoConta;

                if (tipoConta >= 1 and tipoConta <= 3)
                    break;
                else
                    cout << "Tipo de conta informado informado nao e valido" << "\n";
            } while (1);

            cout << "\n" << "Para abrir a conta digite as seguintes informacoes:" << "\n";

            do {
                cout << "\n" << "Agencia da conta (4 digitos): ";
                cin >> agencia;

                if (agencia.size() == 4)
                    break;
                else
                    cout << "A agencia inserida nao e valida" << "\n";
            } while(1);

            do {  
                cout << "\n" << "Cpf do titular: ";
                cin >> cpf;

                if (Utils::validarCpf(cpf))
                    break;
                else
                    cout << "O CPF inserido nao e valido" << "\n";
            } while (1);

            numero = criarNumeroConta();

            try {
                abrirConta(tipoConta, numero, agencia, cpf);
            } catch (const char* str) {
                cout << str << "\n";
            } catch (bad_alloc) {
                cout << "Nao e possivel abrir novas contas" << "\n";
            } catch (...) {
                cout << "Erro ao abrir conta" << "\n";
            }
        } else if (menu == 3) {
            do {
                cout << "\n" << "Numero da conta: ";
                cin >> numero;

                if (numero.size() == 9)
                    break;
                else
                    cout << "O numero da conta inserido nao e valido" << "\n";
            } while(1);

            do {  
                cout << "\n" << "Cpf (sem pontuacao): ";
                cin >> cpf;
            
                if (Utils::validarCpf(cpf))
                    break;
                else
                    cout << "O CPF inserido nao e valido" << "\n";
            } while (1);

            try {
                acessarConta(numero, cpf);
            } catch (const char* str) {
                cout << str << "\n";
            } catch (...) {
                cout << "Erro ao acessar conta" << "\n";
            }
        } else if (menu == 0) {
            cout << "\n" << "Programa encerrado" << "\n";
        } else {
            cout << "\n" << "Operacao inserida invalida" << "\n";
        }
    } while (menu != 0);

    for (auto& titular: vTitular)
        delete(titular);

    for (auto& conta: vConta)
        delete(conta);

    return 0;
}

/* -------------------------------------------------------------------------- */

void lerArquivoTitular() {
    string registro;
    int i;

    // variáveis auxiliares para o titular
    string nome;
    char sexo;
    int dia, mes, ano; // variáveis para data de nascimento
    string cpf;
    float dinheiro;

    arqTitular.open("titular.txt", ios::in); // abre o arquivo no modo de leitura

    while (getline(arqTitular, registro)) {
        i = 1;
        nome = "";

        // lê o nome
        while (registro.at(i) != '\"') {
            nome.push_back(registro.at(i));
            i++;
        }

        i += 2;
        sexo = registro.at(i); // lê o sexo

        i += 2;
        dia = stoi(registro.substr(i, 2)); // lê o dia de nascimento

        i += 3;
        mes = stoi(registro.substr(i, 2)); // lê o mês de nascimento

        i += 3;
        ano = stoi(registro.substr(i, 4)); // lê o ano de nascimento

        i += 5;
        cpf = registro.substr(i, 11); // lê o CPF

        i += 12;
        dinheiro = stof(registro.substr(i)); // lê o dinheiro

        // cadastra o titular no sistema
        vTitular.insert(new Titular(nome, sexo, new Data(dia, mes, ano), cpf, dinheiro));
    }

    arqTitular.close();
}

/* -------------------------------------------------------------------------- */

void lerArquivoConta() {
    string registro;
    int i;
    pair<set<Conta*>::iterator, bool> conta; // armazena o retorno da inserção

    // variáveis auxiliares para abertura de conta
    string tipoConta, numero, agencia, cpf, saldo;
    string chavePix;

    arqConta.open("conta.txt", ios::in); // abre o arquivo no modo de leitura

    while (getline(arqConta, registro)) {
        i = 0;
        tipoConta = "";
        saldo = "";

        // lê o tipo da conta
        while (registro.at(i) != ' ') {
            tipoConta.push_back(registro.at(i));
            i++;
        }

        i++;
        numero = registro.substr(i, 9); // lê o número da conta

        i += 10;
        agencia = registro.substr(i, 4); // lê a agência

        // lê o saldo
        i += 5;
        while (registro.at(i) != ' ') {
            saldo.push_back(registro.at(i));
            i++;
        }

        i++;
        cpf = registro.substr(i, 11); // lê o CPF do titular

        // encontra o titular correpondente ao cpf
        for (auto& titular: vTitular) {
            // caso encontre o titular, insere a conta e armazena o retorno na variável conta
            if (cpf == titular->getCpf())
            {
                if (tipoConta == "simples")
                    conta = vConta.insert(new ContaSimples(numero, agencia, titular));
                else if (tipoConta == "especial")
                    conta = vConta.insert(new ContaEspecial(numero, agencia, titular));
                else if (tipoConta == "poupanca")
                    conta = vConta.insert(new ContaPoupanca(numero, agencia, titular));
            }
        }

        (*conta.first)->setSaldo(stof(saldo));

        i += 12;
        // verifica se existem chaves pix
        if (i < registro.size()) {
            // insere as chaves pix
            while (1) {
                if (i == registro.size() - 1) {
                    chavePix.push_back(registro.at(i));
                    (*conta.first)->inserirChavePix(chavePix);
                    chavePix = "";

                    break;
                }

                if (registro.at(i) == ' ') {
                    (*conta.first)->inserirChavePix(chavePix);
                    chavePix = "";
                } else {
                    chavePix.push_back(registro.at(i));
                }
                    
                i++;
            }
        }
    }

    arqConta.close();
}

/* -------------------------------------------------------------------------- */

void atualizarArquivoTitular() {
    arqTitular.open("titular.txt", ios::out); // abre o arquivo no modo de escrita

    // percorre o vetor de titular e insere os dados no arquivo
    for (auto& titular: vTitular) {
        arqTitular << "\"" << titular->getNome() << "\"" << " ";

        arqTitular << titular->getSexo() << " ";

        if ((titular->getDataDeNascimento()->getDia() / 10) >= 1)
            arqTitular << titular->getDataDeNascimento()->getDia() << " ";
        else
            arqTitular << "0" << titular->getDataDeNascimento()->getDia() << " ";

        if ((titular->getDataDeNascimento()->getMes() / 10) >= 1)
            arqTitular << titular->getDataDeNascimento()->getMes() << " ";
        else
            arqTitular << "0" << titular->getDataDeNascimento()->getMes() << " ";

        arqTitular << titular->getDataDeNascimento()->getAno() << " ";

        arqTitular << titular->getCpf() << " ";

        arqTitular << titular->getDinheiro() << "\n";
    }

    arqTitular.close();
}

/* -------------------------------------------------------------------------- */

void atualizarArquivoConta() {
    arqConta.open("conta.txt", ios::out); // abre o arquivo no modo de escrita

    // percorre o vetor de contas e insere os dados no arquivo
    for (auto& conta: vConta) {
        arqConta << conta->tipo() << " ";
        arqConta << conta->getNumero() << " ";
        arqConta << conta->getAgencia() << " ";
        arqConta << conta->getSaldo() << " ";
        arqConta << conta->getTitular()->getCpf();

        if (conta->getChavesPix().size() > 0) {
            arqConta << " ";
            
            // percorre o vetor de chaves pix para inserir no arquivo
            for (int j = 0; j < conta->getChavesPix().size(); j++) {
                // caso seja a última chave
                if (j == conta->getChavesPix().size() - 1)
                    arqConta << conta->getChavesPix().at(j);
                else
                    arqConta << conta->getChavesPix().at(j) << " ";
            }
        }

        arqConta << "\n";
    }

    arqConta.close();
}

/* -------------------------------------------------------------------------- */

void cadastrarTitular(string nome, char sexo, int dia, int mes, int ano, string cpf, float dinheiro) {
    vTitular.insert(new Titular(nome, sexo, new Data(dia, mes, ano), cpf, dinheiro));

    atualizarArquivoTitular();
}

/* -------------------------------------------------------------------------- */

void abrirConta(short int tipoConta, string numero, string agencia, string cpf) {
    // percorre o vetor de titular para encontrar o titular correpondente ao CPF
    for (auto& titular: vTitular) {
        if (cpf == titular->getCpf()) {            
            if (tipoConta == 1) {
                vConta.insert(new ContaSimples(numero, agencia, titular));
                cout << "\n" << "Conta simples aberta em nome de " << titular->getNome() << "\n";
            } else if (tipoConta == 2) {
                vConta.insert(new ContaEspecial(numero, agencia, titular));
                cout << "\n" << "Conta especial aberta em nome de " << titular->getNome() << "\n";
            } else if (tipoConta == 3) {
                vConta.insert(new ContaPoupanca(numero, agencia, titular));
                cout << "\n" << "Conta poupanca aberta em nome de " << titular->getNome() << "\n";
            }

            cout << "Numero da conta: " << numero << "\n";

            atualizarArquivoConta();            

            return;
        }
    }

    throw "\nO CPF inserido nao pertence a nenhum titular\n";
}

/* -------------------------------------------------------------------------- */

void acessarConta(string numero, string cpf) {
    // precorre o vetor de contas
    for (auto& conta: vConta) {
        if (numero == conta->getNumero()) { // encontra a conta correpondente ao número
            if (cpf == conta->getTitular()->getCpf()) { // verifica se o cpf pertence ao titular
                // variáveis auxiliares
                short int operacao, tipoChavePix;
                float valor;
                string chavePix, chavePixNova;
                float taxaNova;

                cout << "\n" << "Conta acessada" << "\n";                
                cout << "Titular da conta: " << conta->getTitular()->getNome() << "\n";

                do {
                    cout << "\n" << "--------------------" << "\n";
                    cout << "\n" << "Informe a operacao que deseja realizar" << "\n";
                    cout << "1: deposito" << "\n";
                    cout << "2: saque" << "\n";
                    cout << "3: extrato" << "\n";
                    cout << "4: pix" << "\n";
                    cout << "5: inserir chave pix" << "\n";
                    cout << "6: remover chave pix" << "\n";
                    cout << "7: alterar chave pix" << "\n";
                    cout << "8: calcular rendimento mensal (conta poupanca)" << "\n";
                    cout << "9: modificicar taxa de juros (conta poupanca)" << "\n"; 
                    cout << "0: sair da conta" << "\n";

                    cout << "\n" << "Operacao: ";
                    cin >> operacao;

                    if (operacao == 1) {
                        cout << "\n" << "Digite o valor de deposito: ";
                        cin >> valor;

                        if (conta->deposito(valor)) {
                            cout << "\n" << "Deposito realizado" << "\n";
                            cout << "Seu saldo: R$" << conta->getSaldo() << "\n";
                            cout << "Seu dinheiro atual: R$" << conta->getTitular()->getDinheiro() << "\n";
                        } else {
                            cout << "\n" << "Deposito nao pode ser realizado" << "\n";
                        }
                    } else if (operacao == 2) {
                        cout << "\n" << "Digite o valor de saque: ";
                        cin >> valor;

                        if (conta->saque(valor)) {
                            cout << "\n" << "Saque realizado" << "\n";
                            cout << "Seu saldo: R$" << conta->getSaldo() << "\n";
                            cout << "Seu dinheiro atual: R$" << conta->getTitular()->getDinheiro() << "\n";
                        } else {
                            cout << "\n" << "Saque nao pode ser realizado" << "\n";
                        }
                    } else if (operacao == 3) {
                        cout << "\n" << "Seu saldo: " << conta->getSaldo() << "\n";
                    } else if (operacao == 4) {
                        cout << "\n" << "Digite a chave da conta destino: ";
                        cin >> chavePix;

                        Conta* contaAux = obterContaPelaChavePix(chavePix);

                        if (contaAux != NULL) {
                            cout << "Digite o valor de transferencia: ";
                            cin >> valor;
                            
                            if (conta->pix(contaAux, valor)) {
                                cout << "\n" << "Pix realizado para " << contaAux->getTitular()->getNome() << "\n";
                                cout << "Seu saldo: R$" << conta->getSaldo() << "\n";
                            } else {
                                cout << "\n" << "Pix nao pode ser realizado" << "\n";
                            }
                        } else {
                            cout << "\n" << "Conta nao encontrada" << "\n";
                        }
                    } else if (operacao == 5) {
                        cout << "\n" << "Para inserir uma chave pix digite o tipo dela:" << "\n";
                        cout << "1: CPF" << "\n";
                        cout << "2: telefone" << "\n";
                        cout << "3: e-mail" << "\n";

                        do {
                            cout << "\n" << "Tipo da chave: ";
                            cin >> tipoChavePix;

                            if (tipoChavePix >= 1 and tipoChavePix <= 3)
                                break;
                            else
                                cout << "Tipo de chave pix informado nao e valido" << "\n";
                        } while (1);

                        do {
                            cout << "\n" << "Digite a chave pix que deseja inserir: " ;
                            cin >> chavePix;

                            if (tipoChavePix == 1) {
                                if (Utils::validarCpf(chavePix))
                                    break;
                                else
                                    cout << "O CPF informado nao e valido" << "\n";
                            } else if (tipoChavePix == 2) {
                                if (Utils::validarTelefone(chavePix))
                                    break;
                                else
                                    cout << "O telefone informado nao e valido" << "\n";
                            } else if (tipoChavePix == 3) {
                                 if (Utils::validarEmail(chavePix))
                                    break;
                                else
                                    cout << "O e-mail informado nao e valido" << "\n";
                            }
                        } while (1);

                        if (!isChaveRepetida(chavePix)) {
                            conta->inserirChavePix(chavePix);
                            cout << "\n" << "Chave inserida" << "\n";
                        } else {
                            cout << "\n" << "A chave inserida ja pertence a alguem" << "\n";
                        }
                    } else if (operacao == 6) {
                        cout << "\n" << "Digite a chave pix que deseja remover: ";
                        cin >> chavePix;

                        if (conta->removerChavePix(chavePix))
                            cout << "\n" << "Chave removida com sucesso" << "\n";
                        else
                            cout << "\n" << "Chave nao pode ser removida" << "\n";
                    } else if (operacao == 7) {
                        cout << "\n" << "Digite a chave pix que deseja alterar: ";
                        cin >> chavePix;

                        cout << "Digite o tipo da nova chave:" << "\n";
                        cout << "1: CPF" << "\n";
                        cout << "2: telefone" << "\n";
                        cout << "3: e-mail" << "\n";

                        do {
                            cout << "\n" << "Tipo da chave: ";
                            cin >> tipoChavePix;

                            if (tipoChavePix >= 1 and tipoChavePix <= 3)
                                break;
                            else
                                cout << "Tipo de chave pix informado nao e valido" << "\n";
                        } while (1);

                        do {
                            cout << "\n" << "Digite a nova chave pix: " ;
                            cin >> chavePixNova;

                            if (tipoChavePix == 1) {
                                if (Utils::validarCpf(chavePixNova))
                                    break;
                                else
                                    cout << "O CPF informado nao e valido" << "\n";
                            } else if (tipoChavePix == 2) {
                                if (Utils::validarTelefone(chavePixNova))
                                    break;
                                else
                                    cout << "O telefone informado nao e valido" << "\n";
                            } else if (tipoChavePix == 3) {
                                 if (Utils::validarEmail(chavePixNova))
                                    break;
                                else
                                    cout << "O e-mail informado nao e valido" << "\n";
                            }
                        } while (1);

                        if (!isChaveRepetida(chavePixNova)) {
                            if (conta->alterarChavePix(chavePix, chavePixNova))
                                cout << "\n" << "Chave alterada com sucesso" << "\n";
                            else
                                cout << "\n" << "Chave nao pode ser alterada" << "\n";
                        } else {
                            cout << "\n" << "A chave inserida ja pertence a alguem" << "\n";
                        }
                    } else if (operacao == 8) {
                        if (conta->tipo() == "poupanca") {
                            ContaPoupanca* contaAux = static_cast<ContaPoupanca*> (conta);

                            contaAux->calcularRendimentoMensal();
                            cout << "\n" << "Rendimento calculado" << "\n";
                            cout << "Seu saldo: R$" << contaAux->getSaldo() << "\n";
                        } else {
                            cout << "\n" << "Seu tipo de conta nao permite essa operacao" << "\n";
                        }
                    } else if (operacao == 9) {
                        if (conta->tipo() == "poupanca") {
                            ContaPoupanca* contaAux = static_cast<ContaPoupanca*> (conta);

                            do {
                                cout << "\n" << "Entre com a nova taxa: ";
                                cin >> taxaNova;

                                if (Utils::validarTaxaDeJuros(taxaNova))
                                    break;
                                else
                                    cout << "Taxa inserida nao e valida" << "\n";
                            } while(1);

                            contaAux->modificarTaxaDeJuros(taxaNova);
                            cout << "Taxa de juros modificada" << "\n";
                        } else {
                            cout << "\n" << "Seu tipo de conta nao permite essa operacao" << "\n";
                        }
                    } else if (operacao == 0) {
                        cout << "\n" << "Acesso a conta encerrado" << "\n";
                    } else {
                        cout << "\n" << "A operacao inserida nao e valida" << "\n";
                    }

                    atualizarArquivoConta();
                } while(operacao != 0);
            } else {
                cout << "\n" << "O CPF informado nao pertence ao titular da conta" << "\n";
            }

            return;
        }
    }

    throw "\nNumero da conta nao encontrado\n";
}

/* -------------------------------------------------------------------------- */

// gera um número aleatório pra conta
string criarNumeroConta() {
    string numero = Utils::geradorNumeroConta();

    for (auto& conta: vConta) {
        if (conta->getNumero() == numero)
            return criarNumeroConta();
    }

    return numero;
}

/* -------------------------------------------------------------------------- */

Conta* obterContaPelaChavePix(string chavePix) {
    for (auto& conta: vConta) {
        for (int j = 0; j < conta->getChavesPix().size(); j++) {
            if (chavePix == conta->getChavesPix().at(j))
                return conta;
        }
    }

    return NULL;
}

/* -------------------------------------------------------------------------- */

bool isChaveRepetida(string chavePix) {
    for (auto& conta: vConta) {
        for (int j = 0; j < conta->getChavesPix().size(); j++) {
            if (chavePix == conta->getChavesPix().at(j))
                return true;
        }
    }

    return false; 
}
