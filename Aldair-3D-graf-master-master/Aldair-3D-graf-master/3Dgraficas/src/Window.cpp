#include "Window.h"        // Incluir la clase de ventana
#include "GUI.h"           // Incluir la interfaz gráfica de usuario
#include "Prerequisites.h" // Incluir dependencias necesarias
#include <SFML/Graphics.hpp> // Incluir las funcionalidades gráficas de SFML

// Constructor de la clase Window, recibe el ancho, alto y título de la ventana
Window::Window(int width, int height, const std::string& title) {
    // Crear la ventana con las dimensiones y el título especificados
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

    // Verificar si la ventana se creó correctamente
    if (!m_window) {
        ERROR("Window", "Window", "CHECK CONSTRUCTOR");
    }
    else {
        MESSAGE("Window", "Window", "OK");
    }

    // Inicializar los recursos de ImGui
    ImGui::SFML::Init(*m_window);

    // Crear un RenderTexture con las mismas dimensiones que la ventana
    if (!m_renderTexture.create(width, height)) {
        ERROR("Window", "RenderTexture", "CHECK CREATION");
    }
}

// Destructor de la clase Window
Window::~Window() {
    // Cerrar ImGui y liberar los recursos de la ventana
    ImGui::SFML::Shutdown();
    delete m_window;
}

// Función para manejar los eventos de la ventana
void Window::handleEvents() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        // Procesar los eventos de entrada de ImGui
        ImGui::SFML::ProcessEvent(event);

        switch (event.type) {
        case sf::Event::Closed:
            m_window->close();  // Cerrar la ventana
            break;

        case sf::Event::Resized:
            // Obtener las nuevas dimensiones de la ventana
            unsigned int width = event.size.width;
            unsigned int height = event.size.height;

            // Ajustar la vista de la ventana
            m_view = m_window->getView();
            m_view.setSize(static_cast<float>(width), static_cast<float>(height));
            m_window->setView(m_view);

            // Actualizar el RenderTexture si la ventana se redimensiona
            m_renderTexture.create(width, height);
            break;
        }
    }
}

// Función para limpiar el contenido de la ventana y el RenderTexture
void Window::clear() {
    if (m_window != nullptr) {
        m_window->clear();  // Limpiar la ventana
    }
    else {
        ERROR("Window", "clear", "CHECK FOR WINDOW POINTER DATA");
    }

    if (m_renderTexture.getSize().x > 0 && m_renderTexture.getSize().y > 0) {
        m_renderTexture.clear();  // Limpiar el RenderTexture
    }
}

// Función para mostrar el contenido de la ventana
void Window::display() {
    if (m_window != nullptr) {
        m_window->display();  // Mostrar el contenido de la ventana
    }
    else {
        ERROR("Window", "display", "CHECK FOR WINDOW POINTER DATA");
    }
}

// Función que retorna si la ventana está abierta
bool Window::isOpen() const {
    if (m_window != nullptr) {
        return m_window->isOpen();  // Verificar si la ventana está abierta
    }
    else {
        ERROR("Window", "isOpen", "CHECK FOR WINDOW POINTER DATA");
        return false;
    }
}

// Función para dibujar una forma en la ventana (usando RenderTexture)
void Window::draw(const sf::Drawable& drawable) {
    if (m_renderTexture.getSize().x > 0 && m_renderTexture.getSize().y > 0) {
        m_renderTexture.draw(drawable);  // Dibujar la forma en el RenderTexture
    }
}

// Función que retorna un puntero a la ventana
sf::RenderWindow* Window::getWindow() {
    if (m_window != nullptr) {
        return m_window;  // Retornar el puntero a la ventana
    }
    else {
        ERROR("Window", "getWindow", "CHECK FOR WINDOW POINTER DATA");
        return nullptr;
    }
}

// Función para mostrar el RenderTexture
void Window::renderToTexture() {
    m_renderTexture.display();  // Mostrar el contenido del RenderTexture
}

// Función para aplicar un estilo personalizado a ImGui
void Window::setCustomStyle() {
    ImGuiStyle& style = ImGui::GetStyle();

    // Configuración de bordes y tamaños
    style.WindowRounding = 8.0f;
    style.FrameRounding = 5.0f;
    style.ScrollbarRounding = 12.0f;
    style.GrabRounding = 5.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    style.WindowPadding = ImVec2(10, 10);

    // Personalización de la paleta de colores (estilo moderno)
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.15f, 1.0f);      // Fondo azul oscuro
    colors[ImGuiCol_TitleBg] = ImVec4(0.2f, 0.2f, 0.4f, 1.0f);        // Fondo suave para el título
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.3f, 0.3f, 0.5f, 1.0f);  // Fondo activo para el título
    colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.2f, 1.0f);      // Fondo del marco
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3f, 0.3f, 0.4f, 0.7f); // Fondo del marco cuando se pasa el mouse
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.4f, 0.4f, 0.5f, 0.7f);  // Fondo del marco cuando está activo
    colors[ImGuiCol_Button] = ImVec4(0.2f, 0.3f, 0.5f, 1.0f);         // Color del botón
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.4f, 0.6f, 1.0f);  // Color del botón cuando se pasa el mouse
    colors[ImGuiCol_ButtonActive] = ImVec4(0.4f, 0.5f, 0.7f, 1.0f);   // Color del botón cuando está activo
    colors[ImGuiCol_Text] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);           // Color del texto
    colors[ImGuiCol_Border] = ImVec4(0.4f, 0.4f, 0.5f, 0.7f);         // Color del borde
    colors[ImGuiCol_CheckMark] = ImVec4(0.8f, 0.8f, 0.9f, 1.0f);      // Color de la marca de verificación
    colors[ImGuiCol_SliderGrab] = ImVec4(0.5f, 0.5f, 0.7f, 1.0f);     // Color del agarre del deslizador
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.6f, 0.6f, 0.8f, 1.0f); // Color del agarre activo del deslizador
}

// Mostrar la ventana en la interfaz de usuario de ImGui
void Window::showInImGui() {
    setCustomStyle();  // Aplicar el estilo personalizado
    const sf::Texture& texture = m_renderTexture.getTexture();
    ImVec2 size(texture.getSize().x, texture.getSize().y);

    // Panel de la escena
    ImGui::Begin("Scene");
    ImGui::Image((void*)(intptr_t)texture.getNativeHandle(), size, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

// Actualizar la ventana usando el tiempo transcurrido (deltaTime)
void Window::update() {
    // Almacenar el tiempo transcurrido
    deltaTime = clock.restart();

    // Usar deltaTime para actualizar ImGui
    ImGui::SFML::Update(*m_window, deltaTime);
}

// Renderizar el contenido de ImGui en la ventana
void Window::render() {
    ImGui::SFML::Render(*m_window);
}

// Destructor que limpia y libera los recursos
void Window::destroy() {
    ImGui::SFML::Shutdown();
    SAFE_PTR_RELEASE(m_window);  // Liberar el puntero de la ventana
}
