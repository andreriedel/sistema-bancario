#pragma once

class ContaSimples : public Conta {
    public:
        // constructors and destructors
        ContaSimples(string numero, string agencia, Titular* titular);

        // class methods
        string tipo();
};
