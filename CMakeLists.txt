cmake_minimum_required(VERSION 3.0.0)
project(LR10 VERSION 0.1.0)

include(CTest)
enable_testing()

set(HEADERS
    src/RandomSound.h
    src/global.h
    src/HitboxRect.h
    src/objects/Object.h
    src/objects/Healthy.h
    src/objects/Player.h
    src/objects/Sun.h
    src/objects/Wall.h
    src/objects/Nikita.h
    src/objects/HealthBar.h
    src/gui/GUIElement.h
    src/gui/Button.h
    src/Attack.h
    src/MeleeAttack.h
    src/Dragger.h
)
set(SOURCES
    src/RandomSound.cpp
    src/global.cpp
    src/HitboxRect.cpp
    src/objects/Object.cpp
    src/objects/Healthy.cpp
    src/objects/Player.cpp
    src/objects/Sun.cpp
    src/objects/Wall.cpp
    src/objects/Nikita.cpp
    src/objects/HealthBar.cpp
    src/gui/GUIElement.cpp
    src/gui/Button.cpp
    src/Attack.cpp
    src/MeleeAttack.cpp
    src/Dragger.cpp
)

add_executable(LR10
    ${HEADERS}
    ${SOURCES}
    main.cpp
)

target_link_libraries(LR10
    foresteamnd
    pthread
    sfml-graphics
    sfml-window
    sfml-audio
    sfml-system
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
