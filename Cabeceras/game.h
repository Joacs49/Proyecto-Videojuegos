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
#include "recargador.h"

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
    static const std::map<std::string, std::string> fondosDeNivel;
    static const std::map<std::string, std::string> sonidosEfectos;

    vector<Recargador> recargadores;
    void dibujarBarraVida();
    void renderizarFondo();
    sf::Font font;
    float velocidadEnemigos = 1.0f;

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

    sf::Texture fondoTexture;
    sf::Sprite fondoSprite;
    sf::Music musicaFondo;
    sf::RenderWindow renderWindow;
    sf::Texture textura;
    std::map<std::string, sf::Texture> texturas;
    std::map<std::string, sf::SoundBuffer> sonidos;
    sf::Sound efectoSonido;
    sf::Clock reloj;
    std::map<std::string, sf::SoundBuffer> buffers;
    sf::Sound sonidoEfecto;

    std::map<std::string, sf::SoundBuffer> buffersSonido;
    std::map<std::string, sf::Sound> efectosSonido;
    std::vector<sf::Sound> sonidosEnEjecucion;

    unsigned long tiempoRecargador1, tiempoRecargador2;
    int tiempoRecargador;

    static const int maxBalasPorNivel[3];

    bool colision(int x1, int y1, int ancho1, int alto1, int x2, int y2, int ancho2, int alto2);
    void cargarNivel();
    void verificarColisionRecargadores();
    void mostrarPantallaInicio();
    void reproducirMusicaFondo(int nivel);
    void reproducirEfecto(sf::Sound& efecto);
    void cargarRecursos();
    void configurarTexto(sf::Text& texto, const std::string& contenido, int tamano, const sf::Color& color, const sf::Vector2f& posicion);
    sf::Vector2f calcularCentroTexto(const std::string& texto, int tamano);
    void detenerMusica();
    void reiniciarReloj();
};

#endif
