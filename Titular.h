#pragma once

class Titular : public Pessoa {
    private:
        float dinheiro;
    
    public:
        // constructors and destructors
        Titular(string nome, char sexo, Data* dataDeNascimento, string cpf, float dinheiro);

        // setters
        void setDinheiro(float dinheiro);

        // getters
        float getDinheiro();

        // class methods
        void realizarDeposito(float valor);
        void realizarSaque(float valor);

        bool operator<(Titular* t);

        friend class Conta;
};
