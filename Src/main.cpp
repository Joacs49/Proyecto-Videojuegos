#include "../Cabeceras/game.h"

int main(int argc, char *argv[]) {
    game juego;
    juego.iniciar();

    juego.loop();

    return 0;
}
