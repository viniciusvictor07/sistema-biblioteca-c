# 📚 Sistema de Gerenciamento de Biblioteca

Sistema desenvolvido em **Linguagem C** com arquitetura modular e persistência em arquivo de texto. O software oferece controle completo sobre o acervo bibliográfico, permitindo cadastrar, buscar, atualizar, excluir, emprestar e gerar relatórios numéricos do acervo.

---

## 🚀 Funcionalidades

- **Cadastro de Livros:** Geração automática de ID/Código sequencial e validação estrita de dados de entrada.
- **Listagem Geral:** Exibição clara e organizada de todos os livros cadastrados.
- **Busca Flexível:** Pesquisa por código único ou por busca parcial (substring) no título.
- **Atualização e Remoção:** Edição completa de registros e exclusão com reordenação do vetor em memória.
- **Gerenciamento de Empréstimo:** Alternância simples de status entre *Disponível* e *Emprestado*.
- **Estatísticas do Acervo:** Painel numérico com total de livros, exemplares disponíveis e emprestados.
- **Persistência de Dados:** Salvamento e carregamento automático em arquivo texto (`livros.txt`) com formatação em delimitadores `;`.

---

## 📁 Estrutura do Projeto

| Arquivo | Descrição |
| :--- | :--- |
| `src/main.c` | Ponto de entrada da aplicação e loop do menu interativo. |
| `src/livros.h` | Definição da `struct Livro`, constantes globais (`MAX_LIVROS`, `ANO_ATUAL`) e protótipos das funções do acervo. |
| `src/livros.c` | Implementação das regras de negócio e rotinas auxiliares de validação de dados. |
| `src/arquivo.h` | Configuração do caminho do arquivo (`CAMINHO_DADOS`) e declaração das rotinas de arquivo. |
| `src/arquivo.c` | Leitura e gravação de dados em disco (`livros.txt`). |

---

## 🏗️ Estrutura de Dados

```c
typedef struct {
    int codigo;           // Identificador único sequencial
    char titulo[50];      // Título da obra
    char autor[50];       // Autor da obra
    char categoria[30];   // Categoria da obra
    int ano;              // Ano de publicação (validado de 1 até ANO_ATUAL)
    int disponivel;       // Status (1 - Disponível / 0 - Emprestado)
} Livro;
```

---

## 🛠️ Compilação e Execução

Para compilar todo o projeto utilizando o **GCC**, execute o comando no terminal:

```bash
gcc src/main.c src/livros.c src/arquivo.c -I src -o biblioteca
```

Para rodar a aplicação:

```bash
./biblioteca
```

---

## 📋 Formato de Armazenamento (`livros.txt`)

Os dados são armazenados linha por linha no arquivo de texto utilizando o seguinte padrão:

```text
CODIGO;TITULO;AUTOR;CATEGORIA;ANO;DISPONIVEL
```

**Exemplo:**
```text
1;Dom Casmurro;Machado de Assis;Romance;1899;1
2;O Hobbit;J.R.R. Tolkien;Fantasia;1937;0
```

---

## 🛡️ Destaques Técnicos & Validações

- **Tratamento de Entrada Numérica (`lerInteiro`):** Impede travamentos ou loops infinitos no `scanf` caso o usuário digite texto onde se espera um número.
- **Tratamento de Strings (`lerString`):** Garante a remoção da quebra de linha `\n` capturada pelo `fgets` e impede o envio de campos vazios.
- **Reaproveitamento de Código (`pedirEBuscarIndice`):** Centraliza a validação e busca de código de livros para reduzir repetições nas rotinas de remoção, edição e empréstimo.
