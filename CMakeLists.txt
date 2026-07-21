cmake_minimum_required(VERSION 3.7)

# 1. Déclaration du projet
project(Infinitode2D LANGUAGES CXX)

# 2. Recherche de SDL2
find_package(SDL2 REQUIRED)

# 3. Définition de l'exécutable avec les bons chemins vers le dossier src/
add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/Grid.cpp 
    src/GameRender.cpp
    src/Enemy.cpp
)

# 4. Configuration de l'exécutable
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE "SDL_MAIN_HANDLED")
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

# 5. Copie du fichier de carte (Attention : ton fichier s'appelle chem.txt et est dans sprites/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sprites/chem.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)