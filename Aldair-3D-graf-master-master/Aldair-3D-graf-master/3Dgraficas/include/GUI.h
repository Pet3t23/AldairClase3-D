#pragma once
#include "Prerequisites.h"
#include <vector>
#include "Actor.h"

class Window;

class GUI {
public:
    /**
     * @brief Constructor por defecto de la clase GUI.
     */
    GUI() = default;

    /**
     * @brief Destructor de la clase GUI.
     */
    ~GUI() = default;

    /**
     * @brief Inicializa la interfaz gráfica de usuario (GUI).
     */
    void init();

    /**
     * @brief Actualiza los elementos de la GUI en cada frame.
     */
    void update();

    /**
     * @brief Renderiza los elementos de la GUI en la ventana.
     */
    void render();

    /**
     * @brief Destruye los recursos utilizados por la GUI.
     */
    void destroy();

    /**
     * @brief Muestra los mensajes de error de la consola en la GUI.
     * @param programMessages Mensajes de error a mostrar en la consola.
     */
    void console(const std::map<ConsolErrorType, std::vector<std::string>>& programMessages);

    /**
     * @brief Configura el estilo de la GUI.
     */
    void setupGUIStyle();

    /**
     * @brief Muestra la jerarquía de actores en la GUI.
     * @param actors Lista de actores que se van a mostrar.
     * @param selectedActorID ID del actor seleccionado en la jerarquía.
     */
    void hierarchy(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors, int& selectedActorID);

    /**
     * @brief Muestra el menú de creación de actores en la GUI.
     * @param actors Lista de actores donde se añadirán los nuevos actores creados.
     */
    void actorCreationMenu(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

    /**
     * @brief Muestra el inspector para un actor seleccionado.
     * @param selectedActor El actor seleccionado cuya información se mostrará.
     */
    void inspector(EngineUtilities::TSharedPointer<Actor> selectedActor);

private:
    // Mapa de mensajes del programa con su respectivo ID.
    std::map<int, std::string> m_programMessages;
};
