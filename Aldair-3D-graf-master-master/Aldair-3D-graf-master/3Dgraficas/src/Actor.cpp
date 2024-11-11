#include "Actor.h"

Actor::Actor(std::string actorName) {
    // Configuraci�n del nombre del actor
    m_name = actorName;

    // Configuraci�n de la forma (Shape)
    EngineUtilities::TSharedPointer<ShapeFactory> shape = EngineUtilities::MakeShared<ShapeFactory>();
    addComponent(shape);

    // Configuraci�n de la transformaci�n (Transform)
    EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
    addComponent(transform);
}

void Actor::update(float deltaTime) {
    // Obtener los componentes de transformaci�n y forma
    auto transform = getComponent<Transform>();
    auto shape = getComponent<ShapeFactory>();

    // Verificar si ambos componentes existen y actualizar la forma
    if (transform && shape) {
        shape->setPosition(transform->getPosition());  // Actualiza la posici�n de la forma
        shape->setRotation(transform->getRotation().x); // Actualiza la rotaci�n de la forma
        shape->setScale(transform->getScale()); // Actualiza la escala de la forma
    }
}

void Actor::render(Window& window) {
    // Dibujar todos los componentes de tipo ShapeFactory
    for (unsigned int i = 0; i < components.size(); i++) {
        if (components[i].dynamic_pointer_cast<ShapeFactory>()) {
            // Dibuja la forma asociada al componente
            window.draw(*components[i].dynamic_pointer_cast<ShapeFactory>()->getShape());
        }
    }
}

void Actor::destroy() {
    // No se realiza ninguna acci�n en este caso, se puede agregar l�gica si es necesario
}

std::string Actor::getName() const {
    // Retorna el nombre del actor
    return m_name;
}
