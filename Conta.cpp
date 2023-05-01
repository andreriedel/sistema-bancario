#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Data.h"
#include "Pessoa.h"
#include "Titular.h"
#include "Conta.h"

/* ---------------------- constructors and destructors ---------------------- */

Conta::Conta(string numero, string agencia, Titular* titular) {
    this->setNumero(numero);
    this->setAgencia(agencia);
    this->setTitular(titular);
}

/* --------------------------------- setters -------------------------------- */

void Conta::setNumero(string numero) {
    this->numero = numero;
}

void Conta::setAgencia(string agencia) {
    this->agencia = agencia;
}

void Conta::setTitular(Titular* titular) {
    this->titular = titular;
}

void Conta::setSaldo(float saldo) {
    this->saldo = saldo;
}

/* --------------------------------- getters -------------------------------- */

string Conta::getNumero() {
    return this->numero;
}

string Conta::getAgencia() {
    return this->agencia;
}

Titular* Conta::getTitular() {
    return this->titular;
}

float Conta::getSaldo() {
    return this->saldo;
}

vector<string> Conta::getChavesPix() {
    return this->chavesPix;
}

/* ------------------------------ class methods ----------------------------- */

bool Conta::deposito(float valor) {
    if (valor > 0 and valor <= this->titular->getDinheiro()) {
        this->saldo += valor;
        this->titular->realizarDeposito(valor);

        return true;
    }

    return false;
}

bool Conta::saque(float valor) {
    if (valor <= this->saldo) {
        this->saldo -= valor;
        this->titular->realizarSaque(valor);

        return true;
    }
    
    return false;
}

bool Conta::pix(Conta* contaDestino, float valor) {
    if (valor <= this->saldo) {
        this->saldo -= valor;
        contaDestino->receberPix(valor);
        
        return true;
    }     

    return false;
}

void Conta::receberPix(float valor) {
    this->saldo += valor;
}

void Conta::inserirChavePix(string chave) {
    this->chavesPix.push_back(chave);
}

bool Conta::removerChavePix(string chave) {
    for (int i = 0; i < this->chavesPix.size(); i++) {
        if (this->chavesPix.at(i) == chave) {
            this->chavesPix.erase(this->chavesPix.begin() + i);
            
            return true;
        }
    }

    return false;
}

bool Conta::alterarChavePix(string chaveAntiga, string chaveNova) {
    for (int i = 0; i < this->chavesPix.size(); i++) {
        if (this->chavesPix.at(i) == chaveAntiga) {
            this->chavesPix.at(i) = chaveNova;

            return true;
        }
    }

    return false;
}

// sobrecarga do operador para o uso do set
bool Conta::operator<(Conta* c) {
    return this->getNumero() < c->getNumero();
}
