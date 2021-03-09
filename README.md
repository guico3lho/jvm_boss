# Projeto JVM - Software Basico

## Leitor e Exibidor

## Compilação e informações com javac/javap

Converter arquivo ``.java`` para ``.class``

``` bash
$ javac HelloWorld.java
```

Mostra informações do arquivo ``.class``

``` bash
$ javap HelloWorld.class

# para mais info, flags -c, -verbose ou -v
$ javap -v HelloWorld.class
```
# Configurações

## Analisadores 

## [Cppcheck 1.83](http://cppcheck.sourceforge.net) como analisador estático

Instalação no Linux
```
$ sudo apt-get install cppcheck
```

## Valgrind
Instalação no Linux
```
$ sudo apt-get install valgrind
```
Exceutando com mais detalhes sobre vazamento de memória
``` bash
$ valgrind –leak-check=full ./prog
```