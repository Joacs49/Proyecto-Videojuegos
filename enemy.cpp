#include "enemy.h"
#include "miniwin.h"

using namespace miniwin;
using namespace std;

const int escalado = 2;
const bool pintarBorde = false;
const int DERECHA_ENEMIGO = 1;
const int IZQUIERDA_ENEMIGO = -1;

enemy::enemy(int x, int y) : xPos(x), yPos(y), direccion(DERECHA_ENEMIGO), contadorMovimientos(0) {
    srand(static_cast<unsigned int>(time(0)));

    colorMap = {
        {"color_1", {0, 0, 0}},
        {"color_2", {157, 22, 22}},
        {"color_3", {0, 41, 255}},
        {"color_4", {142, 180, 231}},
        {"color_5", {255, 255, 255}},
        {"color_6", {0, 86, 255}},
        {"color_7", {187, 187, 187}},
        {"color_8", {158, 158, 158}},
        {"color_9", {96, 96, 96}},
        {"color_10", {81, 81, 81}},
    };
}

void enemy::setColor(const string& color) {
    if (colorMap.find(color) != colorMap.end()) {
        vector<int> rgb = colorMap[color];
        color_rgb(rgb[0], rgb[1], rgb[2]);
    }
}

void enemy::mover() {
    contadorMovimientos++;

    if (contadorMovimientos > 20) {
        int cambioDireccion = rand() % 3 - 1;
        direccion = cambioDireccion;
        contadorMovimientos = 0;
    }

    if (direccion == IZQUIERDA_ENEMIGO && xPos > 20) {
        xPos -= 16;

    } else if (direccion == DERECHA_ENEMIGO && xPos < 720) {
        xPos += 16;
    }

    /*if (rand() % 50 == 0) {
        yPos += 10;
    }*/
}

void enemy::disparar() {
    if (!disparoEnemigoActivo) {
        disparoEnemigoActivo = true;
        balaEnemigaX = xPos + ancho / 2;
        balaEnemigaY = yPos + alto;
    }

    if (disparoEnemigoActivo) {
        balaEnemigaY += 10;

        color_rgb(255, 0, 0);
        rectangulo_lleno(balaEnemigaX, balaEnemigaY, balaEnemigaX + 4, balaEnemigaY + 10);

        if (balaEnemigaY >= 600) {
            disparoEnemigoActivo = false;
        }
    }
}

void enemy::dibujaCuadrado(int a, int b, const string& colorRelleno) {
    const int x = a * escalado + xPos;
    const int y = b * escalado + yPos;

    setColor(colorRelleno);

    rectangulo_lleno(x, y, x + escalado, y + escalado);

    if (pintarBorde) {
        color_rgb(100, 100, 100);
        linea(x, y, x, y + escalado);
        linea(x, y + escalado, x + escalado, y + escalado);
        linea(x + escalado, y + escalado, x + escalado, y);
        linea(x + escalado, y, x, y);
    }
}

void enemy::dibujaFila(int fila, const vector<string>& colores) {
    for (size_t i = 0; i < colores.size(); ++i) {
        if (!colores[i].empty()) {
            dibujaCuadrado(i, fila, colores[i]);
        }
    }
}

void enemy::dibujar() {
    dibujaFila(0, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_3", "color_3", "color_3", "color_3", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(1, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_3", "color_3", "color_3", "color_3", "color_3", "color_3", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(2, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_3", "color_3", "color_3", "color_4", "color_4", "color_3", "color_3", "color_3", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(3, {"", "", "", "", "", "", "color_3", "", "", "", "", "", "", "", "color_3", "color_3", "color_4", "color_5", "color_5", "color_4", "color_3", "color_3", "", "", "", "", "", "", "", "color_3", "", "", "", "", "", ""});
    dibujaFila(4, {"", "", "", "", "", "color_3", "color_4", "color_3", "", "", "", "", "", "", "color_3", "color_3", "color_4", "color_5", "color_5", "color_4", "color_3", "color_3", "", "", "", "", "", "", "color_3", "color_4", "color_3", "", "", "", "", ""});
    dibujaFila(5, {"", "", "", "", "", "color_3", "color_5", "color_3", "", "", "", "", "", "", "color_3", "color_3", "color_4", "color_5", "color_5", "color_4", "color_3", "color_3", "", "", "", "", "", "", "color_3", "color_5", "color_3", "", "", "", "", ""});
    dibujaFila(6, {"", "", "", "", "", "color_3", "color_5", "color_3", "", "", "", "", "", "", "color_3", "color_3", "color_4", "color_5", "color_5", "color_4", "color_3", "color_3", "", "", "", "", "", "", "color_3", "color_5", "color_3", "", "", "", "", ""});
    dibujaFila(7, {"", "", "", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "", "", "", "", "color_3", "color_3", "color_3", "color_5", "color_5", "color_3", "color_3", "color_3", "", "", "", "", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "", "", ""});
    dibujaFila(8, {"", "", "", "color_1", "color_2", "color_2", "color_2", "color_9", "color_3", "color_1", "color_1", "color_1", "color_1", "", "color_3", "color_3", "color_3", "color_5", "color_5", "color_3", "color_3", "color_3", "", "color_1", "color_1", "color_1", "color_1", "color_3", "color_10", "color_2", "color_2", "color_2", "color_1", "", "", ""});
    dibujaFila(9, {"", "", "", "color_1", "color_2", "color_2", "color_9", "color_9", "color_3", "color_6", "color_3", "color_9", "color_1", "color_1", "color_1", "color_1", "color_3", "color_3", "color_3", "color_3", "color_1", "color_1", "color_1", "color_1", "color_10", "color_3", "color_6", "color_3", "color_10", "color_10", "color_2", "color_2", "color_1", "", "", ""});
    dibujaFila(10, {"", "", "", "color_1", "color_2", "color_9", "color_9", "color_9", "color_3", "color_6", "color_3", "color_9", "color_10", "color_10", "color_10", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_10", "color_10", "color_10", "color_10", "color_3", "color_6", "color_3", "color_10", "color_10", "color_10", "color_2", "color_1", "", "", ""});
    dibujaFila(11, {"", "", "", "color_1", "color_1", "color_9", "color_9", "color_9", "color_3", "color_6", "color_3", "color_9", "color_9", "color_9", "color_9", "color_10", "color_10", "color_10", "color_9", "color_10", "color_10", "color_10", "color_10", "color_10", "color_10", "color_3", "color_6", "color_3", "color_10", "color_10", "color_10", "color_1", "color_1", "", "", ""});
    dibujaFila(12, {"", "", "", "", "color_1", "color_9", "color_9", "color_9", "color_3", "color_6", "color_3", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_10", "color_10", "color_10", "color_10", "color_10", "color_3", "color_6", "color_3", "color_10", "color_10", "color_10", "color_1", "", "", "", ""});
    dibujaFila(13, {"", "", "", "", "color_1", "color_1", "color_9", "color_9", "color_3", "color_3", "color_3", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_10", "color_10", "color_10", "color_10", "color_3", "color_6", "color_3", "color_10", "color_10", "color_1", "color_1", "", "", "", ""});
    dibujaFila(14, {"", "", "", "", "", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_10", "color_10", "color_10", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "", "", "", "", ""});
    dibujaFila(15, {"", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_1", "color_2", "color_2", "color_9", "color_9", "color_9", "color_9", "color_9", "color_9", "color_2", "color_2", "color_1", "color_1", "color_1", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(16, {"", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_2", "color_2", "color_2", "color_9", "color_9", "color_9", "color_9", "color_2", "color_2", "color_2", "color_1", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(17, {"", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_7", "color_2", "color_2", "color_2", "color_2", "color_2", "color_2", "color_8", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(18, {"", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_7", "color_7", "color_2", "color_2", "color_2", "color_2", "color_8", "color_8", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(19, {"", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_7", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(20, {"", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_7", "color_7", "color_8", "color_8", "color_8", "color_8", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(21, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_7", "color_7", "color_8", "color_8", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(22, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_7", "color_7", "color_7", "color_8", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(23, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_2", "color_2", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(24, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(25, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(26, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(27, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});

}

void enemy::mueveYDibuja() {
    mover();
    dibujar();
}
