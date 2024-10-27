#include "game.h"
#include <windows.h>
#include "miniwin.h"

using namespace miniwin;
using namespace std;

game::game() : player(300, 420), juegoActivo(true), disparo(false), balaX(0), balaY(0), score(0), vida(5) {
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

    if (juegoActivo) {
        player.mover();

        if (t == ESPACIO && !disparo) {
            disparo = true;
            balaX = player.getX() + 40;
            balaY = player.getY();
            PlaySound("Sonido.wav", NULL, SND_ASYNC);
        }
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

void game::dibujarBarraVida() {
    color_rgb(255, 0, 0);
    rectangulo_lleno(700, 550, 700 + 100, 560);

    color_rgb(0, 255, 0);
    rectangulo_lleno(700, 550, 700 + (100 * vida / 5), 560);
}

bool game::colision(int x1, int y1, int ancho1, int alto1, int x2, int y2, int ancho2, int alto2) {
    return x1 < x2 + ancho2 &&
           x1 + ancho1 > x2 &&
           y1 < y2 + alto2 &&
           y1 + alto1 > y2;
}

void game::verificarColisiones() {
    static int cont = 0;

    for (auto& enemigo : enemigos) {
        if (colision(player.getX(), player.getY(),
                     player.getAncho(), player.getAlto(),
                     enemigo.getX(), enemigo.getY(),
                     enemigo.getAncho(), enemigo.getAlto())) {
            vida--; // Disminuir la vida

            // Si la vida llega a 0, termina el juego
            if (vida <= 0) {
                PlaySound("explosion.wav", NULL, SND_ASYNC);
                juegoActivo = false;
                enemigos.clear();
                return;
            }
        }

        // Verificar colisión entre la bala enemiga y el jugador
        if (enemigo.disparoEnemigoActivo) {
            if (colision(player.getX(), player.getY(),
                         player.getAncho(), player.getAlto(),
                         enemigo.balaEnemigaX, enemigo.balaEnemigaY, 4, 10)) {
                vida--;

                // Revisa si la vida llega a 0 después de recibir el disparo
                if (vida <= 0) {
                    PlaySound("explosion.wav", NULL, SND_ASYNC);
                    juegoActivo = false;
                    enemigos.clear();
                    return;
                }

                PlaySound("explosion.wav", NULL, SND_ASYNC);
                enemigo.disparoEnemigoActivo = false;
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
            score += 10;
            PlaySound("explosion.wav", NULL, SND_ASYNC);
            cont++;
            break;
        }
    }

    // Verificar si se han destruido todos los enemigos y el conteo
    if (enemigos.empty() && cont == 3) {
        borra();
        color(ROJO);
        const char* mensaje = "GANO JOAQUIN";
        int anchoTexto = strlen(mensaje) * 8;
        int altoTexto = 15;

        int posX = (800 - anchoTexto) / 2;
        int posY = (600 - altoTexto) / 2;

        texto(posX, posY, mensaje);
        refresca();
        espera(100);
        juegoActivo = false;
    }
}

void game::datos(int v, int z) {
    color(ROJO);

    const char* mensaje = "Joaquin Muñoz";
    int anchoTexto = strlen(mensaje) * 8;
    int altoTexto = 15;

    int posX = (800 - anchoTexto) / 2;
    int posY = (600 - altoTexto) / 2;

    texto(posX, posY, mensaje);
}

void game::dibujar() {
    borra();

    if (juegoActivo) {
        player.dibujar();
        color(ROJO);
        char scoreText[50];
        sprintf(scoreText, "Score: %d", score);
        texto(10, 580, scoreText);

        dibujarBarraVida();
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
        const char* mensaje = "FIN DEL JUEGO";
        int anchoTexto = strlen(mensaje) * 8;
        int altoTexto = 15;

        int posX = (800 - anchoTexto) / 2;
        int posY = (600 - altoTexto) / 2;

        texto(posX, posY, mensaje);
    }

    refresca();
}

