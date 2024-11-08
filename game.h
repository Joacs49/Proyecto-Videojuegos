#ifndef GAME_H
#define GAME_H

#include <vector>
#include "player.h"
#include "enemy.h"
#include "recargador.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

using namespace std;

class game {
public:
    game();
    ~game();
    void iniciar();
    void loop();
    void manejarEntradas();
    void actualizar();
    void verificarColisiones();
    void avanzarNivel();
    void dibujar();
    void datos(int v, int z);
    vector<Recargador> recargadores;
    unsigned long tiempoRecargador1, tiempoRecargador2;
    int tiempoRecargador;

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
    int balasRestantes;
    static const int maxBalasPorNivel[3];
    void verificarColisionRecargadores();
    void mostrarPantallaInicio();
    static const vector<string> sonidosDeFondo;
    void reproducirMusicaFondo(int nivel);
    void reproducirEfecto(const char* rutaEfecto);
    int recargadoresGenerados;
};

#endif
