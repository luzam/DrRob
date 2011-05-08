Project ( DrRob )
cmake_minimum_required(VERSION 2.3)
set (
   SOURCES
   source/DashBoard.cpp
   source/Game.cpp
   source/Grille.cpp
   source/InterfaceX.cpp
   source/MoteurPhy.cpp
   source/SDL_rotozoom.c
include/Blobs.h
include/Clock.h
include/Color.h
include/conected.h
include/Controls.h
include/DashBoard.h
include/Enums.h
include/Game.h
include/Grille.h
include/InterfaceX.h
include/Link.h
include/MoteurPhy.h
include/Orientation.h
include/Position.h
include/SDL_rotozoom.h
include/State.h
include/Tree.h
   main.cpp
)

# REQUIRED does not work in CMake <=2.4.6 for SDL
Find_Package ( SDL REQUIRED )
Find_Package ( SDL_image REQUIRED )
Find_Package ( SDL_ttf REQUIRED )

# Workaround for the non-working REQUIRED flag
if ( NOT SDL_FOUND )
   message ( FATAL_ERROR "SDL not found!" )
endif ( NOT SDL_FOUND )

include_directories(${SDL_INCLUDE_DIR}
${SDLTTF_INCLUDE_DIR}
${SDLIMAGE_INCLUDE_DIR})
set (
LIB
   ${SDL_LIBRARY}
   ${SDLIMAGE_LIBRARY} 
   ${SDLTTF_LIBRARY}
  # SDLmain # Sadly not included in SDL_LIBRARY variable
)

link_libraries( ${LIB})

add_executable (
   DrRob
   WIN32 # Only if you don't want the DOS prompt to appear in the background in Windows
   MACOSX_BUNDLE
   ${SOURCES} # We could've listed the source files here directly instead of using a variable to store them
)
TARGET_LINK_LIBRARIES(
DrRob
${LIB}
)