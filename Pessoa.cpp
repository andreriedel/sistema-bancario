#include <iostream>
#include <string>

using namespace std;

#include "Data.h"
#include "Pessoa.h"

/* ---------------------- constructors and destructors ---------------------- */

Pessoa::Pessoa(string nome, char sexo, Data* dataDeNascimento, string cpf) {
    this->setNome(nome);
    this->setDataDeNascimento(dataDeNascimento);
    this->setSexo(sexo);
    this->setCpf(cpf);
}

Pessoa::~Pessoa() {
    delete(dataDeNascimento);
}

/* --------------------------------- setters -------------------------------- */

void Pessoa::setNome(string nome) {
    this->nome = nome;
}

void Pessoa::setSexo(char sexo) {
    this->sexo = sexo;
}

void Pessoa::setDataDeNascimento(Data* dataDeNascimento) {
    this->dataDeNascimento = dataDeNascimento;
}

void Pessoa::setCpf(string cpf) {
    this->cpf = cpf;
}

/* --------------------------------- getters -------------------------------- */

string Pessoa::getNome() {
    return this->nome;
}

char Pessoa::getSexo() {
    return this->sexo;
}

Data* Pessoa::getDataDeNascimento() {
    return this->dataDeNascimento;
}

string Pessoa::getCpf() {
    return this->cpf;
}
