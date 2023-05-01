#pragma once

class Data {
    private:
        int dia, mes, ano;

    public:
        // constructors and destructors
        Data();
        Data(int dia, int mes, int ano);

        // setters
        void setDia(int dia);
        void setMes(int mes);
        void setAno(int ano);

        // getters
        int getDia();
        int getMes();
        int getAno();

        // class methods
        string formatoCompacto();
        string formatoExtenso();
};
