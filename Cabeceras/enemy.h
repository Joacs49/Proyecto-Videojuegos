#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

class enemy {
public:
    enemy(int x, int y, float vel);
    void mover();
    void dibujar(sf::RenderWindow& window);

    void disparar(sf::RenderWindow& window);

    int getX() const { return xPos; };
    int getY() const { return yPos; }
    void setColor(const std::string& color, sf::RectangleShape& shape);

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
    float velocidad;
    void dibujaCuadrado(int a, int b, const std::string& colorRelleno, sf::RenderWindow& window);
    void dibujaFila(int fila, const std::vector<std::string>& colores, sf::RenderWindow& window);
    map<string, sf::Color> colorMap;
    void mueveYDibuja(sf::RenderWindow& window);
};

#endif
