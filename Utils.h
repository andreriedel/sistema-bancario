#pragma once

class Utils {
    public:
        static bool validarNome(string nome);
        static bool validarSexo(char sexo);
        static bool validarDataDeNascimento(int dia, int mes, int ano);
        static bool validarCpf(string cpf);
        static bool validarDinheiro(float dinheiro);
        static string geradorNumeroConta();
        static bool validarTelefone(string telefone);
        static bool validarEmail(string email);
        static bool validarTaxaDeJuros(float novaTaxa);
};
