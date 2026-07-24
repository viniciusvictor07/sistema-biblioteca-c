#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"

void salvarLivros(Livro biblioteca[], int totalLivros) {
    FILE *arquivo = fopen(CAMINHO_DADOS, "w");
    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel criar/abrir o arquivo para salvar.\n");
        return;
    }

    for (int i = 0; i < totalLivros; i++) {
        fprintf(arquivo, "%d;%s;%s;%d;%d\n", 
                biblioteca[i].codigo, 
                biblioteca[i].titulo, 
                biblioteca[i].autor, 
                biblioteca[i].ano, 
                biblioteca[i].disponivel);
    }

    fclose(arquivo);
    printf("\n[SUCESSO] %d livro(s) salvo(s) com sucesso em 'livros.txt'!\n", totalLivros);
}

void carregarLivros(Livro biblioteca[], int *totalLivros) {
    FILE *arquivo = fopen(CAMINHO_DADOS, "r");
    if (arquivo == NULL) {
        printf("\n[AVISO] Nenhum arquivo 'livros.txt' encontrado para carregar.\n");
        return;
    }

    *totalLivros = 0;
    while (fscanf(arquivo, "%d;%49[^;];%49[^;];%d;%d\n", 
                  &biblioteca[*totalLivros].codigo, 
                  biblioteca[*totalLivros].titulo, 
                  biblioteca[*totalLivros].autor, 
                  &biblioteca[*totalLivros].ano, 
                  &biblioteca[*totalLivros].disponivel) == 5) {
        (*totalLivros)++;
    }

    fclose(arquivo);
    printf("\n[SUCESSO] %d livro(s) carregado(s) com sucesso!\n", *totalLivros);
}