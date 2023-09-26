//
// Created by martin on 2022-04-15.
//
#include "crazy_spinners.h"
#include "CircleWindow.h"
#include "AppSettings.h"
#include "SFML/Graphics.hpp"
#include <cmath>
#include "svg-color.h"

/**
 * I still love globals...
 *
 */
extern AppSettings settings;

sf::VideoMode CircleWindow::GetMode(bool is_fullscreen, unsigned int width, unsigned int height) {
    const auto &modes = sf::VideoMode::getFullscreenModes();
    if (is_fullscreen) {
        return modes[0];
    }

    auto mode_width = std::min<decltype(modes[0].width)>(width, modes[0].width);
    auto mode_height = std::min<decltype(modes[0].height)>(height, modes[0].height);
    return {mode_width, mode_height};
}

CircleWindow::CircleWindow(sf::VideoMode mode, bool is_fullscreen) :
        sf::RenderWindow(mode, crazy_spinners::TITLE, is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default) {
    phases.resize(settings.circle_count);
}

/**
 * Ingen blir glad av sån hät programkod, men nu står vi här...
 * Den gick fort att skriva iaf.
 * TODO: Jag borde skapa ett lagom sammansatt exempel för programmeringsmetodiken hur det här kan organiseras mycket bättre.
 * @return
 */
bool CircleWindow::Start() {
    this->setFramerateLimit(0);
    sf::Image image;
    image.create(getSize().x, getSize().y, sf::Color::Black);
    sf::Texture texture;
    sf::Sprite sprite;
    auto running = true;
    sf::Event event{};

    auto do_restart = false;
    while (running) {
        pollEvent(event);
        if (event.type == sf::Event::Closed) {
            running = false;
        }
        if (event.type == sf::Event::Resized) {
            OnResize();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) {
            if (settings.is_fullscreen) {
                create(GetMode(false, settings.size_x, settings.size_y), crazy_spinners::TITLE);
                settings.is_fullscreen = false;
            } else {
                create(GetMode(true), crazy_spinners::TITLE);
                settings.is_fullscreen = true;
            }

            running = false;
            do_restart = true;
        }
        DoDraw(image);

        texture.loadFromImage(image);
        sprite.setTexture(texture);
        draw(sprite);

        display();
    }
    return do_restart;
}

void CircleWindow::DoDraw(sf::Image &image) {
    auto max_x = image.getSize().x;
    auto max_y = image.getSize().y;
    auto pixels_x_per_unit = 0.5 * (max_x - 1) / settings.circle_count;
    auto pixels_y_per_unit = 0.5 * (max_y - 1) / settings.circle_count;

    auto xs = sin(phases);
    auto ys = cos(phases);
    svg_color color;
    svg_color::hsv hsv_color{0, 1, 0xff};

    for (int row = 0; row < settings.circle_count; row++) {
        for (int col = 0; col < settings.circle_count; col++) {
            if (row == 0 && col == 0)
                continue;
            auto x_index = col;
            auto y_index = row;

            if (col == 0) {
                x_index = y_index;
            }

            if (row == 0) {
                y_index = x_index;
            }

            auto x = ((1 + xs[x_index]) + col * 2) * pixels_x_per_unit;
            auto y = ((1 + ys[y_index]) + row * 2) * pixels_y_per_unit;

            hsv_color.hue = 2 * phases[(row + col) / 2];
            auto rgba = color.from_hsv(hsv_color).rgba();

            sf::Color c(rgba);

            image.setPixel(x, y, c);
        }
    }
    IncrementPhases();
}

void CircleWindow::IncrementPhases() {
    for (int circle = 1; circle < settings.circle_count; circle++) {
        auto phase_increment = phase_speed * circle;
        phases[circle] += phase_increment;
    }
}

void CircleWindow::OnResize() {
    auto size = this->getSize();
    settings.size_x = size.x;
    settings.size_y = size.y;
}


