#pragma once
#include <SFML/Graphics.hpp>
#include "Prerequisites.h"
#include <Window.h>
#include "ShapeFactory.h"
#include "Actor.h"
#include "GUI.h"
#include "Services/NotificationSystem.h"

class BaseApp {
public:
    /**
     * @brief Constructor por defecto de la clase BaseApp.
     */
    BaseApp() = default;

    /**
     * @brief Destructor de la clase BaseApp.
     */
    ~BaseApp();

    /**
     * @brief Función principal encargada de ejecutar la aplicación en el main.
     * @return Código de salida de la aplicación.
     */
    int run();

    /**
     * @brief Función de inicialización de la aplicación.
     * @return Verdadero si la inicialización fue exitosa, falso si falló.
     */
    bool initialize();

    /**
     * @brief Función que se actualiza en cada frame.
     */
    void update();

    /**
     * @brief Función de renderizado de la aplicación.
     */
    void render();

    /**
     * @brief Función para limpiar los recursos al final de la ejecución.
     */
    void cleanup();

    /**
     * @brief Actualiza el movimiento de los actores según el tiempo transcurrido.
     * @param deltaTime Tiempo transcurrido desde el último frame.
     * @param circle Actor que representa el círculo que se moverá.
     */
    void updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

    /**
     * @brief Función que mueve el círculo en función de los waypoints.
     * @param deltaTime Tiempo transcurrido desde el último frame.
     * @param Circle Actor que representa el círculo a mover.
     */
    void MovimientoCirculo(float deltaTime, EngineUtilities::TSharedPointer<Actor> Circle);

    // Variable que mantiene la posición actual de los waypoints.
    int ActualPosition = 0;

private:
    // Puntero a la ventana de la aplicación.
    Window* m_window;

    // Actores principales.
    EngineUtilities::TSharedPointer<Actor> Triangle;
    EngineUtilities::TSharedPointer<Actor> Circle;
    EngineUtilities::TSharedPointer<Actor> Track;
    std::vector<EngineUtilities::TSharedPointer<Actor>> m_actors;

    // Variables relacionadas con el movimiento de los actores a través de waypoints.
    int currentWaypoint = 0;
    std::vector<sf::Vector2f> waypoints = {
        {720.0f, 350.0f},
        {720.0f, 260.0f},
        {125.0f, 50.0f},
        {70.0f, 120.0f},
        {70.0f, 450.0f},
        {400.0f, 350.0f},
        {550.0f, 500.0f},
        {650.0f, 550.0f},
        {720.0f, 450.0f}
    };

    // Texturas para los actores.
    sf::Texture Mario;
    sf::Texture texture;

    // Interfaz de usuario (GUI).
    GUI m_GUI;
};
