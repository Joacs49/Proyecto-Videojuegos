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

const int escalado = 3;
const bool pintarBorde = false;
const int DERECHA_ENEMIGO = 1;
const int IZQUIERDA_ENEMIGO = -1;

enemy::enemy(int x, int y, float vel)
    : xPos(x), yPos(y), velocidad(vel), direccion(1), contadorMovimientos(0) {
    srand(static_cast<unsigned>(time(nullptr)));

    colorMap = map<string, Color>({
        {"c_1", Color(210, 178, 20)},
        {"c_2", Color(0, 0, 0)},
        {"c_3", Color(255, 255, 255)},
        {"c_4", Color(21, 119, 193)},
        {"c_5", Color(110, 183, 1)},
        {"c_6", Color(168, 155, 87)},
        {"c_7", Color(205, 220, 86)},
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

void enemy::dibujar(RenderWindow& window) {
    dibujaFila(0, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(1, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(2, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(3, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(4, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(5, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(6, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(7, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(8, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_1", "c_4", "c_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(9, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_1", "c_4", "c_5", "c_4", "c_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(10, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_1", "c_1", "c_4", "c_5", "c_4", "c_1", "c_1", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(11, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_1", "c_1", "c_4", "c_4", "c_4", "c_1", "c_1", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(12, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_1", "c_1", "c_1", "c_1", "c_1", "c_1", "c_1", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(13, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_1", "c_1", "c_1", "c_1", "c_1", "c_1", "c_1", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(14, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_3", "c_3", "c_3", "c_3", "c_3", "c_3", "c_3", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(15, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_3", "c_3", "", "c_3", "", "c_3", "c_3", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(16, {"", "", "", "", "", "", "", "", "", "", "", "", "", "c_2", "c_2", "c_3", "c_3", "c_3", "c_2", "c_3", "c_3", "c_3", "c_2", "c_2", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(17, {"", "", "", "", "", "", "", "", "", "", "", "", "", "c_2", "c_2", "c_3", "c_3", "c_3", "c_2", "c_3", "c_3", "c_3", "c_2", "c_2", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(18, {"", "", "", "", "", "", "", "", "", "", "", "", "c_2", "c_2", "", "c_3", "c_3", "c_2", "c_2", "c_2", "c_3", "c_3", "", "c_2", "c_2", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(19, {"", "", "", "", "", "", "", "", "", "", "", "", "c_2", "c_2", "", "", "", "c_2", "c_2", "c_2", "", "", "", "c_2", "c_2", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(20, {"", "", "", "", "", "", "", "", "", "", "", "", "", "c_2", "", "", "", "", "c_2", "", "", "", "", "", "c_2", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(21, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(22, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(23, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(24, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(25, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(26, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);
    dibujaFila(27, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, window);

}

void enemy::disparar(RenderWindow& window) {
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
        bala.setFillColor(Color::Black);
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
