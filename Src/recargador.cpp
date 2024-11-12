#include "../Cabeceras/Recargador.h"

Recargador::Recargador(int xPos, int yPos) : x(xPos), y(yPos), visible(true) {}

void Recargador::dibujar(sf::RenderWindow& window) {
    if (visible) {
        sf::RectangleShape recargador(sf::Vector2f(20, 20));
        recargador.setPosition(x, y);
        recargador.setFillColor(sf::Color::Green);

        window.draw(recargador);

        sf::Font font;
        if (font.loadFromFile("C:/Users/frank/Desktop/Nuevo/Proyecto/fonts/arial.ttf")) {
            sf::Text texto("+", font, 20);
            texto.setPosition(x + 5, y - 3);
            texto.setFillColor(sf::Color::Black);
            window.draw(texto);
        }
    }
}

bool Recargador::colisionaCon(int px, int py, int ancho, int alto) {
    return (px < x + 20 && px + ancho > x && py < y + 20 && py + alto > y);
}
