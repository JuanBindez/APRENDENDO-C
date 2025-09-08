## Divisor de Conta - Interface Gráfica

### Este programa cria uma interface gráfica para divisão de contas de restaurante, funcionando tanto no Windows quanto no Linux.

#### Como compilar e executar
#### Pré-requisitos

GCC (compilador C)

Biblioteca GTK3

### Instalação das dependências
#### No Linux (Debian/Ubuntu):

    sudo apt-get update
    sudo apt-get install gcc libgtk-3-dev

#### No Windows (usando MSYS2):

    Instale o MSYS2: https://www.msys2.org/

    Abra o terminal MSYS2 MinGW 64-bit

#### Atualize os pacotes:
    pacman -Syu

#### Instale as dependências:

    pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gtk3

### Compilação
#### No Linux:

    gcc main_gtk.c -o main_gtk `pkg-config --cflags --libs gtk+-3.0`

#### No Windows (MSYS2):

    gcc main_gkt.c -o main_gtk.exe `pkg-config --cflags --libs gtk+-3.0`

#### Execução
#### No Linux:


    ./main_gtk

#### No Windows:

    ./main_gtk.exe