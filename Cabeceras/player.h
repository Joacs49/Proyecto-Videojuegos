#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>

using namespace std;
using namespace sf;

class player {
public:
    player(int x, int y);

    void mover();

    int getX() const { return offsetX; }
    int getY() const { return offsetY; }
    void setColor(const string& color, RectangleShape& shape);
    void dibujar(RenderWindow& window);
    int getAncho() const { return ANCHO_NAVE; }
    int getAlto() const { return ALTO_NAVE; }
    void setPosicion(int x, int y);

private:
    int offsetX;
    int offsetY;
    const int ANCHO_NAVE = 80;
    const int ALTO_NAVE = 90;
    void dibujaCuadrado(int a, int b, const string& colorRelleno, RenderWindow& window);
    void dibujaFila(int fila, const vector<string>& colores, RenderWindow& window);
    map<string, Color> colorMap;
};

#endif
