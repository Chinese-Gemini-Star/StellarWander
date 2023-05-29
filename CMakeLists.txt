cmake_minimum_required(VERSION 3.5)

project(StellarWander VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Sql REQUIRED)
find_package(Qt6 COMPONENTS PrintSupport REQUIRED)

configure_file(StellarWanderDatabase.db ${CMAKE_BINARY_DIR}/StellarWanderDatabase.db COPYONLY)

set(TS_FILES StellarWander_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        usermainwindow.h usermainwindow.cpp usermainwindow.ui
        adminmainwindow.h adminmainwindow.cpp adminmainwindow.ui
        logindialog.h logindialog.cpp logindialog.ui
        registerdialog.h registerdialog.cpp registerdialog.ui
        selectdialog.h selectdialog.cpp selectdialog.ui
        newappointmentdialog.h newappointmentdialog.cpp newappointmentdialog.ui
        detaildialog.h detaildialog.cpp detaildialog.ui
        addtouristdialog.h addtouristdialog.cpp addtouristdialog.ui
        appointmentdetail.h appointmentdetail.cpp appointmentdetail.ui
        selecttouristdialog.h selecttouristdialog.cpp selecttouristdialog.ui
        daydelegate.h daydelegate.cpp
        readonlydelegate.h readonlydelegate.cpp
        timedelegate.h timedelegate.cpp
        appointdelegate.h appointdelegate.cpp
        appointmentdetaildelegate.h appointmentdetaildelegate.cpp
        databasetool.h databasetool.cpp
        user.h user.cpp
        tourist.h tourist.cpp
        appointment.h appointment.cpp
        selectappointmentrule.h selectappointmentrule.cpp
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(StellarWander
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET StellarWander APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(StellarWander SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(StellarWander
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(StellarWander PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql Qt6::PrintSupport)

set_target_properties(StellarWander PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS StellarWander
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(StellarWander)
endif()
