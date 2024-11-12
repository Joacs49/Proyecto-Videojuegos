#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>

using namespace std;

class player {
public:
    player(int x, int y);

    void mover();

    int getX() const { return offsetX; }
    int getY() const { return offsetY; }
    void setColor(const std::string& color, sf::RectangleShape& shape);
    void dibujar(sf::RenderWindow& window);
    int getAncho() const { return ANCHO_NAVE; }
    int getAlto() const { return ALTO_NAVE; }
    void setPosicion(int x, int y);

private:
    int offsetX;
    int offsetY;
    const int ANCHO_NAVE = 80;
    const int ALTO_NAVE = 90;
    void dibujaCuadrado(int a, int b, const std::string& colorRelleno, sf::RenderWindow& window);
    void dibujaFila(int fila, const std::vector<std::string>& colores, sf::RenderWindow& window);
    map<string, sf::Color> colorMap;
};

#endif
