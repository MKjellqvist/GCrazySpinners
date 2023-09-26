//
// Created by martin on 2022-04-15.
//

#ifndef GCRAZYSPINNERS_CIRCLEWINDOW_H
#define GCRAZYSPINNERS_CIRCLEWINDOW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <valarray>

class CircleWindow : public sf::RenderWindow {
public:
    explicit CircleWindow(sf::VideoMode mode, bool is_fullscreen);

    /**
     * If is_fullscreen is set the best fullscreen videomode is returned, regardless of
     * width and height.
     *
     * The defaults gives the best fullscreen mode.
     * @param is_fullscreen
     * @param width
     * @param height
     * @return The videomode closest to the given widht and height or the best fullscreen mode.
     */
    static sf::VideoMode GetMode(bool is_fullscreen = true, unsigned int width = 0, unsigned int height = 0);

    /**
     * @return if the Start() method should be called again;
     */
    bool Start();

    void DoDraw(sf::Image &image);

//    std::vector<double> phases;
    std::valarray<double> phases;

    void IncrementPhases();

    double phase_speed = 0.002;

    void OnResize();
};

#endif //GCRAZYSPINNERS_CIRCLEWINDOW_H
