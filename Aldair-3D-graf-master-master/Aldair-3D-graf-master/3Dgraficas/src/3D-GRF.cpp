#include "BaseApp.h"  // Incluir la clase base de la aplicaci�n
#include <SFML/Graphics.hpp>  // Incluir la librer�a gr�fica de SFML
#include "Window.h"  // Incluir la clase para la ventana

// Puntero global a la ventana de renderizado
sf::RenderWindow* window;
// Puntero comentado a un objeto de forma circular (no utilizado en el c�digo actual)
// sf::CircleShape* shape;

int main() {
    // Crear una instancia de la aplicaci�n base
    BaseApp app;

    // Ejecutar la aplicaci�n y devolver el resultado de la ejecuci�n
    return app.run();
}
