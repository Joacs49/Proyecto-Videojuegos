#include "game.h"
#include <windows.h>
#include "miniwin.h"

using namespace miniwin;

game::game() : player(300, 420), juegoActivo(true) {
    enemigos.push_back(enemy(100, 50));
    enemigos.push_back(enemy(200, 100));
    enemigos.push_back(enemy(300, 150));
}

void game::iniciar() {
    vredimensiona(800, 600);
}

void game::loop() {
    while (true) {
        manejarEntradas();
        actualizar();
        dibujar();
        espera(10);
    }
}

void game::manejarEntradas() {
    int t = tecla();

    if (t == ESCAPE) {
        exit(0);
    }

    player.mover(t);

    if (t == ESPACIO && !disparo) {
        disparo = true;
        balaX = player.getX() + 40;
        balaY = player.getY();
        PlaySound("Sonido.wav", NULL, SND_ASYNC);
    }
}

void game::actualizar() {
    if (disparo) {
        balaY -= 30;

        if (balaY <= 0) {
            disparo = false;
        }
    }

    for (auto& enemigo : enemigos) {
        enemigo.mover();

        if (rand() % 100 < 5) {
            enemigo.disparar();
            //PlaySound("sonido_enemigo.wav", NULL, SND_ASYNC);
        }

        if (enemigo.disparoEnemigoActivo) {
            enemigo.balaEnemigaY += 10;

            if (enemigo.balaEnemigaY >= 600) {
                enemigo.disparoEnemigoActivo = false;
            }
        }
    }

    verificarColisiones();
}

bool game::colision(int x1, int y1, int ancho1, int alto1, int x2, int y2, int ancho2, int alto2) {
    return x1 < x2 + ancho2 &&
           x1 + ancho1 > x2 &&
           y1 < y2 + alto2 &&
           y1 + alto1 > y2;
}

void game::verificarColisiones() {
    static int cont = 0;

    // Verificar colisión entre el jugador y los enemigos
    for (const auto& enemigo : enemigos) {
        if (colision(player.getX(), player.getY(),
                     player.getAncho(), player.getAlto(),
                     enemigo.getX(), enemigo.getY(),
                     enemigo.getAncho(), enemigo.getAlto())) {

            borra();
            color_rgb(0, 0, 0);
            rectangulo_lleno(0, 0, 800, 600);
            PlaySound("explosion.wav", NULL, SND_ASYNC);

            color(ROJO);
            texto(320, 270, "FIN DEL JUEGO");
            refresca();
            espera(100);

            juegoActivo = false;
            enemigos.clear();
            return;
        }

        // Verificar colisión entre la bala enemiga y el jugador
        if (enemigo.disparoEnemigoActivo) {
            if (colision(player.getX(), player.getY(),
                         player.getAncho(), player.getAlto(),
                         enemigo.balaEnemigaX, enemigo.balaEnemigaY, 4, 10)) {

                borra();
                color_rgb(0, 0, 0);
                rectangulo_lleno(0, 0, 800, 600);
                PlaySound("explosion.wav", NULL, SND_ASYNC);

                color(ROJO);
                texto(320, 270, "FIN DEL JUEGO");
                refresca();
                espera(100);

                juegoActivo = false;
                enemigos.clear();
                return;
            }
        }
    }

    // Verificar colisión de la bala del jugador con los enemigos
    for (size_t i = 0; i < enemigos.size(); ++i) {
        enemy& enemigo = enemigos[i];

        if (disparo &&
            balaX >= enemigo.getX() &&
            balaX <= enemigo.getX() + enemigo.getAncho() &&
            balaY >= enemigo.getY() &&
            balaY <= enemigo.getY() + enemigo.getAlto()) {
            disparo = false;
            enemigos.erase(enemigos.begin() + i);
            PlaySound("explosion.wav", NULL, SND_ASYNC);
            cont +=1 ;
            break;
        }
    }

    if (enemigos.empty() && cont == 3) {
        borra();
        color(ROJO);
        texto(320, 270, "GANO - Joaquin");
        refresca();
        espera(100);
        juegoActivo = false;
    }
}


void game::datos(int v, int z) {
    color(ROJO);
    texto(v, z, "Joaquin Munoz");
}

void game::dibujar() {
    borra();

    if (juegoActivo) {
        player.dibujar();
    }

    //datos(player.getX(), player.getY() - 20);

    for (auto& enemigo : enemigos) {
        enemigo.dibujar();

        if (enemigo.disparoEnemigoActivo) {
            color_rgb(255, 0, 0);
            rectangulo_lleno(enemigo.balaEnemigaX, enemigo.balaEnemigaY, enemigo.balaEnemigaX + 4, enemigo.balaEnemigaY + 10);
        }
    }

    if (disparo) {
        color_rgb(255, 242, 0);
        rectangulo_lleno(balaX, balaY, balaX + 4, balaY + 10);
    }

    if (!juegoActivo) {
        color(ROJO);
        texto(320, 270, "FIN DEL JUEGO");
    }

    refresca();
}

