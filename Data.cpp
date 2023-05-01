#include <iostream>
#include <string>
#include <ctime>

using namespace std;

#include "Data.h"

/* ---------------------- constructors and destructors ---------------------- */

Data::Data() {
    // used for default values
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    this->setDia(now->tm_mday);
    this->setMes(now->tm_mon + 1);
    this->setAno(now->tm_year + 1900);

    delete(now);
}

Data::Data(int dia, int mes, int ano) {
    this->setDia(dia);
    this->setMes(mes);
    this->setAno(ano);
}

/* --------------------------------- setters -------------------------------- */

void Data::setDia(int dia) {
    this->dia = dia;
}

void Data::setMes(int mes) {
    this->mes = mes;
}

void Data::setAno(int ano) {
    this->ano = ano;
}

/* --------------------------------- getters -------------------------------- */

int Data::getDia() {
    return this->dia;
}

int Data::getMes() {
    return this->mes;
}

int Data::getAno() {
    return this->ano;
}

/* ------------------------------ class methods ----------------------------- */

string Data::formatoCompacto() {
    return to_string(this->dia) + "/" + to_string(this->mes) + "/" + to_string(this->ano);
}

string Data::formatoExtenso() {
    string strMes;
    
    switch (this->mes) {
        case 1:
            strMes = "Janeiro";
            break;
        case 2:
            strMes = "Fevereiro";
            break;
        case 3:
            strMes = "Marco";
            break;
        case 4:
            strMes = "Abril";
            break;
        case 5:
            strMes = "Maio";
            break;
        case 6:
            strMes = "Junho";
            break;
        case 7:
            strMes = "Julho";
            break;
        case 8:
            strMes = "Agosto";
            break;
        case 9:
            strMes = "Setembro";
            break;
        case 10:
            strMes = "Outubro";
            break;
        case 11:
            strMes = "Novembro";
            break;
        case 12:
            strMes = "Dezembro";
            break;
    
        default:
            break;
    }

    return to_string(this->dia) + " de " + strMes + " de " + to_string(this->ano);
}
