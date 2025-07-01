cmake_minimum_required(VERSION 3.16)
project(untitled)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Шлях до Qt
set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.12.12/5.12.12/mingw73_64/lib/cmake")

# Знайти потрібні модулі Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# Створення виконуваного файлу
set(SOURCES
        src/main.cpp
        src/drawingwidget.cpp
        src/mainwindow.cpp
        src/dot.cpp
        src/point.cpp
)
set(HEADERS
        headers/point.h
        headers/mainwindow.h
        headers/drawingwidget.h
        headers/dot.h
)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Лінкування з Qt5
target_link_libraries(untitled Qt5::Core Qt5::Gui Qt5::Widgets)

# Постобробка: копіювання DLL після збірки
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    # Визначення Debug-суфікса (d)
    set(DEBUG_SUFFIX "")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(DEBUG_SUFFIX "d")
    endif()

    # Шлях до Qt
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif()
    endif()

    # Копіювання qwindows[d].dll
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif()

    # Копіювання Qt DLL: Core, Gui, Widgets
    foreach(QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach()

    # Копіювання DLL з MinGW
    set(MINGW_BIN "C:/Qt/Qt5.12.12/Tools/mingw730_64/bin")
    foreach(MINGW_DLL libstdc++-6.dll libgcc_s_seh-1.dll libwinpthread-1.dll)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${MINGW_BIN}/${MINGW_DLL}"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach()
endif()
