#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

class ShapeFactory : public Component {
public:
    /**
     * @brief Constructor por defecto de la clase ShapeFactory.
     */
    ShapeFactory() = default;

    /**
     * @brief Destructor de la clase ShapeFactory.
     */
    virtual ~ShapeFactory() = default;

    /**
     * @brief Constructor de la clase ShapeFactory con un tipo de forma.
     * @param shapeType Tipo de la forma que se va a crear.
     */
    ShapeFactory(ShapeType shapeType) :
        m_shape(nullptr), m_shapeType(ShapeType::EMPTY), Component(ComponentType::SHAPE) {}

    /**
     * @brief Crea una forma según el tipo especificado.
     * @param shapeType Tipo de forma que se desea crear (Círculo, Rectángulo, Triángulo, etc.).
     * @return Puntero a la forma creada, o nullptr si no se crea ninguna forma.
     */
    sf::Shape* createShape(ShapeType shapeType);

    /**
     * @brief Actualiza el componente de malla.
     * @param deltaTime El tiempo transcurrido desde la última actualización.
     */
    void update(float deltaTime) override {}

    /**
     * @brief Renderiza el componente de malla.
     * @param window Contexto del dispositivo para operaciones gráficas.
     */
    void render(Window window) override {}

    /**
     * @brief Establece la posición de la forma.
     * @param x Coordenada X de la posición.
     * @param y Coordenada Y de la posición.
     */
    void setPosition(float x, float y);

    /**
     * @brief Establece la posición de la forma.
     * @param position Coordenada (x, y) de la posición.
     */
    void setPosition(const sf::Vector2f& position);

    /**
     * @brief Establece el color de relleno de la forma.
     * @param color El color a establecer.
     */
    void setFillColor(const sf::Color& color);

    /**
     * @brief Establece la rotación de la forma.
     * @param angle Ángulo en grados para la rotación.
     */
    void setRotation(float angle);

    /**
     * @brief Establece la escala de la forma.
     * @param scl Factor de escala para la forma.
     */
    void setScale(const sf::Vector2f& scl);

    /**
     * @brief Obtiene la forma creada.
     * @return Puntero a la forma, o nullptr si no se ha creado ninguna.
     */
    sf::Shape* getShape() {
        return m_shape;
    }

private:
    sf::Shape* m_shape; ///< Puntero a la forma creada.
    ShapeType m_shapeType; ///< Tipo de la forma (Círculo, Rectángulo, Triángulo, etc.).
};
