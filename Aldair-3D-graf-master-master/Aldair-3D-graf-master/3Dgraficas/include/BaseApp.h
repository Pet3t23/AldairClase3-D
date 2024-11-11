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
     * @brief Funci�n principal encargada de ejecutar la aplicaci�n en el main.
     * @return C�digo de salida de la aplicaci�n.
     */
    int run();

    /**
     * @brief Funci�n de inicializaci�n de la aplicaci�n.
     * @return Verdadero si la inicializaci�n fue exitosa, falso si fall�.
     */
    bool initialize();

    /**
     * @brief Funci�n que se actualiza en cada frame.
     */
    void update();

    /**
     * @brief Funci�n de renderizado de la aplicaci�n.
     */
    void render();

    /**
     * @brief Funci�n para limpiar los recursos al final de la ejecuci�n.
     */
    void cleanup();

    /**
     * @brief Actualiza el movimiento de los actores seg�n el tiempo transcurrido.
     * @param deltaTime Tiempo transcurrido desde el �ltimo frame.
     * @param circle Actor que representa el c�rculo que se mover�.
     */
    void updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

    /**
     * @brief Funci�n que mueve el c�rculo en funci�n de los waypoints.
     * @param deltaTime Tiempo transcurrido desde el �ltimo frame.
     * @param Circle Actor que representa el c�rculo a mover.
     */
    void MovimientoCirculo(float deltaTime, EngineUtilities::TSharedPointer<Actor> Circle);

    // Variable que mantiene la posici�n actual de los waypoints.
    int ActualPosition = 0;

private:
    // Puntero a la ventana de la aplicaci�n.
    Window* m_window;

    // Actores principales.
    EngineUtilities::TSharedPointer<Actor> Triangle;
    EngineUtilities::TSharedPointer<Actor> Circle;
    EngineUtilities::TSharedPointer<Actor> Track;
    std::vector<EngineUtilities::TSharedPointer<Actor>> m_actors;

    // Variables relacionadas con el movimiento de los actores a trav�s de waypoints.
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
