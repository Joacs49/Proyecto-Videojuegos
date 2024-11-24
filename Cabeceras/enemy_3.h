#ifndef ENEMY_3_H
#define ENEMY_3_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

class enemy_3 {
public:
    enemy_3(int x, int y, float vel);
    void mover();
    void dibujar(sf::RenderWindow& window);

    void disparar(sf::RenderWindow& window);

    int getX() const { return xPos; };
    int getY() const { return yPos; };
    int getAncho() const { return ancho; };
    int getAlto() const { return alto; };

    void setColor(const std::string& color, sf::RectangleShape& shape);

    bool disparoEnemigoActivo = false;
    int balaEnemigaX;
    int balaEnemigaY;

private:
    int xPos, yPos;
    float velocidad;
    int direccion;
    int contadorMovimientos;
    int ancho = 80;
    int alto = 30;
    void dibujaCuadrado(int a, int b, const std::string& colorRelleno, sf::RenderWindow& window);
    void dibujaFila(int fila, const std::vector<std::string>& colores, sf::RenderWindow& window);
    std::map<std::string, sf::Color> colorMap;
    void mueveYDibuja(sf::RenderWindow& window);
};

#endif
