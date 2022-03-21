/*
 * Test_OpenGL - Copyright © 2022 DAVID Axel
 * Mail to: axel.david@etu.univ-amu.fr.
 *
 * Test_OpenGL is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * Test_OpenGL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <memory>
#include <vector>
#include <string_view>
#include <string>
#include <filesystem>
#include <iostream>

#include <glengine/shaderProgram.hpp>
#include <glengine/shader.hpp>
#include <glengine/utility.hpp>
#include <glengine/window.hpp>

#include <stbimage/stb_image.h>

#include <glengine/glfw/exception_factory.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

// Préciser le dossier de la bibliothèque
#include "test_imgui/config.hpp"

static void loadGLAD() {
    // Vérification du chargement de GLAD
    // On lui demande de charger la fonction permettant d’obtenir les adresses mémoire
    if ( 0 == ::gladLoadGLLoader( reinterpret_cast<GLADloadproc>(::glfwGetProcAddress) ) ) {
        throw std::runtime_error( "Impossible de charger GLAD" );
    }
}

static void cubeMenu() {
    using namespace ImGui;

    static bool normal = true;
    static int normalSize = 1;
    static int normalEpaisseur = 1;
    static auto normalColorRGB = std::make_unique<float[]>(3);
    normalColorRGB[0] = normalColorRGB[1] = normalColorRGB[2] = 1.0f;
    static bool normalDirectionalColor = false;

    ImGui::Begin("Paramètre de la scène cube");

    // TODO Permettre de réduire l'enfant
    // Header rétractable
    // TODO Impossible de sélectionner la couleur
    ImGui::BeginChild("Paramètres des normales :");

    ImGui::Checkbox("Activer les normales", &normal);
    ImGui::SliderInt("Taille", &normalSize, 0, 10);
    SliderInt("Epaisseur", &normalEpaisseur, 0, 10);
    static float color[3] { 1.0f, 1.0f, 1.0f};
    ImGui::ColorEdit3("Color",color);
    ImGui::Checkbox("Couleur en fonction de la direction", &normalDirectionalColor);

    ImGui::EndChild();

    static float edgesSize = 1.0f;
    static auto cubePos = std::make_unique<float[]>(3);
    cubePos[0] = cubePos[1] = cubePos[2] = 0.0f;
    static auto cubeRot = std::make_unique<float[]>(3);
    cubeRot[0] = cubeRot[1] = cubeRot[2] = 0.0f;
    static auto cubeColor = std::make_unique<float[]>(3);
    cubeColor[0] = cubeColor[1] = cubeColor[2] = 0.0f;

    // Pas visible
    ImGui::BeginChild("Paramètres du cube :");

    ImGui::SliderFloat("Taille des arêtes", &edgesSize,0.0f, 10.0f);

    InputFloat3("Position", cubePos.get());
    InputFloat3("Rotation", cubeRot.get());
    ColorEdit3("Couleur", cubeColor.get());

    ImGui::EndChild();

    ImGui::End();
}

static void objMenu() {

}

static void moduleMenu() {
    // TODO Dimensionner les dimensions du module
    // TODO Fixer la position en haut à gauche
    // TODO Empêcher de fermer le menu
    // TODO Permettre de réduire
    // TODO Rajouter une aide pour expliquer le choix module
    // TODO Un espace de plus entre le sélecteur et le nom "Module"
    // TODO Rajouter une barre de menu si on veut permettre la fermeture du module
    ImGuiIO& io = ImGui::GetIO();

    ImGui::Begin("Modules");
    ImGui::Text("Choix du module :");

    static int moduleID = 0;
    ImGui::Combo("Module", &moduleID, "Cube\0Objet\0");
    switch (moduleID) {
        case 0: cubeMenu(); break;
        case 1: objMenu(); break;
        default :
            throw std::runtime_error("Erreur");
    }

    ImGui::End();
}



int main() {
    using namespace gl_engine;
    Window window(Dimension{.width=800, .height=600}, "Titre", Window_t::WINDOWED);
    window.becomeContext();

    // Définir la version glsl pour imgui
    constexpr const char* glslVersion = "#version 330 core";

    loadGLAD();

    using namespace ImGui;

    bool open = true;

    IMGUI_CHECKVERSION();
    auto contextGUI = ImGui::CreateContext();
    ImGui::SetCurrentContext(contextGUI);

    ImGuiIO& io = ImGui::GetIO();
    // Activation des controles clavier
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.get(), true);
    ImGui_ImplOpenGL3_Init(glslVersion);


    while(!glfwWindowShouldClose(window.get())) {
        glfwPollEvents();

        // Nouvelle fenêtre d'affichage imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow( &open );
        //moduleMenu();
        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window.get(), &display_w, &display_h);
        glViewport(0,0,display_w,display_h);
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window.get());
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(contextGUI);


    return 0;
}
