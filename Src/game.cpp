#include "../Cabeceras/game.h"
#include <windows.h>
#include "../Cabeceras/miniwin.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace miniwin;
using namespace std;

game::game() : player(300, 420), juegoActivo(true), disparo(false), balaX(0), balaY(0), score(0), vida(5), nivelActual(1),
            balasRestantes(maxBalasPorNivel[0]), tiempoRecargador1(0), tiempoRecargador2(0), recargadoresGenerados(0),
            tiempoRecargador(0)  {

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cerr << "Error al inicializar SDL: " << SDL_GetError() << endl;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "Error al inicializar Mix: " << Mix_GetError() << endl;
    }

    cargarNivel();
}

game::~game() {
    Mix_HaltMusic();
    Mix_CloseAudio();
    SDL_Quit(); // Asegate de cerrar SDL
}

void game::iniciar() {
    vredimensiona(800,600);
    mostrarPantallaInicio(); // Muestra la pantalla de inicio
}

const int game::maxBalasPorNivel[3] = {10, 15, 20};

const vector<string> game::sonidosDeFondo =  {
    "C:/Users/frank/Desktop/Nuevo/Proyecto/Sonidos/Nivel_1.wav",
    "C:/Users/frank/Desktop/Nuevo/Proyecto/Sonidos/Nivel_2.wav",
    "C:/Users/frank/Desktop/Nuevo/Proyecto/Sonidos/Nivel_3.wav"
};

void game::mostrarPantallaInicio() {
    borra();
    color(ROJO);
    const char* mensaje = "Presiona ESPACIO para iniciar el juego";
    int anchoTexto = strlen(mensaje) * 8;
    int altoTexto = 15;

    int posX = (800 - anchoTexto) / 2;
    int posY = (600 - altoTexto) / 2;

    texto(posX, posY, mensaje);
    refresca();

    while (true) {
        int t = tecla();
        if (t == ESPACIO) {
            break;
        }
        espera(10);
    }
}

void game::loop() {
    while (true) {
        manejarEntradas();
        actualizar();
        dibujar();
        espera(10);
    }

    if (!juegoActivo) {
        dibujar();
        espera(2000);
    }
}

void game::manejarEntradas() {
    int t = tecla();

    if (t == ESCAPE) {
        exit(0);
    }

    if (juegoActivo) {
        player.mover();
        datos(player.getX(), player.getY() - 20);
        if (t == ESPACIO && !disparo && balasRestantes > 0) {
            disparo = true;
            balaX = player.getX() + 40;
            balaY = player.getY();
            balasRestantes--;
            reproducirEfecto("C:/Users/frank/Desktop/Nuevo/Proyecto/Sonidos/Sonido.wav");
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
            reproducirEfecto("C:/Users/frank/Desktop/Nuevo/Proyecto/Sonidos/sonido_enemigo.wav");
        }

        if (enemigo.disparoEnemigoActivo) {
            enemigo.balaEnemigaY += 10;

            if (enemigo.balaEnemigaY >= 600) {
                enemigo.disparoEnemigoActivo = false;
            }
        }
    }

    unsigned long tiempoActual = SDL_GetTicks();

    if (balasRestantes == 0 && recargadoresGenerados < 2) {
        // Inicializa el temporizador si es la primera vez
        if (tiempoRecargador1 == 0 && recargadoresGenerados == 0) {
            tiempoRecargador1 = tiempoActual; // Iniciar el temporizador para el primer recargador
        }

        // Comprueba si es hora de generar el primer recargador
        if (recargadoresGenerados == 0 && tiempoActual - tiempoRecargador1 >= 2000) {
            recargadores.emplace_back(rand() % 780, rand() % 400);
            tiempoRecargador1 = tiempoActual; // Reiniciar el temporizador
            recargadoresGenerados++;
        }

        // Inicializa el temporizador para el segundo recargador si se ha generado el primero
        if (recargadoresGenerados == 1 && tiempoRecargador2 == 0) {
            tiempoRecargador2 = tiempoActual; // Iniciar el temporizador para el segundo recargador
        }

        // Comprueba si es hora de generar el segundo recargador
        if (recargadoresGenerados == 1 && tiempoActual - tiempoRecargador2 >= 4000) {
            recargadores.emplace_back(rand() % 780, rand() % 400);
            tiempoRecargador2 = tiempoActual; // Iniciar el temporizador para el segundo recargador
            recargadoresGenerados++;
        }
    }

    verificarColisiones();
    verificarColisionRecargadores();
}

void game::verificarColisionRecargadores() {
    for (auto it = recargadores.begin(); it != recargadores.end(); ) {
        if (it->isVisible() &&
            it->colisionaCon(player.getX(), player.getY(), player.getAncho(), player.getAlto())) {
            balasRestantes += 2;
            it->desactivar();  // Desactivar recargador despu廥 de colisi鏮
            recargadoresGenerados--;
            it = recargadores.erase(it); // Elimina el recargador de la lista
        } else {
            ++it; // Solo avanzamos si no hemos borrado el elemento
        }
    }
}

void game::dibujarBarraVida() {
    color_rgb(255, 0, 0);
    rectangulo_lleno(700, 550, 700 + 100, 560);

    color_rgb(0, 255, 0);
    rectangulo_lleno(700, 550, 700 + (100 * vida / 5), 560);
}

// M彋odo para verificar si dos rect嫕gulos colisionan
bool game::colision(int x1, int y1, int ancho1, int alto1, int x2, int y2, int ancho2, int alto2) {
    return (x1 < x2 + ancho2 && x1 + ancho1 > x2 &&
            y1 < y2 + alto2 && y1 + alto1 > y2);
}

void game::verificarColisiones() {
    static int cont = 0;

    for (auto& enemigo : enemigos) {
        if (colision(player.getX(), player.getY(),
                     player.getAncho(), player.getAlto(),
                     enemigo.getX(), enemigo.getY(),
                     enemigo.getAncho(), enemigo.getAlto())) {
            vida--;

            // Si la vida llega a 0, termina el juego
            if (vida <= 0) {
                reproducirEfecto("C:/Users/frank/Desktop/Nuevo/Proyecto/Sonidos/explosion.wav");
                juegoActivo = false;
                enemigos.clear();
                return;
            }
        }

        // Verificar colisi鏮 entre la bala enemiga y el jugador
        if (enemigo.disparoEnemigoActivo) {
            if (colision(player.getX(), player.getY(),
                         player.getAncho(), player.getAlto(),
                         enemigo.balaEnemigaX, enemigo.balaEnemigaY, 4, 10)) {
                vida--;

                // Revisa si la vida llega a 0 despu廥 de recibir el disparo
                if (vida <= 0) {
                    reproducirEfecto("C:/Users/frank/Desktop/Nuevo/Proyecto/Sonidos/explosion.wav");
                    juegoActivo = false;
                    enemigos.clear();
                    return;
                }

                reproducirEfecto("C:/Users/frank/Desktop/Nuevo/Proyecto/Sonidos/explosion.wav");
                enemigo.disparoEnemigoActivo = false;
            }
        }
    }

    // Verificar colisi鏮 de la bala del jugador con los enemigos
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
            reproducirEfecto("C:/Users/frank/Desktop/Nuevo/Proyecto/Sonidos/explosion.wav");
            cont++;
            break;
        }
    }

    // Verificar si se han destruido todos los enemigos
    if (juegoActivo && enemigos.empty()) {
        if (nivelActual < 3) {
            recargadores.clear();
            borra();
            color(ROJO);
            char mensaje[50];
            sprintf(mensaje, "Nivel %d Completo!", nivelActual);
            int anchoTexto = strlen(mensaje) * 8;
            int altoTexto = 15;

            int posX = (800 - anchoTexto) / 2;
            int posY = (600 - altoTexto) / 2;

            texto(posX, posY, mensaje);

            nivelActual++;
            balasRestantes = maxBalasPorNivel[nivelActual - 1];
            cargarNivel();

            refresca();
            espera(2000);
        } else {
            borra();
            color(ROJO);
            recargadores.clear();
            const char* mensaje = "GANASTE LA PARTIDA!";
            int anchoTexto = strlen(mensaje) * 8;
            int altoTexto = 15;

            int posX = (800 - anchoTexto) / 2;
            int posY = (600 - altoTexto) / 2;

            texto(posX, posY, mensaje);
            refresca();
            espera(2000);
            juegoActivo = false;
        }
    }
}

void game::reproducirMusicaFondo(int nivel) {
    // Libera la mica anterior si hay alguna en reproducci鏮
    Mix_HaltMusic();

    // Carga y reproduce la mica de fondo del nivel actual
    Mix_Music* musica = Mix_LoadMUS(sonidosDeFondo[nivel - 1].c_str());
    if (musica) {
        Mix_PlayMusic(musica, -1);  // -1 para reproducir en loop
    } else {
        cerr << "Error al cargar la mica de fondo: " << Mix_GetError() << endl;
    }
}


void game::reproducirEfecto(const char* rutaEfecto) {
    Mix_Chunk* efecto = Mix_LoadWAV(rutaEfecto);
    if (efecto) {
        Mix_PlayChannel(-1, efecto, 0);  // -1 para usar el primer canal libre
    } else {
        cerr << "Error al cargar el efecto: " << Mix_GetError() << endl;
    }
}

void game::cargarNivel() {
    enemigos.clear();
    recargadores.clear();

    tiempoRecargador1 = 0;
    tiempoRecargador2 = 0;

    int cantidadEnemigos;
    if (nivelActual == 1) {
        cantidadEnemigos = 3;
    } else if (nivelActual == 2) {
        cantidadEnemigos = 5;
    } else if (nivelActual == 3) {
        cantidadEnemigos = 6;
    } else {
        cantidadEnemigos = 0;
    }

    // Define posiciones fijas para los enemigos
    vector<pair<int, int>> posiciones = {
        {100, 30}, {200, 100}, {300, 170}, {400, 240}, {500, 310}, {600, 380}
    };

    // No exceder la cantidad de posiciones disponibles
    for (size_t i = 0; i < static_cast<size_t>(cantidadEnemigos) && i < posiciones.size(); ++i) {
        enemy nuevoEnemigo(posiciones[i].first, posiciones[i].second);
        enemigos.push_back(nuevoEnemigo);
    }

    player.setPosicion(300, 420);

    vida = 5;

    balasRestantes = maxBalasPorNivel[nivelActual - 1];

    reproducirMusicaFondo(nivelActual);
}

void game::datos(int x, int y) {
    color(ROJO);

    const char* mensaje = "Joaquin Muñoz";
    int anchoTexto = strlen(mensaje) * 8;

    int posX = x + (player.getAncho() - anchoTexto) / 2;
    int posY = y + player.getAlto() + 5;

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

        char nivelText[50];
        sprintf(nivelText, "Nivel: %d", nivelActual);
        texto(10, 560, nivelText);

        dibujarBarraVida();

        //datos(player.getX(), player.getY());

        char balasText[50];
        sprintf(balasText, "Balas: x%d", balasRestantes);
        texto(700, 530, balasText);
    }

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

    for (auto& recargador : recargadores) {
        if (recargador.isVisible()) {
            recargador.dibujar();
        }
    }

    if (!juegoActivo) {
        Mix_HaltMusic();

        color(ROJO);
        recargadores.clear();
        const char* mensaje = "FIN DEL JUEGO";
        int anchoTexto = strlen(mensaje) * 8;
        int altoTexto = 15;

        int posX = (800 - anchoTexto) / 2;
        int posY = (600 - altoTexto) / 2;

        texto(posX, posY, mensaje);
    }

    refresca();
}
