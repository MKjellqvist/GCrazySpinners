find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

pkg_check_modules(GLIBMM glibmm-2.4)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(
        ${GTKMM_LIBRARY_DIRS} ${GLIBMM_LIBRARY_DIRS})

include_directories(
        ${GTKMM_INCLUDE_DIRS} ${GLIBMM_INCLUDE_DIRS})

add_executable(GCrazySpinners main.cpp AppSettings.h svg-color.h crazy_spinners.h CircleWindow.cpp CircleWindow.h)

target_link_libraries(GCrazySpinners ${GTKMM_LIBRARIES})
target_link_libraries(GCrazySpinners sfml-graphics)
target_link_libraries(GCrazySpinners sfml-audio)
