cmake_minimum_required(VERSION 3.16)

project(Client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Network)
qt_standard_project_setup()
qt_add_executable(appClient
    main.cpp
    Resource.qrc
    backend.h
    backend.cpp
)

qt_add_qml_module(appClient
    URI Client
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES ContentBar.qml
    RESOURCES Resource.qrc
    QML_FILES Home.qml
    QML_FILES Live.qml
    QML_FILES Setting.qml
    QML_FILES HomeExemple.qml
    SOURCES backend.h backend.cpp
    QML_FILES ItemHome.qml
    RESOURCES qtquickcontrols2.conf
)

set(CMAKE_AUTORCC ON)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appClient PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appClient
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appClient
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Core
    PRIVATE Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS appClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


