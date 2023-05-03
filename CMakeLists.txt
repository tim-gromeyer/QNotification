cmake_minimum_required(VERSION 3.16)
project(QNotification VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS AndroidExtras Widgets)

set(HEADERS
    include/QNotification.h
)

set(SOURCES
    ${HEADERS} # Otherwise build will fail
    src/QAbstractNotifier.h
    src/QNotification.cpp
    src/QNotifierFactory.cpp src/QNotifierFactory.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_library(qnotification SHARED MANUAL_FINALIZATION ${SOURCES})
else()
    add_library(qnotification SHARED ${SOURCES})
endif()

target_link_libraries(qnotification PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
)

set_target_properties(qnotification PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${HEADERS}"
)
target_include_directories(qnotification PRIVATE include src)
target_compile_features(qnotification PUBLIC cxx_std_11) # Require at least c++11

target_compile_definitions(qnotification PRIVATE QT${QT_VERSION_MAJOR}=1)

set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/android")

set_target_properties(qnotification PROPERTIES
    QT_ANDROID_PACKAGE_SOURCE_DIR ${ANDROID_PACKAGE_SOURCE_DIR}
)

set(PLATFORM_SPECIFIC_SOURCES "")

if(ANDROID)
    set(PLATFORM_SPECIFIC_SOURCES
        src/android/QAndroidNotifier.cpp src/android/QAndroidNotifier.h
    )

    if(${QT_VERSION_MAJOR} EQUAL 5)
        target_link_libraries(qnotification PUBLIC
            Qt5::AndroidExtras
        )
    endif()
elseif(IOS)
    set(PLATFORM_SPECIFIC_SOURCES
        src/ios/QIOSNotifier.h ios/QIOSNotifier.mm
    )

    target_link_libraries(qnotification PUBLIC
        "-framework Foundation"
        "-framework UIKit"
        "-framework UserNotifications"
    )
elseif(EMSCRIPTEN)
    set(PLATFORM_SPECIFIC_SOURCES
        src/wasm/QWebassemblyNotifier.h
        src/wasm/QWebassemblyNotifier.cpp
    )
else()
    set(PLATFORM_SPECIFIC_SOURCES
        src/desktop/QDesktopNotifier.cpp src/desktop/QDesktopNotifier.h
    )

    target_link_libraries(qnotification PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
    )
endif()

target_sources(qnotification PUBLIC ${PLATFORM_SPECIFIC_SOURCES})

install(TARGETS qnotification
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(main main.cpp ${SOURCES} ${PLATFORM_SPECIFIC_SOURCES})
else()
    if(ANDROID)
        add_library(main SHARED main.cpp ${SOURCES} ${PLATFORM_SPECIFIC_SOURCES})
    else()
        add_executable(main main.cpp ${SOURCES} ${PLATFORM_SPECIFIC_SOURCES})
    endif()
endif()

target_link_libraries(main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(main PRIVATE include src)
