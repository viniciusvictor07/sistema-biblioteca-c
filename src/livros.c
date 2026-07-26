#include "livros.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Funções Principais ---
void cadastrarLivro(Livro biblioteca[], int *totalLivros, int *proximoCodigo) {
    if (bibliotecaCheia(*totalLivros)) return;

    Livro novoLivro;
    novoLivro.codigo = *proximoCodigo;

    printf("\n--- CADASTRO DE NOVO LIVRO ---\n");
    printf("Codigo: %d\n", novoLivro.codigo);

    printf("Digite o titulo: ");
    lerString(novoLivro.titulo, sizeof(novoLivro.titulo));

    printf("Digite o autor: ");
    lerString(novoLivro.autor, sizeof(novoLivro.autor));

    strcpy(novoLivro.categoria, escolherCategoria());

    novoLivro.ano = lerInteiro("Digite o ano de publicacao: ", 1, ANO_ATUAL);
    novoLivro.disponivel = lerInteiro("O livro esta disponivel? (1 - Sim / 0 - Nao): ", 0, 1);

    biblioteca[*totalLivros] = novoLivro;
    (*totalLivros)++;
    (*proximoCodigo)++;

    printf("\nLivro cadastrado com sucesso!\n");
}

void exibirTodosLivros(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;

    printf("\n=== LISTA DE LIVROS CADASTRADOS ===\n");
    for (int i = 0; i < totalLivros; i++) {
        exibirLivro(biblioteca[i]);
    }
}

void buscarLivroPorCodigo(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;

    printf("\n--- BUSCAR LIVRO ---\n");
    int indice = pedirEBuscarIndice(biblioteca, totalLivros);
    if (indice != -1) {
        exibirLivro(biblioteca[indice]);
    }
}

void buscarLivroPorTitulo(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;

    char tituloBuscado[50];
    printf("\n--- BUSCAR LIVRO POR TITULO ---\n");
    printf("Digite o titulo do livro: ");
    lerString(tituloBuscado, sizeof(tituloBuscado));

    int encontrados = 0;
    for (int i = 0; i < totalLivros; i++) {
        if (strstr(biblioteca[i].titulo, tituloBuscado) != NULL) {
            exibirLivro(biblioteca[i]);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\n[ERRO] Nenhum livro com o titulo \"%s\" foi encontrado.\n", tituloBuscado);
    }
}

void atualizarLivro(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;

    printf("\n--- ATUALIZAR LIVRO ---\n");
    exibirTodosLivros(biblioteca, totalLivros);

    int indice = pedirEBuscarIndice(biblioteca, totalLivros);
    if (indice == -1) return;

    printf("\nDigite o novo titulo: ");
    lerString(biblioteca[indice].titulo, sizeof(biblioteca[indice].titulo));

    printf("Digite o novo autor: ");
    lerString(biblioteca[indice].autor, sizeof(biblioteca[indice].autor));

    printf("Digite a nova categoria: ");
    strcpy(biblioteca[indice].categoria, escolherCategoria());

    biblioteca[indice].ano = lerInteiro("Digite o novo ano de publicacao: ", 1, ANO_ATUAL);
    biblioteca[indice].disponivel = lerInteiro("O livro esta disponivel? (1 - Sim / 0 - Nao): ", 0, 1);

    printf("\n[SUCESSO] Informacoes do livro atualizadas com sucesso!\n");
}

void excluirLivro(Livro biblioteca[], int *totalLivros) {
    if (bibliotecaVazia(*totalLivros)) return;

    printf("\n--- REMOVER LIVRO ---\n");
    exibirTodosLivros(biblioteca, *totalLivros);

    int indice = pedirEBuscarIndice(biblioteca, *totalLivros);
    if (indice == -1) return;

    for (int i = indice; i < *totalLivros - 1; i++) {
        biblioteca[i] = biblioteca[i + 1];
    }

    (*totalLivros)--;
    printf("\nLivro removido com sucesso!\n");
}

void exibirLivrosDisponiveis(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;

    printf("\n=== LIVROS DISPONIVEIS ===\n");

    int encontrados = 0;
    for (int i = 0; i < totalLivros; i++) {
        if (biblioteca[i].disponivel) {
            exibirLivro(biblioteca[i]);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum livro disponivel no momento.\n");
    }
    printf("===========================\n");
}

// --- Funções Extras ---
void alterarStatusEmprestimo(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;

    printf("\n--- ALTERAR STATUS DE EMPRESTIMO ---\n");
    exibirTodosLivros(biblioteca, totalLivros);

    int indice = pedirEBuscarIndice(biblioteca, totalLivros);
    if (indice == -1) return;

    biblioteca[indice].disponivel = !biblioteca[indice].disponivel;
    printf("\n[SUCESSO] Status do livro '%s' alterado para: %s\n",
           biblioteca[indice].titulo,  //
           biblioteca[indice].disponivel ? "Disponivel" : "Emprestado");
}

void exibirEstatisticas(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) return;

    int disponiveis = 0;
    int emprestados = 0;

    for (int i = 0; i < totalLivros; i++) {
        if (biblioteca[i].disponivel) {
            disponiveis++;
        } else {
            emprestados++;
        }
    }

    printf("\n=== ESTATISTICAS DA BIBLIOTECA ===\n");
    printf("Total de livros cadastrados: %d\n", totalLivros);
    printf("Livros disponiveis: %d\n", disponiveis);
    printf("Livros emprestados: %d\n", emprestados);
    printf("==================================\n");
}

void buscarLivrosPorCategoria(Livro biblioteca[], int totalLivros) {
    if (bibliotecaVazia(totalLivros)) {
        return;
    }

    const char *categoriaSelecionada = escolherCategoria();
    int encontrados = 0;

    limparTela();
    printf("=== LIVROS DA CATEGORIA: %s ===\n\n", categoriaSelecionada);

    for (int i = 0; i < totalLivros; i++) {
        if (strcmp(biblioteca[i].categoria, categoriaSelecionada) == 0) {
            exibirLivro(biblioteca[i]);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum livro encontrado para a categoria '%s'.\n", categoriaSelecionada);
    }
}

// --- Funções Auxiliares ---

// Validação e busca interna
int pedirEBuscarIndice(Livro biblioteca[], int totalLivros) {
    int codigo = lerInteiro("Digite o codigo do livro: ", 1, 999999);
    int indice = buscarIndicePorCodigo(biblioteca, totalLivros, codigo);

    if (indice == -1) {
        printf("\n[ERRO] Livro com o codigo %d nao foi encontrado.\n", codigo);
    }

    return indice;
}

int buscarIndicePorCodigo(Livro biblioteca[], int totalLivros, int codigoBuscado) {
    for (int i = 0; i < totalLivros; i++) {
        if (biblioteca[i].codigo == codigoBuscado) {
            return i;
        }
    }
    return -1;
}

int bibliotecaCheia(int totalLivros) {
    if (totalLivros >= MAX_LIVROS) {
        printf("\n[AVISO] A biblioteca esta cheia! Nao e possivel cadastrar mais livros.\n");
        return 1;
    }
    return 0;
}

int bibliotecaVazia(int totalLivros) {
    if (totalLivros <= 0) {
        printf("\n[AVISO] Nenhum livro cadastrado na biblioteca.\n");
        return 1;
    }
    return 0;
}

// Entrada e saída de dados
int lerInteiro(const char *mensagem, int min, int max) {
    int valor;
    int resultado;

    while (1) {
        printf("%s", mensagem);
        resultado = scanf("%d", &valor);
        limparBuffer();

        if (resultado == 1 && valor >= min && valor <= max) {
            return valor;
        }

        printf("[ERRO] Entrada invalida. Digite um numero entre %d e %d.\n", min, max);
    }
}

void lerString(char *buffer, int tamanho) {
    do {
        fgets(buffer, tamanho, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (buffer[0] == '\0') {
            printf("O campo nao pode ficar em branco. Digite novamente: ");
        }
    } while (buffer[0] == '\0');
}

const char *escolherCategoria(void) {
    printf("\n--- CATEGORIAS ---\n");
    printf("1. Ficcao Cientifica\n");
    printf("2. Fantasia\n");
    printf("3. Terror / Suspense\n");
    printf("4. Romance\n");
    printf("5. Historia\n");
    printf("6. Biografia\n");
    printf("7. Autoajuda\n");
    printf("8. Tecnologia / Programacao\n");
    printf("9. Didatico / Academico\n");
    printf("10. Outros\n");

    int opcao = lerInteiro("Digite a opcao desejada: ", 1, 10);

    switch (opcao) {
        case 1:
            return "Ficcao Cientifica";
        case 2:
            return "Fantasia";
        case 3:
            return "Terror / Suspense";
        case 4:
            return "Romance";
        case 5:
            return "Historia";
        case 6:
            return "Biografia";
        case 7:
            return "Autoajuda";
        case 8:
            return "Tecnologia / Programacao";
        case 9:
            return "Didatico / Academico";
        case 10:
            return "Outros";
        default:
            return "Outros";
    }
}

void exibirLivro(Livro livro) {
    printf("Codigo: %d | Titulo: %s | Autor: %s | Categoria: %s | Ano: %d | Status: %s\n",
           livro.codigo,     //
           livro.titulo,     //
           livro.autor,      //
           livro.categoria,  //
           livro.ano,        //
           livro.disponivel ? "Disponivel" : "Emprestado");
}

// Controle do terminal e fluxo
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void mostrarMenu() {
    printf("\n==========================================\n");
    printf("  SISTEMA DE GERENCIAMENTO DE BIBLIOTECA \n");
    printf("==========================================\n");
    printf("1.  Cadastrar novo livro\n");
    printf("2.  Exibir todos os livros\n");
    printf("3.  Buscar livro por codigo\n");
    printf("4.  Buscar livro por titulo\n");
    printf("5.  Atualizar dados de um livro\n");
    printf("6.  Excluir livro\n");
    printf("7.  Exibir livros disponiveis\n");
    printf("8.  Emprestar/Devolver livro (Extra)\n");
    printf("9.  Exibir estatisticas da biblioteca (Extra)\n");
    printf("10. Exibir livros por categoria (Extra)\n");
    printf("11. Salvar dados no arquivo\n");
    printf("0.  Sair\n");
    printf("------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

void pausar(void) {
    printf("\nPressione ENTER para continuar...");
    limparBuffer();
}