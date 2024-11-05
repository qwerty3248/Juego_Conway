/**
 * @file main.cpp
 * @brief Implementación del Juego de la Vida de Conway usando SFML.
 * 
 * Este archivo contiene la implementación principal del Juego de la Vida de Conway,
 * incluyendo la clase GameOfLife que gestiona la lógica del juego y la renderización
 * usando la biblioteca SFML.
 */

#include <SFML/Graphics.hpp> ///< Biblioteca para gráficos
#include <vector> ///< Biblioteca para usar vectores
#include <cstdlib> ///< Biblioteca para funciones generales como rand()

// Definir constantes para el ancho y alto de la ventana, y el tamaño de las celdas
const int WIDTH = 800; ///< Ancho de la ventana
const int HEIGHT = 600; ///< Alto de la ventana
const int CELL_SIZE = 10; ///< Tamaño de cada celda en la cuadrícula

/**
 * @class GameOfLife
 * @brief Clase que representa el Juego de la Vida de Conway.
 * 
 * La clase gestiona la cuadrícula del juego, actualiza su estado y la dibuja en la ventana.
 */
class GameOfLife {
public:
    /**
     * @brief Constructor que inicializa el juego con un tamaño específico.
     * @param width Ancho de la cuadrícula.
     * @param height Alto de la cuadrícula.
     */
    GameOfLife(int width, int height) : width(width), height(height) {
        // Redimensionar la cuadrícula y llenarla con celdas muertas (false)
        grid.resize(height / CELL_SIZE, std::vector<bool>(width / CELL_SIZE, false));
        // Inicialización aleatoria de celdas vivas (true) y muertas (false)
        for (int i = 0; i < height / CELL_SIZE; ++i) {
            for (int j = 0; j < width / CELL_SIZE; ++j) {
                grid[i][j] = rand() % 2; // Asignar aleatoriamente 0 o 1
            }
        }
    }

    /**
     * @brief Actualiza el estado de la cuadrícula según las reglas del juego.
     * 
     * Este método aplica las reglas del Juego de la Vida de Conway para determinar
     * qué celdas viven y mueren en la siguiente generación.
     */
    void update() {
        // Crear una nueva cuadrícula para almacenar el próximo estado
        std::vector<std::vector<bool>> newGrid = grid;

        // Iterar sobre cada celda de la cuadrícula
        for (int i = 0; i < height / CELL_SIZE; ++i) {
            for (int j = 0; j < width / CELL_SIZE; ++j) {
                // Contar vecinos vivos
                int aliveNeighbors = countAliveNeighbors(i, j);
                
                // Aplicar reglas de Conway
                if (grid[i][j]) {
                    // Una celda viva sigue viva si tiene 2 o 3 vecinos vivos
                    newGrid[i][j] = (aliveNeighbors == 2 || aliveNeighbors == 3);
                } else {
                    // Una celda muerta se convierte en viva si tiene exactamente 3 vecinos vivos
                    newGrid[i][j] = (aliveNeighbors == 3);
                }
            }
        }

        // Actualizar la cuadrícula actual con la nueva cuadrícula
        grid = newGrid;
    }

    /**
     * @brief Dibuja la cuadrícula en la ventana.
     * @param window La ventana de SFML donde se dibujará la cuadrícula.
     */
    void draw(sf::RenderWindow& window) {
        // Iterar sobre cada celda de la cuadrícula
        for (int i = 0; i < height / CELL_SIZE; ++i) {
            for (int j = 0; j < width / CELL_SIZE; ++j) {
                if (grid[i][j]) {
                    // Crear un rectángulo que representa una celda viva
                    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                    cell.setFillColor(sf::Color::Green); // Color de la celda viva
                    cell.setPosition(j * CELL_SIZE, i * CELL_SIZE); // Posición de la celda
                    window.draw(cell); // Dibujar la celda en la ventana
                }
            }
        }
    }

private:
    /**
     * @brief Cuenta los vecinos vivos alrededor de una celda.
     * @param x Posición y de la celda en la cuadrícula.
     * @param y Posición x de la celda en la cuadrícula.
     * @return El número de vecinos vivos.
     */
    int countAliveNeighbors(int x, int y) {
        int count = 0; // Inicializar contador de vecinos vivos
        // Iterar sobre las posiciones vecinas
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue; // Ignorar la celda misma
                int newX = x + dx;
                int newY = y + dy;
                // Comprobar límites de la cuadrícula
                if (newX >= 0 && newX < height / CELL_SIZE && newY >= 0 && newY < width / CELL_SIZE) {
                    count += grid[newX][newY]; // Incrementar contador si el vecino está vivo
                }
            }
        }
        return count; // Retornar el número de vecinos vivos
    }

    int width, height; ///< Ancho y alto de la cuadrícula
    std::vector<std::vector<bool>> grid; ///< Cuadrícula que almacena el estado de cada celda (viva o muerta)
};

/**
 * @brief Función principal del programa.
 * 
 * Inicializa la ventana, crea una instancia del juego y gestiona el bucle principal.
 * 
 * @return 0 si la ejecución es exitosa.
 */
int main() {
    // Crear una ventana con el tamaño definido
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Juego de la Vida de Conway");
    GameOfLife game(WIDTH, HEIGHT); // Crear una instancia del juego

    sf::Clock clock; // Reloj para controlar el tiempo de actualización
    while (window.isOpen()) {
        sf::Event event; // Evento para manejar entradas
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Cerrar la ventana al recibir el evento de cierre
        }

        // Actualizar el juego cada 100 ms
        if (clock.getElapsedTime().asMilliseconds() > 100) {
            game.update(); // Llamar a la función de actualización
            clock.restart(); // Reiniciar el reloj
        }

        window.clear(); // Limpiar la ventana antes de dibujar
        game.draw(window); // Dibujar la cuadrícula en la ventana
        window.display(); // Mostrar el contenido de la ventana
    }

    return 0; // Fin del programa
}

