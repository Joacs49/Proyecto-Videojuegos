#include "../Cabeceras/miniwin.h"
#include "../Cabeceras/game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace miniwin;

int main() {
    game juego;
    juego.iniciar();

    juego.loop();

    return 0;
}
