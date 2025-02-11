#ifndef __GERAR__

#define __GERAR__

// Criação do tipo estruturado Config
struct Config
{
    // Os valores definidos nos parâmetros serão utilizados como um padrão, caso o usuário não informe.
    int identificador;
    int espacamento; // -e
    int tam_area; // Definição da área para cada barra. Largura total será de: L = tam_area * 67. ; -a
    int altura; // -h
    std::string nome_imagem; //-n
};

// Declaração das funções utilizadas como condição necessária para a execução do programa
bool valida_parametros(int quantidade_argumentos);

bool valida_quantidade_identificador(const std::string& id);

bool valida_digitos_identificador(const std::string& id);

bool valida_digito_verificador(int id);

// Funções para identificar os parâmetros passados na linha de comando
int espacamento(int quantidade_argumentos, char* argumentos[]);

int tamanho_area(int quantidade_argumentos, char* argumento[]);

int altura(int quantidade_argumentos, char* argumentos[]);

std::string nome_do_arquivo_imagem(int quantidade_argumentos, char* argumentos[]);

// Configuração das linhas inseridas no arquivo
std::string segunda_linha(int tamanho, int altura, int espacamento);

// Extração dos dígitos

int *digitosIdentificador(int identificador);

// Geração das linhas binárias para cada tipo de dígito no lado esquerdo
std::string umLcode(int area);
std::string doisLcode(int area);
std::string tresLcode(int area);
std::string quatroLcode(int area);
std::string cincoLcode(int area);
std::string seisLcode(int area);
std::string seteLcode(int area);
std::string oitoLcode(int area);
std::string noveLcode(int area);
std::string zeroLcode(int area);

// Geração das linhas binárias para cada tpo de dígito no lado direito
std::string umRcode(int area);
std::string doisRcode(int area);
std::string tresRcode(int area);
std::string quatroRcode(int area);
std::string cincoRcode(int area);
std::string seisRcode(int area);
std::string seteRcode(int area);
std::string oitoRcode(int area);
std::string noveRcode(int area);
std::string zeroRcode(int area);

// Geração da linha principal
std::string marcadorInicialFinal(int area);
std::string marcadorCentral(int area);
std::string stringPrincipal(int *arrayDeDigitos, int area);
std::string espacamentoInicial(std::string principal, int espacamento);
std::string repeticaoLinhaPrincipal(std::string terceiraLinha, int altura, int area, int espacamento);

// Criação do código da imagem a ser inserido no arquivo
/*
class CodigoImagem
{


    public:

}
*/

#endif