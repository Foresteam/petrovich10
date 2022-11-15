rm -rf dist
mkdir dist
mkdir dist/assets
cp -r assets/textures dist/assets
cp -r assets/sounds dist/assets
mkdir -p dist/usr/lib

cp /usr/lib/libsfml-audio.so dist/usr/lib
cp /usr/lib/libsfml-window.so dist/usr/lib
cp /usr/lib/libsfml-graphics.so dist/usr/lib
cp /usr/lib/libsfml-system.so dist/usr/lib

cp /usr/lib/libfreetype.so dist/usr/lib
cp /usr/lib/libX11.so dist/usr/lib
cp /usr/lib/libXrandr.so dist/usr/lib
cp /usr/lib/libudev.so dist/usr/lib
cp /usr/lib/libOpenGL.so dist/usr/lib
cp /usr/lib/libFLAC.so dist/usr/lib
cp /usr/lib/libogg.so dist/usr/lib
cp /usr/lib/libvorbis.so dist/usr/lib
cp /usr/lib/libvorbisenc.so dist/usr/lib
cp /usr/lib/libvorbisfile.so dist/usr/lib
cp /usr/lib/libopenal.so dist/usr/lib

cp appimage_assets/* dist
chmod +x dist/AppRun

rm -rf build
mkdir build
cmake -DCMAKE_BUILD_TYPE=Release . -B build
cmake --build build -j12
cp build/LR10 dist

ARCH=x86_64 appimagetool dist petrovich10-linux.AppImage