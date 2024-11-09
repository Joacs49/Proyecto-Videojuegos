#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string> // Agrega esta línea para usar std::string
#include "player.h"
#include "enemy.h"
#include "recargador.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


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

    static const std::vector<std::string> sonidosDeFondo;
    vector<Recargador> recargadores;
    void dibujarBarraVida();

private:
    player player;
    bool juegoActivo;
    vector<enemy> enemigos;
    bool disparo = false;
    int balaX, balaY;
    int score = 0;
    int vida = 5;
    int nivelActual;
    int balasRestantes;
    int recargadoresGenerados;



    unsigned long tiempoRecargador1, tiempoRecargador2;
    int tiempoRecargador;

    static const int maxBalasPorNivel[3]; // Constante para balas por nivel

    bool colision(int x1, int y1, int ancho1, int alto1, int x2, int y2, int ancho2, int alto2);
    void cargarNivel();
    void verificarColisionRecargadores();
    void mostrarPantallaInicio();
    void reproducirMusicaFondo(int nivel);
    void reproducirEfecto(const char* rutaEfecto);
    void cargarRecursos();
};

#endif
