#include <iostream>
#include <fstream>
#include <string>
#include "gerar.h"

// #include "imagem.h"
// #include "cod_barra.h"

int main(int argc, char *argv[])
{
    if (valida_parametros(argc) == true)
    {
        Config conf;

        // Armazena o identificador passado
        std::string identificador = argv[1];

        // Verificação da quantidade de dígitos
        if (valida_quantidade_identificador(identificador) == false) return 0;

        // Verificação de que os caracteres informados são apenas números
        if (valida_digitos_identificador(identificador) == false) return 0;

        // Conversão do identificador em inteiro e a sua atribução no parâmetro do 'conf'
        conf.identificador = std::stoi(identificador);

        // Validação do cálculo do dígito verificador
        if (valida_digito_verificador(conf.identificador) == false) return 0;

        std::cout << "O código identificador informado foi: " << conf.identificador << std::endl;

        conf.espacamento = espacamento(argc, argv);
        std::cout << "O valor do espaçamento é " << conf.espacamento << std::endl;

        conf.tam_area = tamanho_area(argc, argv);
        std::cout << "O tamanho da área mede " << conf.tam_area << std::endl;

        conf.altura = altura(argc, argv);
        std::cout << "A altura da imagem mede " << conf.altura << std::endl;

        conf.nome_imagem = nome_do_arquivo_imagem(argc, argv);
        std::cout << "O nome do arquivo de imagem gerado é " << conf.nome_imagem << std::endl;

        // Teste para a funcionalidade de criação dos arquivos
        /*std::ofstream arquivo(conf.nome_imagem);
        arquivo << "P1" << std::endl << segunda_linha(conf.tam_area, conf.altura, conf.espacamento) << std::endl << "0000000000001000000100000010000001000000100000010010001000111000000000" << std::endl;
        arquivo.close(); 
        */
        
        int *separacaoDigitos = digitosIdentificador(conf.identificador);

        std::string linhaPrincipal = stringPrincipal(separacaoDigitos, conf.tam_area);
        
        linhaPrincipal = espacamentoInicial(linhaPrincipal, conf.espacamento);
        
        linhaPrincipal = repeticaoLinhaPrincipal(linhaPrincipal, conf.altura, conf.tam_area, conf.espacamento);

        std::ofstream arquivo(conf.nome_imagem);
        arquivo << "P1" << std::endl << segunda_linha(conf.tam_area, conf.altura, conf.espacamento) << std::endl << linhaPrincipal << std::endl;
        arquivo.close();
    }

    return 0;
}