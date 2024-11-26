#ifndef DATOS_H
#define DATOS_H

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

class Datos {
public:
    Datos(int x = 0, int y = 0);
    void dibujar(RenderWindow& window);
    void dibujaFila(int fila, const vector<string>& colores, RenderWindow& window);
    void dibujaCuadrado(int a, int b, const string& colorRelleno, RenderWindow& window);
private:
    map<string, Color> colorMap;
    int offsetX, offsetY;
};

#endif // DATOS_H
