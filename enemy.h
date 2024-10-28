#ifndef ENEMY_H
#define ENEMY_H

#include "miniwin.h"
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

class enemy {
public:
    enemy(int x, int y);
    void mover();
    void dibujar();

    void disparar();

    int getX() const { return xPos; };
    int getY() const { return yPos; }
    void setColor(const string& color);

    int getAncho() const { return ancho; }
    int getAlto() const { return alto; }

    bool disparoEnemigoActivo = false;
    int balaEnemigaX;
    int balaEnemigaY;

private:
    int xPos, yPos;
    int direccion;
    int contadorMovimientos;
    int ancho = 60;
    int alto = 30;
    void dibujaCuadrado(int a, int b, const string& colorRelleno);
    void dibujaFila(int fila, const vector<string>& colores);
    map<string, vector<int>> colorMap;
    void mueveYDibuja();
};

#endif
