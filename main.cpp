#include "miniwin.h"
#include "game.h"

using namespace miniwin;

int main() {
    game juego;
    juego.iniciar();

    juego.loop();

    return 0;
}
