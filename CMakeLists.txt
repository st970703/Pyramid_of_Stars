cmake_minimum_required(VERSION 4.2)
project(Print_Pyramid)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/Qt/6.11.1/mingw_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Test
        Widgets
        REQUIRED)

add_executable(Print_Pyramid WIN32
        src/main.cpp
        src/pyramid/pyramid.cpp
        src/pyramid/pyramid.h
        src/ui/pyramidwindow.cpp
        src/ui/pyramidwindow.h)
target_include_directories(Print_Pyramid PRIVATE src)
target_link_libraries(Print_Pyramid
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

enable_testing()

add_executable(Print_Pyramid_Tests
        tests/pyramidwindow_test.cpp
        src/pyramid/pyramid.cpp
        src/pyramid/pyramid.h
        src/ui/pyramidwindow.cpp
        src/ui/pyramidwindow.h)
target_include_directories(Print_Pyramid_Tests PRIVATE src)
target_link_libraries(Print_Pyramid_Tests
        Qt::Core
        Qt::Gui
        Qt::Test
        Qt::Widgets
)
add_test(NAME Print_Pyramid_Tests COMMAND Print_Pyramid_Tests)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()

    function(copy_qt_runtime TARGET_NAME)
        get_filename_component(MINGW_RUNTIME_PATH "${CMAKE_CXX_COMPILER}" DIRECTORY)

        if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
            add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "$<TARGET_FILE_DIR:${TARGET_NAME}>/plugins/platforms/")
            add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${TARGET_NAME}>/plugins/platforms/")
        endif ()

        foreach (QT_LIB ${ARGN})
            add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${TARGET_NAME}>")
        endforeach ()

        foreach (MINGW_DLL libgcc_s_seh-1.dll libstdc++-6.dll libwinpthread-1.dll)
            if (EXISTS "${MINGW_RUNTIME_PATH}/${MINGW_DLL}")
                add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy
                        "${MINGW_RUNTIME_PATH}/${MINGW_DLL}"
                        "$<TARGET_FILE_DIR:${TARGET_NAME}>")
            endif ()
        endforeach ()
    endfunction()

    copy_qt_runtime(Print_Pyramid Core Gui Widgets)
    copy_qt_runtime(Print_Pyramid_Tests Core Gui Test Widgets)
endif ()
