cmake_minimum_required(VERSION 3.7)

# Nom de ton nouveau projet
project(Infinitode2D LANGUAGES CXX)

# Recherche de la bibliothèque SDL2 sur ton système
find_package(SDL2 REQUIRED)

# Définition de l'exécutable (Remplace main.cpp par le nom réel de ton fichier si besoin)
add_executable(${PROJECT_NAME} src/main.cpp)

# Inclusion des dossiers de headers de SDL2 (pour enlever les squiggles et compiler)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})

# Définition pour éviter les conflits avec le main de SDL sur certaines plateformes
target_compile_definitions(${PROJECT_NAME} PRIVATE "SDL_MAIN_HANDLED")

# Liaison (Link) de ton exécutable avec les fichiers binaires de SDL2
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})