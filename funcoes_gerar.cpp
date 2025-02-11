#include <iostream>
#include <fstream>
#include <string>
#include "gerar.h"

// Validação da quantidade de parâmetros informados
bool valida_parametros(int quantidade_argumentos)
{
    std::cout << "O usuário passou " << quantidade_argumentos << " argumento";

    if (quantidade_argumentos < 2)
    {
        std::cout << std::endl << "Falta o identificador!" << std::endl;
        return false;
    }
    std::cout << "s" << std::endl;
    return true;
}

// Validação da quantidade de caracteres do identificador informado
bool valida_quantidade_identificador(const std::string& id)
{
    if (id.size() == 8) return true;
    std::cout << "Identificador não possui 8 dígitos" << std::endl;
    return false;
}

// Validação para verificar se dígitos do verificador informado são apenas números
bool valida_digitos_identificador(const std::string& id)
{
    for (int i = 0; i < 8; i++)
    {
        if (id[i] < '0' || id[i] > '9') 
        {
            std::cout << "Identificador contém valores não numéricos" << std::endl;
            return false;
        }
    }
    return true;
}

// Cálculo para verificar o dígito verificador informado, determinando a execução do programa.
bool valida_digito_verificador(int id)
{
    int somaVerificador = 0;
    int ultimoDigito = id % 10; // Armazenar o dígito verificador
    int aux = id / 10;

    // Laço para realizar a soma ponderada dos 7 primeiros dígitos
    for (int i = 0; i < 7; i++)
    {
        int resto = aux % 10;

        if (i == 0 || i % 2 == 0) somaVerificador = somaVerificador + (resto * 3);
        else somaVerificador = somaVerificador + resto;

        aux = aux / 10;
    }
    
    aux = 0;

    // Laço para encontrar o próximo múltiplo de 10 da soma ponderada dos 7 primeiros dígitos
    do
    {
        aux = aux + 10;   
    } while (somaVerificador > aux);
    
    // Lógica para validar o dígito verificador
    if (aux - somaVerificador == ultimoDigito) return true;
    std::cout << "O dígito verificador do identificador é inválido (não corresponde aos valores anteriores)." << std::endl;
    return false;
}

// Funções para identificar os parâmetros passados na linha de comando
int espacamento(int quantidade_argumentos, char* argumentos[])
{
    int confEspacamento = 4; // Valor padrão

    // Laço para encontrar o parâmetro que identifica o valor de espaçamento adotado
    for(int i = 2; i < quantidade_argumentos; i++)
    {
        // Identifica a localização do parâmetro informado como espaçamento
        std::string arg = argumentos[i];
        if (arg == "-e" && i < quantidade_argumentos-1)
        {
            std::string valorEspacamento = argumentos[i+1];
            // Conversão da string em um número inteiro, retornando para que seja inserido no parâmetro do objeto config
            confEspacamento = std::stoi(valorEspacamento);
            return confEspacamento;
        }
    }

    return confEspacamento;
}

int tamanho_area(int quantidade_argumentos, char* argumentos[])
{
    int confTamanhoArea = 3; // Valor padrão.

    // Laço para encontrar o parâmetro que identifica o valor do tamanho da área adotado
    for(int i = 2; i < quantidade_argumentos; i++)
    {
        // Identifica a localização do parâmetro informado como tamanho da área
        std::string arg = argumentos[i];
        if (arg == "-a" && i < quantidade_argumentos-1)
        {
            std::string valorArea = argumentos[i+1];
            // Conversão da string em um número inteiro, retornando para que seja inserido no parâmetro do objeto config
            confTamanhoArea = std::stoi(valorArea);
            return confTamanhoArea;
        }
    }

    return confTamanhoArea;
}

int altura(int quantidade_argumentos, char* argumentos[])
{
    int confAltura = 50; // Valor padrão.

    // Laço para encontrar o parâmetro que identifica o valor da altura adotada
    for(int i = 2; i < quantidade_argumentos; i++)
    {
        // Identifica a localização do parâmetro informado como altura
        std::string arg = argumentos[i];
        if (arg == "-h" && i < quantidade_argumentos-1)
        {
            std::string valorAltura = argumentos[i+1];
            // Conversão da string em um número inteiro, retornando para que seja inserido no parâmetro do objeto config
            confAltura = std::stoi(valorAltura);
            return confAltura;
        }
    }

    return confAltura;
}

std::string nome_do_arquivo_imagem(int quantidade_argumentos, char* argumentos[])
{
    std::string nomeDaImagem = "codigo.pbm"; // Valor padrão.
    std::string extensaoArquivo = ".pbm";

    // Laço para encontrar o parâmetro que identifica o valor da altura adotada
    for(int i = 2; i < quantidade_argumentos; i++)
    {
        // Identifica a localização do parâmetro informado como altura
        std::string arg = argumentos[i];
        if (arg == "-n" && i < quantidade_argumentos-1)
        {
            std::string nomeDaImagem = argumentos[i+1] + extensaoArquivo;
            return nomeDaImagem;
        }
    }
    
    return nomeDaImagem;
}

// Configuração das linhas inseridas no arquivo
std::string segunda_linha(int tamanho, int altura, int espacamento)
{
    int larguraBpm = (tamanho * 67) + (espacamento * 2);
    int alturaBpm = altura;

    std::string tamanhoStr = std::to_string(larguraBpm);
    std::string alturaStr = std::to_string(alturaBpm);
    std::string segundaLinha = tamanhoStr + " " + alturaStr;

    return segundaLinha;
}

// Extração dos dígitos do código identificador em um array de inteiros
int *digitosIdentificador(int identificador)
{
    int *arrayDigitos = new int[8];
    int divisor = 10000000;
    for (int i = 0; i < 8; i++)
    {
        arrayDigitos[i] = (identificador / divisor);
        identificador = (identificador % divisor);
        divisor = (divisor / 10);
    }

    return arrayDigitos;
}

// Código para gerar o binário dos números no lado esquerdo do identificador
std::string zeroLcode(int area)
{
    std::string retornoDigitoLcode = "";
    std::string binarioDigitoLcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 1) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 2) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 3) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 4) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 5) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 6) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
        }
        retornoDigitoLcode = retornoDigitoLcode + binarioDigitoLcode[i];
    }

    return retornoDigitoLcode;
}

std::string umLcode(int area)
{
    std::string retornoDigitoLcode = "";
    std::string binarioDigitoLcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 1) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 2) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 3) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 4) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 5) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 6) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
        }
        retornoDigitoLcode = retornoDigitoLcode + binarioDigitoLcode[i];
    }

    return retornoDigitoLcode;
}

std::string doisLcode(int area)
{
    std::string retornoDigitoLcode = "";
    std::string binarioDigitoLcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 1) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 2) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 3) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 4) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 5) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 6) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
        }
        retornoDigitoLcode = retornoDigitoLcode + binarioDigitoLcode[i];
    }

    return retornoDigitoLcode;
}

std::string tresLcode(int area)
{
    std::string retornoDigitoLcode = "";
    std::string binarioDigitoLcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 1) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 2) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 3) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 4) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 5) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 6) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
        }
        retornoDigitoLcode = retornoDigitoLcode + binarioDigitoLcode[i];
    }

    return retornoDigitoLcode;
}

std::string quatroLcode(int area)
{
    std::string retornoDigitoLcode = "";
    std::string binarioDigitoLcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 1) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 2) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 3) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 4) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 5) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 6) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
        }
        retornoDigitoLcode = retornoDigitoLcode + binarioDigitoLcode[i];
    }

    return retornoDigitoLcode;
}

std::string cincoLcode(int area)
{
    std::string retornoDigitoLcode = "";
    std::string binarioDigitoLcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 1) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 2) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 3) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 4) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 5) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 6) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
        }
        retornoDigitoLcode = retornoDigitoLcode + binarioDigitoLcode[i];
    }

    return retornoDigitoLcode;
}

std::string seisLcode(int area)
{
    std::string retornoDigitoLcode = "";
    std::string binarioDigitoLcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 1) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 2) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 3) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 4) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 5) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 6) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
        }
        retornoDigitoLcode = retornoDigitoLcode + binarioDigitoLcode[i];
    }

    return retornoDigitoLcode;
}

std::string seteLcode(int area)
{
    std::string retornoDigitoLcode = "";
    std::string binarioDigitoLcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 1) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 2) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 3) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 4) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 5) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 6) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
        }
        retornoDigitoLcode = retornoDigitoLcode + binarioDigitoLcode[i];
    }

    return retornoDigitoLcode;
}

std::string oitoLcode(int area)
{
    std::string retornoDigitoLcode = "";
    std::string binarioDigitoLcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 1) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 2) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 3) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 4) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 5) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 6) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
        }
        retornoDigitoLcode = retornoDigitoLcode + binarioDigitoLcode[i];
    }

    return retornoDigitoLcode;
}

std::string noveLcode(int area)
{
    std::string retornoDigitoLcode = "";
    std::string binarioDigitoLcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 1) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 2) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 3) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 4) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "0";
            if (i == 5) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
            if (i == 6) binarioDigitoLcode[i] = binarioDigitoLcode[i] + "1";
        }
        retornoDigitoLcode = retornoDigitoLcode + binarioDigitoLcode[i];
    }

    return retornoDigitoLcode;
}

// Código para gerar o binário dos números no lado direito do identificador

std::string zeroRcode(int area)
{
    std::string retornoDigitoRcode = "";
    std::string binarioDigitoRcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 1) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 2) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 3) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 4) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 5) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 6) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
        }
        retornoDigitoRcode = retornoDigitoRcode + binarioDigitoRcode[i];
    }

    return retornoDigitoRcode;
}

std::string umRcode(int area)
{
    std::string retornoDigitoRcode = "";
    std::string binarioDigitoRcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 1) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 2) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 3) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 4) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 5) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 6) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
        }
        retornoDigitoRcode = retornoDigitoRcode + binarioDigitoRcode[i];
    }

    return retornoDigitoRcode;
}

std::string doisRcode(int area)
{
    std::string retornoDigitoRcode = "";
    std::string binarioDigitoRcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 1) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 2) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 3) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 4) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 5) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 6) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
        }
        retornoDigitoRcode = retornoDigitoRcode + binarioDigitoRcode[i];
    }

    return retornoDigitoRcode;
}

std::string tresRcode(int area)
{
    std::string retornoDigitoRcode = "";
    std::string binarioDigitoRcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 1) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 2) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 3) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 4) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 5) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 6) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
        }
        retornoDigitoRcode = retornoDigitoRcode + binarioDigitoRcode[i];
    }

    return retornoDigitoRcode;
}

std::string quatroRcode(int area)
{
    std::string retornoDigitoRcode = "";
    std::string binarioDigitoRcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 1) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 2) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 3) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 4) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 5) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 6) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
        }
        retornoDigitoRcode = retornoDigitoRcode + binarioDigitoRcode[i];
    }

    return retornoDigitoRcode;
}

std::string cincoRcode(int area)
{
    std::string retornoDigitoRcode = "";
    std::string binarioDigitoRcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 1) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 2) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 3) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 4) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 5) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 6) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
        }
        retornoDigitoRcode = retornoDigitoRcode + binarioDigitoRcode[i];
    }

    return retornoDigitoRcode;
}

std::string seisRcode(int area)
{
    std::string retornoDigitoRcode = "";
    std::string binarioDigitoRcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 1) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 2) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 3) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 4) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 5) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 6) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
        }
        retornoDigitoRcode = retornoDigitoRcode + binarioDigitoRcode[i];
    }

    return retornoDigitoRcode;
}

std::string seteRcode(int area)
{
    std::string retornoDigitoRcode = "";
    std::string binarioDigitoRcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 1) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 2) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 3) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 4) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 5) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 6) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
        }
        retornoDigitoRcode = retornoDigitoRcode + binarioDigitoRcode[i];
    }

    return retornoDigitoRcode;
}

std::string oitoRcode(int area)
{
    std::string retornoDigitoRcode = "";
    std::string binarioDigitoRcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 1) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 2) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 3) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 4) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 5) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 6) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
        }
        retornoDigitoRcode = retornoDigitoRcode + binarioDigitoRcode[i];
    }

    return retornoDigitoRcode;
}

std::string noveRcode(int area)
{
    std::string retornoDigitoRcode = "";
    std::string binarioDigitoRcode[7] = {};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 1) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 2) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 3) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 4) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "1";
            if (i == 5) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
            if (i == 6) binarioDigitoRcode[i] = binarioDigitoRcode[i] + "0";
        }
        retornoDigitoRcode = retornoDigitoRcode + binarioDigitoRcode[i];
    }

    return retornoDigitoRcode;
}


// Geração dos marcadores

std::string marcadorInicialFinal(int area)
{
    std::string marcador = "";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) marcador = marcador + "1";
            if (i == 1) marcador = marcador + "0";
            if (i == 2) marcador = marcador + "1";
        }
    }
    return marcador;
}

std::string marcadorCentral(int area)
{
    std::string marcador = "";
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < area; j++)
        {
            if (i == 0) marcador = marcador + "0";
            if (i == 1) marcador = marcador + "1";
            if (i == 2) marcador = marcador + "0";
            if (i == 3) marcador = marcador + "1";
            if (i == 4) marcador = marcador + "0";
        }
    }
    return marcador;
}

// Geração da linha principal 
std::string stringPrincipal(int *arrayDeDigitos, int area)
{
    std::string terceiraLinha = "";
    
    // Inserção do marcador inicial na linha principal
    terceiraLinha =  marcadorInicialFinal(area) + terceiraLinha;

    for (int i = 0; i < 4; i++)
    {
        if (arrayDeDigitos[i] == 0) terceiraLinha = terceiraLinha + zeroLcode(area);
        if (arrayDeDigitos[i] == 1) terceiraLinha = terceiraLinha + umLcode(area);
        if (arrayDeDigitos[i] == 2) terceiraLinha = terceiraLinha + doisLcode(area);
        if (arrayDeDigitos[i] == 3) terceiraLinha = terceiraLinha + tresLcode(area);
        if (arrayDeDigitos[i] == 4) terceiraLinha = terceiraLinha + quatroLcode(area);
        if (arrayDeDigitos[i] == 5) terceiraLinha = terceiraLinha + cincoLcode(area);
        if (arrayDeDigitos[i] == 6) terceiraLinha = terceiraLinha + seisLcode(area);
        if (arrayDeDigitos[i] == 7) terceiraLinha = terceiraLinha + seteLcode(area);
        if (arrayDeDigitos[i] == 8) terceiraLinha = terceiraLinha + oitoLcode(area);
        if (arrayDeDigitos[i] == 9) terceiraLinha = terceiraLinha + noveLcode(area);
    }

    // Inserção do marcador central
    terceiraLinha = terceiraLinha + marcadorCentral(area);

    for (int i = 4; i < 8; i++)
    {
        if (arrayDeDigitos[i] == 0) terceiraLinha = terceiraLinha + zeroRcode(area);
        if (arrayDeDigitos[i] == 1) terceiraLinha = terceiraLinha + umRcode(area);
        if (arrayDeDigitos[i] == 2) terceiraLinha = terceiraLinha + doisRcode(area);
        if (arrayDeDigitos[i] == 3) terceiraLinha = terceiraLinha + tresRcode(area);
        if (arrayDeDigitos[i] == 4) terceiraLinha = terceiraLinha + quatroRcode(area);
        if (arrayDeDigitos[i] == 5) terceiraLinha = terceiraLinha + cincoRcode(area);
        if (arrayDeDigitos[i] == 6) terceiraLinha = terceiraLinha + seisRcode(area);
        if (arrayDeDigitos[i] == 7) terceiraLinha = terceiraLinha + seteRcode(area);
        if (arrayDeDigitos[i] == 8) terceiraLinha = terceiraLinha + oitoRcode(area);
        if (arrayDeDigitos[i] == 9) terceiraLinha = terceiraLinha + noveRcode(area);
    }

    // Inserção do marcador final
    terceiraLinha = terceiraLinha + marcadorInicialFinal(area);

    return terceiraLinha;
}

// Adição do espaçamento lateral na linha principal
std::string espacamentoInicial(std::string principal, int espacamento)
{
    std::string espacamentoLateral = "";
    for (int i = 0; i < espacamento; i++)
    {
        espacamentoLateral = espacamentoLateral + "0";
    }
    
    std::string terceiraLinha = espacamentoLateral + principal + espacamentoLateral;
    return terceiraLinha;
}

// Repetição da linha principal
std::string repeticaoLinhaPrincipal(std::string terceiraLinha, int altura, int area, int espacamento)
{
    std::string linhaPrincipal = "";
    std::string espacamentoSuperior = "";
    
    // linha e altura modificadas para o teste
    int tamanhoLinha = (area * 67) + (espacamento * 2);
    int tamanhoAltura = altura;

    /* Criação da linha do espaçamento superior
    for (int i = 0; i < tamanhoLinha; i++)
    {
        espacamentoSuperior = espacamentoSuperior + "0";
    }

    // Inserção das linhas superiores em branco
    for (int i = 0; i < espacamento; i++)
    {
        linhaPrincipal = linhaPrincipal + espacamentoSuperior;
    }
    */

    // Inserção das linhas principais
    for (int i = 0; i < tamanhoAltura; i++)
    {
        linhaPrincipal = linhaPrincipal + terceiraLinha;
    }

    return linhaPrincipal;
}