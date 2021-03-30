# Projeto JVM - Software Basico

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

# Compilando

``` bash
# Linux
$ ./compile.sh -l

# Windows
$ ./compile.sh -w
```

# Executando

## Leitor e Exibidor

Exibe o bytecode do arquivo .class

``` bash
# Linux e Windows
$ ./jvm_boss -e test/HelloJava.class

# Bash script
$ ./read.sh HelloJava
```

## Interpretador JVM

Interpreta e executa o arquivo .class

``` bash
# Linux e Windows
$ ./jvm_boss -i test/HelloJava.class

# Bash script
$ ./exec.sh HelloJava
```

# Configurações

## Versão [Java SE 8](https://docs.oracle.com/javase/specs/jvms/se8/html/index.html)

## Analisadores 

## [Cppcheck 1.83](http://cppcheck.sourceforge.net) como analisador estático

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

# ou com bash script
$ ./check.sh -v main
$ ./check.sh -w main
$ ./check.sh -all

```

## [Valgrind](https://www.valgrind.org/) como analisador dinâmico

Instalação no Linux

``` bash
$ sudo apt-get install valgrind
```

Executando

``` bash
# com mais detalhes sobre vazamento de memória
$ valgrind –leak-check=full ./jvm_boss -e test/HelloJava.class

# bash script
$ ./valgrind.sh HelloJava
```