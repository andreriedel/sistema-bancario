#pragma once

class Conta {
    protected:
        string numero, agencia;
        float saldo = 0.0;
        Titular* titular;
        vector<string> chavesPix;

    public:
        // constructors and destructors
        Conta(string numero, string agencia, Titular* titular);        

        // setters
        void setNumero(string numero);
        void setAgencia(string agencia);
        void setTitular(Titular* titular);
        void setSaldo(float saldo);

        // getters
        string getNumero();
        string getAgencia();
        Titular* getTitular();
        float getSaldo();
        vector<string> getChavesPix();

        // class methods  
        bool deposito(float valor);
        virtual bool saque(float valor);
        virtual bool pix(Conta* contaDestino, float valor);
        void receberPix(float valor);
        void inserirChavePix(string chave);
        bool removerChavePix(string chave);
        bool alterarChavePix(string chaveAntiga, string chaveNova);
        virtual string tipo() = 0;

        bool operator<(Conta* c);
};
