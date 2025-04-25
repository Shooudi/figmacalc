cmake_minimum_required(VERSION 3.16)

project(figmacalc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core CorePrivate QuickControls2)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appfigmacalc
    main.cpp
)

qt_add_qml_module(appfigmacalc
    URI figmacalc
    VERSION 1.0

    SOURCES
    Calculator.h
    Calculator.cpp

    QML_FILES
        "Main.qml"
        "content/Display.qml"
        "content/NumberPad.qml"
        "content/NormalButton.qml"
        "content/ActionButton.qml"
        "content/ClearButton.qml"

    RESOURCES 
        "content/icon/bkt.svg"
        "content/icon/division.svg"
        "content/icon/equal.svg"
        "content/icon/minus.svg"
        "content/icon/multiplication.svg"
        "content/icon/percent.svg"
        "content/icon/plus.svg"
        "content/icon/plus_minus.svg"
        "android/AndroidManifest.xml"
        "android/build.gradle"
        "android/res/values/libs.xml"
        "android/res/xml/qtprovider_paths.xml"

)

if(ANDROID)
    set_target_properties(appfigmacalc
        PROPERTIES
        QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android"
        QT_ANDROID_PACKAGE_NAME "io.qt.figmacalc"
        QT_ANDROID_TARGET_SDK_VERSION 35
        QT_ANDROID_VERSION_CODE 10
        QT_ANDROID_VERSION_NAME "1.0"
    )

    qt_import_plugins(appfigmacalc
        INCLUDE_BY_TYPE imageformats Qt::QSvgPlugin
        EXCLUDE_BY_TYPE qmltooling
        EXCLUDE_BY_TYPE iconengines
        EXCLUDE_BY_TYPE networkinformation
        EXCLUDE_BY_TYPE tls
        EXCLUDE_BY_TYPE platforminputcontexts
    )
endif()

target_link_libraries(appfigmacalc
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
    PRIVATE Qt6::Core
    PRIVATE Qt6::CorePrivate
)
