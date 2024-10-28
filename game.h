#ifndef GAME_H
#define GAME_H

#include <vector>
#include "player.h"
#include "enemy.h"

using namespace std;

class game {
public:
    game();
    void iniciar();
    void loop();
    void manejarEntradas();
    void actualizar();
    void verificarColisiones();
    void dibujar();
    void datos(int v, int z);

private:
    player player;
    bool juegoActivo;
    vector<enemy> enemigos;
    bool disparo = false;
    int balaX, balaY;
    int score = 0;
    int vida = 5;
    bool colision(int x1, int y1, int ancho1, int alto1, int x2, int y2, int ancho2, int alto2);
    void dibujarBarraVida();
    void cargarNivel();
    int nivelActual;
    void mostrarPantallaInicio();
};

#endif
