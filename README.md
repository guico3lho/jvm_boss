# Projeto JVM - Software Basico

## [Wiki do Projeto](https://guicoelhodev.github.io/jvm_boss/)

![Diagrama](/diagrama.png)

# Compilando

Compilando usando CMake de forma manual

``` bash
# cria pasta build
mkdir -p build 
cd build

# executa o cmake dentro da pasta build
cmake .. -G "Unix Makefiles"

# executa o make dentro de build
make

# volta para diretório raiz do projeto
cd ..

```

Utilizando script shell

``` bash
# Linux
$ ./compile.sh -l

# Windows
$ ./compile.sh -w
```

Caso apresente erro de formatação de arquivos shell ``.sh`` no Linux, usar o comando 

```bash
$ sed -i 's/\r$//' scriptname.sh
```

Caso prefira, no ambiente Windows, pode utilizar apenas o ``Makefile``

``` bash
make
``` 

# Executando

## Leitor e Exibidor

Exibe o bytecode do arquivo .class (flag `` -e``)

``` bash
# Linux e Windows
$ ./jvm_boss -e test/HelloJava.class

# shell script
$ ./read.sh HelloJava
```

## Interpretador JVM

Interpreta e executa o arquivo .class (flag `` -i``)

``` bash
# Linux e Windows
$ ./jvm_boss -i test/HelloJava.class

# shell script
$ ./jvm.sh HelloJava
```

## Compilação e informações com javac/javap

Compila arquivo ``.java`` para ``.class``

``` bash
$ javac HelloJava.java
```

Mostra informações do bytecode do arquivo ``.class``

``` bash
$ javap HelloJava.class

# para mais info, flags: -c, -verbose ou -v
$ javap -v HelloJava.class
```

## Arquivos Teste

Arquivos java (``.java``) encontram-se na pasta ``test/java`` e arquivos de classe (``.class``) encontram-se na pasta ``test/class``.

Para adicionar mais arquivos classe de teste, basta inserir o ``arquivo.java`` no diretorio ``test/java`` e executar na pasta raiz do projeto o comando:

``` bash
# Linux e Windows
$ java test/java/arquivo.java -d test/class

# shell script
$  javac.sh arquivo
```

## Classes Java (``.class``) de Teste

- [x] cafebabe
- [x] HelloJava
- [x] Prints

## Aritmeticos

- [x] Sum
- [x] Multiply
- [x] int_aritmetica
- [x] float_aritmetica
- [x] double_aritmetica

## Vetores

- [x] vetor
- [x] vetor2
- [x] Vector_1
- [x] Vector_2
- [x] multi
## Controle

- [x] Loop_for
- [x] Loop_while
- [x] Switch
- [x] tableswitch
- [x] lookupswitch

## Comparação

- [x] Comparison
## Conversão

- [x] Convert_int
- [x] Convert_float
- [x] Convert_double
- [x] Convert_long

## Metodos

- [x] methods
- [x] MethodStatic
- [x] MethodParams
- [x] recursao

# Configurações

### Até a versão [Java SE 8](https://docs.oracle.com/javase/specs/jvms/se8/html/index.html)

## Analisadores 

### Analisador estático: [Cppcheck 1.83](http://cppcheck.sourceforge.net) 

Instalação no Linux

``` bash
$ sudo apt-get install cppcheck
```

Executando CppCheck

``` bash
# arquivos especificos
$ cppcheck --verbose ./src/main.cpp
$ cppcheck --enable=warning ./src/main.cpp

# todos arquivos .cpp dentro de src
$ cppcheck --verbose --enable=warning ./src/*.cpp

# ou com shell script
$ ./check.sh -v main
$ ./check.sh -w main
$ ./check.sh -all

```

### Analisador dinâmico: [Valgrind](https://www.valgrind.org/) 

Instalação no Linux

``` bash
$ sudo apt-get install valgrind
```

Executando

``` bash
# com mais detalhes sobre vazamento de memória
$ valgrind –leak-check=full ./jvm_boss -e test/HelloJava.class

# shell script
$ ./valgrind.sh HelloJava
```
## Documentação

### [Doxygen](https://www.doxygen.nl/index.html) 

Instalação no Linux

``` bash
$ git clone https://github.com/doxygen/doxygen.git

$ cd doxygen

$ mkdir build

$ cd build

$ cmake -G "Unix Makefiles" ..

$ make

$ make install
```

Criando arquivo de configuração do Doxygen

``` bash
# Cria um arquivo de configuração do doxygen com o nome "doxygen_config"
$ doxygen -g doxygen_config
```

No arquivo "doxygen_config", foi necessário modificar a configuração "RECURSIVE = YES" para gerar a documentação.

Executando

``` bash
# Gera ou atualiza a pasta "html" do projeto. Deve-se rodar este comando sempre que o código for atualizado
$ doxygen doxygen_config
```

Para visualizar a documentação gerada, basta abrir a pasta "html" do projeto e abrir o arquivo "index.html" com o navegador.