#include "GUI.h"
#include "Window.h"
#include "Actor.h"
#include "transform.h"
#include "Services/NotificationSystem.h"

// Método para inicializar la GUI
void GUI::init() {
    // Configuración del estilo de la GUI
    setupGUIStyle();
}

// Método de actualización, actualmente vacío
void GUI::update() {
}

// Método de renderizado, actualmente vacío
void GUI::render() {
}

// Método para destruir y liberar recursos de la GUI
void GUI::destroy() {
}

// Configuración de los estilos de la GUI (colores, bordes, etc.)
void GUI::setupGUIStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colores = style.Colors;

    // Colores de la GUI basados en el estilo de Unreal Engine 5
    colores[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);  // Fondo de la ventana
    colores[ImGuiCol_Border] = ImVec4(0.40f, 0.40f, 0.40f, 0.50f);  // Bordes
    colores[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);  // Fondo de cuadros
    colores[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);  // Hover sobre cuadros
    colores[ImGuiCol_FrameBgActive] = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);  // Cuadro activo
    colores[ImGuiCol_TitleBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);  // Fondo del título
    colores[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);  // Título activo
    colores[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);  // Fondo de la barra de menú
    colores[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);  // Botón inactivo
    colores[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);  // Hover en el botón
    colores[ImGuiCol_ButtonActive] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);  // Botón activo
    colores[ImGuiCol_Text] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);  // Texto principal
    colores[ImGuiCol_TextDisabled] = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);  // Texto deshabilitado
    colores[ImGuiCol_Header] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);  // Encabezado
    colores[ImGuiCol_HeaderHovered] = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);  // Hover en el encabezado
    colores[ImGuiCol_HeaderActive] = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);  // Encabezado activo
    colores[ImGuiCol_ScrollbarBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);  // Fondo del scrollbar
    colores[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);  // Scrollbar inactivo
    colores[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);  // Hover en scrollbar
    colores[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);  // Scrollbar activo
    colores[ImGuiCol_CheckMark] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);  // Marca de check

    // Configuración del estilo general (bordes redondeados, tamaño de bordes, etc.)
    style.WindowRounding = 5.0f;  // Bordes redondeados en las ventanas
    style.FrameRounding = 5.0f;  // Bordes redondeados en los cuadros
    style.ScrollbarRounding = 5.0f;  // Bordes redondeados en el scrollbar
    style.GrabRounding = 5.0f;  // Bordes redondeados en los botones de "agarrar"
    style.FrameBorderSize = 1.0f;  // Grosor de borde de los cuadros
    style.WindowBorderSize = 1.0f;  // Grosor de borde de las ventanas
    style.PopupBorderSize = 1.0f;  // Grosor de borde de los popups
}

// Muestra la consola con mensajes y filtros
void GUI::console(const std::map<ConsolErrorType, std::vector<std::string>>& programMessages) {
    ImGui::Begin("Console");
    static ImGuiTextFilter filter;  // Filtro de búsqueda
    filter.Draw("Filter (\"error\", \"warning\", etc.)", 180.0f);
    ImGui::Separator();
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    // Recorrer y mostrar los mensajes según su tipo
    for (const auto& pair : programMessages) {
        ImVec4 color;
        switch (pair.first) {
        case ConsolErrorType::ERROR:
            color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f);  // Rojo para errores
            break;
        case ConsolErrorType::WARNING:
            color = ImVec4(1.0f, 1.0f, 0.4f, 1.0f);  // Amarillo para advertencias
            break;
        case ConsolErrorType::NORMAL:
        default:
            color = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);  // Gris para mensajes normales
            break;
        }

        // Mostrar los mensajes filtrados
        for (const auto& message : pair.second) {
            if (!filter.PassFilter(message.c_str())) continue;
            ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::Text("[%d] %s", pair.first, message.c_str());
            ImGui::PopStyleColor();
        }
    }
    // Asegurarse de que el scrollbar esté al final
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);
    ImGui::EndChild();
    ImGui::End();
}

// Muestra la jerarquía de los actores en la escena
void GUI::hierarchy(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors, int& selectedActorID) {
    ImGui::Begin("Hierarchy");

    for (int i = 0; i < actors.size(); ++i) {
        if (!actors[i].isNull()) {
            // Seleccionar un actor
            if (ImGui::Selectable(actors[i]->getName().c_str(), selectedActorID == i)) {
                selectedActorID = i;
            }
        }
    }

    ImGui::End();
}

// Muestra la ventana del inspector para modificar propiedades del actor seleccionado
void GUI::inspector(EngineUtilities::TSharedPointer<Actor> selectedActor) {
    if (selectedActor.isNull()) return;

    ImGui::Begin("Inspector");

    ImGui::Text("Actor: %s", selectedActor->getName().c_str());

    auto transform = selectedActor->getComponent<Transform>();
    if (!transform.isNull()) {
        sf::Vector2f position = transform->getPosition();
        sf::Vector2f scale = transform->getScale();

        // Mostrar y editar la posición
        if (ImGui::InputFloat2("Position", reinterpret_cast<float*>(&position))) {
            transform->setPosition(position);
        }

        // Mostrar y editar la escala
        if (ImGui::InputFloat2("Scale", reinterpret_cast<float*>(&scale))) {
            transform->setScale(scale);
        }
    }

    ImGui::End();
}
