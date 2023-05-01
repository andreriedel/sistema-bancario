#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Data.h"
#include "Pessoa.h"
#include "Titular.h"
#include "Conta.h"
#include "ContaSimples.h"

/* ---------------------- constructors and destructors ---------------------- */

ContaSimples::ContaSimples(string numero, string agencia, Titular* titular) :
Conta(numero, agencia, titular) {}

/* ------------------------------ class methods ----------------------------- */

string ContaSimples::tipo() {
    return "simples";
}
