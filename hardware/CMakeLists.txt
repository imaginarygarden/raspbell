set(HARDWARE_EXTENSTIONS "src/*.cpp" "src/*.h" "src/*.ui")
file(GLOB_RECURSE HARDWARE_FILES CONFIGURE_DEPENDS ${HARDWARE_EXTENSTIONS})

qt_add_executable(hardware
    WIN32 MACOSX_BUNDLE
    ${HARDWARE_FILES}
)

target_include_directories(hardware PRIVATE src/)

target_compile_features(hardware PUBLIC cxx_std_20)

set_target_properties(hardware PROPERTIES CMAKE_AUTOUIC ON)
set_target_properties(hardware PROPERTIES CMAKE_AUTOMOC ON)
set_target_properties(hardware PROPERTIES CMAKE_AUTORCC ON)

target_link_libraries(hardware
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::HttpServer
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Multimedia
  Qt${QT_VERSION_MAJOR}::MultimediaWidgets
)

install(TARGETS hardware
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET hardware
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
    NO_TRANSLATIONS
)
install(SCRIPT ${deploy_script})
