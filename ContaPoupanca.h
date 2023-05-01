#pragma once

class ContaPoupanca : public Conta {
    private:
        static float taxaDeJurosAnual;

    public:
        // constructors and destructors
        ContaPoupanca(string numero, string agencia, Titular* titular);
        
        // class methods
        void calcularRendimentoMensal();
        void modificarTaxaDeJuros(float novaTaxa);
        string tipo();
};
