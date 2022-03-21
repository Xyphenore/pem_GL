# PEX_GL - PROJET NON FINIS

Outil de présentation des exemples vu en cours d'Open GL.

Il est nécessaire d'utiliser les compilateurs gcc 10 ou clang 9 ou VS 2019 16,8 car ils ont corrigé une erreur dans la norme lors de la déclaration de méthode implicite noexcept :
https://stackoverflow.com/questions/65521419/why-is-default-noexcept-move-constructor-being-accepted
Discussion stackoverflow qui cite la norme et sa correction.

Correction de la norme : p1286r2
http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1286r2.html

- MSVC Conformité à la norme :
https://docs.microsoft.com/fr-fr/cpp/overview/visual-cpp-language-conformance?view=msvc-170
- GCC 10 Patch Note : https://gcc.gnu.org/gcc-10/changes.html
( Ajout : "The noexcept-specifier is now properly treated as a complete-class context as per [class.mem]." )

Il est nécessaire d'avoir CMake 3.19 pour générer le projet.
Dans le futur, la version de CMake sera inférieure, car la 3.19 est nécessaire pour générer la doc de glengine, ainsi il sera possible de créer le projet et la bibliothèque sans la documentation.
  
Pour exécuter le projet, il est nécessaire de créer un dossier build et déplacez vous dedans, puis d'entrer la ligne :<br>
cmake "chemin vers le CMakeList.txt du dossier pem_gl"

Ainsi si le dossier build se trouve au même niveau que le dossier pem_gl cela donnera :
cmake ../pem_gl/CMakeList.txt
Il suffira de faire make après si aucune erreur n'est survenue.

Ou bien il faut que vous chargez le projet dans un IDE prenant en charge CMake, puis générer le projet soit comme un projet MSVS ou MakeFile ou ninja.
