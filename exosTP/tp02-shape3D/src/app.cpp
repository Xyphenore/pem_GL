#include <GLFW/glfw3.h>
#include "app.hpp"

#include "window.hpp"

#include <memory>

// Public interface
std::unique_ptr<bidon::App> bidon::App::createApp( std::unique_ptr<Window> window ) {
    // Utilisation de l'héritage pour transformer une méthode protected en publique.
    // Nécessaire pour l'utilisation de std::make_unique.
    // Car std::make_unique a besoin de constructeur public.
    class SubApp final : public bidon::App {
    public:
        explicit SubApp( std::unique_ptr<Window> window ) : bidon::App(std::move(window) ) {};
    };

    return std::make_unique<SubApp>(std::move(window) );
}

bidon::App::~App() noexcept {
    ::glfwTerminate();
    appExists = false;
}


bidon::Window* bidon::App::getWindow() const {
    return window_.get();
}



void bidon::App::addWindow( std::unique_ptr<Window> window ) {
    if ( window != nullptr ) {
        throw bidon::appWindow_already_exists("L'application a déjà une fenêtre de rendu."
                                              " S'il vous plait supprimer l'ancienne "
                                              "fenêtre de rendu avec la méthode App::deleteWindow(), puis réitérer.");
    }

    window_ = std::move(window);
}



// Protected interface
bidon::App::App()
: App( nullptr ) {}

bidon::App::App( std::unique_ptr<Window> window )
: window_( std::move(window) ) {
    if ( appExists ) {
        throw bidon::app_already_exists("L'application existe déjà, il n'est pas possible de créer deux applications en même temps.");
    }

    const auto success = ::glfwInit();

    if ( GLFW_FALSE == success ) {
        const char * description = nullptr;
        const auto code = ::glfwGetError(&description);

        bidon::GLFWErrorCallback(code, description);
    }

    ::glfwSetErrorCallback(bidon::GLFWErrorCallback);

    ::glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, ::GL_CONTEXT_VERSION_MAJOR );
    ::glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, ::GL_CONTEXT_VERSION_MINOR );
    ::glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    // Précise un anticrénelage de 4 couches d’échantillonnage
    //::glfwWindowHint( GLFW_SAMPLES, 4 );

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    appExists = true;
}
