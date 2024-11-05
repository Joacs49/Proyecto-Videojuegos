#ifndef RECARGADOR_H
#define RECARGADOR_H

class Recargador {
private:
    int x, y;
    bool visible;

public:
    Recargador(int xPos, int yPos);

    int getX() const { return x; }
    int getY() const { return y; }

    bool isVisible() const { return visible; }

    void dibujar();

    void desactivar() { visible = false; }

    bool colisionaCon(int px, int py, int ancho, int alto);
};

#endif

