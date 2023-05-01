#include <iostream>
#include <string>

using namespace std;

#include "Data.h"
#include "Pessoa.h"
#include "Titular.h"

/* ---------------------- constructors and destructors ---------------------- */

Titular::Titular(string nome, char sexo, Data* dataDeNascimento, string cpf, float dinheiro) :
Pessoa(nome, sexo, dataDeNascimento, cpf) {
    this->setDinheiro(dinheiro);
}

/* --------------------------------- setters -------------------------------- */

void Titular::setDinheiro(float dinheiro) {
    this->dinheiro = dinheiro;
}

/* --------------------------------- getters -------------------------------- */

float Titular::getDinheiro() {
    return this->dinheiro;
}

/* ------------------------------ class methods ----------------------------- */

void Titular::realizarDeposito(float valor) {
    this->dinheiro -= valor;
}

void Titular::realizarSaque(float valor) {
    this->dinheiro += valor;
}

// sobrecarga do operador para o uso do set
bool Titular::operator<(Titular* t) {
    return this->getNome() < t->getNome();
}
