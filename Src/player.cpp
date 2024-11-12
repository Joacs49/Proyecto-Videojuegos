#include "../Cabeceras/player.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

constexpr int escalado = 2;

player::player(int x, int y) : offsetX(x), offsetY(y) {
    colorMap = {
        {"color_1", Color(3, 2, 2)},
        {"color_2", Color(46, 46, 46)},
        {"color_3", Color(93, 94, 96)},
        {"color_4", Color(104, 21, 23)},
        {"color_5", Color(223, 43, 47)},
        {"color_6", Color(27, 44, 80)},
        {"color_7", Color(15, 53, 109)},
        {"color_8", Color(224, 225, 227)},
        {"color_9", Color(255, 253, 254)},
    };
}

void player::mover() {
    const int VELOCIDAD = 1;

    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        if (offsetX > 0) offsetX -= VELOCIDAD;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        if (offsetX < 800 - ANCHO_NAVE) offsetX += VELOCIDAD;
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (offsetY > 0) offsetY -= VELOCIDAD;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (offsetY < 600 - ALTO_NAVE) offsetY += VELOCIDAD;
    }
}

void player::dibujaCuadrado(int a, int b, const string& colorRelleno, RenderWindow& window) {
    const int x = a * escalado + offsetX;
    const int y = b * escalado + offsetY;

    RectangleShape rect(Vector2f(escalado, escalado));
    rect.setPosition(x, y);
    rect.setFillColor(colorMap[colorRelleno]);

    window.draw(rect);
}

void player::dibujaFila(int fila, const vector<string>& colores, RenderWindow& window) {
    for (size_t i = 0; i < colores.size(); ++i) {
        if (!colores[i].empty()) {
            dibujaCuadrado(i, fila, colores[i], window);
        }
    }
}

void player::setPosicion(int x, int y) {
    offsetX = x;
    offsetY = y;
}

void player::dibujar(RenderWindow& window) {
    dibujaFila(0, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(1, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(2, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(3, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(4, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(5, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(6, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(7, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(8, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(9, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(10, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(11, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_3", "color_3", "color_3", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(12, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_3", "color_9", "color_9", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(13, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_3", "color_9", "color_1", "color_9", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(14, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_9", "color_1", "color_1", "color_1", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(15, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_9", "color_1", "color_9", "color_1", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(16, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_9", "color_9", "color_8", "color_8", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(17, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_3", "color_3", "color_9", "color_8", "color_8", "color_3", "color_3", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(18, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_7", "color_3", "color_9", "color_3", "color_3", "color_3", "color_8", "color_3", "color_7", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(19, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_7", "color_6", "color_3", "color_9", "color_9", "color_9", "color_8", "color_8", "color_3", "color_6", "color_7", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);;
    dibujaFila(20, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_3", "color_9", "color_9", "color_9", "color_8", "color_8", "color_3", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(21, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_3", "color_9", "color_9", "color_8", "color_8", "color_8", "color_3", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(22, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_3", "color_3", "color_9", "color_8", "color_8", "color_3", "color_3", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(23, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_3", "color_9", "color_3", "color_3", "color_3", "color_8", "color_3", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(24, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_3", "color_9", "color_9", "color_8", "color_8", "color_8", "color_3", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(25, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_3", "color_9", "color_9", "color_8", "color_8", "color_8", "color_3", "color_9", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(26, {"", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_3", "color_9", "color_3", "color_8", "color_3", "color_8", "color_3", "color_9", "color_9", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(27, {"", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_8", "color_3", "color_9", "color_3", "color_8", "color_3", "color_8", "color_3", "color_9", "color_9", "color_9", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(28, {"", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_8", "color_8", "color_3", "color_9", "color_3", "color_8", "color_3", "color_8", "color_3", "color_9", "color_9", "color_9", "color_8", "color_8", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(29, {"", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_9", "color_8", "color_8", "color_3", "color_9", "color_9", "color_8", "color_8", "color_8", "color_3", "color_9", "color_9", "color_9", "color_8", "color_8", "color_8", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(30, {"", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_9", "color_8", "color_8", "color_8", "color_3", "color_8", "color_8", "color_8", "color_8", "color_8", "color_3", "color_9", "color_9", "color_9", "color_8", "color_8", "color_8", "color_8", "color_6", "color_7", "color_1", "", "", "", "", "", "", ""}, window);
    dibujaFila(31, {"", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_9", "color_8", "color_8", "color_8", "color_8", "color_3", "color_8", "color_8", "color_8", "color_8", "color_8", "color_3", "color_9", "color_9", "color_8", "color_8", "color_8", "color_8", "color_8", "color_6", "color_6", "color_7", "color_1", "", "", "", "", "", ""}, window);
    dibujaFila(32, {"", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_9", "color_8", "color_8", "color_8", "color_8", "color_3", "color_3", "color_3", "color_3", "color_3", "color_3", "color_3", "color_9", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_6", "color_7", "color_1", "", "", "", "", "", ""}, window);
    dibujaFila(33, {"", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_8", "color_8", "color_8", "color_8", "color_4", "color_5", "color_5", "color_5", "color_5", "color_5", "color_5", "color_5", "color_4", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_6", "color_7", "color_1", "", "", "", "", "", ""}, window);
    dibujaFila(34, {"", "", "", "", "", "", "", "", "", "color_1", "color_9", "color_9", "color_9", "color_8", "color_8", "color_2", "color_8", "color_4", "color_4", "color_4", "color_4", "color_4", "color_4", "color_4", "color_4", "color_4", "color_8", "color_8", "color_2", "color_8", "color_8", "color_8", "color_8", "color_8", "color_1", "", "", "", "", "", "", ""}, window);
    dibujaFila(35, {"", "", "", "", "", "", "", "", "", "color_1", "color_9", "color_2", "color_2", "color_2", "color_2", "color_2", "color_8", "color_3", "color_9", "color_9", "color_8", "color_3", "color_9", "color_9", "color_8", "color_3", "color_8", "color_8", "color_2", "color_2", "color_2", "color_2", "color_2", "color_8", "color_1", "", "", "", "", "", "", ""}, window);
    dibujaFila(36, {"", "", "", "", "", "", "", "", "", "color_1", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_3", "color_9", "color_9", "color_8", "color_3", "color_9", "color_9", "color_8", "color_3", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_1", "", "", "", "", "", "", ""}, window);
    dibujaFila(37, {"", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_3", "color_8", "color_8", "color_8", "color_3", "color_9", "color_8", "color_8", "color_3", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(38, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_8", "color_8", "color_8", "color_3", "color_8", "color_8", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(39, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(40, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(41, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(42, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(43, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(44, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(45, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(46, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(47, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(48, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(49, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
}
