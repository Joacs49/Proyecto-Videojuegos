#include "../Cabeceras/enemy.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace sf;

const int escalado = 2;
const bool pintarBorde = false;
const int DERECHA_ENEMIGO = 1;
const int IZQUIERDA_ENEMIGO = -1;

enemy::enemy(int x, int y, float vel)
    : xPos(x), yPos(y), velocidad(vel), direccion(1), contadorMovimientos(0) {
    srand(static_cast<unsigned>(time(nullptr)));

    colorMap = map<string, Color>({
        {"color_1", Color(0, 0, 0)},
        {"color_2", Color(157, 22, 22)},
        {"color_3", Color(0, 41, 255)},
        {"color_4", Color(142, 180, 231)},
        {"color_5", Color(255, 255, 255)},
        {"color_6", Color(0, 86, 255)},
        {"color_7", Color(187, 187, 187)},
        {"color_8", Color(158, 158, 158)},
        {"color_9", Color(96, 96, 96)},
        {"color_10", Color(81, 81, 81)}
    });
}

void enemy::setColor(const string& color, RectangleShape& shape) {
    if (colorMap.find(color) != colorMap.end()) {
        shape.setFillColor(colorMap[color]);
    }
}

void enemy::mover() {
    if (contadorMovimientos > 100) {
        int cambioDireccion = rand() % 2; // 0 o 1
        direccion = (cambioDireccion == 0) ? IZQUIERDA_ENEMIGO : DERECHA_ENEMIGO;
        contadorMovimientos = 0;
    }

    if (direccion == IZQUIERDA_ENEMIGO && xPos > 20) {
        xPos -= velocidad;
    } else if (direccion == DERECHA_ENEMIGO && xPos < 720) {
        xPos += velocidad;
    }

    contadorMovimientos++;
}


void enemy::dibujaCuadrado(int a, int b, const string& colorRelleno, RenderWindow& window) {
    RectangleShape square(Vector2f(escalado, escalado));
    const int x = a * escalado + xPos;
    const int y = b * escalado + yPos;

    setColor(colorRelleno, square);
    square.setPosition(x, y);

    window.draw(square);

    if (pintarBorde) {
        square.setOutlineThickness(1);
        square.setOutlineColor(Color(100, 100, 100));
        window.draw(square);
    }
}

void enemy::dibujaFila(int fila, const vector<string>& colores, RenderWindow& window) {
    for (size_t i = 0; i < colores.size(); ++i) {
        if (!colores[i].empty()) {
            dibujaCuadrado(i, fila, colores[i], window);
        }
    }
}

void enemy::dibujar(sf::RenderWindow& window) {
    dibujaFila(0, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_3", "color_3", "color_3", "color_3", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(1, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_3", "color_3", "color_3", "color_3", "color_3", "color_3", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(2, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_3", "color_3", "color_3", "color_4", "color_4", "color_3", "color_3", "color_3", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(3, {"", "", "", "", "", "", "color_3", "", "", "", "", "", "", "", "color_3", "color_3", "color_4", "color_5", "color_5", "color_4", "color_3", "color_3", "", "", "", "", "", "", "", "color_3", "", "", "", "", "", ""}, window);
    dibujaFila(4, {"", "", "", "", "", "color_3", "color_4", "color_3", "", "", "", "", "", "", "color_3", "color_3", "color_4", "color_5", "color_5", "color_4", "color_3", "color_3", "", "", "", "", "", "", "color_3", "color_4", "color_3", "", "", "", "", ""}, window);
    dibujaFila(5, {"", "", "", "", "", "color_3", "color_5", "color_3", "", "", "", "", "", "", "color_3", "color_3", "color_4", "color_5", "color_5", "color_4", "color_3", "color_3", "", "", "", "", "", "", "color_3", "color_5", "color_3", "", "", "", "", ""}, window);
    dibujaFila(6, {"", "", "", "", "", "color_3", "color_5", "color_3", "", "", "", "", "", "", "color_3", "color_3", "color_4", "color_5", "color_5", "color_4", "color_3", "color_3", "", "", "", "", "", "", "color_3", "color_5", "color_3", "", "", "", "", ""}, window);
    dibujaFila(7, {"", "", "", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "", "", "", "", "color_3", "color_3", "color_3", "color_5", "color_5", "color_3", "color_3", "color_3", "", "", "", "", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "", "", ""}, window);
    dibujaFila(8, {"", "", "", "color_1", "color_2", "color_2", "color_2", "color_9", "color_3", "color_1", "color_1", "color_1", "color_1", "", "color_3", "color_3", "color_3", "color_5", "color_5", "color_3", "color_3", "color_3", "", "color_1", "color_1", "color_1", "color_1", "color_3", "color_10", "color_2", "color_2", "color_2", "color_1", "", "", ""}, window);
    dibujaFila(9, {"", "", "", "color_1", "color_2", "color_2", "color_9", "color_9", "color_3", "color_6", "color_3", "color_9", "color_1", "color_1", "color_1", "color_1", "color_3", "color_3", "color_3", "color_3", "color_1", "color_1", "color_1", "color_1", "color_10", "color_3", "color_6", "color_3", "color_10", "color_10", "color_2", "color_2", "color_1", "", "", ""}, window);
    dibujaFila(10, {"", "", "", "color_1", "color_2", "color_9", "color_9", "color_9", "color_3", "color_6", "color_3", "color_9", "color_10", "color_10", "color_10", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_10", "color_10", "color_10", "color_10", "color_3", "color_6", "color_3", "color_10", "color_10", "color_10", "color_2", "color_1", "", "", ""}, window);
    dibujaFila(11, {"", "", "", "color_1", "color_1", "color_9", "color_9", "color_9", "color_3", "color_6", "color_3", "color_9", "color_9", "color_9", "color_9", "color_10", "color_10", "color_10", "color_9", "color_10", "color_10", "color_10", "color_10", "color_10", "color_10", "color_3", "color_6", "color_3", "color_10", "color_10", "color_10", "color_1", "color_1", "", "", ""}, window);
    dibujaFila(12, {"", "", "", "", "color_1", "color_9", "color_9", "color_9", "color_3", "color_6", "color_3", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_10", "color_10", "color_10", "color_10", "color_10", "color_3", "color_6", "color_3", "color_10", "color_10", "color_10", "color_1", "", "", "", ""}, window);
    dibujaFila(13, {"", "", "", "", "color_1", "color_1", "color_9", "color_9", "color_3", "color_3", "color_3", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_10", "color_10", "color_10", "color_10", "color_3", "color_6", "color_3", "color_10", "color_10", "color_1", "color_1", "", "", "", ""}, window);
    dibujaFila(14, {"", "", "", "", "", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_10", "color_10", "color_10", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "", "", "", "", ""}, window);
    dibujaFila(15, {"", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_1", "color_2", "color_2", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_2", "color_2", "color_1", "color_1", "color_1", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(16, {"", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_2", "color_2", "color_2", "color_9", "color_9", "color_9", "color_9", "color_2", "color_2", "color_2", "color_1", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(17, {"", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_7", "color_2", "color_2", "color_2", "color_2", "color_2", "color_2", "color_8", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(18, {"", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_7", "color_7", "color_2", "color_2", "color_2", "color_2", "color_8", "color_8", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(19, {"", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_7", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(20, {"", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_7", "color_7", "color_8", "color_8", "color_8", "color_8", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(21, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_7", "color_7", "color_8", "color_8", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(22, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_7", "color_7", "color_7", "color_8", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(23, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_2", "color_2", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(24, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(25, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(26, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(27, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
}

void enemy::disparar(RenderWindow& window) {
    static int velocidadDisparo = 1;
    static int contadorVelocidad = 0;
    static int tiempoEntreDisparos = 15;
    static int contadorDisparo = 0;

    if (contadorDisparo >= tiempoEntreDisparos && !disparoEnemigoActivo) {
        disparoEnemigoActivo = true;
        balaEnemigaX = xPos + ancho / 2;
        balaEnemigaY = yPos + alto;
        contadorDisparo = 0;
    }

    if (disparoEnemigoActivo) {
        if (contadorVelocidad >= velocidadDisparo) {
            balaEnemigaY += 2;
            contadorVelocidad = 0;
        } else {
            contadorVelocidad++;
        }

        RectangleShape bala(Vector2f(5, 10));
        bala.setFillColor(Color::Red);
        bala.setPosition(balaEnemigaX, balaEnemigaY);
        window.draw(bala);

        if (balaEnemigaY > static_cast<int>(window.getSize().y)) {
            disparoEnemigoActivo = false;
        }
    }

    contadorDisparo++;
}


void enemy::mueveYDibuja(RenderWindow& window) {
    mover();
    dibujar(window);
}
