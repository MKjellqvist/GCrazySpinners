//
// Created by martin on 2022-04-13.
//

#ifndef GCRAZYSPINNERS_APPSETTINGS_HPP
#define GCRAZYSPINNERS_APPSETTINGS_HPP

struct AppSettings {
    bool is_fullscreen;

    size_t size_x;
    size_t size_y;
    size_t circle_count;

    friend std::ostream &operator<<(std::ostream &out, AppSettings s) {
        out << "fullscreen: " << s.is_fullscreen << "\nX = " << s.size_x << "\nY = " << s.size_y << "\n"
            << "\ncircle-count: " << s.circle_count;
        return out;
    }
};

#endif //GCRAZYSPINNERS_APPSETTINGS_HPP
