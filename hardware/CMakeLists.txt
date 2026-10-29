file(GLOB_RECURSE HARDWARE_FILES CONFIGURE_DEPENDS "src/*.cpp" "src/*.h" "src/*.ui")

qt_add_executable(hardware
    WIN32 MACOSX_BUNDLE
    ${HARDWARE_FILES}
)

find_package(Crow CONFIG REQUIRED)
find_package(SqliteOrm CONFIG REQUIRED)

target_include_directories(hardware PRIVATE src/)

target_link_libraries(hardware
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Multimedia
  Qt${QT_VERSION_MAJOR}::MultimediaWidgets
  Crow::Crow
  sqlite_orm::sqlite_orm
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
