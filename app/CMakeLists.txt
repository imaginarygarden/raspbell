file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(app ${APP_SOURCES})

target_include_directories(app PRIVATE "src/")

find_package(Qt5 COMPONENTS Core REQUIRED)

target_link_directories(app Qt5::Core)