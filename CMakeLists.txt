cmake_minimum_required(VERSION 3.5)

set(TARGET_NAME rtc_quickdemo_qt)
project(${TARGET_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if (WIN32)
    add_compile_options(/wd4819)
    add_compile_options(/wd4996)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8) #检测 windows 32/64
        set(RTC_LIBS_PATH ${CMAKE_SOURCE_DIR}/sdk/lib/win/x64)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(RTC_LIBS_PATH ${CMAKE_SOURCE_DIR}/sdk/lib/win/x86)
    endif()
 elseif(APPLE)
 elseif(UNIX AND NOT APPLE)
 endif(WIN32)

set(RTC_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/sdk/include)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mix_streams_layout.cpp
        mix_streams_layout.h
        nlohmann_json.hpp
        remoteuserui.cpp
        remoteuserui.h
        remoteuserui.ui
        mainwindow.ui
        meeting.cpp
        meeting.h
        meeting.ui
        live.cpp
        live.h
        live.ui
)

add_executable(${TARGET_NAME}
    ${PROJECT_SOURCES}
)

target_link_directories(${TARGET_NAME}
    PRIVATE
    ${RTC_LIBS_PATH}
    )

target_include_directories(${TARGET_NAME}
    PRIVATE
    ${RTC_INCLUDE_PATH} #通用头文件
    ${RTC_INCLUDE_PATH}/im #IM 头文件
    ${RTC_INCLUDE_PATH}/rtc #RTC 头文件
    )


if (WIN32)
    set(LINK_LIBS
     ${RTC_LIBS_PATH}/rongim.dll.lib
     ${RTC_LIBS_PATH}/rongcommon.dll.lib
     ${RTC_LIBS_PATH}/rongrtc.dll.lib
     opengl32.lib
     Kernel32.lib)
 elseif(APPLE)
 elseif(UNIX AND NOT APPLE)
     set(LINK_LIBS
         rongcommon
         rongim
         rongrtc
         GL
         EGL
         pthread
         dl
         )
 endif(WIN32)

target_link_libraries(${TARGET_NAME}
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${LINK_LIBS}
    )
