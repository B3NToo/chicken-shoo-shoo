QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        avatar.cpp \
        camera.cpp \
        chicken.cpp \
        drawable.cpp \
        game.cpp \
        inputhandler.cpp \
        level.cpp \
        levelloader.cpp \
        main.cpp \
        utils.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L$$PWD/SFML/bin/ -lsfml-system-2

INCLUDEPATH += $$PWD/SFML/include
DEPENDPATH += $$PWD/SFML/lib



LIBS += -L$$PWD/SFML/bin/ -lsfml-graphics-2

LIBS += -L$$PWD/SFML/bin/ -lsfml-window-2

DISTFILES += \
  .gitignore \
  CMakeLists.txt \
  SFML/bin/openal32.dll \
  SFML/bin/sfml-audio-2.dll \
  SFML/bin/sfml-audio-d-2.dll \
  SFML/bin/sfml-graphics-2.dll \
  SFML/bin/sfml-graphics-d-2.dll \
  SFML/bin/sfml-network-2.dll \
  SFML/bin/sfml-network-d-2.dll \
  SFML/bin/sfml-system-2.dll \
  SFML/bin/sfml-system-d-2.dll \
  SFML/bin/sfml-window-2.dll \
  SFML/bin/sfml-window-d-2.dll \
  SFML/lib/cmake/SFML/SFMLConfig.cmake \
  SFML/lib/cmake/SFML/SFMLConfigDependencies.cmake \
  SFML/lib/cmake/SFML/SFMLConfigVersion.cmake \
  SFML/lib/cmake/SFML/SFMLSharedTargets-debug.cmake \
  SFML/lib/cmake/SFML/SFMLSharedTargets-release.cmake \
  SFML/lib/cmake/SFML/SFMLSharedTargets.cmake \
  SFML/lib/cmake/SFML/SFMLStaticTargets-debug.cmake \
  SFML/lib/cmake/SFML/SFMLStaticTargets-release.cmake \
  SFML/lib/cmake/SFML/SFMLStaticTargets.cmake \
  SFML/lib/libFLAC.a \
  SFML/lib/libfreetype.a \
  SFML/lib/libogg.a \
  SFML/lib/libopenal32.a \
  SFML/lib/libsfml-audio-d.a \
  SFML/lib/libsfml-audio-s-d.a \
  SFML/lib/libsfml-audio-s.a \
  SFML/lib/libsfml-audio.a \
  SFML/lib/libsfml-graphics-d.a \
  SFML/lib/libsfml-graphics-s-d.a \
  SFML/lib/libsfml-graphics-s.a \
  SFML/lib/libsfml-graphics.a \
  SFML/lib/libsfml-main-d.a \
  SFML/lib/libsfml-main.a \
  SFML/lib/libsfml-network-d.a \
  SFML/lib/libsfml-network-s-d.a \
  SFML/lib/libsfml-network-s.a \
  SFML/lib/libsfml-network.a \
  SFML/lib/libsfml-system-d.a \
  SFML/lib/libsfml-system-s-d.a \
  SFML/lib/libsfml-system-s.a \
  SFML/lib/libsfml-system.a \
  SFML/lib/libsfml-window-d.a \
  SFML/lib/libsfml-window-s-d.a \
  SFML/lib/libsfml-window-s.a \
  SFML/lib/libsfml-window.a \
  SFML/lib/libvorbis.a \
  SFML/lib/libvorbisenc.a \
  SFML/lib/libvorbisfile.a \
  build-chicken-shoo-shoo-Desktop_Qt_6_0_3_MinGW_64_bit-Debug/.qmake.stash \
  build-chicken-shoo-shoo-Desktop_Qt_6_0_3_MinGW_64_bit-Debug/debug/chicken-shoo-shoo.exe \
  build-chicken-shoo-shoo-Desktop_Qt_6_0_3_MinGW_64_bit-Debug/penal32.exe \
  build-chicken-shoo-shoo-Desktop_Qt_6_0_3_MinGW_64_bit-Profile/.qmake.stash \
  build-chicken-shoo-shoo-Desktop_Qt_6_0_3_MinGW_64_bit-Profile/penal32.exe \
  build-chicken-shoo-shoo-Desktop_Qt_6_0_3_MinGW_64_bit-Release/.qmake.stash \
  build-chicken-shoo-shoo-Desktop_Qt_6_0_3_MinGW_64_bit-Release/penal32.exe \
  build-chicken-shoo-shoo-Desktop_Qt_6_0_3_MinGW_64_bit-Release/release/chicken-shoo-shoo.exe

HEADERS += \
  SFML/include/SFML/Audio.hpp \
  SFML/include/SFML/Audio/AlResource.hpp \
  SFML/include/SFML/Audio/Export.hpp \
  SFML/include/SFML/Audio/InputSoundFile.hpp \
  SFML/include/SFML/Audio/Listener.hpp \
  SFML/include/SFML/Audio/Music.hpp \
  SFML/include/SFML/Audio/OutputSoundFile.hpp \
  SFML/include/SFML/Audio/Sound.hpp \
  SFML/include/SFML/Audio/SoundBuffer.hpp \
  SFML/include/SFML/Audio/SoundBufferRecorder.hpp \
  SFML/include/SFML/Audio/SoundFileFactory.hpp \
  SFML/include/SFML/Audio/SoundFileFactory.inl \
  SFML/include/SFML/Audio/SoundFileReader.hpp \
  SFML/include/SFML/Audio/SoundFileWriter.hpp \
  SFML/include/SFML/Audio/SoundRecorder.hpp \
  SFML/include/SFML/Audio/SoundSource.hpp \
  SFML/include/SFML/Audio/SoundStream.hpp \
  SFML/include/SFML/Config.hpp \
  SFML/include/SFML/GpuPreference.hpp \
  SFML/include/SFML/Graphics.hpp \
  SFML/include/SFML/Graphics/BlendMode.hpp \
  SFML/include/SFML/Graphics/CircleShape.hpp \
  SFML/include/SFML/Graphics/Color.hpp \
  SFML/include/SFML/Graphics/ConvexShape.hpp \
  SFML/include/SFML/Graphics/Drawable.hpp \
  SFML/include/SFML/Graphics/Export.hpp \
  SFML/include/SFML/Graphics/Font.hpp \
  SFML/include/SFML/Graphics/Glsl.hpp \
  SFML/include/SFML/Graphics/Glsl.inl \
  SFML/include/SFML/Graphics/Glyph.hpp \
  SFML/include/SFML/Graphics/Image.hpp \
  SFML/include/SFML/Graphics/PrimitiveType.hpp \
  SFML/include/SFML/Graphics/Rect.hpp \
  SFML/include/SFML/Graphics/Rect.inl \
  SFML/include/SFML/Graphics/RectangleShape.hpp \
  SFML/include/SFML/Graphics/RenderStates.hpp \
  SFML/include/SFML/Graphics/RenderTarget.hpp \
  SFML/include/SFML/Graphics/RenderTexture.hpp \
  SFML/include/SFML/Graphics/RenderWindow.hpp \
  SFML/include/SFML/Graphics/Shader.hpp \
  SFML/include/SFML/Graphics/Shape.hpp \
  SFML/include/SFML/Graphics/Sprite.hpp \
  SFML/include/SFML/Graphics/Text.hpp \
  SFML/include/SFML/Graphics/Texture.hpp \
  SFML/include/SFML/Graphics/Transform.hpp \
  SFML/include/SFML/Graphics/Transformable.hpp \
  SFML/include/SFML/Graphics/Vertex.hpp \
  SFML/include/SFML/Graphics/VertexArray.hpp \
  SFML/include/SFML/Graphics/VertexBuffer.hpp \
  SFML/include/SFML/Graphics/View.hpp \
  SFML/include/SFML/Main.hpp \
  SFML/include/SFML/Network.hpp \
  SFML/include/SFML/Network/Export.hpp \
  SFML/include/SFML/Network/Ftp.hpp \
  SFML/include/SFML/Network/Http.hpp \
  SFML/include/SFML/Network/IpAddress.hpp \
  SFML/include/SFML/Network/Packet.hpp \
  SFML/include/SFML/Network/Socket.hpp \
  SFML/include/SFML/Network/SocketHandle.hpp \
  SFML/include/SFML/Network/SocketSelector.hpp \
  SFML/include/SFML/Network/TcpListener.hpp \
  SFML/include/SFML/Network/TcpSocket.hpp \
  SFML/include/SFML/Network/UdpSocket.hpp \
  SFML/include/SFML/OpenGL.hpp \
  SFML/include/SFML/System.hpp \
  SFML/include/SFML/System/Clock.hpp \
  SFML/include/SFML/System/Err.hpp \
  SFML/include/SFML/System/Export.hpp \
  SFML/include/SFML/System/FileInputStream.hpp \
  SFML/include/SFML/System/InputStream.hpp \
  SFML/include/SFML/System/Lock.hpp \
  SFML/include/SFML/System/MemoryInputStream.hpp \
  SFML/include/SFML/System/Mutex.hpp \
  SFML/include/SFML/System/NativeActivity.hpp \
  SFML/include/SFML/System/NonCopyable.hpp \
  SFML/include/SFML/System/Sleep.hpp \
  SFML/include/SFML/System/String.hpp \
  SFML/include/SFML/System/String.inl \
  SFML/include/SFML/System/Thread.hpp \
  SFML/include/SFML/System/Thread.inl \
  SFML/include/SFML/System/ThreadLocal.hpp \
  SFML/include/SFML/System/ThreadLocalPtr.hpp \
  SFML/include/SFML/System/ThreadLocalPtr.inl \
  SFML/include/SFML/System/Time.hpp \
  SFML/include/SFML/System/Utf.hpp \
  SFML/include/SFML/System/Utf.inl \
  SFML/include/SFML/System/Vector2.hpp \
  SFML/include/SFML/System/Vector2.inl \
  SFML/include/SFML/System/Vector3.hpp \
  SFML/include/SFML/System/Vector3.inl \
  SFML/include/SFML/Window.hpp \
  SFML/include/SFML/Window/Clipboard.hpp \
  SFML/include/SFML/Window/Context.hpp \
  SFML/include/SFML/Window/ContextSettings.hpp \
  SFML/include/SFML/Window/Cursor.hpp \
  SFML/include/SFML/Window/Event.hpp \
  SFML/include/SFML/Window/Export.hpp \
  SFML/include/SFML/Window/GlResource.hpp \
  SFML/include/SFML/Window/Joystick.hpp \
  SFML/include/SFML/Window/Keyboard.hpp \
  SFML/include/SFML/Window/Mouse.hpp \
  SFML/include/SFML/Window/Sensor.hpp \
  SFML/include/SFML/Window/Touch.hpp \
  SFML/include/SFML/Window/VideoMode.hpp \
  SFML/include/SFML/Window/Window.hpp \
  SFML/include/SFML/Window/WindowHandle.hpp \
  SFML/include/SFML/Window/WindowStyle.hpp \
  avatar.h \
  camera.h \
  chicken.h \
  drawable.h \
  game.h \
  inputhandler.h \
  level.h \
  levelloader.h \
  utils.h
