#include "../Cabeceras/enemy_3.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace sf;

const int escalado = 3;
const bool pintarBorde = false;
const int DERECHA_ENEMIGO = 1;
const int IZQUIERDA_ENEMIGO = -1;

enemy_3::enemy_3(int x, int y, float vel)
    : xPos(x), yPos(y), velocidad(vel), direccion(1), contadorMovimientos(0) {
    srand(static_cast<unsigned>(time(nullptr)));

    colorMap = map<string, Color>({
        {"c_1", Color(0, 0, 0)},
        {"c_2", Color(250, 241, 148)},
        {"c_3", Color(205, 153, 43)},
        {"c_4", Color(236, 194, 74)},
        {"c_5", Color(157, 112, 31)},
        {"c_6", Color(121, 146, 81)},
        {"c_7", Color(105, 105, 35)},
        {"c_8", Color(229, 220, 145)},
        {"c_9", Color(206, 196, 130)},
        {"c_10", Color(87, 62, 21)},
        {"c_11", Color(255, 255, 255)},
        {"c_12", Color(187, 163, 89)},
    });
}

void enemy_3::setColor(const string& color, RectangleShape& shape) {
    if (colorMap.find(color) != colorMap.end()) {
        shape.setFillColor(colorMap[color]);
    }
}

void enemy_3::mover() {
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


void enemy_3::dibujaCuadrado(int a, int b, const string& colorRelleno, RenderWindow& window) {
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

void enemy_3::dibujaFila(int fila, const vector<string>& colores, RenderWindow& window) {
    for (size_t i = 0; i < colores.size(); ++i) {
        if (!colores[i].empty()) {
            dibujaCuadrado(i, fila, colores[i], window);
        }
    }
}

void enemy_3::dibujar(RenderWindow& window) {
    dibujaFila(0, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_1", "c_1", "c_1", "", "", "", "", "", "", "", "", "c_1", "c_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(1, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_1", "c_4", "c_3", "c_3", "c_1", "c_1", "", "", "", "", "", "c_1", "c_3", "c_1", "c_1", "c_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(2, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_1", "c_3", "c_10", "c_10", "c_10", "c_5", "c_3", "c_1", "", "", "", "c_1", "c_3", "c_1", "", "", "c_1", "c_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(3, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_1", "c_10", "c_5", "c_4", "c_5", "c_10", "c_3", "c_3", "c_1", "", "c_1", "c_4", "c_1", "", "", "", "c_1", "c_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(4, {"", "", "", "", "", "", "", "", "c_1", "c_1", "c_1", "c_1", "", "", "", "c_1", "c_10", "c_5", "c_4", "c_5", "c_5", "c_3", "c_1", "", "", "c_1", "c_4", "c_5", "c_1", "c_1", "c_1", "c_1", "c_1", "", "", "", "c_1", "", "c_1", "c_1", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(5, {"", "", "", "", "", "", "c_1", "c_1", "c_4", "c_4", "c_2", "c_2", "c_1", "c_1", "", "c_1", "c_4", "c_3", "c_1", "c_1", "c_5", "c_3", "c_3", "c_1", "c_1", "c_3", "c_4", "c_3", "c_5", "c_2", "c_5", "c_4", "c_3", "c_1", "", "c_1", "c_4", "c_1", "c_3", "c_3", "c_1", "", "", "", "", "", "", ""}, window);
    dibujaFila(6, {"", "", "", "", "", "", "c_1", "c_12", "c_10", "c_10", "c_5", "c_2", "c_2", "c_1", "", "", "c_1", "c_1", "", "", "c_1", "c_3", "c_1", "", "", "c_1", "c_4", "c_4", "c_5", "c_1", "c_1", "c_1", "c_1", "c_5", "c_1", "c_4", "c_3", "c_10", "c_10", "c_5", "c_3", "c_1", "", "", "", "", "", ""}, window);
    dibujaFila(7, {"", "", "", "", "", "c_1", "c_2", "c_5", "c_4", "c_12", "c_5", "c_5", "c_2", "c_3", "c_1", "c_1", "", "", "", "c_1", "c_3", "c_4", "c_3", "c_1", "", "c_1", "c_3", "c_3", "c_1", "", "", "", "", "c_1", "c_3", "c_3", "c_5", "c_5", "c_12", "c_5", "c_3", "c_3", "c_1", "", "", "", "", ""}, window);
    dibujaFila(8, {"", "", "", "", "", "c_1", "c_2", "c_10", "c_10", "c_4", "c_12", "c_10", "c_12", "c_3", "c_4", "c_1", "", "", "", "c_1", "c_3", "c_4", "c_1", "", "", "c_1", "c_4", "c_3", "c_1", "", "", "", "c_1", "c_3", "c_3", "c_5", "c_5", "c_12", "c_12", "c_5", "c_5", "c_3", "c_1", "", "", "", "", ""}, window);
    dibujaFila(9, {"", "", "", "", "", "c_1", "c_2", "c_4", "c_5", "c_4", "c_12", "c_1", "c_5", "c_4", "c_4", "c_1", "", "", "", "c_1", "c_3", "c_3", "c_3", "c_1", "c_1", "c_3", "c_4", "c_4", "c_4", "c_1", "", "", "c_1", "c_3", "c_3", "c_5", "c_1", "c_12", "c_5", "c_5", "c_5", "c_12", "c_1", "", "", "", "", ""}, window);
    dibujaFila(10, {"", "", "", "", "", "", "c_1", "c_4", "c_4", "c_5", "c_1", "", "c_1", "c_4", "c_4", "c_4", "c_1", "", "", "c_1", "c_4", "c_4", "c_1", "", "", "c_1", "c_4", "c_4", "c_4", "c_1", "", "c_1", "c_4", "c_4", "c_4", "c_1", "", "c_1", "c_1", "c_12", "c_12", "c_1", "", "", "", "", "", ""}, window);
    dibujaFila(11, {"", "", "", "", "", "c_1", "c_10", "c_5", "c_5", "c_1", "", "", "c_1", "c_4", "c_4", "c_4", "c_3", "c_1", "c_1", "c_12", "c_4", "c_4", "c_3", "c_1", "c_1", "c_4", "c_4", "c_4", "c_1", "", "", "c_1", "c_4", "c_4", "c_2", "c_1", "", "", "", "c_1", "c_1", "", "", "", "", "", "", ""}, window);
    dibujaFila(12, {"", "", "", "c_1", "c_1", "c_2", "c_2", "c_10", "c_10", "c_1", "", "", "", "c_1", "c_2", "c_4", "c_4", "c_3", "c_5", "c_3", "c_3", "c_4", "c_3", "c_4", "c_4", "c_3", "c_3", "c_3", "c_3", "c_1", "c_1", "c_4", "c_3", "c_4", "c_1", "", "", "", "c_1", "c_5", "c_12", "c_1", "c_1", "c_1", "", "", "", ""}, window);
    dibujaFila(13, {"", "", "c_1", "c_2", "c_2", "c_2", "c_2", "c_10", "c_10", "c_3", "c_1", "c_1", "", "c_1", "c_2", "c_3", "c_3", "c_5", "c_5", "c_5", "c_5", "c_3", "c_3", "c_3", "c_4", "c_12", "c_12", "c_3", "c_3", "c_3", "c_3", "c_4", "c_3", "c_4", "c_1", "", "c_1", "c_1", "c_12", "c_2", "c_2", "c_2", "c_2", "c_2", "c_1", "c_1", "", ""}, window);
    dibujaFila(14, {"", "c_1", "c_2", "c_10", "c_10", "c_10", "c_10", "c_10", "c_10", "c_3", "c_3", "c_10", "c_1", "c_10", "c_5", "c_12", "c_3", "c_3", "c_3", "c_3", "c_3", "c_3", "c_5", "c_3", "c_5", "c_12", "c_5", "c_3", "c_3", "c_5", "c_3", "c_3", "c_4", "c_1", "", "c_1", "c_12", "c_2", "c_2", "c_2", "c_2", "c_4", "c_5", "c_5", "c_4", "c_4", "c_1", ""}, window);
    dibujaFila(15, {"", "c_1", "c_5", "c_3", "c_4", "c_4", "c_3", "c_10", "c_10", "c_3", "c_10", "c_10", "c_3", "c_5", "c_10", "c_12", "c_3", "c_3", "c_4", "c_3", "c_5", "c_4", "c_4", "c_3", "c_5", "c_3", "c_5", "c_5", "c_3", "c_3", "c_5", "c_5", "c_5", "c_5", "c_1", "c_4", "c_4", "c_2", "c_2", "c_2", "c_3", "c_10", "c_3", "c_3", "c_10", "c_5", "c_1", ""}, window);
    dibujaFila(16, {"c_1", "c_12", "c_5", "c_1", "c_4", "c_4", "c_5", "c_1", "c_1", "c_3", "c_10", "c_3", "c_2", "c_3", "c_5", "c_12", "c_3", "c_3", "c_3", "c_3", "c_5", "c_3", "c_5", "c_5", "c_5", "c_12", "c_4", "c_5", "c_12", "c_3", "c_3", "c_3", "c_3", "c_3", "c_4", "c_4", "c_4", "c_4", "c_2", "c_1", "c_5", "c_4", "c_4", "c_4", "c_5", "c_5", "c_4", "c_1"}, window);
    dibujaFila(17, {"c_1", "c_12", "c_1", "", "c_1", "c_12", "c_3", "c_1", "", "c_1", "c_3", "c_2", "c_2", "c_3", "c_10", "c_5", "c_5", "c_12", "c_5", "c_5", "c_5", "c_5", "c_3", "c_3", "c_5", "c_12", "c_5", "c_5", "c_5", "c_5", "c_3", "c_3", "c_3", "c_3", "c_3", "c_3", "c_4", "c_4", "c_1", "", "c_1", "c_4", "c_12", "c_5", "c_5", "c_4", "c_4", "c_1"}, window);
    dibujaFila(18, {"c_1", "c_12", "c_3", "c_1", "c_10", "c_5", "c_5", "c_1", "", "", "c_1", "c_1", "c_2", "c_3", "c_10", "c_3", "c_12", "c_3", "c_4", "c_4", "c_3", "c_5", "c_3", "c_3", "c_10", "c_12", "c_12", "c_12", "c_12", "c_3", "c_3", "c_3", "c_3", "c_3", "c_3", "c_3", "c_1", "c_1", "", "", "c_1", "c_4", "c_12", "c_10", "c_5", "c_4", "c_5", "c_1"}, window);
    dibujaFila(19, {"c_1", "c_1", "c_3", "c_5", "c_10", "c_5", "c_10", "c_1", "", "", "", "", "c_1", "c_10", "c_5", "c_12", "c_3", "c_3", "c_3", "c_4", "c_6", "c_7", "c_5", "c_3", "c_10", "c_7", "c_5", "c_12", "c_12", "c_12", "c_12", "c_12", "c_5", "c_3", "c_5", "c_1", "", "", "", "", "", "c_1", "c_4", "c_4", "c_4", "c_1", "c_1", ""}, window);
    dibujaFila(20, {"", "", "c_1", "c_1", "c_10", "c_12", "c_5", "c_12", "c_1", "c_1", "c_1", "c_1", "c_10", "c_10", "c_5", "c_12", "c_4", "c_4", "c_3", "c_5", "c_3", "c_5", "c_3", "c_3", "c_5", "c_5", "c_4", "c_4", "c_12", "c_12", "c_12", "c_3", "c_5", "c_10", "c_5", "c_10", "c_1", "c_1", "c_1", "c_1", "c_1", "c_5", "c_10", "c_1", "c_1", "", "", ""}, window);
    dibujaFila(21, {"", "", "", "", "c_1", "c_5", "c_3", "c_2", "c_2", "c_2", "c_3", "c_3", "c_3", "c_3", "c_10", "c_4", "c_4", "c_5", "c_5", "c_5", "c_3", "c_3", "c_3", "c_10", "c_5", "c_5", "c_3", "c_3", "c_12", "c_12", "c_12", "c_3", "c_5", "c_3", "c_4", "c_4", "c_3", "c_4", "c_4", "c_4", "c_3", "c_5", "c_1", "", "", "", "", ""}, window);
    dibujaFila(22, {"", "", "", "c_1", "c_3", "c_2", "c_2", "c_2", "c_2", "c_2", "c_3", "c_3", "c_3", "c_3", "c_10", "c_4", "c_4", "c_3", "c_3", "c_5", "c_11", "c_9", "c_5", "c_3", "c_5", "c_3", "c_2", "c_12", "c_12", "c_5", "c_3", "c_3", "c_3", "c_3", "c_4", "c_3", "c_5", "c_5", "c_3", "c_3", "c_5", "c_5", "c_5", "c_1", "", "", "", ""}, window);
    dibujaFila(23, {"", "", "", "c_1", "c_3", "c_3", "c_5", "c_3", "c_5", "c_1", "c_1", "c_3", "c_3", "c_3", "c_3", "c_4", "c_4", "c_3", "c_3", "c_12", "c_12", "c_12", "c_12", "c_3", "c_3", "c_12", "c_12", "c_12", "c_3", "c_3", "c_3", "c_3", "c_4", "c_3", "c_4", "c_4", "c_3", "c_5", "c_5", "c_5", "c_5", "c_10", "c_5", "c_1", "", "", "", ""}, window);
    dibujaFila(24, {"", "", "c_1", "c_5", "c_5", "c_10", "c_10", "c_3", "c_1", "", "", "c_1", "c_3", "c_5", "c_3", "c_4", "c_3", "c_5", "c_5", "c_5", "c_5", "c_10", "c_5", "c_5", "c_5", "c_5", "c_12", "c_12", "c_3", "c_3", "c_3", "c_3", "c_3", "c_4", "c_4", "c_3", "c_10", "c_5", "c_8", "c_9", "c_8", "c_10", "c_5", "c_12", "c_1", "", "", ""}, window);
    dibujaFila(25, {"", "", "c_1", "c_5", "c_10", "c_10", "c_3", "c_5", "c_3", "c_1", "c_1", "", "c_1", "c_4", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_10", "c_10", "c_5", "c_5", "c_10", "c_3", "c_4", "c_3", "c_3", "c_10", "c_10", "c_10", "c_5", "c_10", "c_10", "c_9", "c_8", "c_8", "c_8", "c_8", "c_10", "c_12", "c_1", "", "", ""}, window);
    dibujaFila(26, {"", "", "c_1", "c_3", "c_10", "c_1", "c_1", "c_1", "c_5", "c_2", "c_3", "c_1", "c_4", "c_3", "c_5", "c_4", "c_4", "c_3", "c_3", "c_3", "c_5", "c_5", "c_5", "c_5", "c_3", "c_3", "c_5", "c_4", "c_2", "c_3", "c_4", "c_4", "c_5", "c_10", "c_10", "c_5", "c_10", "c_9", "c_9", "c_5", "c_8", "c_9", "c_1", "c_12", "c_12", "c_1", "", ""}, window);
    dibujaFila(27, {"", "", "c_1", "c_3", "c_5", "c_1", "", "", "c_1", "c_2", "c_1", "c_1", "c_4", "c_5", "c_1", "c_10", "c_2", "c_4", "c_4", "c_3", "c_3", "c_3", "c_4", "c_1", "c_1", "c_5", "c_10", "c_4", "c_4", "c_3", "c_3", "c_2", "c_3", "c_1", "c_5", "c_1", "c_1", "c_1", "c_9", "c_5", "c_10", "c_10", "c_12", "c_12", "c_1", "", "", ""}, window);
    dibujaFila(28, {"", "", "c_1", "c_5", "c_5", "c_5", "c_1", "c_1", "c_2", "c_1", "", "", "c_1", "c_1", "", "c_1", "c_3", "c_3", "c_3", "c_4", "c_5", "c_3", "c_1", "", "", "c_1", "c_5", "c_5", "c_4", "c_3", "c_5", "c_3", "c_1", "", "c_1", "", "", "", "c_1", "c_12", "c_12", "c_12", "c_12", "c_12", "c_1", "", "", ""}, window);
    dibujaFila(29, {"", "", "", "c_1", "c_1", "c_3", "c_3", "c_2", "c_1", "c_1", "", "", "", "", "", "", "c_1", "c_3", "c_3", "c_3", "c_5", "c_1", "c_1", "", "", "c_1", "c_1", "c_5", "c_3", "c_5", "c_5", "c_1", "", "", "", "", "", "", "", "c_1", "c_12", "c_12", "c_12", "c_1", "", "", "", ""}, window);
    dibujaFila(30, {"", "", "", "", "", "c_1", "c_1", "c_1", "", "", "", "", "", "", "", "", "c_1", "c_3", "c_5", "c_5", "c_1", "", "", "", "", "", "", "c_1", "c_1", "c_1", "c_1", "c_1", "", "", "", "", "", "", "", "", "c_1", "c_1", "c_1", "", "", "", "", ""}, window);
    dibujaFila(31, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_1", "c_1", "c_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);

}

void enemy_3::disparar(RenderWindow& window) {
    static int velocidadDisparo = 25;
    static int contadorVelocidad = 0;
    static int tiempoEntreDisparos = 17;
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
        bala.setFillColor(Color::Magenta);
        bala.setPosition(balaEnemigaX, balaEnemigaY);
        window.draw(bala);

        if (balaEnemigaY > static_cast<int>(window.getSize().y)) {
            disparoEnemigoActivo = false;
        }
    }

    contadorDisparo++;
}


void enemy_3::mueveYDibuja(RenderWindow& window) {
    mover();
    dibujar(window);
}

