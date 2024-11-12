#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

class enemy {
public:
    enemy(int x, int y, float vel);
    void mover();
    void dibujar(RenderWindow& window);

    void disparar(RenderWindow& window);

    int getX() const { return xPos; };
    int getY() const { return yPos; }
    void setColor(const string& color, RectangleShape& shape);

    int getAncho() const { return ancho; }
    int getAlto() const { return alto; }

    bool disparoEnemigoActivo = false;
    int balaEnemigaX;
    int balaEnemigaY;

private:
    int xPos, yPos;
    float velocidad;
    int direccion;
    int contadorMovimientos;
    int ancho = 60;
    int alto = 30;
    void dibujaCuadrado(int a, int b, const string& colorRelleno, RenderWindow& window);
    void dibujaFila(int fila, const vector<string>& colores, RenderWindow& window);
    map<string, Color> colorMap;
    void mueveYDibuja(RenderWindow& window);
};

#endif
