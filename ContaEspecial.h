#pragma once

class ContaEspecial : public Conta {
    private:
        const int limite = 1000;

    public:
        // constructors and destructors
        ContaEspecial(string numero, string agencia, Titular* titular);

        // class methods        
        bool saque(float valor) override; // método sobrescrito
        bool pix(Conta* contaDestino, float valor) override; // método sobrescrito
        string tipo();
};
