# Projeto JVM - Software Basico

## Compilação e informações com javac/javap

Converter arquivo ``.java`` para ``.class``

``` bash
$ javac HelloJava.java
```

Mostra informações do arquivo ``.class``

``` bash
$ javap HelloJava.class

# para mais info, flags -c, -verbose ou -v
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

``` bash
$ ./jvm_boss.exe -e test/HelloJava.class

# ou utilizar bash script
$ ./leitor.sh HelloJava
```

# Configurações

## Versão Java SE 8

## Analisadores 

## [Cppcheck 1.83](http://cppcheck.sourceforge.net) como analisador estático

Instalação no Linux

```
$ sudo apt-get install cppcheck
```

## [Valgrind](https://www.valgrind.org/) como analisador dinâmico

Instalação no Linux

```
$ sudo apt-get install valgrind
```

Executando com mais detalhes sobre vazamento de memória

``` bash
$ valgrind –leak-check=full ./prog
```