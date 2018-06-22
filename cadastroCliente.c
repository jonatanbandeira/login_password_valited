#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> //Biblioteca para usar a funçao strcm
#include <ctype.h>
#include <locale.h>
#include <windows.h>

char nomeArquivo[20] = "cadastro.txt";

struct Pessoa{
    char login[30];
    int idade;
    char email[20];
    char senha[9];
};

// prototipação
void menu();
FILE *abrirArquivo(char modo, char *caminho);
void fecharArquivo(FILE *arquivo);
void inserirContato(struct Pessoa umaPessoa);
struct Pessoa lerLogin();
void validarCadastro(struct Pessoa umaPessoa);
void menutempo();

int main()
{
    int op;
    struct Pessoa umaPessoa;
    char nome[20];

    setlocale(LC_ALL, "Portuguese");


        menu();
        printf("\t|--------------Digite uma opcão-----------------|\n");
        printf("\t  Opção desejada: ");
        scanf("%d", &op);

        switch (op){
        case 1:
            system("cls");
            printf("\n\t-----------SISTEMA DE CADASTRO JLINVEST LTDA-------------");
            printf("\n\n\tDigite seu login: ");
            getchar();
            scanf("%[^\n]s", umaPessoa.login);
            printf("\tDigite uma senha de até 8 digitos: ");
            getchar();
            scanf("%[^\n]s", umaPessoa.senha);
            printf("\tDigite sua idade: ");
            scanf("%d", &umaPessoa.idade);
            printf("\tDigite seu E-mail: ");
            getchar();
            scanf("%[^\n]s", umaPessoa.email);

            if(umaPessoa.idade<18){
                printf("\n\n\tATENÇÃO: Sistema não disponível para menores de 18 anos!\n\n\n");
            }else{
                inserirContato(umaPessoa);
                puts("\n\n\t*************CASDASTRO REALIZADO COM SUCESSO**************\n\n");
                system("pause");
                system("cls");
                validarCadastro(umaPessoa);
            }

            system("pause");
            break;
        case 2:
            validarCadastro(umaPessoa);
            break;
        case 0:
            printf("\n\nFinalizando o sistema...\n\n");
            Sleep(2000);
            break;
        default:
            system("cls");
            printf("\n\nOpcao invalida!\n");
        }
    return 0;
    }


void menu(){

    puts("\n");

    printf("\t-------------BEM VINDO À JLINVEST LTDA ----------\n");
    printf("\t|                                               |\n");
    printf("\t| Digite 1 para cadastrar                       |\n");
    printf("\t| Digite 2 para logar                           |\n");
    printf("\t| Digite 0 para sair                            |\n");
    printf("\t|                                               |\n");
}

FILE *abrirArquivo(char modo, char *caminho){
    FILE *arquivo;

    switch (modo){
    case 'a':
        arquivo = fopen(caminho, "a");
        break;
    case 'r':
        arquivo = fopen(caminho, "rt");
        break;
    case 'w':
        arquivo = fopen(caminho, "wt");
        break;
    }
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo!");
        exit(0);
    }

    return arquivo;
}


 void validarCadastro(struct Pessoa umaPessoa){

    FILE *fp = fopen("cadastro.txt", "rt"); //"r" para ler o que tem no arquivo

    if (fp == NULL){
        printf("\nO arquivo não foi aberto!");
        exit(0);
    }

    char login[100], senha[100], str[2];
    int logou = 0;
    struct Pessoa pess;

    printf("\n\tLOGIN........: ");
    getchar();
    scanf("%[^\n]s" ,login);

    printf("\n\tSENHA........: ");
    getchar();
    scanf("%[^\n]s" ,senha);


    //printf("\nLogin: %s", login); //teste p ver o que estava imprimindo
    //printf("\nSenha: %s", senha); //teste p ver o que estava imprimindo

    while(!feof(fp)) {
        fscanf(fp, "%[^;]s", pess.login);
        fscanf(fp, ";%[^;]s", pess.senha);
        fscanf(fp, ";%d", &pess.idade);
        fscanf(fp, ";%s ", pess.email);
        if((strcmp(pess.login, login) == 0) && (strcmp(pess.senha, senha) == 0) ) {
            logou = 1;
        }
    }//Fim while

    fclose(fp);

    if (logou) {
        system("cls");
        printf("\n\tBEM VINDO! USUÁRIO LOGADO!\n");
        bemvindo();

    } else {
        system("cls");
        printf("\n\tNAO LOGADO! TENTE NOVAMENTE!\n");
        validarCadastro(umaPessoa);
        Sleep(2000);

    }

}


struct Pessoa lerLogin() {

    struct Pessoa p;

    printf("\n\tLOGIN........: ");
    gets(p.login);
    getchar();

    printf("\n\tSENHA........: ");
    gets(p.senha);
    getchar();

    return p;
}


void fecharArquivo(FILE *arquivo){
    fclose(arquivo);
}

void inserirContato(struct Pessoa umaPessoa){
    FILE *arquivo;
    arquivo = abrirArquivo('a', nomeArquivo);
    fprintf(arquivo, "%s;%s;%d;%s\n", umaPessoa.login, umaPessoa.senha, umaPessoa.idade, umaPessoa.email);
    fecharArquivo(arquivo);
}



