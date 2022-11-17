cmake_minimum_required(VERSION 3.0.0)
project(LR10 VERSION 0.1.0)

include(CTest)
enable_testing()
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

include_directories(LR10 PUBLIC include)
link_directories(LR10 PUBLIC lib)

set(HEADERS
	src/sound/Sound.h
	src/sound/RandomSound.h
	src/global.h
	src/HitboxRect.h
	src/entities/Entity.h
	src/entities/Overlay.h
	src/entities/Healthy.h
	src/entities/Player.h
	src/entities/Sun.h
	src/entities/Wall.h
	src/entities/Nikita.h
	src/entities/Vadid/Vadid.h
	src/entities/Vadid/Afterimage.h
	src/entities/Vadid/Rasengan.h
	src/entities/HealthBar.h
	src/gui/GUIElement.h
	src/gui/Button.h
	src/attacks/Attack.h
	src/attacks/MeleeAttack.h
	src/attacks/SpikeAttack.h
	src/Dragger.h
	src/engine/Level.h
	src/engine/Game.h
)
set(SOURCES
	src/sound/Sound.cpp
	src/sound/RandomSound.cpp
	src/global.cpp
	src/HitboxRect.cpp
	src/entities/Entity.cpp
	src/entities/Overlay.cpp
	src/entities/Healthy.cpp
	src/entities/Player.cpp
	src/entities/Sun.cpp
	src/entities/Wall.cpp
	src/entities/Nikita.cpp
	src/entities/Vadid/Vadid.cpp
	src/entities/Vadid/Afterimage.cpp
	src/entities/Vadid/Rasengan.cpp
	src/entities/HealthBar.cpp
	src/gui/GUIElement.cpp
	src/gui/Button.cpp
	src/attacks/Attack.cpp
	src/attacks/MeleeAttack.cpp
	src/attacks/SpikeAttack.cpp
	src/Dragger.cpp
	src/engine/Level.cpp
	src/engine/Game.cpp
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
if(WIN32)
	target_link_libraries(LR10 shlwapi)
	execute_process(
		COMMAND mkdir assets
	)
	execute_process(
		COMMAND cp -r ../assets/textures assets
		COMMAND cp -r ../assets/sounds assets
		COMMAND cp ../bin/*.dll .
	)
else()
	target_link_libraries(LR10 FLAC ogg)
	execute_process(COMMAND ln -s ../assets)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)