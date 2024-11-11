#include "BaseApp.h"  // Incluir la clase base de la aplicación
#include <SFML/Graphics.hpp>  // Incluir la librería gráfica de SFML
#include "Window.h"  // Incluir la clase para la ventana

// Puntero global a la ventana de renderizado
sf::RenderWindow* window;
// Puntero comentado a un objeto de forma circular (no utilizado en el código actual)
// sf::CircleShape* shape;

int main() {
    // Crear una instancia de la aplicación base
    BaseApp app;

    // Ejecutar la aplicación y devolver el resultado de la ejecución
    return app.run();
}
