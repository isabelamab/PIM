/*
  Projeto: PIM - Projeto Integrado Multidisciplinar
   Author: Isabela Martins Abrão Barbosa
   Versão: 1.0
     Data: 24/11/2022
Descrição: Sistema que visa controlar de forma simples o cadastro, alteração, consulta e eclusão de dados
            para gerenciar uma startUp.
            Os módulos criados foram: Login (Perfil), Clientes, Funcionários e Relatórios
*/

#include<stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <dos.h>

/* Struct do Perfil*/
struct Perfil{
int Codigo;
char Login[50];
char Nome[50];
char Senha[6];
char Ativo;
};

/* Struct de Funcionario*/
struct Funcionario{
int Codigo;
char Nome[50];
char DataNasc[10];
char Endereco[50];
char Complemento[20];
char Cep[8];
char Cidade[20];
char Estado[20];
char Email[30];
float Salario;
char Ativo;
};

/* Struct do Cliente*/
struct Cliente {
int Codigo;
char Nome[50];
char Endereco[50];
char Complemento[20];
char Cep[8];
char Cidade[20];
char Estado[20];
char Email[30];
char Telefone[15];
char Ativo;
};

/* Declaração dos arquivos*/
FILE *arqPerfil;
FILE *arqFuncionario;
FILE *arqCliente;

/* Declaração das Interfaces */
void montarMenu(const char* funcionalidade);
void gerenciarMenuLogin(void);
void gerenciarMenu(int opcao, const char* funcionalidade);
void montarMenuPrincipal(void);
void gerenciarMenuPrincipal(int opcao);
void cadastrarClientes(void);
void cadastrarFuncionario(void);
void cadastrarPerfil(void);

/* Inicio do Programa */
int main()
{
    setlocale(LC_ALL,"Portuguese");
    system("title PIM - Projeto Integrado Multidisciplinar");
    system("color 1F");
    montarMenuPrincipal();
}

void montarMenuPrincipal()
{
    int opcao = 0;
    printf("\n\tMenu de Principal\n\n");
    printf("Informe uma opção válida e aperte a tecla enter\n\n");
    printf("1. Login\n");
    printf("2. Sair\n");
    system("pause>nul");
    scanf("%i", &opcao);
    system("cls || clear");
    gerenciarMenuPrincipal(opcao);
}

void gerenciarMenuPrincipal(int opcao)
{
    switch(opcao)
    {
        case 1:
            gerenciarMenuLogin();
            break;
        case 2:
            exit(1);
            break;
        default:
            printf("Digite uma opcao valida\n");
            system("pause");
    }
}
/*
Função para tratar entrada com login e senha
*/
void gerenciarMenuLogin()
{
    /* Carrega estrutura da struct*/
    struct Perfil perfil;

    /* Define usuário e senha interno */
    char usuario = "admin";
    char senha[6] = "teste";

    /* variaveis de trabalho */
    char nomePerfil[50];
    char senhaPerfil[6];
    char teclaSenha;
    int tamanho = 0;
    int ret;

    system("cls || clear");

    /* Solicita Login*/
    printf("\n\tLogin: ");
    scanf("%s",&nomePerfil);

    /* Solicita Senha*/
    printf("\n\tSenha: ");
    fflush(stdin);

    /* Oculta a senha */
    while(teclaSenha != 13  && tamanho < 6)
    {
         senhaPerfil[tamanho++] = teclaSenha = getch();
         printf((teclaSenha!=13)?"*":"\n");
    }
    //senhaPerfil[tamanho--] = '\0';

    /* Abre arquivo de Perfil*/
    arqPerfil = fopen("perfil.pim", "ab");

    /* Trata erro na abertura do Arquivo*/
    if (arqPerfil == NULL)
    {
        printf("Erro ao abrir arquivo \n");
        return -1;
    }

    if (nomePerfil != "admin")
    {
        /* Verifica se Perfil existe */
        while (fread (&perfil, sizeof(perfil), 1, arqPerfil))
        {
            if ((nomePerfil != perfil.Nome) || (senhaPerfil != perfil.Senha ))
            {
                printf("Usuário ou senha inválido!");
                system("pause>nul");
                system("cls || clear");
            }
            else
            {
                /*  Login encontrado, monta o menu */
                system("cls || clear");
                montarMenuPrincipal();
            }
        }
    }
    else
    {
        if(nomePerfil == "admin" && strcmp(senhaPerfil, senha) != 0)
        {
            printf("\n Senha inválida! \n");
            system("pause");
            system("cls || clear");
            montarMenuPrincipal();
        }
    }
    /* Monta menu apos login */
    system("cls || clear");
    menuAdministrador();
}

void menuAdministrador()
{
    int continuar = 0;

    printf("\n\tMenu de Administrador\n\n");
    printf("Informe uma opção válida e aperte a tecla enter\n\n");
    printf("1. Gerenciar Cliente\n");
    printf("2. Gerenciar Funcionários\n");
    printf("3. Gerenciar Perfil\n");
    printf("4. Gerenciar Relatórios\n");
    printf("5. Voltar ao Menu Principal\n");

    scanf("%i", &continuar);
    system("cls || clear");

    switch(continuar)
    {
        case 1:
            montarMenu("Clientes");
            break;
        case 2:
            montarMenu("Funcionarios");
            break;
        case 3:
            montarMenu("Perfil");
            break;
        case 4:
            montarMenu("Relatorios");
            break;
        case 5:
            gerenciarMenuLogin();
            break;
        default:
            printf("Digite uma opcao valida \n");
            system("pause");
    }
}

/* Função para montar menu com descrição da funcionalidade */
void montarMenu(const char* funcionalidade)
{
   int opcao = 0;
   if(funcionalidade != "Relatorios")
   {
        printf("\n\tMenu de Administrador - %s\n\n", funcionalidade);
        printf("Informe uma opção válida e aperte a tecla enter\n\n");
        printf("1. Cadastrar %s\n", funcionalidade);
        printf("2. Alterar %s\n", funcionalidade);
        printf("3. Consultar %s\n", funcionalidade);
        printf("4. Excluir %s\n", funcionalidade);
        printf("5. Voltar ao Menu Principal\n");
   }
   else
    {
        printf("\n\tMenu de Administrador - %s\n\n", funcionalidade);
        printf("Informe uma opção válida e aperte a tecla enter\n\n");
        printf("1. Relatorio de Clientes Ativos \n");
        printf("2. Relatorio de Funcionarios \n");
        printf("3. Relatorio de Perfil \n");
    }

    system("pause>nul");
    scanf("%i", &opcao);
    system("cls || clear");

    gerenciarMenu(opcao, funcionalidade);
}
/* Função para gerenciar os menus do sistema PIM */
void gerenciarMenu(int opcao, const char* funcionalidade)
{
    char funcao;
    switch(opcao)
    {
        case 1:
            if(funcionalidade == "Clientes"){
                cadastrarCliente();
            }
            else if(funcionalidade == "Funcionarios"){
                cadastrarFuncionario();
            }
            else{
                cadastrarPerfil();
            }
            break;
        case 2:
            if(funcionalidade == "Clientes"){
                alterarCliente();
            }
            else if(funcionalidade == "Funcionarios"){
                alterarFuncionario();
            }
            else{
                alterarPerfil();
            }
            break;
        case 3:
            if(funcionalidade == "Clientes"){
                consultarCliente();
            }
            else if(funcionalidade == "Funcionarios"){
                consultarFuncionario();
            }
            else{
                consultarPerfil();
            }
            break;
        case 4:
            if(funcionalidade == "Clientes"){
                excluirCliente();
            }
            else if(funcionalidade == "Funcionarios"){
                excluirFuncionario();
            }
            else{
                excluirPerfil();
            }
            break;
        case 5:
            menuAdministrador();
            break;
        default:
            printf("Digite uma opcao valida\n");
            system("pause");
    }

}

/* Método para cadastrar os clientes no arquivo*/
void cadastrarCliente()
{
    /* Define a estrutura do cliente*/
    struct Cliente cliente;

    /* variável para tratar o retorno do arquivo*/
    int retorno;

    /* Recebe status para abrir o arquivo*/
    arqCliente = fopen("cliente.pim", "ab");

    /* Verifica se teve sucesso na abetura do arquivo*/
    if (arqCliente == NULL)
    {
        printf("Erro ao abrir arquivo \n");
        return;
    }

    /* Recebe os dados digitados na tela*/
    printf("Código do cliente: \n");
    scanf("%d", &cliente.Codigo);

    printf("Nome: \n");
    fflush(stdin);
    gets(cliente.Nome);

    printf("Endereço : \n");
    fflush(stdin);
    gets(cliente.Endereco);

    printf("Complemento : \n");
    fflush(stdin);
    gets(cliente.Complemento);

    printf("Cep: \n");
    fflush(stdin);
    gets(cliente.Cep);

    printf("Cidade: \n");
    fflush(stdin);
    gets(cliente.Cidade);

    printf("Estado: \n");
    fflush(stdin);
    gets(cliente.Estado);

    printf("E-mail: \n");
    fflush(stdin);
    gets(cliente.Email);

    printf("Telefone: \n");
    fflush(stdin);
    gets(cliente.Telefone);

    cliente.Ativo = "S";

    /* Grava dados do cliente */
    retorno = fwrite (&cliente, sizeof(cliente), 1, arqCliente);

    /* verifica se houve sucesso na gravação */
    if (retorno == 1)
    {
        fclose (arqCliente);
        printf("\n Dados do cliente incluídos com sucesso!");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Clientes");
    }
    else
    {
        fclose (arqCliente);
        printf("\n Falha ao gravar dados do cliente.");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Clientes");
    }

}

/* Método para consultar os clientes do arquivo*/
void consultarCliente()
{
    arqCliente = fopen("cliente.pim", "rb");
    if (arqCliente == NULL)
    {
        printf("Arquivo inexistente!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Clientes");
    }
    /* Carrega estruct de clientes */
    struct Cliente cliente;

    int cod, encontrado = 0;
    printf ("\nDigite o codigo que procura: \n");
    scanf ("%d", &cod);

    while (fread (&cliente, sizeof(cliente), 1, arqCliente))
    {
        if ((cod == cliente.Codigo) && (cliente.Ativo != '*'))
        {
            printf("     Codigo: %d \n",cliente.Codigo);
            printf("       Nome: %s \n", cliente.Nome);
            printf("   Endereco: %s \n", cliente.Endereco);
            printf("Complemento: %s \n", cliente.Complemento);
            printf("        Cep: %s \n", cliente.Cep);
            printf("     Cidade: %s \n", cliente.Cidade);
            printf("     Estado: %s \n", cliente.Estado);
            printf("      Email: %s \n", cliente.Email);
            printf("   Telefone: %s \n", cliente.Telefone);

            encontrado = 1;
            system("pause>nul");
            system("cls || clear");
            montarMenu("Clientes");
        }
    }
    if (!encontrado)
    {
        printf("\nCodigo nao cadastrado!!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Produtos");
    }
    fclose(arqCliente);
}
/* Função para alterar os dados do cliente */
void alterarCliente()
{
    arqCliente = fopen("cliente.pim", "r+b");
    if (arqCliente == NULL)
    {
        printf("Arquivo inexistente!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Clintes");
    }

    struct Cliente cliente;
    int cod, encontrado = 0;
    printf ("\nDigite o codigo que deseja alterar: \n");
    scanf ("%d", &cod);

    /* Busca código no arquivo*/
    while (fread (&cliente, sizeof(cliente), 1, arqCliente))
    {
        if (cod == cliente.Codigo)
        {
            printf("     Codigo: %d \n", cliente.Codigo);
            printf("       Nome: %s \n", cliente.Nome);
            printf("   Endereco: %s \n", cliente.Endereco);
            printf("Complemento: %s \n", cliente.Complemento);
            printf("        Cep: %s \n", cliente.Cep);
            printf("     Cidade: %s \n", cliente.Cidade);
            printf("     Estado: %s \n", cliente.Estado);
            printf("      Email: %s \n", cliente.Email);
            printf("   Telefone: %s \n", cliente.Telefone);

            encontrado = 1;

            fseek(arqCliente,sizeof(struct Cliente)*-1, SEEK_CUR);
            printf("\nTecle algo para as alterações \n");
            system("pause>nul");
            system("cls");

            printf("Nome: %s \n", cliente.Nome);
            fflush(stdin);
            gets(cliente.Nome);

            printf("Endereço: %s \n", cliente.Endereco);
            fflush(stdin);
            gets(cliente.Endereco);

            printf("Complemento : %s \n", cliente.Complemento);
            fflush(stdin);
            gets(cliente.Complemento);

            printf("Cep: %s \n", cliente.Cep);
            fflush(stdin);
            gets(cliente.Cep);

            printf("Cidade: %s \n", cliente.Cidade);
            fflush(stdin);
            gets(cliente.Cidade);

            printf("Estado: %s \n", cliente.Estado);
            fflush(stdin);
            gets(cliente.Estado);

            printf("E-mail: %s \n", cliente.Email);
            fflush(stdin);
            gets(cliente.Email);

            printf("Telefone: %s \n", cliente.Telefone);
            fflush(stdin);
            gets(cliente.Telefone);

            fwrite(&cliente, sizeof(cliente), 1, arqCliente);
            fseek(arqCliente, sizeof(cliente)* 0, SEEK_END);

            printf("\n Dados do cliente alterados com sucesso!");
            system("pause>nul");
            system("cls || clear");
            montarMenu("Clientes");
        }
    }
    if (!encontrado)
    {
        printf("\nCódigo não cadastrado!!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Clientes");
    }
    fclose(arqCliente);
}
/* Função que exclui os clientes */
void excluirCliente()
{
    arqCliente = fopen("cliente.pim", "r+b");
    if (arqCliente == NULL)
    {
        printf("Arquivo inexistente!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Clientes");
    }
    struct Cliente cliente;
    int cod, encontrado = 0;
    char certeza;
    printf ("\nDigite o codigo que deseja EXCLUIR: \n");
    scanf ("%d", &cod);

    while (fread (&cliente, sizeof(cliente), 1, arqCliente))
    {
        if (cod == cliente.Codigo)
        {
            printf("       Nome: %s \n", cliente.Nome);
            printf("   Endereco: %s \n", cliente.Endereco);
            printf("Complemento: %s \n", cliente.Complemento);
            printf("        Cep: %s \n", cliente.Cep);
            printf("     Cidade: %s \n", cliente.Cidade);
            printf("     Estado: %s \n", cliente.Estado);
            printf("      Email: %s \n", cliente.Email);
            printf("   Telefone: %s \n", cliente.Telefone);

            encontrado = 1;

            printf("\nTem certeza que quer excluir este cliente? s/n \n");
            fflush(stdin);
            scanf("%c", &certeza);
            if (certeza == 's')
            {
                cliente.Ativo = '*';
                fseek(arqCliente,sizeof(struct Cliente)*-1, SEEK_CUR);
                fwrite(&cliente, sizeof(cliente), 1, arqCliente);
                fseek(arqCliente, sizeof(cliente)* 0, SEEK_END);
                printf("\nCliente excluido com Sucesso! \n");
                system("pause>nul");
                system("cls || clear");
                montarMenu("Clientes");
            }
            else if (certeza == 'n')
            {
                system("cls || clear");
                montarMenu("Clientes");
            }
        }
    }
    if (!encontrado)
    {
        printf ("\nCodigo nao cadastrado!!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Clientes");
    }
    fclose(arqCliente);
}
/* Função para cadastrar umm funcionário */
void cadastrarFuncionario()
{
/* Define a estrutura do funcionario*/
    struct Funcionario funcionario;

    /* variável para tratar o retorno do arquivo*/
    int retorno;

    /* Recebe status para abrir o arquivo*/
    arqFuncionario = fopen("funcionario.pim", "ab");

    /* Verifica se teve sucesso na abetura do arquivo*/
    if (arqFuncionario == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    /* Recebe os dados digitados na tela*/
    printf("Código do funcionário: \n");
    scanf("%d", &funcionario.Codigo);

    printf("Nome: \n");
    fflush(stdin);
    gets(funcionario.Nome);

    printf("Data Nascimento: \n");
    fflush(stdin);
    gets(funcionario.DataNasc);

    printf("Endereço : \n");
    fflush(stdin);
    gets(funcionario.Endereco);

    printf("Complemento : \n");
    fflush(stdin);
    gets(funcionario.Complemento);

    printf("Cep: \n");
    fflush(stdin);
    gets(funcionario.Cep);

    printf("Cidade: \n");
    fflush(stdin);
    gets(funcionario.Cidade);

    printf("Estado: \n");
    fflush(stdin);
    gets(funcionario.Estado);

    printf("E-mail: \n");
    fflush(stdin);
    gets(funcionario.Email);

    printf("Salário: \n");
    scanf("%f", &funcionario.Salario);

    funcionario.Ativo = "S";

    /* Grava dados do funcionário */
    retorno = fwrite (&funcionario, sizeof(funcionario), 1, arqFuncionario);

    /* verifica se houve sucesso na gravação */
    if (retorno == 1)
    {
        fclose (arqFuncionario);
        printf("\n Dados do funcionário incluídos com sucesso!");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Clientes");
    }
    else
    {
        fclose (arqFuncionario);
        printf("\n Falha ao gravar dados do funcionário.");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Funcionarios");
    }
}
/* Função para consultar um funcionário */
void consultarFuncionario()
{
    arqFuncionario = fopen("funcionario.pim", "rb");
    if (arqFuncionario == NULL)
    {
        printf("Arquivo inexistente!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Funcionarios");
    }
    /* Carrega estruct de clientes */
    struct Funcionario funcionario;

    int cod, encontrado = 0;
    printf ("\nDigite o codigo que procura: \n");
    scanf ("%d", &cod);

    while (fread (&funcionario, sizeof(funcionario), 1, arqFuncionario))
    {
        if ((cod == funcionario.Codigo) && (funcionario.Ativo != '*'))
        {
            printf("         Codigo: %d \n", funcionario.Codigo);
            printf("           Nome: %s \n", funcionario.Nome);
            printf("Data Nascimento: %s \n", funcionario.DataNasc);
            printf("       Endereco: %s \n", funcionario.Endereco);
            printf("    Complemento: %s \n", funcionario.Complemento);
            printf("            Cep: %s \n", funcionario.Cep);
            printf("         Cidade: %s \n", funcionario.Cidade);
            printf("         Estado: %s \n", funcionario.Estado);
            printf("          Email: %s \n", funcionario.Email);
            printf("        Salario: %f \n", funcionario.Salario);

            encontrado = 1;
            system("pause>nul");
            system("cls || clear");
            montarMenu("Clientes");
        }
    }
    if (!encontrado)
    {
        printf("\nCodigo nao cadastrado!!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Funcionarios");
    }
    fclose(arqFuncionario);
}
/* Função para alterar os dados de um funcionário */
void alterarFuncionario()
{
    arqFuncionario = fopen("funcionario.pim", "r+b");
    if (arqFuncionario == NULL)
    {
        printf("Arquivo inexistente!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Funcionario");
    }

    struct Funcionario funcionario;
    int cod, encontrado = 0;
    printf ("\nDigite o codigo que deseja alterar: \n");
    scanf ("%d", &cod);

    /* Busca código no arquivo*/
    while (fread (&funcionario, sizeof(funcionario), 1, arqFuncionario))
    {
        if (cod == funcionario.Codigo)
        {
            printf("         Codigo: %d \n", funcionario.Codigo);
            printf("           Nome: %s \n", funcionario.Nome);
            printf("Data Nascimento: %s \n", funcionario.DataNasc);
            printf("       Endereco: %s \n", funcionario.Endereco);
            printf("    Complemento: %s \n", funcionario.Complemento);
            printf("            Cep: %s \n", funcionario.Cep);
            printf("         Cidade: %s \n", funcionario.Cidade);
            printf("         Estado: %s \n", funcionario.Estado);
            printf("          Email: %s \n", funcionario.Email);
            printf("        Salario: %f \n", funcionario.Salario);

            encontrado = 1;

            fseek(arqFuncionario,sizeof(struct Funcionario)*-1, SEEK_CUR);
            printf("\nTecle algo para as alterações \n");
            system("pause>nul");
            system("cls");

            printf("Nome: %s \n", funcionario.Nome);
            fflush(stdin);
            gets(funcionario.Nome);

            printf("Data Nascimento: %s \n", funcionario.DataNasc);
            fflush(stdin);
            gets(funcionario.DataNasc);

            printf("Endereço: %s \n", funcionario.Endereco);
            fflush(stdin);
            gets(funcionario.Endereco);

            printf("Complemento : %s \n", funcionario.Complemento);
            fflush(stdin);
            gets(funcionario.Complemento);

            printf("Cep: %s \n", funcionario.Cep);
            fflush(stdin);
            gets(funcionario.Cep);

            printf("Cidade: %s \n", funcionario.Cidade);
            fflush(stdin);
            gets(funcionario.Cidade);

            printf("Estado: %s \n", funcionario.Estado);
            fflush(stdin);
            gets(funcionario.Estado);

            printf("E-mail: %s \n", funcionario.Email);
            fflush(stdin);
            gets(funcionario.Email);

            printf("Salario: %f \n", funcionario.Salario);
            scanf("%f", funcionario.Salario);

            fwrite(&funcionario, sizeof(funcionario), 1, arqFuncionario);
            fseek(arqFuncionario, sizeof(funcionario)* 0, SEEK_END);

            printf("\n Dados do funcionario alterados com sucesso!");
            system("pause>nul");
            system("cls || clear");
            montarMenu("Funcionrios");
        }
    }
    if (!encontrado)
    {
        printf("\nCódigo não cadastrado!!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Funcionarios");
    }
    fclose(arqFuncionario);
}
/* Função para excluir um funcionário */
void excluirFuncionario()
{
    arqFuncionario = fopen("funcionario.pim", "r+b");
    if (arqFuncionario == NULL)
    {
        printf("Arquivo inexistente!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Funcionarios");
    }
    struct Funcionario funcionario;
    int cod, encontrado = 0;
    char certeza;
    printf ("\nDigite o codigo que deseja EXCLUIR: \n");
    scanf ("%d", &cod);

    while (fread (&funcionario, sizeof(funcionario), 1, arqFuncionario))
    {
        if (cod == funcionario.Codigo)
        {
            printf("           Nome: %s \n", funcionario.Nome);
            printf("Data Nascimento: %s \n", funcionario.DataNasc);
            printf("       Endereco: %s \n", funcionario.Endereco);
            printf("    Complemento: %s \n", funcionario.Complemento);
            printf("            Cep: %s \n", funcionario.Cep);
            printf("         Cidade: %s \n", funcionario.Cidade);
            printf("         Estado: %s \n", funcionario.Estado);
            printf("          Email: %s \n", funcionario.Email);
            printf("        Salário: %f \n", funcionario.Salario);

            encontrado = 1;

            printf("\nTem certeza que quer excluir este funcionario? s/n \n");
            fflush(stdin);
            scanf("%c", &certeza);
            if (certeza == 's')
            {
                funcionario.Ativo = '*';
                fseek(arqFuncionario,sizeof(struct Funcionario)*-1, SEEK_CUR);
                fwrite(&funcionario, sizeof(funcionario), 1, arqFuncionario);
                fseek(arqFuncionario, sizeof(funcionario)* 0, SEEK_END);
                printf("\nFuncionário excluido com Sucesso! \n");
                system("pause>nul");
                system("cls || clear");
                montarMenu("Funcionarios");
            }
            else if (certeza == 'n')
            {
                system("cls || clear");
                montarMenu("Funcionarios");
            }
        }
    }
    if (!encontrado)
    {
        printf ("\nCodigo nao cadastrado!!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Funcionarios");
    }
    fclose(arqFuncionario);
}

void cadastrarPerfil()
{
    /* Define a estrutura do perfil*/
    struct Perfil perfil;

    /* variável para tratar o retorno do arquivo*/
    int retorno;

    /* Recebe status para abrir o arquivo*/
    arqPerfil = fopen("perfil.pim", "ab");

    /* Verifica se teve sucesso na abetura do arquivo*/
    if (arqPerfil == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    /* Recebe os dados digitados na tela*/
    printf("Código do Perfil: ");
    scanf("%d", &perfil.Codigo);

    printf("Login: ");
    fflush(stdin);
    gets(perfil.Login);

    printf("Nome : ");
    fflush(stdin);
    gets(perfil.Nome);

    printf("Senha : ");
    fflush(stdin);
    gets(perfil.Senha);

    perfil.Ativo = "S";

    /* Grava dados do perfil */
    retorno = fwrite (&perfil, sizeof(perfil), 1, arqPerfil);

    /* verifica se houve sucesso na gravação */
    if (retorno == 1)
    {
        fclose (arqPerfil);
        printf("\n Dados do perfil incluídos com sucesso!");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Perfil");
    }
    else
    {
        fclose (arqPerfil);
        printf("\n Falha ao gravar dados do perfil.");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Perfil");
    }
}
/* Função para Consultar o perfil */
void consultarPerfil()
{
    arqPerfil = fopen("perfil.pim", "rb");
    if (arqPerfil == NULL)
    {
        printf("Arquivo inexistente!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Perfil");
    }
    /* Carrega estruct de clientes */
    struct Perfil perfil;

    int cod, encontrado = 0;
    printf ("\nDigite o codigo que procura: \n");
    scanf ("%d", &cod);

    while (fread (&perfil, sizeof(perfil), 1, arqPerfil))
    {
        if ((cod == perfil.Codigo) && (perfil.Ativo != '*'))
        {
            printf("     Codigo: %d \n", perfil.Codigo);
            printf("      Login: %s \n", perfil.Login);
            printf("       Nome: %s \n", perfil.Nome);
            printf("      Senha: %s \n", perfil.Senha);

            encontrado = 1;
            system("pause>nul");
            system("cls || clear");
            montarMenu("Perfil");
        }
    }
    if (!encontrado)
    {
        printf("\nCodigo nao cadastrado!!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Perfil");
    }
    fclose(arqPerfil);
}
void alterarPerfil()
{
    arqPerfil = fopen("perfil.pim", "r+b");
    if (arqPerfil == NULL)
    {
        printf("Arquivo inexistente!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Perfil");
    }

    struct Perfil perfil;
    int cod, encontrado = 0;
    printf ("\nDigite o codigo que deseja alterar: \n");
    scanf ("%d", &cod);

    /* Busca código no arquivo*/
    while (fread (&perfil, sizeof(perfil), 1, arqPerfil))
    {
        if (cod == perfil.Codigo)
        {
            printf("     Codigo: %d \n", perfil.Codigo);
            printf("      Login: %d \n", perfil.Login);
            printf("       Nome: %s \n", perfil.Nome);
            printf("      Senha: %s \n", perfil.Senha);

            encontrado = 1;

            fseek(arqPerfil,sizeof(struct Perfil)*-1, SEEK_CUR);
            printf("\nTecle algo para as alterações \n");
            system("pause>nul");
            system("cls");

            printf("Login: %s \n", perfil.Login);
            fflush(stdin);
            gets(perfil.Login);

            printf("Nome: %s \n", perfil.Nome);
            fflush(stdin);
            gets(perfil.Nome);

            printf("Senha: %s \n", perfil.Senha);
            fflush(stdin);
            gets(perfil.Senha);

            fwrite(&perfil, sizeof(perfil), 1, arqPerfil);
            fseek(arqPerfil, sizeof(perfil)* 0, SEEK_END);

            printf("\n Dados do perfil alterados com sucesso!");
            system("pause>nul");
            system("cls || clear");
            montarMenu("Perfil");
        }
    }
    if (!encontrado)
    {
        printf("\nCódigo não cadastrado!!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Perfil");
    }
    fclose(arqPerfil);
}
/* Função para excluir o perfil */
void excluirPerfil()
{
    arqPerfil = fopen("perfil.pim", "r+b");
    if (arqPerfil == NULL)
    {
        printf("Arquivo inexistente!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Perfil");
    }
    struct Perfil perfil;
    int cod, encontrado = 0;
    char certeza;
    printf ("\nDigite o codigo que deseja EXCLUIR: \n");
    scanf ("%d", &cod);

    while (fread (&perfil, sizeof(perfil), 1, arqPerfil))
    {
        if (cod == perfil.Codigo)
        {
            printf("      Login: %s \n", perfil.Login);
            printf("       Nome: %s \n", perfil.Nome);
            printf("      Senha: %s \n", perfil.Senha);

            encontrado = 1;

            printf("\nTem certeza que quer excluir este perfil? s/n \n");
            fflush(stdin);
            scanf("%c", &certeza);
            if (certeza == 's')
            {
                perfil.Ativo = '*';
                fseek(arqPerfil,sizeof(struct Perfil)*-1, SEEK_CUR);
                fwrite(&perfil, sizeof(perfil), 1, arqPerfil);
                fseek(arqPerfil, sizeof(perfil)* 0, SEEK_END);
                printf("\nPerfil excluido com Sucesso! \n");
                system("pause>nul");
                system("cls || clear");
                montarMenu("Perfil");
            }
            else if (certeza == 'n')
            {
                system("cls || clear");
                montarMenu("Perfil");
            }
        }
    }
    if (!encontrado)
    {
        printf ("\nCodigo nao cadastrado!!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Perfil");
    }
    fclose(arqPerfil);
}

/* Relatorio de clientes */
void relatorioClientesAtivos()
{
        arqCliente = fopen("cliente.pim", "rb");
    if (arqCliente == NULL)
    {
        printf("Arquivo inexistente!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Clientes");
    }
    /* Carrega estruct de clientes */
    struct Cliente cliente;

    int cod, encontrado = 0;

    while (fread (&cliente, sizeof(cliente), 1, arqCliente))
    {
        if ((cod == cliente.Codigo) && (cliente.Ativo != '*'))
        {
            printf("Cod. %d     Nome %-20s      Endereço %10s       Cep %s      Cidade %s   Est %s      Email %s        Tel. %s",cliente.Codigo, cliente.Nome, cliente.Endereco, cliente.Complemento, cliente.Cep, cliente.Cidade, cliente.Estado, cliente.Email, cliente.Telefone);

            encontrado = 1;
            system("pause>nul");
            system("cls || clear");
            montarMenu("Clientes");
        }
    }
    if (!encontrado)
    {
        printf("\nCodigo nao cadastrado!!\n");
        system("pause>nul");
        system("cls || clear");
        montarMenu("Produtos");
    }
    fclose(arqCliente);
}

