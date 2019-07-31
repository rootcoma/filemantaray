PROG_NAME=filemantaray.elf

SDL2_DIR=/usr/include/SDL2
IMGUI_DIR=lib/imgui-1.72
TEENYPATH_DIR=lib/teenypath

SRC_FILES=\
src/main.cpp \
src/gui.cpp \
src/file_system/*.cpp \
${IMGUI_DIR}/imgui.cpp \
${IMGUI_DIR}/imgui_draw.cpp \
${IMGUI_DIR}/imgui_widgets.cpp \
${IMGUI_DIR}/examples/libs/gl3w/GL/gl3w.cpp \
${IMGUI_DIR}/examples/imgui_impl_sdl.cpp \
${IMGUI_DIR}/examples/imgui_impl_opengl3.cpp \
${TEENYPATH_DIR}/src/teenypath.cpp

CXX_OPT=\
-O2 \
-Wall \
-m32

INC_DIR=\
-Isrc \
-I${IMGUI_DIR} \
-I${IMGUI_DIR}/examples \
-I${IMGUI_DIR}/examples/libs/gl3w \
-I${SDL2_DIR} \
-I${TEENYPATH_DIR}/include

LINK_OPT=\
-lSDL2 \
-lGL \
-ldl \
-ludev

build:
	mkdir -p build
	g++ -o build/${PROG_NAME} ${CXX_OPT} ${INC_DIR} ${SRC_FILES} ${LIBS} ${LINK_OPT}


run:
	cd build && ./${PROG_NAME}


