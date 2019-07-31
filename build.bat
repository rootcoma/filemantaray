@ECHO off
set PROG_NAME=filemantaray.exe

set SDL2_DIR=lib\SDL2-2.0.9
set IMGUI_DIR=lib\imgui-1.72
set TEENYPATH_DIR=lib\teenypath

set SRC_FILES=^
src\main.cpp ^
src\gui.cpp ^
src\file_system\*.cpp ^
%IMGUI_DIR%\imgui.cpp ^
%IMGUI_DIR%\imgui_draw.cpp ^
%IMGUI_DIR%\imgui_widgets.cpp ^
%IMGUI_DIR%\examples\libs\gl3w\GL\gl3w.cpp ^
%IMGUI_DIR%\examples\imgui_impl_sdl.cpp ^
%IMGUI_DIR%\examples\imgui_impl_opengl3.cpp ^
%TEENYPATH_DIR%\src\teenypath.cpp

set CXX_OPT=^
-O2 ^
-Wall ^
-m32 ^
-DUNICODE

set INC_DIR=^
-Isrc ^
-I%IMGUI_DIR% ^
-I%IMGUI_DIR%\examples ^
-I%IMGUI_DIR%\examples\libs\gl3w ^
-I%SDL2_DIR%\include ^
-I%TEENYPATH_DIR%\include

set LINK_OPT=^
-lSDL2 ^
-lopengl32 ^
-luser32 ^
-lkernel32 ^
-ladvapi32 ^
-lshell32

set LIBS=^
-L%SDL2_DIR%\lib\x86

mkdir build


@ECHO on
clang++ -o build\%PROG_NAME% %CXX_OPT% %INC_DIR% %SRC_FILES% %LIBS% %LINK_OPT% -Xlinker /subsystem:console
@ECHO off

echo Done!
@ECHO on

pause
