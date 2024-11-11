#pragma once
#include "Prerequisites.h"
#include "Entity.h"
#include "ShapeFactory.h"
#include "Transform.h"

class Actor : public Entity { // Se debe usar 'public' para heredar de Entity
public:
    /**
     * @brief Constructor por defecto.
     */
    Actor() = default;

    /**
     * @brief Constructor con nombre para el actor.
     * @param actorName Nombre del actor.
     */
    Actor(std::string actorName);

    /**
     * @brief Destructor virtual.
     */
    virtual ~Actor() = default;

    /**
     * @brief Actualiza el actor.
     * @param deltaTime El tiempo transcurrido desde la última actualización.
     */
    void update(float deltaTime) override;

    /**
     * @brief Renderiza el actor.
     * @param window Contexto del dispositivo para operaciones gráficas.
     */
    void render(Window& window) override;

    /**
     * @brief Destruye el actor y libera los recursos asociados.
     */
    void destroy();

    /**
     * @brief Función para obtener únicamente el nombre del actor.
     * @return El nombre del actor.
     */
    std::string getName() const;

    /**
     * @brief Obtiene un componente específico del actor.
     * @tparam T Tipo del componente que se va a obtener.
     * @return Puntero compartido al componente, o nullptr si no se encuentra.
     */
    template <typename T>
    EngineUtilities::TSharedPointer<T> getComponent();

private:
    std::string m_name = "Actor"; ///< Nombre del actor.
};

/**
 * @brief Función para buscar y devolver un componente específico de un actor,
 * utilizando el tipo de componente especificado como argumento de la plantilla.
 * Si el componente no se encuentra, la función devuelve un puntero nulo.
 */
template<typename T>
inline EngineUtilities::TSharedPointer<T> Actor::getComponent() {
    for (auto& component : components) {
        EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
        if (specificComponent) {
            return specificComponent;  // Si se encuentra el componente, se retorna
        }
    }
    // Devuelve un TSharedPointer vacío si no se encuentra el componente
    return EngineUtilities::TSharedPointer<T>();
}
