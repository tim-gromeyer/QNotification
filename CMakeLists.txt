cmake_minimum_required(VERSION 3.16)
project(QNotification VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS AndroidExtras Widgets)

set(SOURCES
    QtAbstractNotifier.h
    QtNotification.cpp QtNotification.h
    QtNotifierFactory.cpp QtNotifierFactory.h
)
set(PUBLIC_HEADER
    QtNotification.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_library(qnotification MANUAL_FINALIZATION ${SOURCES} ${PUBLIC_HEADER})
else()
    add_library(qnotification ${SOURCES} ${PUBLIC_HEADER})
endif()

target_link_libraries(qnotification PUBLIC
    Qt::Core
    Qt::Gui
)

target_compile_definitions(qnotification PRIVATE QT${QT_VERSION_MAJOR}=1)

set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/android")

set_target_properties(qnotification PROPERTIES
    QT_ANDROID_PACKAGE_SOURCE_DIR ${ANDROID_PACKAGE_SOURCE_DIR}
)

if(ANDROID)
    target_sources(qnotification PUBLIC
        QtAndroidNotifier.cpp QtAndroidNotifier.h
    )

    if(${QT_VERSION_MAJOR} EQUAL 5)
        target_link_libraries(qnotification PUBLIC
            Qt::AndroidExtras
        )
    endif()
elseif(IOS)
    target_sources(qnotification PUBLIC
        QtIOSNotifier.h QtIOSNotifier.mm
    )

    target_link_libraries(qnotification PUBLIC
        "-framework Foundation"
        "-framework UIKit"
        "-framework UserNotifications"
    )
elseif(EMSCRIPTEN)
    target_sources(qnotification PUBLIC
        wasm/notification.h
        wasm/notification.cpp
    )

    target_link_options(qnotification PRIVATE "--bind --pre-js wasm/notification.js")
else()
    target_sources(qnotification PUBLIC
        QtDesktopNotifier.cpp QtDesktopNotifier.h
    )

    target_link_libraries(qnotification PUBLIC
        Qt::Widgets
    )
endif()

install(TARGETS qnotification DESTINATION lib)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(main main.cpp)
else()
    if(ANDROID)
        add_library(main SHARED main.cpp)
    else()
        add_executable(main main.cpp)
    endif()
endif()

target_link_libraries(main PUBLIC qnotification Qt::Widgets)