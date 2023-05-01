#include <iostream>
#include <string>
#include <ctime>
#include <regex>

using namespace std;

#include "Utils.h"

/* -------------------------------------------------------------------------- */

bool Utils::validarNome(string nome) {
    int aux;

    for (int i = 0; i < nome.size(); i++) {        
        aux = (int)nome[i];

        if ((aux != 32) && ((aux < 65) || (aux > 90)) && ((aux < 97) || (aux > 122)))
            return false;
    }

    return true;  
}

/* -------------------------------------------------------------------------- */

bool Utils::validarSexo(char sexo) {
    return (sexo == 'M' or sexo == 'F');
}

/* -------------------------------------------------------------------------- */

bool Utils::validarDataDeNascimento(int dia, int mes, int ano) {
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    /* -------------------- verifica se é uma data válida ------------------- */

    if (dia < 1) return false;

    if (mes < 1 or mes > 12) return false;

    if (ano < 1 or ano > now->tm_year + 1900) return false;

    switch (mes) {
        case 2:
            // verificação de ano bissexto
            if ((ano % 400 == 0) or ((ano % 4 == 0) and (ano % 100 != 0)))
                if (dia > 29) return false;
            else
                if (dia > 28) return false;

            break;

        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (dia > 31) return false;
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            if (dia > 30) return false;
            break;
    
        default:
            break;
    }

    /* -------------------- verifica se é maior de idade -------------------- */

    if (ano > now->tm_year + 1900 - 18) return false;

    if (ano == now->tm_year + 1900 - 18) {
        if (mes > now->tm_mon + 1) return false;

        if (mes == now->tm_mon + 1)
            if (dia > now->tm_mday) return false;
    }

    return true;
}

/* -------------------------------------------------------------------------- */

bool Utils::validarCpf(string cpf) {
    if (cpf.size() != 11) return false;

    int soma = 0;
    int resto;

    if (cpf == "00000000000") return false;

    for (int i = 1; i <= 9; i++)
        soma += ((int)cpf.at(i - 1) - 48) * (11 - i);

    resto = (soma * 10) % 11;

    if (resto == 10 or resto == 11)
        resto = 0;

    if (resto !=  ((int)cpf.at(9) - 48)) return false;

    soma = 0;

    for (int i = 1; i <= 10; i++)
        soma += ((int)cpf.at(i - 1) - 48) * (12 - i);

    resto = (soma * 10) % 11;

    if (resto == 10 or resto == 11)
        resto = 0;

    if (resto !=  ((int)cpf.at(10) - 48)) return false;

    return true;
}

/* -------------------------------------------------------------------------- */

bool Utils::validarDinheiro(float dinheiro) {
    return (dinheiro > 0.0);
}

/* -------------------------------------------------------------------------- */

string Utils::geradorNumeroConta() {
    unsigned seed = (time(0) + 1);
    string buffer;
    int i;

    srand(seed);

    for (i = 0; i < 9; i++)
        buffer += ((rand() % 10) + 48);

    return buffer;
}

/* -------------------------------------------------------------------------- */

bool Utils::validarTelefone(string telefone) {
    int aux;

    if (telefone.size() != 9 && telefone.size() != 11)
        return false;

    for (int i = 0; i < telefone.size(); i++) {
        aux = (int)telefone[i];

        if ((aux < 48) || (aux > 57))
            return false;
    }

    return true;
}

/* -------------------------------------------------------------------------- */

bool Utils::validarEmail(string email) {
    // define a regex
    const regex pattern ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

    return regex_match(email, pattern);
}

/* -------------------------------------------------------------------------- */

bool Utils::validarTaxaDeJuros(float novaTaxa) {
    return (novaTaxa > 0.0 && novaTaxa <= 5.0);
}
