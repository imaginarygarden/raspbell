file(GLOB_RECURSE HARDWARE_SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.qrc")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(hardware
        MANUAL_FINALIZATION
        ${HARDWARE_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET hardware APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(hardware SHARED
            ${HARDWARE_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(hardware
          ${HARDWARE_SOURCES}
        )
    endif()
endif()

target_include_directories(hardware PRIVATE "src/")

file(GLOB_RECURSE HARDWARE_QML_FILES RELATIVE CONFIGURE_DEPENDS "src/*.qml")

qt_add_qml_module(hardware
    URI MyHardware
    VERSION 1.0
    QML_FILES
        ${HARDWARE_QML_FILES}
)

target_link_libraries(hardware
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.hardware)
endif()
set_target_properties(hardware PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)

qt_generate_deploy_qml_app_script(
    TARGET hardware
    OUTPUT_SCRIPT deploy_script
    NO_TRANSLATIONS
)

install(SCRIPT ${deploy_script})

install(TARGETS hardware
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(hardware)
    qt_finalize_executable(hardware)
endif()