#include "BaseApp.h"
#include "Services/NotificationSystem.h"

BaseApp::~BaseApp() {
    // Guardar los mensajes de notificación en un archivo al destruir la aplicación
    NotificationService::getInstance().saveMessagesToFile("LogData.txt");
}

int BaseApp::run() {
    NotificationService& notifier = NotificationService::getInstance();

    // Inicializar la aplicación
    if (!initialize()) {
        // Agregar un mensaje de error si la inicialización falla
        notifier.addMessage(ConsolErrorType::ERROR, "Initializes result on a false statemente, check method validations");
        notifier.saveMessagesToFile("LogData.txt");
        ERROR("BaseApp", "run", "Initializes result on a false statemente, check method validations");
    }
    else {
        // Mensaje informativo si la inicialización es exitosa
        notifier.addMessage(ConsolErrorType::NORMAL, "All programs were initialized correctly");
    }
    m_GUI.init();

    // Bucle principal de la ventana
    while (m_window->isOpen()) {
        m_window->handleEvents();
        update();
        render();
    }

    cleanup();
    return 0;
}

bool BaseApp::initialize() {
    NotificationService& notifier = NotificationService::getInstance();
    m_window = new Window(1920, 1080, "Patas Engine");
    if (!m_window) {
        // Error en la creación de la ventana
        ERROR("BaseApp", "initialize", "Error on window creation, var is null");
        return false;
    }

    // Actor de tipo Track
    Track = EngineUtilities::MakeShared<Actor>("Track");
    if (!Track.isNull()) {
        Track->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);

        // Establecer posición, rotación y escala desde Transform
        Track->getComponent<Transform>()->setPosition(sf::Vector2f(0.0f, 0.0f));
        Track->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
        Track->getComponent<Transform>()->setScale(sf::Vector2f(11.0f, 12.0f));

        // Cargar la textura del circuito
        if (!texture.loadFromFile("Circuit.png")) {
            std::cout << "Error de carga de textura" << std::endl;
            return -1; // Manejo de error al cargar la textura
        }
        Track->getComponent<ShapeFactory>()->getShape()->setTexture(&texture);
    }

    // Actor de tipo Circle
    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (!Circle.isNull()) {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);

        // Establecer posición, rotación y escala desde Transform
        Circle->getComponent<Transform>()->setPosition(sf::Vector2f(200.0f, 200.0f));
        Circle->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
        Circle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));

        // Cargar la textura del personaje Mario
        if (!Mario.loadFromFile("Characters/tile000.png")) {
            std::cout << "Error de carga de textura" << std::endl;
            return -1; // Manejo de error al cargar la textura
        }
        Circle->getComponent<ShapeFactory>()->getShape()->setTexture(&Mario);
    }
    m_actors.push_back(Circle);

    // Actor de tipo Triangle
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull()) {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
        Triangle->getComponent<Transform>()->setPosition(sf::Vector2f(200.0f, 200.0f));
        Triangle->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
        Triangle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));
    }
    m_actors.push_back(Triangle);

    return true;
}

void BaseApp::update() {
    // Actualizar la ventana
    m_window->update();

    // Obtener la posición del mouse
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    // Actualizar los actores
    if (!Track.isNull()) {
        Track->update(m_window->deltaTime.asSeconds());
    }
    if (!Triangle.isNull()) {
        Triangle->update(m_window->deltaTime.asSeconds());
    }
    if (!Circle.isNull()) {
        Circle->update(m_window->deltaTime.asSeconds());
        updateMovement(m_window->deltaTime.asSeconds(), Circle);
    }
    // Actualizar todos los actores en la lista
    for (auto& actor : m_actors) {
        if (!actor.isNull()) {
            actor->update(m_window->deltaTime.asSeconds());
            if (actor->getName() == "Circle") {
                MovimientoCirculo(m_window->deltaTime.asSeconds(), actor);
            }
        }
    }
}

void BaseApp::MovimientoCirculo(float deltaTime, EngineUtilities::TSharedPointer<Actor> Circle) {
    if (Circle.isNull()) return;

    auto transform = Circle->getComponent<Transform>();
    if (transform.isNull()) return;

    // Obtener la siguiente posición de destino
    sf::Vector2f targetPos = waypoints[ActualPosition];
    transform->Seek(targetPos, 200.0f, deltaTime, 10.0f);

    // Calcular la distancia al objetivo
    sf::Vector2f currentPos = transform->getPosition();
    float distanceToTarget = std::sqrt(std::pow(targetPos.x - currentPos.x, 2) + std::pow(targetPos.y - currentPos.y, 2));

    // Verificar si el actor ha llegado al destino
    if (distanceToTarget < 10.0f) {
        ActualPosition = (ActualPosition + 1) % waypoints.size();
    }
}

void BaseApp::render() {
    NotificationService& notifier = NotificationService::getInstance();
    m_window->clear();

    // Renderizar los actores en la ventana
    if (!Track.isNull()) {
        Track->render(*m_window);
    }
    if (!Circle.isNull()) {
        Circle->render(*m_window);
    }
    if (!Triangle.isNull()) {
        Triangle->render(*m_window);
    }

    // Renderizar todos los actores
    for (auto& actor : m_actors) {
        if (!actor.isNull()) {
            actor->render(*m_window);
        }
    }

    // Renderizar en ImGui
    m_window->renderToTexture();
    m_window->showInImGui();

    // Mostrar la consola de notificaciones
    m_GUI.console(notifier.getNotifications());

    // Mostrar la jerarquía de actores
    m_GUI.hierarchy(m_actors, selectedActorID);

    // Mostrar el inspector del actor seleccionado
    if (selectedActorID >= 0 && selectedActorID < m_actors.size()) {
        m_GUI.inspector(m_actors[selectedActorID]);
    }

    // Mostrar el menú de creación de actores
    m_GUI.actorCreationMenu(m_actors);

    m_window->render();
    m_window->display();
}

void BaseApp::cleanup() {
    // Limpiar y destruir la ventana
    m_window->destroy();
    delete m_window;
}

void BaseApp::updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle) {
    // Verificar si el actor es nulo
    if (!circle || circle.isNull()) {
        return;
    }

    // Obtener el componente Transform
    auto transform = circle->getComponent<Transform>();
    if (transform.isNull()) {
        return;
    }

    // Obtener la posición de destino
    sf::Vector2f targetPos = waypoints[currentWaypoint];

    // Llamar al método Seek del Transform
    transform->Seek(targetPos, 200.0f, deltaTime, 10.0f);

    // Obtener la posición actual del actor
    sf::Vector2f currentPos = transform->getPosition();

    // Verificar si el actor ha llegado al destino
    float distanceToTarget = std::sqrt(std::pow(targetPos.x - currentPos.x, 2) + std::pow(targetPos.y - currentPos.y, 2));

    if (distanceToTarget < 10.0f) { // Umbral de distancia para considerar que ha llegado
        currentWaypoint = (currentWaypoint + 1) % waypoints.size(); // Ciclo a través de los puntos
    }
}
