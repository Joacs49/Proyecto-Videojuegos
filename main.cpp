#include "miniwin.h"
#include "game.h"

using namespace miniwin;

int _main_() {
    game juego;
    juego.iniciar();

    juego.loop();

    return 0;
}
