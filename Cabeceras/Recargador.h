#ifndef RECARGADOR_H
#define RECARGADOR_H
#include <SFML/Graphics.hpp>

class Recargador {
public:
    Recargador(int xPos, int yPos);
    void dibujar(sf::RenderWindow& window);
    bool colisionaCon(int px, int py, int ancho, int alto);
    bool isVisible() const { return visible; }
    void desactivar() { visible = false; }

private:
    int x, y;
    bool visible;
};

#endif
