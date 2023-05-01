#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Data.h"
#include "Pessoa.h"
#include "Titular.h"
#include "Conta.h"
#include "ContaEspecial.h"

/* ---------------------- constructors and destructors ---------------------- */

ContaEspecial::ContaEspecial(string numero, string agencia, Titular* titular) :
Conta(numero, agencia, titular) {}

/* ------------------------------ class methods ----------------------------- */

// método sobrescrito
bool ContaEspecial::saque(float valor) {
    if (valor <= this->saldo + limite) {
        this->saldo -= valor;
        this->titular->realizarSaque(valor);

        return true;
    }
    
    return false;
}

// método sobrescrito
bool ContaEspecial::pix(Conta* contaDestino, float valor) {
    if (valor <= this->saldo + limite) {
        this->saldo -= valor;
        contaDestino->receberPix(valor);
        
        return true;
    }     

    return false;
}

string ContaEspecial::tipo() {
    return "especial";
}
