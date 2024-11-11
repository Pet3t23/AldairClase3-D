#include "ShapeFactory.h"  // Incluir la definición de la fábrica de formas

// Función para crear una forma basada en el tipo especificado
sf::Shape* ShapeFactory::createShape(ShapeType shapeType) {
    // Asignar el tipo de forma
    m_shapeType = shapeType;

    // Seleccionar el tipo de forma a crear
    switch (shapeType) {
    case EMPTY: {
        return nullptr;  // Si el tipo es "vacío", no se crea ninguna forma
    }
    case CIRCLE: {
        // Crear un círculo con un radio de 10 unidades
        sf::CircleShape* circle = new sf::CircleShape(10.0f);
        circle->setFillColor(sf::Color::White);  // Establecer el color de relleno a blanco
        m_shape = circle;  // Guardar la forma creada
        return circle;  // Retornar el puntero al círculo
    }
    case RECTANGLE: {
        // Crear un rectángulo con dimensiones de 100x50 unidades
        sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2(100.0f, 50.0f));
        rectangle->setFillColor(sf::Color::White);  // Establecer el color de relleno a blanco
        m_shape = rectangle;  // Guardar la forma creada
        return rectangle;  // Retornar el puntero al rectángulo
    }
    case TRIANGLE: {
        // Crear un triángulo utilizando un círculo con 3 vértices (triángulo equilátero)
        sf::CircleShape* triangle = new sf::CircleShape(50.0f, 3);
        triangle->setFillColor(sf::Color::White);  // Establecer el color de relleno a blanco
        m_shape = triangle;  // Guardar la forma creada
        return triangle;  // Retornar el puntero al triángulo
    }
    default:
        return nullptr;  // Si no se reconoce el tipo de forma, retornar nullptr
    }
}

// Establecer la posición de la forma mediante coordenadas X e Y
void ShapeFactory::setPosition(float x, float y) {
    if (m_shape) {  // Verificar si existe una forma creada
        m_shape->setPosition(x, y);  // Establecer la posición de la forma
    }
}

// Establecer la posición de la forma utilizando un objeto de tipo sf::Vector2f
void ShapeFactory::setPosition(const sf::Vector2f& position) {
    if (m_shape) {  // Verificar si existe una forma creada
        m_shape->setPosition(position);  // Establecer la posición de la forma
    }
}

// Establecer la rotación de la forma en grados
void ShapeFactory::setRotation(float angle) {
    if (m_shape) {  // Verificar si existe una forma creada
        m_shape->setRotation(angle);  // Establecer la rotación de la forma
    }
}

// Establecer la escala de la forma utilizando un objeto sf::Vector2f
void ShapeFactory::setScale(const sf::Vector2f& scl) {
    if (m_shape) {  // Verificar si existe una forma creada
        m_shape->setScale(scl);  // Establecer la escala de la forma
    }
}

// Establecer el color de relleno de la forma
void ShapeFactory::setFillColor(const sf::Color& color) {
    if (m_shape) {  // Verificar si existe una forma creada
        m_shape->setFillColor(color);  // Establecer el color de relleno
    }
}
