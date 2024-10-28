#ifndef PLAYER_H
#define PLAYER_H

#include "miniwin.h"
#include <string>
#include <vector>
#include <map>

using namespace miniwin;
using namespace std;

class player {
public:
    player(int x, int y);

    void mover();

    int getX() const { return offsetX; }
    int getY() const { return offsetY; }
    void setColor(const string& color);
    void dibujar();
    int getAncho() const { return ANCHO_NAVE; }
    int getAlto() const { return ALTO_NAVE; }
    void setPosicion(int x, int y);

private:
    int offsetX;
    int offsetY;
    const int ANCHO_NAVE = 80;
    const int ALTO_NAVE = 90;
    void dibujaCuadrado(int a, int b, const string& colorRelleno);
    void dibujaFila(int fila, const vector<string>& colores);
    map<string, vector<int>> colorMap;
};

#endif
