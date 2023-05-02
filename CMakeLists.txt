cmake_minimum_required(VERSION 3.16)
project(QNotification VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS AndroidExtras Widgets)

set(SOURCES
    QAbstractNotifier.h
    QNotification.cpp
    QNotifierFactory.cpp QNotifierFactory.h
)
set(PUBLIC_HEADER
    include/QNotification.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_library(qnotification MANUAL_FINALIZATION ${SOURCES} ${PUBLIC_HEADER})
else()
    add_library(qnotification ${SOURCES} ${PUBLIC_HEADER})
endif()

target_link_libraries(qnotification PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
)

target_compile_definitions(qnotification PRIVATE QT${QT_VERSION_MAJOR}=1)

set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/android")

set_target_properties(qnotification PROPERTIES
    QT_ANDROID_PACKAGE_SOURCE_DIR ${ANDROID_PACKAGE_SOURCE_DIR}
)

if(ANDROID)
    target_sources(qnotification PUBLIC
        QAndroidNotifier.cpp QAndroidNotifier.h
    )

    if(${QT_VERSION_MAJOR} EQUAL 5)
        target_link_libraries(qnotification PUBLIC
            Qt5::AndroidExtras
        )
    endif()
elseif(IOS)
    target_sources(qnotification PUBLIC
        QIOSNotifier.h QIOSNotifier.mm
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
else()
    target_sources(qnotification PUBLIC
        QDesktopNotifier.cpp QDesktopNotifier.h
    )

    target_link_libraries(qnotification PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
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

target_link_libraries(main PUBLIC qnotification Qt${QT_VERSION_MAJOR}::Widgets)
