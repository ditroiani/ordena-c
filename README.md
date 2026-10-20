<div align="center">

# 🔢 OrdenaC

### Laboratório de Algoritmos de Ordenação em C

**Projeto acadêmico • Algoritmos e Pensamento Computacional • Atividade Avaliativa 03**

![Linguagem](https://img.shields.io/badge/Linguagem-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Status](https://img.shields.io/badge/Status-Em%20desenvolvimento-F59E0B?style=for-the-badge)
![Compilador](https://img.shields.io/badge/Compilador-GCC-555555?style=for-the-badge)

</div>

---

## 📖 Sobre o projeto

**OrdenaC** é um programa de terminal desenvolvido em linguagem **C** para estudar e comparar algoritmos de ordenação. O projeto faz parte da **Atividade Avaliativa 03** da disciplina de Algoritmos e Pensamento Computacional, no curso de Engenharia de Software.

A aplicação gera conjuntos de números pseudoaleatórios, registra os dados em arquivo TXT e permite carregá-los em memória. Ao longo do desenvolvimento, serão adicionados diferentes métodos de ordenação e recursos para comparar seus resultados e desempenho.

O projeto também é utilizado como prática de **ponteiros, alocação dinâmica de memória e manipulação de arquivos em C**.

> 🚧 **Em desenvolvimento:** o README acompanha a evolução do programa. As funcionalidades planejadas abaixo ainda não estão disponíveis na versão atual.

## ✅ Funcionalidades atuais

- [x] Menu interativo no terminal.
- [x] Geração de números pseudoaleatórios com `rand()` e inicialização da semente com `srand()`.
- [x] Definição da quantidade de números pelo usuário (de 1 a 10.000).
- [x] Gravação dos números em `data/dados.txt`, separados por vírgulas.
- [x] Leitura do arquivo TXT e carregamento dos números em um vetor.
- [x] Visualização dos dados originais.
- [x] Uso de `malloc()` e `free()` para gerenciamento de memória.

## 🛠️ Próximas funcionalidades

- [ ] Implementar **Bubble Sort**.
- [ ] Implementar **Insertion Sort**.
- [ ] Implementar **Selection Sort**.
- [ ] Implementar **Merge Sort**.
- [ ] Implementar **Quick Sort**.
- [ ] Permitir a escolha do método de ordenação no menu.
- [ ] Salvar os números ordenados em `output/ordenado.txt`.
- [ ] Alterar um número do arquivo original e executar nova ordenação.
- [ ] Comparar o tempo de execução dos algoritmos.
- [ ] Exportar resultados e medições para CSV.
- [ ] Importar um arquivo TXT fornecido pelo usuário.

## 📂 Estrutura do projeto

```text
atividade03/
├── main.c                 # Código-fonte principal
├── data/
│   └── dados.txt          # Números originais
├── output/                # Arquivos de saída (planejado)
│   ├── ordenado.txt
│   └── resultado.csv
├── logs/                  # Registros de desempenho (planejado)
│   └── benchmark.csv
└── README.md
```

> As pastas `output/` e `logs/` e seus arquivos representam a organização planejada e poderão ainda não existir na versão atual.

## ▶️ Como executar

### Pré-requisitos

- Compilador C, como **GCC** (por exemplo, MinGW no Windows).
- Terminal ou editor, como **Visual Studio Code**.

### Compilação

Abra o terminal na pasta do projeto e execute:

```bash
gcc -Wall -Wextra -std=c11 main.c -o ordenac.exe
```

No **Windows (PowerShell)**, execute:

```powershell
.\ordenac.exe
```

> Antes de gerar números, certifique-se de que a pasta `data/` existe na raiz do projeto. Execute o programa a partir dessa raiz, pois os caminhos dos arquivos são relativos.

## 🧪 Exemplo de uso

1. Execute o programa e selecione **1 — Criar arquivo de números**.
2. Informe quantos números deseja gerar (por exemplo, `5`).
3. O programa salvará os dados em `data/dados.txt`:

```text
45,12,89,3,27
```

4. Selecione **3 — Visualizar dados originais** para conferir os números carregados do arquivo.

*Os valores acima são ilustrativos; os números gerados pelo programa variam.*

## 🧠 Conceitos praticados

| Conceito | Aplicação no projeto |
|---|---|
| Funções | Separação de responsabilidades do programa |
| Ponteiros | Acesso e alteração de dados por endereço |
| Memória dinâmica | Alocação e liberação com `malloc()` e `free()` |
| Arquivos | Escrita e leitura com `fopen()`, `fprintf()`, `fscanf()` e `fclose()` |
| Vetores | Armazenamento dos números para processamento |
| Estruturas de controle | Menu com `switch`, repetições com `for` e `while` |
| Algoritmos | Implementação e comparação dos métodos de ordenação (em desenvolvimento) |

## 🎯 Objetivos de aprendizagem

- Aplicar conceitos de programação estruturada em C.
- Manipular arquivos de texto e vetores de inteiros.
- Praticar alocação dinâmica e gerenciamento de memória.
- Implementar diferentes algoritmos de ordenação.
- Analisar resultados e comparar desempenho em condições equivalentes.

## 👨‍💻 Autor

Desenvolvido por **Diego Troiani** como projeto acadêmico de Engenharia de Software.

[![GitHub](https://img.shields.io/badge/GitHub-ditroiani-181717?style=flat-square&logo=github)](https://github.com/ditroiani)

---

<div align="center">
  <sub>📚 Projeto acadêmico desenvolvido para fins de estudo e evolução contínua.</sub>
</div>
