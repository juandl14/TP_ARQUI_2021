# TPE ARQUITECTURA DE COMPUTADORAS - 1er CUATRIMESTRE 2021
***
## Autores:
* De Luca, Juan Manuel - 60103 - jdeluca@itba.edu.ar
* Kim, Azul Candelaria - 60264 - azkim@itba.edu.ar
* López Guzmán, Pedro Jeremías - 60711 - pelopez@itba.edu.ar
***
## Manual de usuario:

### Prerrequisitos
* Contar con el archivo _60103-60264-60711.zip_ descargado y descomprimido en su computadora.
* Contar con el programa qemu instalado.
* Contar con el programa docker instalado.
* Contar con acceso a la terminal de su computadora.

### Compilación
1. Ubicándose en el directorio del trabajo, correr el comando `docker pull agodio/itba-so:1.0`.
2. Ubicándose en el directorio del trabajo, correr el comando `docker run -v ${PWD}:/root --security-opt seccomp:unconfined -ti agodio/itba-so:1.0`. Esto hará que se ingrese a docker.
3. Una vez dentro de docker, dirigirse al directorio _Toolchain_ con el comando `cd root/Toolchain` y ejecutar el comando `make all`.
4. Salir del directorio _Toolchain_ con `cd ..` y ejecutar nuevamente `make all`.
5. Salir de docker con el comando `exit`.

### Ejecución
* Una vez completada la compilación y ubicado en el directrio del trabajo, correr el comando `./run.sh` si se encuentra en Linux, o `./run.bat` si se encuentra en Windows. Esto abrirá las dos terminales correspondientes al trabajo y podrá comenzar a usarse.

### Funcionalidades

#### Comandos
* `datetime` Muestra la fecha y hora del Sistema Operativo.
* `inforeg` Muestra el estado de los registros. Para su correcto funcionamiento, presionar la tecla F12 antes de correrlo para así guardar el estado de los registros.
* `printmem [ARGUMENTO]` Realiza un volcado de 32 bytes de memoria a partir de la dirección provista en el argumento.
* `clear` Limpia la pantalla de la shell donde se corra el comando.
* `echo [ARGUMENTO]` Imprime en pantalla el string provisto en el argumento.
* `divzero` Fuerza una división por 0 para que se prodzca una excepción. Luego reinicia la shell y muestra el mensaje de error correspondiente junto con el estado de los registros.
* `invalidopcode` Fuerza un código de operación inválido para que se produzca una excepción. Luego reinicia la shell y muestra el mensaje de error correspondiente junto con el estado de los registros.
* `help` Despliega el centro de ayuda.

#### Teclas especiales
* F1 - Sirve para cambiar la terminal seleccionada.
* F12 - Sirve para guardar el estado de los registros.

Además, un progrmador podría setear la funcionalidad que quiera para las teclas F1 a F10 mediante punteros a función.

#### Syscalls
Las syscalls a disposición del usuario son las siguientes: <br>

| %rax | Name                 | %rdi                 | %rsi             |      %rdx        |      %rcx       |      %r8       |
|------|----------------------|----------------------|------------------|------------------|-----------------|----------------|
|  0   | readKeyboard         | char * buffer        | uint64_t size    | uint64_t * count |        -        |       -        |
|  1   | drawString           | char * buffer        | uint64_t size    | uint64_t x       | uint64_t y      |       -        |
|  2   | clearDisplay         | uint64_t color       |        -         |        -         |        -        |       -        |
|  3   | drawLine             |         -            |        -         |        -         |        -        |       -        |
|  4   | drawPixel            |         -            |        -         |        -         |        -        |       -        |
|  5   | drawRect             | uint64_t xi          | uint64_t yi      | uint64_t width   | uint64_t height | uint64_t color |
|  6   | drawMatrix           |         -            |        -         |        -         |        -        |       -        |
|  7   | getTicks             | uint64_t * ticks     |        -         |        -         |        -        |       -        |
|  8   | getTime              | uint8_t mode         | uint8_t * target |        -         |        -        |       -        |
|  9   | getRegisters         | uint64_t * registers |        -         |        -         |        -        |       -        |
|  10  | getMem               | uint64_t address     | uint64_t * bytes | uint8_t size     |        -        |       -        |
|  11  | isKeyboardEmpty      | uint64_t * target    |        -         |        -         |        -        |       -        |
|  12  | readError            | uint64_t * err       |        -         |        -         |        -        |       -        |
|  13  | setFunctionKeyMethod | uint64_t index       | void(*)()        |        -         |        -        |       -        |
