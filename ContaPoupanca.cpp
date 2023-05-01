#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Data.h"
#include "Pessoa.h"
#include "Titular.h"
#include "Conta.h"
#include "ContaPoupanca.h"

/* ---------------------- constructors and destructors ---------------------- */

ContaPoupanca::ContaPoupanca(string numero, string agencia, Titular* titular) :
Conta(numero, agencia, titular) {}

/* ------------------------------ class methods ----------------------------- */

void ContaPoupanca::calcularRendimentoMensal() {
    float rendimento = this->saldo * (taxaDeJurosAnual / 12);
    this->saldo += rendimento;
}

void ContaPoupanca::modificarTaxaDeJuros(float novaTaxa) {
    taxaDeJurosAnual = novaTaxa;
}

float ContaPoupanca::taxaDeJurosAnual = 2.5; // valor inicial da taxa de juros

string ContaPoupanca::tipo() {
    return "poupanca";
}
