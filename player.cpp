#include "player.h"
#include "miniwin.h"
#include <windows.h>

using namespace miniwin;
using namespace std;

const int escalado = 2;
const bool pintarBorde = false;

player::player(int x, int y) : offsetX(x), offsetY(y) {
    colorMap = {
        {"color_1", {3, 2, 2}},
        {"color_2", {46, 46, 46}},
        {"color_3", {93, 94, 96}},
        {"color_4", {104, 21, 23}},
        {"color_5", {223, 43, 47}},
        {"color_6", {27, 44, 80}},
        {"color_7", {15, 53, 109}},
        {"color_8", {224, 225, 227}},
        {"color_9", {255, 253, 254}},
    };
}

void player::setColor(const string& color) {
    if (colorMap.find(color) != colorMap.end()) {
        vector<int> rgb = colorMap[color];
        color_rgb(rgb[0], rgb[1], rgb[2]);
    }
}

void player::mover() {
    const int VELOCIDAD = 5;

    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        if (offsetX > 0) {
            offsetX -= VELOCIDAD;
        }
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        if (offsetX < 800 - ANCHO_NAVE) {
            offsetX += VELOCIDAD;
        }
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        if (offsetY > 0) {
            offsetY -= VELOCIDAD;
        }
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        if (offsetY < 600 - ALTO_NAVE) {
            offsetY += VELOCIDAD;
        }
    }
}

void player::dibujaCuadrado(int a, int b, const string& colorRelleno) {
    const int x = a * escalado + offsetX;
    const int y = b * escalado + offsetY;

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

void player::dibujaFila(int fila, const vector<string>& colores) {
    for (size_t i = 0; i < colores.size(); ++i) {
        if (!colores[i].empty()) {
            dibujaCuadrado(i, fila, colores[i]);
        }
    }
}

void player::setPosicion(int x, int y) {
    offsetX = x;
    offsetY = y;
}

void player::dibujar() {
    dibujaFila(0, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(1, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(2, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(3, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(4, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(5, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(6, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(7, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(8, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(9, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(10, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(11, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_3", "color_3", "color_3", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(12, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_3", "color_9", "color_9", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(13, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_3", "color_9", "color_1", "color_9", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(14, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_9", "color_1", "color_1", "color_1", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(15, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_9", "color_1", "color_9", "color_1", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(16, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_9", "color_9", "color_8", "color_8", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(17, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_3", "color_3", "color_9", "color_8", "color_8", "color_3", "color_3", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(18, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_7", "color_3", "color_9", "color_3", "color_3", "color_3", "color_8", "color_3", "color_7", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(19, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_7", "color_6", "color_3", "color_9", "color_9", "color_9", "color_8", "color_8", "color_3", "color_6", "color_7", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(20, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_3", "color_9", "color_9", "color_9", "color_8", "color_8", "color_3", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(21, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_3", "color_9", "color_9", "color_8", "color_8", "color_8", "color_3", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(22, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_3", "color_3", "color_9", "color_8", "color_8", "color_3", "color_3", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(23, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_3", "color_9", "color_3", "color_3", "color_3", "color_8", "color_3", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(24, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_3", "color_9", "color_9", "color_8", "color_8", "color_8", "color_3", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(25, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_3", "color_9", "color_9", "color_8", "color_8", "color_8", "color_3", "color_9", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(26, {"", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_3", "color_9", "color_3", "color_8", "color_3", "color_8", "color_3", "color_9", "color_9", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(27, {"", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_8", "color_3", "color_9", "color_3", "color_8", "color_3", "color_8", "color_3", "color_9", "color_9", "color_9", "color_9", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(28, {"", "", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_8", "color_8", "color_3", "color_9", "color_3", "color_8", "color_3", "color_8", "color_3", "color_9", "color_9", "color_9", "color_8", "color_8", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", "", ""});
    dibujaFila(29, {"", "", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_9", "color_8", "color_8", "color_3", "color_9", "color_9", "color_8", "color_8", "color_8", "color_3", "color_9", "color_9", "color_9", "color_8", "color_8", "color_8", "color_6", "color_7", "color_1", "", "", "", "", "", "", "", ""});
    dibujaFila(30, {"", "", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_9", "color_8", "color_8", "color_8", "color_3", "color_8", "color_8", "color_8", "color_8", "color_8", "color_3", "color_9", "color_9", "color_9", "color_8", "color_8", "color_8", "color_8", "color_6", "color_7", "color_1", "", "", "", "", "", "", ""});
    dibujaFila(31, {"", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_9", "color_8", "color_8", "color_8", "color_8", "color_3", "color_8", "color_8", "color_8", "color_8", "color_8", "color_3", "color_9", "color_9", "color_8", "color_8", "color_8", "color_8", "color_8", "color_6", "color_6", "color_7", "color_1", "", "", "", "", "", ""});
    dibujaFila(32, {"", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_9", "color_8", "color_8", "color_8", "color_8", "color_3", "color_3", "color_3", "color_3", "color_3", "color_3", "color_3", "color_9", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_6", "color_7", "color_1", "", "", "", "", "", ""});
    dibujaFila(33, {"", "", "", "", "", "", "", "", "color_1", "color_7", "color_6", "color_9", "color_9", "color_8", "color_8", "color_8", "color_8", "color_4", "color_5", "color_5", "color_5", "color_5", "color_5", "color_5", "color_5", "color_4", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_6", "color_7", "color_1", "", "", "", "", "", ""});
    dibujaFila(34, {"", "", "", "", "", "", "", "", "", "color_1", "color_9", "color_9", "color_9", "color_8", "color_8", "color_2", "color_8", "color_4", "color_4", "color_4", "color_4", "color_4", "color_4", "color_4", "color_4", "color_4", "color_8", "color_8", "color_2", "color_8", "color_8", "color_8", "color_8", "color_8", "color_1", "", "", "", "", "", "", ""});
    dibujaFila(35, {"", "", "", "", "", "", "", "", "", "color_1", "color_9", "color_2", "color_2", "color_2", "color_2", "color_2", "color_8", "color_3", "color_9", "color_9", "color_8", "color_3", "color_9", "color_9", "color_8", "color_3", "color_8", "color_8", "color_2", "color_2", "color_2", "color_2", "color_2", "color_8", "color_1", "", "", "", "", "", "", ""});
    dibujaFila(36, {"", "", "", "", "", "", "", "", "", "color_1", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_3", "color_9", "color_9", "color_8", "color_3", "color_9", "color_9", "color_8", "color_3", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_8", "color_1", "", "", "", "", "", "", ""});
    dibujaFila(37, {"", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_3", "color_8", "color_8", "color_8", "color_3", "color_9", "color_8", "color_8", "color_3", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "", "", "", "", "", "", "", ""});
    dibujaFila(38, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_8", "color_8", "color_8", "color_3", "color_8", "color_8", "color_8", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(39, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "color_1", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(40, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(41, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(42, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(43, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(44, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(45, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(46, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(47, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(48, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(49, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});

}
