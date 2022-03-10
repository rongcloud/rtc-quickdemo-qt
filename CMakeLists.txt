cmake_minimum_required(VERSION 3.5)

project(rtc-quickdemo-qt VERSION 0.1 LANGUAGES CXX)

add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8) #检测 windows 32/64
        set(RTC_LIBS_PATH ${CMAKE_SOURCE_DIR}/sdk/lib/win/x64)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(RTC_LIBS_PATH ${CMAKE_SOURCE_DIR}/sdk/lib/win/x86)
    endif()
 endif(WIN32)

set(RTC_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/sdk)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    rcrtc_listener_impl.cpp
    rcrtc_listener_impl.h
    rtc_constants.h
    rtc_live_model.cpp
    rtc_live_model.h
    rtc_live_model.ui
    rtc_meeting_model.cpp
    rtc_meeting_model.h
    rtc_meeting_model.ui
    rtc_video_render.cpp
    rtc_video_render.h
    rtc_video_render.ui
    utility.cpp
    utility.h
)
add_executable(rtc-quickdemo-qt
    ${PROJECT_SOURCES}
)

if (WIN32)
    add_compile_definitions(GLEW_STATIC)
    add_compile_definitions(WEBRTC_WIN WIN32_LEAN_AND_MEAN NOMINMAX QT_NO_KEYWORDS _ITERATOR_DEBUG_LEVEL=0 BUILD_IM_WITH_RTC _CRT_SECURE_NO_WARNINGS)
endif(WIN32)

target_link_directories(rtc-quickdemo-qt
    PRIVATE
    ${RTC_LIBS_PATH}
    )

target_include_directories(rtc-quickdemo-qt
    PRIVATE
    ${RTC_INCLUDE_PATH}/include/im
    ${RTC_INCLUDE_PATH}/include/rtc
    )

if (WIN32)
    set(LINK_LIBS
     ${RTC_LIBS_PATH}/rongim.dll.lib
     ${RTC_LIBS_PATH}/rongcommon.dll.lib
     ${RTC_LIBS_PATH}/rongrtc.dll.lib
     opengl32.lib
     Kernel32.lib
     )
 endif(WIN32)


if(WIN32)
    if(MSVC)
        set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE YES
        LINK_FLAGS "/ENTRY:mainCRTStartup"
        )
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
    else()
        message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
    endif(MSVC)
endif(WIN32)

target_link_libraries(rtc-quickdemo-qt
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${LINK_LIBS}
    )
