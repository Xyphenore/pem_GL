/*
 * PEM_GL - Copyright © 2022 DAVID Axel
 * Mail to:
 * axel.david@etu.univ-amu.fr
 *
 * PEM_GL is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * PEM_GL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */


#ifndef GLENGINE_OBJECTFACTORY_HPP
#define GLENGINE_OBJECTFACTORY_HPP

#ifndef __cplusplus
#error Un compilateur C++ est nécessaire.
#endif

#if __cplusplus < 201703L
#error GL_Engine a été développée pour C++17. Veuillez supprimer cette condition est testé le code à vos risques et périls.
#endif

#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <execution>
#include <glengine/complex_object.hpp>
#include <glengine/utility.hpp>

namespace gl_engine {
    /**
     * @brief Factory permettant de charger un objet.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::Object
     */
    class ObjectFactory final {
    public:
        // Note développeur : C'est la même usine dans tout le code, il est donc impossible de l’instancier.

        ObjectFactory() noexcept = delete;
        ObjectFactory( const ObjectFactory& ) noexcept = delete;
        ObjectFactory( ObjectFactory&& ) noexcept = delete;
        ObjectFactory& operator=( const ObjectFactory& ) noexcept = delete;
        ObjectFactory& operator=( ObjectFactory&& ) noexcept = delete;
        ~ObjectFactory() noexcept = delete;

        /**
         * @brief Construit un objet gl_engine::Object à partir d’un contenu gl_engine::utility::Content.
         * @param content Objet gl_engine::utility::Content représentant le contenu d’un fichier '.obj'.
         * @return Un pointeur propriétaire gl_engine::Object.
         *
         * @pre Le contenu dans content doit être valide.
         *
         * @post L’objet gl_engine::Object représente l’objet décrit dans le contenu passé.
         *
         * @exceptsafe TODO
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::Object
         * @see gl_engine::Content
         *
         * @note Peut seulement lire un objet.
         * @note Ne prend pas en charge le lissage des normales.
         */
        static std::unique_ptr<Object> load(Content content) {
            // Note développeur : Tous les attributs disponibles dans le format obj
            // http://www.hodge.net.au/sam/blog/wp-content/uploads/obj_format.txt

            // Vérifier le type du contenu, que c'est bien un obj

            // Lire et extraire le contenu et le stocker dans des vecteurs
            std::string word{};

            std::stringstream stream(content.content());
            try {
                stream.exceptions( std::ios_base::failbit | std::ios_base::badbit );
            }
            catch (const std::ios_base::failure&) {
                throw std::runtime_error("Erreur lors de la création du buffer de string");
            }

            struct Point {
                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                float w = 1.0f;
            };

            struct TexturePosition {
                float s = 0.0f;
                float t = 0.0f;
                float u = 0.0f;
            };

            struct Face {
                unsigned int vertex1;
                unsigned int vertex2;
                unsigned int vertex3;
            };

            std::vector<Point> vertices;
            std::vector<Point> normales;
            std::vector<TexturePosition> texturePositions;

            std::vector<Face> indices;

            std::string textureName;

            bool readVertices = false;
            bool readNormales = false;
            bool readTexturePositions = false;

            try {
                while ( !stream.eof() ) {
                    stream >> word;

                    if ( word.at( 0 ) == '#' && word.at( word.size() - 1 ) != '\n' ) {
                        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }

                    if ( word == "mtllib" ) {
                        stream >> textureName;
                        break;
                    }

                    if ( word == "v" || word == "vn" ) {
                        auto x = 0.0f;
                        auto y = 0.0f;
                        auto z = 0.0f;
                        auto w = 0.0f;
                        
                        // Extract line

                        stream >> x >> y >> z;

                        if ( word == "v" ) {
                            vertices.push_back( { x, y, z } );
                            readVertices = true;
                        }
                        else {
                            normales.push_back( { x, y, z } );
                            readNormales = true;
                        }
                    }

                    if ( word == "vt" ) {
                        auto x = 0.0f;
                        auto y = 0.0f;

                        stream >> x >> y;
                        texturePositions.push_back({x,y});

                        readTexturePositions = true;
                    }

                    if ( word == "s" ) {
                        // Détection du lissage des normales
                        // https://community.khronos.org/t/how-do-i-use-smoothing-groups-from-obj-files/73070/13

                        std::string idGroupNormal{};

                        stream >> idGroupNormal;

                        // Note développeur : le format est en ascii pur, donc les lettres UTF-8 ne sont pas disponible pour les attributs
                        // L'utilisation de std::tolower est suffisante
                        // Sinon il faudrait utiliser la lib ICU
                        // https://icu.unicode.org/
                        // qui contient une fonction de conversion to lower pour l'UTF-8
                        auto to_lower = [](auto& letter){
                            letter = std::tolower(letter);
                        };

                        std::for_each( std::execution::par_unseq, idGroupNormal.begin(), idGroupNormal.end(), to_lower );
                        if( idGroupNormal != "off" || idGroupNormal != "0" ) {
                            throw std::invalid_argument("Le lissage des normales n'est pas pris en charge.");
                        }
                    }

                    if ( word == "f" ) {
                        // Récupération des faces en fonction du modèle
                        // récupération des indices séparés par /
                        // En fonction si v a été lu
                        stream.sepa
                    }
                }
            }
            catch (...) {
                // TODO Erreur de lecture
            }

            // Vérifier que tous les vecteurs fassent la même taille finale.



            return std::make_unique<ComplexObject>();
        }
    };
}

#endif // GLENGINE_OBJECTFACTORY_HPP
