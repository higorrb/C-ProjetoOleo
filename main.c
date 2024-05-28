#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    long int dia, mes, ano;
    double litragem;
    char nome_arquivo[30];
}dados;


int Adicionar_dados(dados *reg, int *indice_registros){


    FILE *arquivo = fopen(reg->nome_arquivo, "r");
        if(arquivo == NULL){
            printf("Erro ao abrir o arquivo");
            return 1;}
   
   
    char linha[20];
   
    while(fgets(linha, sizeof(linha), arquivo) != NULL){


        sscanf(linha,"%2li/%li/%4li %lf", &reg[*indice_registros].dia, &reg[*indice_registros].mes, &reg[*indice_registros].ano, &reg[*indice_registros].litragem);
               
        printf("Dia: %li\n", reg[*indice_registros].dia);
        printf("Mes: %li\n", reg[*indice_registros].mes);
        printf("Ano: %li\n", reg[*indice_registros].ano);
        printf("Litragem: %.2f\n", reg[*indice_registros].litragem);


    (*indice_registros)++;
    }
   
    fclose(arquivo);
    return 0;
}

int Dados_para_csv(dados *reg, int *indice_registros){
    
    int i;
    
    FILE *arquivo = fopen("ListaDados.csv", "w");
        if(arquivo == NULL){
            printf("Erro ao abrir o arquivo");
            return 1;}
    
    fprintf(arquivo,"DIA;MES;ANO;LITRAGEM\n");
    
    for(i = 0; i < *indice_registros; i++){
        fprintf(arquivo, "%li;%li;%li;%.2f\n", reg[i].dia,reg[i].mes,reg[i].ano,reg[i].litragem);
    }
    
    fclose(arquivo);
    return 0;
    
}

int main(int argc, char *argv[])
{
    dados reg[1000];
    int indice_registros = 0;




    if (argc < 2) {
        fprintf(stderr, "Uso: %s <nome_do_arquivo>\n", argv[0]);
        return 1;
    }


    strncpy(reg[indice_registros].nome_arquivo, argv[1], sizeof(reg[indice_registros].nome_arquivo) - 1);
    reg[indice_registros].nome_arquivo[sizeof(reg[indice_registros].nome_arquivo) - 1] = '\0';


   
    Adicionar_dados(reg, &indice_registros);
    Dados_para_csv(reg, &indice_registros);


   
   
    return 0;
}