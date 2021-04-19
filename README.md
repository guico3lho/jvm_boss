# Projeto JVM - Software Basico

## Compilação e informações com javac/javap

Converter arquivo ``.java`` para ``.class``

``` bash
$ javac HelloJava.java
```

Mostra informações do arquivo ``.class``

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

Caso apresente erro de formatação de arquivos bash ``.sh`` no Linux, usar o comando 

```bash
$ sed -i 's/\r$//' scriptname.sh
```

# Executando

## Leitor e Exibidor

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
$ ./jvm.sh HelloJava
```

## Classes Java (``.class``) de Teste

- [x] cafebabe
- [x] HelloJava
- [x] Teste
- [x] double_aritmetica
- [x] tableswitch
- [ ] multi
- [ ] vetor_8
- [ ] vetor2
- [ ] vetor

<!-- 1- Fazer vetor e multi funcionar -->
<!-- Fazer os .java de multi e vetor-->
<!-- 1- Refatorar o class_loader -->
<!-- Frame teria que pegar dentro do Method area.  -->
<!-- 1- Ver as funções de Cp_Info. Existem 2 funções -->
 
<!-- Frame -->
<!-- Class Loader -->
<!-- Cp_Info  -->
<!-- Arquivos que usam super class -->
<!-- Testar vetor -->
<!--  -->
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

# ou com bash script
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

# bash script
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