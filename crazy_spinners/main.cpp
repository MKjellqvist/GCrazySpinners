#include <iostream>
#include <string>

#include <giomm/settings.h>
#include <giomm/file.h>
#include <giomm/settingsschemasource.h>
#include <glibmm.h>
#include <gtkmm/application.h>

#include "AppSettings.h"
#include "crazy_spinners.h"
#include "CircleWindow.h"

/**
 * @mainpage
 *
 * I saw a gif on reddit. Nuff said.
 */

/**
 * I love globals like this. fite me!
 */
AppSettings settings;

using namespace crazy_spinners;
/**
 *
 */
void init_app() {
    auto gio_settings = Gio::Settings::create(APPLICATION_ID);
    settings.is_fullscreen = gio_settings->get_boolean(SETTING_FULLSCREEN);
    settings.size_y = gio_settings->get_int(SETTING_HEIGHT);
    settings.size_x = gio_settings->get_int(SETTING_WIDTH);
    settings.circle_count = gio_settings->get_int(SETTING_CIRCLE_COUNT);
    if (!settings.circle_count) {
        std::cerr << "Zero circles, reset to 10\n";
        settings.circle_count = 10;
    }
}

/**
 * Use this function to terminate the application gracefully.
 */
void shutdown_app() {
    auto gio_settings = Gio::Settings::create(APPLICATION_ID);
    gio_settings->set_boolean(SETTING_FULLSCREEN, settings.is_fullscreen);
    gio_settings->set_int(SETTING_HEIGHT, settings.size_y);
    gio_settings->set_int(SETTING_WIDTH, settings.size_x);
    gio_settings->set_int(SETTING_CIRCLE_COUNT, settings.circle_count);

    if (gio_settings->get_has_unapplied()) {
        std::cerr << "unapplied settings\n";
    }
}

/**
 * I no longer remember how this works.
 * Ah, It's coming back to me now.
 */
void add_gsettings_path_env() {
    auto settings_path = Gio::File::create_for_path("..");

    auto env = getenv("GSETTINGS_SCHEMA_DIR");
    std::string datadir;
    if (env) {
        datadir = env;
        datadir += ":";
    }
    datadir += settings_path->get_path();

    setenv("GSETTINGS_SCHEMA_DIR", datadir.c_str(), true);
}

int main() {
    auto app = Gtk::Application::create(APPLICATION_ID);

    add_gsettings_path_env();
    init_app();
    auto mode = CircleWindow::GetMode(settings.is_fullscreen, settings.size_x, settings.size_y);
    settings.circle_count = 10;
    CircleWindow window(mode, settings.is_fullscreen);
    while (window.Start()) {}
    shutdown_app();

    app->run();
}
