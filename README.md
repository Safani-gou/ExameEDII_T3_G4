# 💧 Sistema de Gestão de Rede Hidráulica

```
Grupo:            4
Disciplina:       Estrutura de Dados II
Categoria:        Exame Final da Disciplina
Linguagem:        C
Ano:              2025 - 2026
Repositório:      https://github.com/Safani-gou/ExameEDII_T3_G4
```

### 👥 Membros do Grupo

```
Estefani Famorosa       Nº: 20240217
Jorge Veloso            Nº: 20241500
Josemar Chipandeca      Nº: 20242447
```

---

## 🎯 Objectivo do Projecto

Desenvolver um sistema em linguagem C que simule o planeamento e gestão de uma rede de distribuição de água numa cidade. O sistema permite cadastrar pontos da rede (reservatórios, casas, escolas e hospitais), criar ligações entre eles com custo e distância, e determinar a rede de menor custo utilizando algoritmos de grafos.

---

## ⚙️ Modo de Funcionamento

Ao iniciar o programa, o ficheiro `dados_entrada.txt` é lido **automaticamente** e o grafo é construído sem qualquer intervenção do utilizador:

```
[INFO] Ficheiro 'dados_entrada.txt' encontrado. A carregar dados...
[SUCESSO] Grafo construido automaticamente.
          Pontos: 8 | Ligacoes: 9
```

A partir daí, o utilizador interage com o sistema através de um menu interativo no terminal.

---

## 🗂️ Menu Principal

```
=======================================================
  SISTEMA DE GESTAO DE REDE HIDRAULICA
=======================================================
  1. Gerir Pontos da Rede
  2. Gerir Ligacoes
  3. Visualizar Grafo
  4. Algoritmos de Ordenacao
  5. Algoritmos de Busca
  6. Estruturas de Dados
  7. Rede de Menor Custo (MST)
  8. Estatisticas
  9. Ficheiros (Carregar/Salvar)
  0. Sair
```

---

## 🔧 Funções Principais

| Módulo | Funcionalidades |
|---|---|
| **Pontos** | Inserir, remover, listar pontos da rede |
| **Ligações** | Adicionar, remover, listar ligações (tubagens) |
| **Grafo** | Visualização da lista de adjacência |
| **Ordenação** | Insertion, Selection, Shell, Merge, Quick, Heap Sort com medição de tempo |
| **Busca** | Linear, Binária, AVL, Hash, por Nome |
| **MST** | Kruskal e Prim para rede de menor custo |
| **Estatísticas** | Total de pontos, ligações, custo, algoritmo mais rápido |
| **Ficheiros** | Leitura de `dados_entrada.txt` e escrita em `dados_saida.txt` |

---

## 📦 Tipos de Dados Definidos (TADs)

```c
/* Ponto da rede */
typedef struct {
    int id;
    char nome[100];
    TipoPonto tipo;   /* RESERVATORIO, CASA, ESCOLA, HOSPITAL */
} Ponto;

/* Ligação entre dois pontos */
typedef struct {
    int origem;
    int destino;
    float custo;      /* em Kwanzas */
    float distancia;  /* em metros */
} Ligacao;

/* Nó da lista de adjacência */
typedef struct NoAdj {
    int destino;
    float custo;
    float distancia;
    struct NoAdj* prox;
} NoAdj;
```

As estruturas de dados implementadas manualmente são:
- **BST** — Árvore Binária de Busca
- **AVL** — Árvore Balanceada com rotações automáticas
- **Hash Table** — Tabela Hash com encadeamento (tamanho primo 101)
- **Union-Find** — Para detecção de ciclos no algoritmo de Kruskal

---

## 📁 Integração de Ficheiros

O sistema usa dois ficheiros de dados:

**`dados_entrada.txt`** — carregado automaticamente ao arrancar:
```
# Formato dos pontos
PONTO id nome tipo

# Formato das ligações
LIGACAO origem destino custo distancia

# Exemplo
PONTO 1 Reservatorio_Central Reservatorio
PONTO 2 Escola_Primaria Escola
LIGACAO 1 2 1500.00 300.00
```

**`dados_saida.txt`** — gerado ao escolher a opção 9 → Salvar dados.

---

## 🗃️ Estrutura do Projecto

```
ExameEDII_T3_G4/
├── main.c              # Ponto de entrada + carregamento automático
├── ponto.h / ponto.c   # TAD Ponto
├── ligacao.h / ligacao.c  # TAD Ligação
├── grafo.h / grafo.c   # Grafo + Kruskal + Prim
├── bst.h / bst.c       # Árvore Binária de Busca
├── avl.h / avl.c       # Árvore AVL
├── hash.h / hash.c     # Tabela Hash
├── ordenacao.h / ordenacao.c  # 6 algoritmos de ordenação
├── busca.h / busca.c   # Algoritmos de busca
├── ficheiros.h / ficheiros.c  # Leitura e escrita de ficheiros
├── menu.h / menu.c     # Menu interativo
├── utils.h / utils.c   # Funções auxiliares
├── dados_entrada.txt   # Dados iniciais da rede
└── dados_saida.txt     # Dados gerados pelo sistema
```

---

## 🚀 Como Compilar e Executar (Windows)

```cmd
gcc -Wall -o rede main.c ponto.c ligacao.c grafo.c bst.c avl.c hash.c ordenacao.c busca.c ficheiros.c menu.c utils.c

rede.exe
```

## 🚀 Como Compilar e Executar (Linux/Mac)

```bash
gcc -Wall -o rede main.c ponto.c ligacao.c grafo.c bst.c avl.c hash.c ordenacao.c busca.c ficheiros.c menu.c utils.c

./rede
```

---

## 🏫 Informação Académica

- **Instituição:** Instituto Superior Politécnico de Tecnologias e Ciências (ISPTC)
- **Docente:** Sílvia António
- **Turma:** T3 | **Grupo:** 4
- **Semestre:** 2025/2
