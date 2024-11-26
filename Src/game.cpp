#include "../Cabeceras/game.h"
#include "../Cabeceras/Recargador.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

SoundBuffer bufferDisparoJugador;
SoundBuffer bufferDisparoEnemigo;
SoundBuffer bufferExplosion;
Sound sonidoDisparoJugador;
Sound sonidoDisparoEnemigo;
Sound sonidoExplosion;
Music musicaFondo;
Font font;

game::game() : player(300, 420), juegoActivo(true), disparo(false), balaX(0), balaY(0), score(0), vida(5), nivelActual(1),
            balasRestantes(maxBalasPorNivel[0]), tiempoRecargador1(0), tiempoRecargador2(0), tiempoRecargador(0),
            recargadoresGenerados(0){

    if (!bufferDisparoJugador.loadFromFile("C:/Users/frank/Desktop/Nuevo/Proyecto/Sonidos/Sonido.wav") ||
        !bufferDisparoEnemigo.loadFromFile("C:/Users/frank/Desktop/Nuevo/Proyecto/Sonidos/sonido_enemigo.wav") ||
        !bufferExplosion.loadFromFile("C:/Users/frank/Desktop/Nuevo/Proyecto/Sonidos/explosion.wav")) {
        cerr << "Error al cargar algunos efectos de sonido." << endl;
    }

    if (!font.loadFromFile("C:/Users/frank/Desktop/Nuevo/Proyecto/fonts/arial.ttf")) {
        cerr << "Error al cargar el fondo de letra." << endl;
    }

    sonidoDisparoJugador.setBuffer(bufferDisparoJugador);
    sonidoDisparoEnemigo.setBuffer(bufferDisparoEnemigo);
    sonidoExplosion.setBuffer(bufferExplosion);

    cargarNivel();
}

game::~game() {
    renderWindow.close();
}

void game::iniciar() {
    renderWindow.create(sf::VideoMode(800, 600), "Juego");
    mostrarPantallaInicio();
}

void game::renderizarFondo() {
    string claveFondo = "nivel_" + to_string(nivelActual);
    if (texturas.find(claveFondo) != texturas.end()) {
        fondoSprite.setTexture(texturas[claveFondo]);

        // Redimensionamos la textura para que ocupe toda la ventana
        fondoSprite.setScale(
            renderWindow.getSize().x / fondoSprite.getLocalBounds().width,
            renderWindow.getSize().y / fondoSprite.getLocalBounds().height
        );
    } else {
        cerr << "No se encontró la textura para el nivel " << nivelActual << endl;
        return;
    }

    renderWindow.draw(fondoSprite);
}

const int game::maxBalasPorNivel[3] = {10, 15, 20};

const vector<string> game::sonidosDeFondo =  {
    "C:/Users/frank/Desktop/Nuevo/Proyecto/Sonidos/Nivel_1.wav",
    "C:/Users/frank/Desktop/Nuevo/Proyecto/Sonidos/Nivel_2.wav",
    "C:/Users/frank/Desktop/Nuevo/Proyecto/Sonidos/Nivel_3.wav"
};

const map<string, string> game::fondosDeNivel = {
    {"inicio", "C:/Users/frank/Desktop/Nuevo/Proyecto/Fondo/inicio.jpg"},
    {"nivel_1", "C:/Users/frank/Desktop/Nuevo/Proyecto/Fondo/nivel_1.jpg"},
    {"nivel_2", "C:/Users/frank/Desktop/Nuevo/Proyecto/Fondo/nivel_2.jpg"},
    {"nivel_3", "C:/Users/frank/Desktop/Nuevo/Proyecto/Fondo/nivel_3.jpg"},
    {"final", "C:/Users/frank/Desktop/Nuevo/Proyecto/Fondo/final.jpg"},
    {"derrota", "C:/Users/frank/Desktop/Nuevo/Proyecto/Fondo/derrota.jpg"}
};

void game::mostrarPantallaInicio() {
    // Cargar la textura del fondo
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile(game::fondosDeNivel.at("inicio"))) {
        cerr << "Error al cargar el fondo" << endl;
        return;
    }

    // Crear el sprite para el fondo
    sf::Sprite fondoSprite(fondoTexture);

    // Obtener el tamaño de la ventana
    sf::Vector2u tamanoVentana = renderWindow.getSize();

    // Escalar el sprite para que ocupe toda la ventana
    fondoSprite.setScale(
        static_cast<float>(tamanoVentana.x) / fondoTexture.getSize().x, // Escala horizontal
        static_cast<float>(tamanoVentana.y) / fondoTexture.getSize().y  // Escala vertical
    );

    while (renderWindow.isOpen()) {
        sf::Event event;
        while (renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                renderWindow.close();
                return;
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                return;
            }
        }

        // Dibujar el fondo
        renderWindow.clear();
        renderWindow.draw(fondoSprite);
        renderWindow.display();
    }
}

void game::loop() {
    Clock clock;
    while (renderWindow.isOpen() && juegoActivo) {
        Time elapsed = clock.restart();

        manejarEntradas();
        actualizar();

        renderWindow.clear();

        renderizarFondo();
        dibujar();
    }
}

void game::manejarEntradas() {
    Event event;
    while (renderWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            juegoActivo = false;
            renderWindow.close();
        } else if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Escape) {
                exit(0);
            } else if (event.key.code == Keyboard::Space && !disparo && balasRestantes > 0) {
                disparo = true;
                balaX = player.getX() + 40;
                balaY = player.getY();
                balasRestantes--;
                reproducirEfecto(sonidoDisparoJugador);
            }
        }
    }

    // Control de movimiento para `player`
    player.mover();
    datos(player.getX(), player.getY() - 20);
}

void game::actualizar() {
    if (disparo) {
        balaY -= 30;

        if (balaY <= 0) {
            disparo = false;
        }
    }

    // Mover enemigos dependiendo del nivel actual
    if (nivelActual == 1) {
        // Mover enemigos de nivel 1
        for (auto& enemigo : enemigos) {
            enemigo.mover();

            if (rand() % 100 < 5) {
                enemigo.disparar(renderWindow);
                reproducirEfecto(sonidoDisparoEnemigo);
            }

            if (enemigo.disparoEnemigoActivo) {
                enemigo.balaEnemigaY += 10;

                if (enemigo.balaEnemigaY >= 600) {
                    enemigo.disparoEnemigoActivo = false;
                }
            }
        }

        // Verificar colisiones con los enemigos de nivel 1
        verificarColisiones(enemigos);
    } else if (nivelActual == 2) {
        // Mover enemigos de nivel 2
        for (auto& enemigo_2 : enemigos_2) {
            enemigo_2.mover();

            if (rand() % 100 < 5) {
                enemigo_2.disparar(renderWindow);
                reproducirEfecto(sonidoDisparoEnemigo);
            }

            if (enemigo_2.disparoEnemigoActivo) {
                enemigo_2.balaEnemigaY += 10;

                if (enemigo_2.balaEnemigaY >= 600) {
                    enemigo_2.disparoEnemigoActivo = false;
                }
            }
        }

        // Verificar colisiones con los enemigos de nivel 2
        verificarColisiones(enemigos_2);
    } else if (nivelActual == 3) {
        // Mover enemigos de nivel 3 (enemy_3)
        for (auto& enemigo : enemigos) {
            enemigo.mover();

            if (rand() % 100 < 5) {
                enemigo.disparar(renderWindow);
                reproducirEfecto(sonidoDisparoEnemigo);
            }

            if (enemigo.disparoEnemigoActivo) {
                enemigo.balaEnemigaY += 10;

                if (enemigo.balaEnemigaY >= 600) {
                    enemigo.disparoEnemigoActivo = false;
                }
            }
        }

        // Mover enemigos de nivel 3 (enemy_2)
        for (auto& enemigo_2 : enemigos_2) {
            enemigo_2.mover();

            if (rand() % 100 < 5) { // Probabilidad del 5% de disparar
                enemigo_2.disparar(renderWindow);
                reproducirEfecto(sonidoDisparoEnemigo);
            }

            if (enemigo_2.disparoEnemigoActivo) {
                enemigo_2.balaEnemigaY += 10;

                if (enemigo_2.balaEnemigaY >= 600) { // Limitar el rango de la bala
                    enemigo_2.disparoEnemigoActivo = false;
                }
            }
        }

        // Verificar colisiones con enemigos de nivel 3
        verificarColisiones(enemigos);
        verificarColisiones(enemigos_2);
    }

    unsigned long tiempoActual = reloj.getElapsedTime().asMilliseconds();

    if (balasRestantes == 0 && recargadoresGenerados < 2) {
        if (tiempoRecargador1 == 0 && recargadoresGenerados == 0) {
            tiempoRecargador1 = tiempoActual;
        }

        if (recargadoresGenerados == 0 && tiempoActual - tiempoRecargador1 >= 2000) {
            recargadores.emplace_back(rand() % 780, rand() % 400);
            tiempoRecargador1 = tiempoActual;
            recargadoresGenerados++;
        }

        if (recargadoresGenerados == 1 && tiempoRecargador2 == 0) {
            tiempoRecargador2 = tiempoActual;
        }

        if (recargadoresGenerados == 1 && tiempoActual - tiempoRecargador2 >= 4000) {
            recargadores.emplace_back(rand() % 780, rand() % 400);
            tiempoRecargador2 = tiempoActual;
            recargadoresGenerados++;
        }
    }

    verificarColisionRecargadores();
}

void game::verificarColisionRecargadores() {
    for (auto it = recargadores.begin(); it != recargadores.end(); ) {
        if (it->isVisible() &&
            it->colisionaCon(player.getX(), player.getY(), player.getAncho(), player.getAlto())) {
            balasRestantes += 2;
            it->desactivar();
            recargadoresGenerados--;
            it = recargadores.erase(it);
        } else {
            ++it;
        }
    }
}

void game::dibujarBarraVida() {
    RectangleShape fondoBarra(Vector2f(100, 10));
    fondoBarra.setPosition(700, 550);
    fondoBarra.setFillColor(Color(255, 0, 0));

    float anchoVida = 100.0f * vida / 5.0f;
    RectangleShape barraVida(Vector2f(anchoVida, 10));
    barraVida.setPosition(700, 550);
    barraVida.setFillColor(Color(0, 255, 0));

    renderWindow.draw(fondoBarra);
    renderWindow.draw(barraVida);
}

// Verificar si dos rectangulos colisionan
bool game::colision(int x1, int y1, int ancho1, int alto1, int x2, int y2, int ancho2, int alto2) {
    return (x1 < x2 + ancho2 && x1 + ancho1 > x2 &&
            y1 < y2 + alto2 && y1 + alto1 > y2);
}

template <typename T>
void game::verificarColisiones(std::vector<T>& enemigos) {
    static int cont = 0;

    if (!juegoActivo) {
        return;
    }

    // Colisión jugador-enemigo
    for (auto& enemigo : enemigos) {
        if (colision(player.getX(), player.getY(), player.getAncho(), player.getAlto(),
                     enemigo.getX(), enemigo.getY(), enemigo.getAncho(), enemigo.getAlto())) {
            this->vida--;

            if (this->vida <= 0) {
                reproducirEfecto(sonidoExplosion);
                mostrarPantallaDerrota();
                enemigos.clear();
                return;
            }
        }

        // Colisión de disparo enemigo con el jugador
        if (enemigo.disparoEnemigoActivo) {
            if (colision(player.getX(), player.getY(), player.getAncho(), player.getAlto(),
                         enemigo.balaEnemigaX, enemigo.balaEnemigaY, 4, 10)) {
                this->vida--;

                if (this->vida <= 0) {
                    reproducirEfecto(sonidoExplosion);
                    mostrarPantallaDerrota();
                    return;
                }

                reproducirEfecto(sonidoExplosion);
                enemigo.disparoEnemigoActivo = false;
            }
        }
    }

    // Colisiones de la bala del jugador con los enemigos
    for (auto it = enemigos.begin(); it != enemigos.end(); ) {
        if (colision(balaX, balaY, 4, 10, it->getX(), it->getY(), it->getAncho(), it->getAlto())) {
            it = enemigos.erase(it); // Elimina al enemigo
            score += 10;
            reproducirEfecto(sonidoExplosion);

            disparo = false;  // Desactiva la bala
            break; // La bala impacta solo un enemigo
        } else {
            ++it;
        }
    }

    // Verificar si se han destruido todos los enemigos
    bool enemigosRestantes = !enemigos.empty(); // Si el vector no está vacío, hay enemigos restantes

    if (juegoActivo && !enemigosRestantes) {  // Si no quedan enemigos
        if (nivelActual < 3) {
            avanzarNivel(); // Función para manejar transición entre niveles
        } else {
            // Verificar que los enemigos de los niveles anteriores estén vacíos
            if (enemigos.empty() && enemigos_2.empty()) {
                nivelActual = 0;
                juegoActivo = false; // Terminar el juego después del nivel 3 solo si no quedan enemigos
            }
        }
    }
}

// Función para mostrar la pantalla de derrota
void game::mostrarPantallaDerrota() {
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile(fondosDeNivel.at("derrota"))) {
        std::cerr << "Error al cargar el fondo final" << std::endl;
        return;
    }

    sf::Sprite fondoSprite(fondoTexture);
    sf::Vector2u tamanoVentana = renderWindow.getSize();
    fondoSprite.setScale(
        static_cast<float>(tamanoVentana.x) / fondoTexture.getSize().x,
        static_cast<float>(tamanoVentana.y) / fondoTexture.getSize().y
    );

    renderWindow.clear();
    renderWindow.draw(fondoSprite);
    renderWindow.display();

    sleep(milliseconds(2000));
    this->juegoActivo = false;
}

// Función para avanzar al siguiente nivel
void game::avanzarNivel() {
    recargadores.clear();
    renderWindow.clear(Color::Black);

    Text texto;
    texto.setFont(font);
    texto.setString("Nivel " + std::to_string(nivelActual) + " Completo!");
    texto.setCharacterSize(20);
    texto.setFillColor(Color::Red);
    texto.setStyle(Text::Bold);

    FloatRect textoBounds = texto.getLocalBounds();
    texto.setPosition(
        (800 - textoBounds.width) / 2,
        (600 - textoBounds.height) / 2
    );

    renderWindow.draw(texto);
    renderWindow.display();

    nivelActual++;
    balasRestantes = maxBalasPorNivel[nivelActual - 1];
    cargarNivel();

    sleep(milliseconds(2000));
}


void game::cargarRecursos() {
    for (const auto& par : fondosDeNivel) {
        const string& clave = par.first;
        const string& rutaFondo = par.second;

        Texture fondoTexture;
        if (!fondoTexture.loadFromFile(rutaFondo)) {
            cerr << "Error al cargar el fondo: " << rutaFondo << endl;
        } else {
            texturas[clave] = fondoTexture;
            cout << "Fondo cargado con clave: " << clave << " desde " << rutaFondo << endl;
        }
    }
}

void game::reproducirEfecto(Sound& efecto) {
    efecto.play();
}

void game::reproducirMusicaFondo(int nivel) {
    if (musicaFondo.getStatus() == Music::Playing) {
        musicaFondo.stop();
    }

    // Cargar y reproducir la música de fondo del nivel actual
    if (!musicaFondo.openFromFile(sonidosDeFondo[nivel - 1])) {
        cerr << "Error al cargar la música de fondo del nivel " << nivel << endl;
        return;
    }

    musicaFondo.setLoop(true);
    musicaFondo.play();
}

void game::cargarNivel() {
    enemigos.clear();
    enemigos_2.clear();
    enemigos_3.clear();

    tiempoRecargador1 = 0;
    tiempoRecargador2 = 0;

    // Cargar fondo
    string claveNivel = "nivel_" + to_string(nivelActual);
    if (texturas.find(claveNivel) != texturas.end()) {
        fondoSprite.setTexture(texturas[claveNivel]);
    } else {
        if (fondoTexture.loadFromFile(fondosDeNivel.at(claveNivel))) {
            fondoSprite.setTexture(fondoTexture);
            texturas[claveNivel] = fondoTexture;
        } else {
            cerr << "No se pudo cargar el fondo para el nivel " << claveNivel << endl;
        }
    }

    // Crear enemigos dependiendo del nivel
    if (nivelActual == 1) {
        vector<pair<int, int>> posiciones = {
            {100, 30}, {200, 100}, {300, 170}
        };

        // Cantidad de enemigos depende del nivel
        int cantidadEnemigos = 3;

        for (int i = 0; i < cantidadEnemigos; ++i) {
            enemy nuevoEnemigo(posiciones[i].first, posiciones[i].second, velocidadEnemigos);
            enemigos.push_back(nuevoEnemigo);
        }
    }

    if (nivelActual == 2) {
        vector<pair<int, int>> posicionesNivel2 = {
            {450, 120}, {500, 180}, {550, 240}, {600, 300}, {650, 360}
        };

        for (int i = 0; i < 5; ++i) {
            enemy_2 enemigoNivel2(posicionesNivel2[i].first, posicionesNivel2[i].second, velocidadEnemigos);
            enemigos_2.push_back(enemigoNivel2);
        }
    }

    if (nivelActual == 3) {
        vector<pair<int, int>> posicionesNivel3 = {
            {100, 100}, {200, 150}, {300, 200}, {400, 250}, {500, 300}
        };

        int totalEnemigosNivel3 = 5;
        int cantidadEnemy3 = totalEnemigosNivel3 / 2; // La mitad (aproximada) será de enemy_3
        int cantidadEnemy2 = totalEnemigosNivel3 - cantidadEnemy3; // El resto será de enemy_2

        // Generar enemigos de tipo enemy_3
        for (int i = 0; i < cantidadEnemy3; ++i) {
            enemy nuevoEnemigoEspecial(posicionesNivel3[i].first, posicionesNivel3[i].second, velocidadEnemigos);
            enemigos.push_back(nuevoEnemigoEspecial);
        }

        // Generar enemigos de tipo enemy_2
        for (int i = 0; i < cantidadEnemy2; ++i) {
            enemy_2 enemigoNivel2(posicionesNivel3[cantidadEnemy3 + i].first, posicionesNivel3[cantidadEnemy3 + i].second, velocidadEnemigos);
            enemigos_2.push_back(enemigoNivel2);
        }
    }

    // Establecer la posición inicial del jugador
    player.setPosicion(300, 420);

    // Inicializar vida y balas restantes según el nivel
    vida = 5;
    balasRestantes = maxBalasPorNivel[nivelActual - 1];

    // Reproducir la música de fondo para el nivel actual
    reproducirMusicaFondo(nivelActual);
}

void game::datos(int x, int y) {
    Text texto;
    texto.setFont(font);
    texto.setString("Joaquin Muñoz");
    texto.setCharacterSize(16);
    texto.setFillColor(Color::Red);

    FloatRect textoBounds = texto.getLocalBounds();
    int posX = x + (player.getAncho() - textoBounds.width) / 2;
    int posY = y + player.getAlto() + 5;
    texto.setPosition(posX, posY);

    renderWindow.draw(texto);
}

void game::configurarTexto(sf::Text& texto, const string& contenido, int tamano, const Color& color, const Vector2f& posicion) {
    texto.setFont(font);
    texto.setString(contenido);
    texto.setCharacterSize(tamano);
    texto.setFillColor(color);
    texto.setPosition(posicion);
}

sf::Vector2f game::calcularCentroTexto(const string& texto, int tamano) {
    Text tempText;
    tempText.setFont(font);
    tempText.setString(texto);
    tempText.setCharacterSize(tamano);
    FloatRect bounds = tempText.getLocalBounds();

    return Vector2f((800 - bounds.width) / 2, (600 - bounds.height) / 2);
}

void game::dibujar() {
    renderWindow.clear();
    renderizarFondo();

    if (juegoActivo) {
        player.dibujar(renderWindow);

        Text scoreText;
        configurarTexto(scoreText, "Score: " + to_string(score), 16, Color::Red, {10, 580});
        renderWindow.draw(scoreText);

        Text nivelText;
        configurarTexto(nivelText, "Nivel: " + to_string(nivelActual), 16, Color::Red, {10, 560});
        renderWindow.draw(nivelText);

        dibujarBarraVida();

        Text balasText;
        configurarTexto(balasText, "Balas: x" + to_string(balasRestantes), 16, Color::Red, {700, 530});
        renderWindow.draw(balasText);
    }

    // Dibujar enemigos de nivel 1
    if (nivelActual == 1) {
        for (auto& enemigo : enemigos) {
            enemigo.dibujar(renderWindow);

            if (enemigo.disparoEnemigoActivo) {
                RectangleShape balaEnemiga(Vector2f(4, 10));
                balaEnemiga.setPosition(enemigo.balaEnemigaX, enemigo.balaEnemigaY);
                balaEnemiga.setFillColor(Color(255, 0, 0));
                renderWindow.draw(balaEnemiga);
            }
        }
    }

    // Dibujar enemigos de nivel 2
    if (nivelActual == 2) {
        for (auto& enemigo_2 : enemigos_2) {
            enemigo_2.dibujar(renderWindow);

            if (enemigo_2.disparoEnemigoActivo) {
                RectangleShape balaEnemiga(Vector2f(4, 10));
                balaEnemiga.setPosition(enemigo_2.balaEnemigaX, enemigo_2.balaEnemigaY);
                balaEnemiga.setFillColor(Color(0, 255, 255));
                renderWindow.draw(balaEnemiga);
            }
        }
    }

    // Dibujar enemigos de nivel 3
    if (nivelActual == 3) {
        for (auto& enemigo : enemigos) {
            enemigo.dibujar(renderWindow);

            if (enemigo.disparoEnemigoActivo) {
                RectangleShape balaEnemiga(Vector2f(4, 10));
                balaEnemiga.setPosition(enemigo.balaEnemigaX, enemigo.balaEnemigaY);
                balaEnemiga.setFillColor(Color(255, 0, 0));
                renderWindow.draw(balaEnemiga);
            }
        }

        for (auto& enemigo_2 : enemigos_2) {
            enemigo_2.dibujar(renderWindow);

            if (enemigo_2.disparoEnemigoActivo) {
                RectangleShape balaEnemiga(Vector2f(4, 10));
                balaEnemiga.setPosition(enemigo_2.balaEnemigaX, enemigo_2.balaEnemigaY);
                balaEnemiga.setFillColor(Color(0, 255, 255));
                renderWindow.draw(balaEnemiga);
            }
        }
    }

    // Dibujar la bala del jugador
    if (disparo) {
        RectangleShape bala(Vector2f(4, 10));
        bala.setPosition(balaX, balaY);
        bala.setFillColor(Color(255, 242, 0));
        renderWindow.draw(bala);
    }

    // Dibujar recargadores
    for (auto& recargador : recargadores) {
        if (recargador.isVisible()) {
            recargador.dibujar(renderWindow);
        }
    }

    // Mostrar mensaje de fin del juego
    if (!juegoActivo && nivelActual == 0) {
        recargadores.clear();

        sf::Texture fondoTexture;
            if (!fondoTexture.loadFromFile(fondosDeNivel.at("final"))) {
                std::cerr << "Error al cargar el fondo final" << std::endl;
                return;
            }

            // Crear el sprite para el fondo
            sf::Sprite fondoSprite(fondoTexture);

            // Obtener el tamaño de la ventana
            sf::Vector2u tamanoVentana = renderWindow.getSize();

            // Escalar el sprite para que ocupe toda la ventana
            fondoSprite.setScale(
                static_cast<float>(tamanoVentana.x) / fondoTexture.getSize().x, // Escala horizontal
                static_cast<float>(tamanoVentana.y) / fondoTexture.getSize().y  // Escala vertical
            );

            // Limpiar la ventana antes de dibujar el nuevo fondo
            renderWindow.clear();

            // Dibujar el fondo de victoria
            renderWindow.draw(fondoSprite);

            // Mostrar la ventana con el fondo de victoria
            renderWindow.display();


        sleep(seconds(3));

        juegoActivo = false;
    }

    renderWindow.display();
}
