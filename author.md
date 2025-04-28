# Introduction

O passgen é um programa de linha de comando (CLI) desenvolvido para gerar senhas, de acordo com as opções passadas como argumento de linha de comando. Além de gerar genhas aleatória, o programa também é capaz de determinar a entropia da senha gerada e, consequentemente, a qualidade da senha.

# Author(s)

- Déborah Kelly Macedo de Sousa- deborahkmacedo@gmail.com
- Tiago Rodrigues dos Santos- tiago.rodrigues.709@ufrn.edu.br

Indique o nome do autor e email.

# Problems found or limitations

Lista aqui os problemas encontrados (se houve algum) e as
possíveis limitações do programa.

# Grading

<!-- TODO -->

Preencha os itens que você implementou, indicando qual a nota esperada para cada item.

| Item                                             | Valor máximo | Valor esperado |
| ------------------------------------------------ | :----------: | :------------: |
| Interface de acordo com o especificado           |      20      |       20       |
| Seleciona caracteres dos grupos adequadamente    |      15      |       15       |
| Apresenta a tela de ajuda quando solicitado      |      5       |       5        |
| Trata os erros de entrada corretamente           |      12      |       12       |
| Avalia a qualidade da senha com 5 categorias     |      10      |       10       |
| Implementa os 9 grupos de caracteres solicitados |      18      |       18       |
| Utiliza corretamente a aleatoriedade             |      10      |       10       |

# Compiling and Runnig

1. Na raiz do projeto, rode:
```sh
cmake -S . -B build
```
2. Em seguida, para compilar:
```sh
cmake -build build
```
3. Vá para a pasta onde o executável foi gerado:
```sh
cd build
```
4. Por fim, para rodar:
```sh
./passgen <options>
```
