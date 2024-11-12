#include "../Cabeceras/game.h"
#include "../Cabeceras/Recargador.h"
#include <fstream>
#include <iostream>

using namespace std;

sf::SoundBuffer bufferDisparoJugador;
sf::SoundBuffer bufferDisparoEnemigo;
sf::SoundBuffer bufferExplosion;
sf::Sound sonidoDisparoJugador;
sf::Sound sonidoDisparoEnemigo;
sf::Sound sonidoExplosion;
sf::Music musicaFondo;
sf::Font font;

game::game() : player(300, 420), juegoActivo(true), disparo(false), balaX(0), balaY(0), score(0), vida(5), nivelActual(1),
            balasRestantes(maxBalasPorNivel[0]), tiempoRecargador1(0), tiempoRecargador2(0), recargadoresGenerados(0),
            tiempoRecargador(0) {

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
    std::string claveFondo = "nivel_" + std::to_string(nivelActual);
    if (texturas.find(claveFondo) != texturas.end()) {
        fondoSprite.setTexture(texturas[claveFondo]);

        // Redimensionamos la textura para que ocupe toda la ventana
        fondoSprite.setScale(
            renderWindow.getSize().x / fondoSprite.getLocalBounds().width,
            renderWindow.getSize().y / fondoSprite.getLocalBounds().height
        );
    } else {
        std::cerr << "No se encontró la textura para el nivel " << nivelActual << std::endl;
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

const std::map<std::string, std::string> game::fondosDeNivel = {
    {"nivel_1", "C:/Users/frank/Desktop/Nuevo/Proyecto/Fondo/nivel_1.jpg"},
    {"nivel_2", "C:/Users/frank/Desktop/Nuevo/Proyecto/Fondo/nivel_2.jpg"},
    {"nivel_3", "C:/Users/frank/Desktop/Nuevo/Proyecto/Fondo/nivel_3.jpg"}
};

void game::mostrarPantallaInicio() {
    sf::Font font;
    if (!font.loadFromFile("C:/Users/frank/Desktop/Nuevo/Proyecto/fonts/arial.ttf")) {
        cerr << "Error al cargar la fuente" << endl;
        return;
    }

    sf::Text mensaje("Presiona ESPACIO para iniciar el juego", font, 20);
    mensaje.setFillColor(sf::Color::Red);
    mensaje.setPosition(
        (800 - mensaje.getLocalBounds().width) / 2,
        (600 - mensaje.getLocalBounds().height) / 2
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

        renderWindow.clear();
        renderWindow.draw(mensaje);
        renderWindow.display();
    }
}

void game::loop() {
    sf::Clock clock;
    while (renderWindow.isOpen() && juegoActivo) {
        sf::Time elapsed = clock.restart();

        manejarEntradas();
        actualizar();

        renderWindow.clear();

        renderizarFondo();
        dibujar();
    }
}

void game::manejarEntradas() {
    sf::Event event;
    while (renderWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            juegoActivo = false;
            renderWindow.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                exit(0);
            } else if (event.key.code == sf::Keyboard::Space && !disparo && balasRestantes > 0) {
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

    verificarColisiones();
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
    sf::RectangleShape fondoBarra(sf::Vector2f(100, 10));
    fondoBarra.setPosition(700, 550);
    fondoBarra.setFillColor(sf::Color(255, 0, 0));

    float anchoVida = 100.0f * vida / 5.0f;
    sf::RectangleShape barraVida(sf::Vector2f(anchoVida, 10));
    barraVida.setPosition(700, 550);
    barraVida.setFillColor(sf::Color(0, 255, 0));

    renderWindow.draw(fondoBarra);
    renderWindow.draw(barraVida);
}

// Verificar si dos rectangulos colisionan
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
                reproducirEfecto(sonidoExplosion);
                sf::Text texto;
                texto.setFont(font);
                texto.setString("PERDISTE :(");
                texto.setCharacterSize(20);
                texto.setFillColor(sf::Color::Red);
                texto.setStyle(sf::Text::Bold);

                sf::FloatRect textoBounds = texto.getLocalBounds();
                texto.setPosition(
                    (800 - textoBounds.width) / 2,
                    (600 - textoBounds.height) / 2
                );

                renderWindow.clear();
                renderWindow.draw(texto);
                renderWindow.display();

                sf::sleep(sf::milliseconds(2000));

                juegoActivo = false;

                enemigos.clear();
                return;
            }
        }

        // Verificar colision entre la bala enemiga y el jugador
        if (enemigo.disparoEnemigoActivo) {
            if (colision(player.getX(), player.getY(),
                         player.getAncho(), player.getAlto(),
                         enemigo.balaEnemigaX, enemigo.balaEnemigaY, 4, 10)) {
                vida--;

                // Revisa si la vida llega a 0 despues de recibir el disparo
                if (vida <= 0) {
                    reproducirEfecto(sonidoExplosion);
                    sf::Text texto;
                    texto.setFont(font);
                    texto.setString("PERDISTE :(");
                    texto.setCharacterSize(20);
                    texto.setFillColor(sf::Color::Red);
                    texto.setStyle(sf::Text::Bold);

                    sf::FloatRect textoBounds = texto.getLocalBounds();
                    texto.setPosition(
                        (800 - textoBounds.width) / 2,
                        (600 - textoBounds.height) / 2
                    );

                    renderWindow.clear();
                    renderWindow.draw(texto);
                    renderWindow.display();

                    sf::sleep(sf::milliseconds(2000));

                    juegoActivo = false;

                }

                reproducirEfecto(sonidoExplosion);
                enemigo.disparoEnemigoActivo = false;
            }
        }
    }

    // Verificar colision de la bala del jugador con los enemigos
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
            reproducirEfecto(sonidoExplosion);
            cont++;
            break;
        }
    }

    // Verificar si se han destruido todos los enemigos
        if (juegoActivo && enemigos.empty()) {
        if (nivelActual < 3) {
            recargadores.clear();
            renderWindow.clear(sf::Color::Black);


            sf::Text texto;
            texto.setFont(font);
            texto.setString("Nivel " + std::to_string(nivelActual) + " Completo!");
            texto.setCharacterSize(20);
            texto.setFillColor(sf::Color::Red);
            texto.setStyle(sf::Text::Bold);

            // Centrar texto
            sf::FloatRect textoBounds = texto.getLocalBounds();
            texto.setPosition(
                (800 - textoBounds.width) / 2,
                (600 - textoBounds.height) / 2
            );

            // Dibujar texto en pantalla
            renderWindow.draw(texto);
            renderWindow.display();

            nivelActual++;
            balasRestantes = maxBalasPorNivel[nivelActual - 1];
            cargarNivel();

            sf::sleep(sf::milliseconds(2000));
        } else {
            renderWindow.clear(sf::Color::Black);

            // Configuración de texto
            sf::Text texto;
            texto.setFont(font);
            texto.setString("GANASTE LA PARTIDA!");
            texto.setCharacterSize(20);
            texto.setFillColor(sf::Color::Red);
            texto.setStyle(sf::Text::Bold);

            // Centrar texto
            sf::FloatRect textoBounds = texto.getLocalBounds();
            texto.setPosition(
                (800 - textoBounds.width) / 2,
                (600 - textoBounds.height) / 2
            );

            // Dibujar texto en pantalla
            renderWindow.draw(texto);
            renderWindow.display();

            sf::sleep(sf::milliseconds(2000));
            juegoActivo = false;
        }
    }

}

void game::cargarRecursos() {
    for (const auto& par : fondosDeNivel) {
        const std::string& clave = par.first;
        const std::string& rutaFondo = par.second;

        sf::Texture fondoTexture;
        if (!fondoTexture.loadFromFile(rutaFondo)) {
            std::cerr << "Error al cargar el fondo: " << rutaFondo << std::endl;
        } else {
            texturas[clave] = fondoTexture;
            std::cout << "Fondo cargado con clave: " << clave << " desde " << rutaFondo << std::endl;
        }
    }
}

void game::reproducirEfecto(sf::Sound& efecto) {
    efecto.play();
}

void game::reproducirMusicaFondo(int nivel) {
    if (musicaFondo.getStatus() == sf::Music::Playing) {
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
    recargadores.clear();

    tiempoRecargador1 = 0;
    tiempoRecargador2 = 0;

    std::string claveNivel = "nivel_" + std::to_string(nivelActual);
    std::cout << "Buscando fondo con clave: " << claveNivel << std::endl;

    if (texturas.find(claveNivel) != texturas.end()) {
        fondoSprite.setTexture(texturas[claveNivel]);
        std::cout << "Fondo cargado para: " << claveNivel << std::endl;
    } else {
        if (fondoTexture.loadFromFile(fondosDeNivel.at(claveNivel))) {
            fondoSprite.setTexture(fondoTexture);
            texturas[claveNivel] = fondoTexture;
            std::cout << "Fondo cargado desde archivo para: " << claveNivel << std::endl;
        } else {
            std::cerr << "No se pudo cargar el fondo para el nivel " << claveNivel << std::endl;
        }
    }

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
    std::vector<std::pair<int, int>> posiciones = {
        {100, 30}, {200, 100}, {300, 170}, {400, 240}, {500, 310}, {600, 380}
    };

    // No exceder la cantidad de posiciones disponibles
    for (size_t i = 0; i < static_cast<size_t>(cantidadEnemigos) && i < posiciones.size(); ++i) {
        enemy nuevoEnemigo(posiciones[i].first, posiciones[i].second, velocidadEnemigos);
        enemigos.push_back(nuevoEnemigo);
    }

    player.setPosicion(300, 420);

    vida = 5;
    balasRestantes = maxBalasPorNivel[nivelActual - 1];

    reproducirMusicaFondo(nivelActual);
}

void game::datos(int x, int y) {
    sf::Text texto;
    texto.setFont(font);
    texto.setString("Joaquin Muñoz");
    texto.setCharacterSize(16);
    texto.setFillColor(sf::Color::Red);

    sf::FloatRect textoBounds = texto.getLocalBounds();
    int posX = x + (player.getAncho() - textoBounds.width) / 2;
    int posY = y + player.getAlto() + 5;
    texto.setPosition(posX, posY);

    renderWindow.draw(texto);
}

void game::configurarTexto(sf::Text& texto, const std::string& contenido, int tamano, const sf::Color& color, const sf::Vector2f& posicion) {
    texto.setFont(font);
    texto.setString(contenido);
    texto.setCharacterSize(tamano);
    texto.setFillColor(color);
    texto.setPosition(posicion);
}

sf::Vector2f game::calcularCentroTexto(const std::string& texto, int tamano) {
    sf::Text tempText;
    tempText.setFont(font);
    tempText.setString(texto);
    tempText.setCharacterSize(tamano);
    sf::FloatRect bounds = tempText.getLocalBounds();

    return sf::Vector2f((800 - bounds.width) / 2, (600 - bounds.height) / 2);
}

void game::dibujar() {
    renderWindow.clear();

    renderizarFondo();

    if (juegoActivo) {
        player.dibujar(renderWindow);

        sf::Text scoreText;
        configurarTexto(scoreText, "Score: " + std::to_string(score), 16, sf::Color::Red, {10, 580});
        renderWindow.draw(scoreText);

        sf::Text nivelText;
        configurarTexto(nivelText, "Nivel: " + std::to_string(nivelActual), 16, sf::Color::Red, {10, 560});
        renderWindow.draw(nivelText);

        dibujarBarraVida();

        sf::Text balasText;
        configurarTexto(balasText, "Balas: x" + std::to_string(balasRestantes), 16, sf::Color::Red, {700, 530});
        renderWindow.draw(balasText);
    }

    for (auto& enemigo : enemigos) {
        enemigo.dibujar(renderWindow);

        if (enemigo.disparoEnemigoActivo) {
            sf::RectangleShape balaEnemiga(sf::Vector2f(4, 10));
            balaEnemiga.setPosition(enemigo.balaEnemigaX, enemigo.balaEnemigaY);
            balaEnemiga.setFillColor(sf::Color(255, 0, 0));
            renderWindow.draw(balaEnemiga);
        }
    }

    if (disparo) {
        sf::RectangleShape bala(sf::Vector2f(4, 10));
        bala.setPosition(balaX, balaY);
        bala.setFillColor(sf::Color(255, 242, 0));
        renderWindow.draw(bala);
    }

    for (auto& recargador : recargadores) {
        if (recargador.isVisible()) {
            recargador.dibujar(renderWindow);
        }
    }

    if (!juegoActivo) {
        recargadores.clear();

        sf::Text mensaje;
        configurarTexto(mensaje, "FIN DEL JUEGO", 20, sf::Color::Red, calcularCentroTexto("FIN DEL JUEGO", 20));

        renderWindow.clear();
        renderWindow.draw(mensaje);
        renderWindow.display();

        sf::sleep(sf::seconds(1));

        juegoActivo = false;
    }

    renderWindow.display();
}

