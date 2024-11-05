#include "recargador.h"
#include "miniwin.h"

using namespace miniwin;

Recargador::Recargador(int xPos, int yPos) : x(xPos), y(yPos), visible(true) {}

void Recargador::dibujar() {
    if (visible) {
        color_rgb(0, 255, 0);
        rectangulo_lleno(x, y, x + 20, y + 20);
        color(NEGRO);
        texto(x + 6, y + 2, "+");
    }
}

bool Recargador::colisionaCon(int px, int py, int ancho, int alto) {
    return (px < x + 20 && px + ancho > x && py < y + 20 && py + alto > y);
}

