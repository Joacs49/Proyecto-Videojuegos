#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include <map>
#include "player.h"
#include "enemy.h"
#include "enemy_2.h"
#include "enemy_3.h"
#include "recargador.h"
#include "Datos.h"

using namespace std;
using namespace sf;

class game {
public:
    game();
    ~game();
    void iniciar();
    void loop();
    void manejarEntradas();
    void actualizar();

    template <typename T>
    void verificarColisiones(std::vector<T>& enemigos);

    void verificarColisiones();

    void dibujar();
    void datos(int v, int z);

    static const vector<string> sonidosDeFondo;
    static const map<string, string> fondosDeNivel;
    static const map<string, string> sonidosEfectos;

    vector<Recargador> recargadores;
    void dibujarBarraVida();
    void renderizarFondo();
    Font font;
    float velocidadEnemigos = 1.0f;
    void mostrarMensaje(const string& mensaje, const Color& color);
    void mostrarPantallaDerrota();
    void avanzarNivel();

private:
    player player;
    Datos datosJugador;
    bool juegoActivo;
    vector<enemy> enemigos;
    vector<enemy_2> enemigos_2;
    vector<enemy_3> enemigos_3;
    bool disparo = false;
    int balaX, balaY;
    int score = 0;
    int vida = 5;
    int nivelActual;
    int balasRestantes;
    int recargadoresGenerados;

    Texture fondoTexture;
    Sprite fondoSprite;
    Music musicaFondo;
    RenderWindow renderWindow;
    Texture textura;
    map<string, Texture> texturas;
    map<string, SoundBuffer> sonidos;
    Sound efectoSonido;
    Clock reloj;
    map<string, SoundBuffer> buffers;
    Sound sonidoEfecto;

    map<string, SoundBuffer> buffersSonido;
    map<string, Sound> efectosSonido;
    vector<Sound> sonidosEnEjecucion;

    unsigned long tiempoRecargador1, tiempoRecargador2;
    int tiempoRecargador;

    static const int maxBalasPorNivel[3];

    bool colision(int x1, int y1, int ancho1, int alto1, int x2, int y2, int ancho2, int alto2);

    void cargarNivel();
    void verificarColisionRecargadores();
    void mostrarPantallaInicio();
    void reproducirMusicaFondo(int nivel);
    void reproducirEfecto(Sound& efecto);
    void cargarRecursos();
    void configurarTexto(Text& texto, const string& contenido, int tamano, const Color& color, const Vector2f& posicion);
    Vector2f calcularCentroTexto(const string& texto, int tamano);
    void detenerMusica();

};

#endif
