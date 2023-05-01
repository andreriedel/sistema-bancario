#pragma once

class Pessoa {
    private:
        string nome;
        char sexo;
        Data* dataDeNascimento;
        string cpf;

    public:
        // constructors and destructors
        Pessoa(string nome, char sexo, Data* dataDeNascimento, string cpf);
        ~Pessoa();

        // setters
        void setNome(string nome);
        void setSexo(char sexo);
        void setDataDeNascimento(Data* dataDeNascimento);
        void setCpf(string cpf);

        // getters
        string getNome();
        char getSexo();
        Data* getDataDeNascimento();
        string getCpf();
};
