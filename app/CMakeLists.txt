set(APP_EXTENSTIONS "src/*.cpp" "src/*.h" "src/*.ui")
file(GLOB_RECURSE APP_FILES CONFIGURE_DEPENDS ${APP_EXTENSTIONS})

qt_add_executable(app
    WIN32 MACOSX_BUNDLE
    ${APP_FILES}
)

target_include_directories(app PRIVATE src/)

target_compile_features(app PUBLIC cxx_std_20)

set_target_properties(app PROPERTIES CMAKE_AUTOUIC ON)
set_target_properties(app PROPERTIES CMAKE_AUTOMOC ON)
set_target_properties(app PROPERTIES CMAKE_AUTORCC ON)

target_link_libraries(app
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Multimedia
  Qt${QT_VERSION_MAJOR}::MultimediaWidgets
)

install(TARGETS app
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET app
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
    NO_TRANSLATIONS
)
install(SCRIPT ${deploy_script})
