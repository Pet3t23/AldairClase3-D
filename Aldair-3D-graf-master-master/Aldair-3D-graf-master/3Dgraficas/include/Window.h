#pragma once
#include <SFML/Graphics.hpp>

class Window {
public:
    /**
     * @brief Constructor por defecto de la clase Window.
     */
    Window() = default;

    /**
     * @brief Constructor de la clase Window con parámetros de tamaño y título.
     * @param width Ancho de la ventana.
     * @param height Alto de la ventana.
     * @param title Título de la ventana.
     */
    Window(int width, int height, const std::string& title);

    /**
     * @brief Destructor de la clase Window.
     */
    ~Window();

    /**
     * @brief Maneja los eventos de la ventana, como el cierre o el cambio de tamaño.
     */
    void handleEvents();

    /**
     * @brief Limpia el contenido de la ventana con el color predeterminado.
     */
    void clear();

    /**
     * @brief Muestra el contenido de la ventana en la pantalla.
     */
    void display();

    /**
     * @brief Verifica si la ventana sigue abierta.
     *
     * @return true si la ventana está abierta, false en caso contrario.
     */
    bool isOpen() const;

    /**
     * @brief Dibuja un objeto que puede ser dibujado en la ventana.
     *
     * @param drawable Referencia a un objeto SFML que puede ser dibujado.
     */
    void draw(const sf::Drawable& drawable);

    /**
     * @brief Obtiene el objeto interno SFML RenderWindow.
     *
     * @return Un puntero al objeto interno SFML RenderWindow.
     */
    sf::RenderWindow* getWindow();

    /**
     * @brief Realiza el renderizado a una textura, útil para crear efectos de renderizado complejos.
     */
    void renderToTexture();

    /**
     * @brief Aplica un estilo personalizado a la ventana (usado para ImGui o UI personalizada).
     */
    void setCustomStyle();

    /**
     * @brief Muestra el contenido de la ventana en un panel de ImGui.
     */
    void showInImGui();

    /**
     * @brief Inicializa la ventana y configura los elementos necesarios.
     */
    void init();

    /**
     * @brief Actualiza la ventana, incluyendo el cálculo del tiempo transcurrido.
     */
    void update();

    /**
     * @brief Renderiza la ventana después de cada actualización.
     */
    void render();

    /**
     * @brief Libera los recursos utilizados por la ventana.
     */
    void destroy();

private:
    sf::RenderWindow* m_window; ///< Puntero a la ventana principal SFML.
    sf::View m_view; ///< Vista actual de la ventana.
public:
    sf::RenderTexture m_renderTexture; ///< Textura de renderizado, usada para crear efectos gráficos.
    sf::Time deltaTime; ///< Tiempo transcurrido desde la última actualización.
    sf::Clock clock; ///< Reloj para calcular el deltaTime entre frames.
};
