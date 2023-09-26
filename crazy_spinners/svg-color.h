#ifndef GCRAZYSPINNER_SVG_COLORS_H
#define GCRAZYSPINNER_SVG_COLORS_H

#include <cmath>
#include <algorithm>

/**
 * Color names from https://doc.qt.io/qt-5/qml-color.html
 * hsv implementation translated from https://en.wikipedia.org/wiki/HSL_and_HSV
 */

struct svg_color {
    /**
     * A Hue Saturation Value color
     */
    struct hsv {
        /**
         * Angle degrees [0-360]
         */
        float hue;
        float saturation;
        unsigned value;
    };
    unsigned rgb;

    svg_color() = default;

    svg_color(unsigned rgb) : rgb(rgb) {}

    /**
     * Maps the rgb components to a HSV value
     * @return hsv where hue [0, 360] saturation [0, 1] value [0, 255]
     */
    [[nodiscard]] hsv hsv_value() const {
        hsv v{};
        auto r = rgb >> 16;
        auto g = (rgb >> 8) & 0xFF;
        auto b = rgb & 0xFF;

        auto M = std::max({r, g, b});
        auto m = std::min({r, g, b});

        auto chroma = M - m;
        float h_prime =
                M == r ? std::remainder((g - b) * 1.f / chroma, 6.f) :
                M == g ? (b - r) * 1.f / chroma + 2 :
                M == b ? (r - g) * 1.f / chroma + 4 : 0.f;

        v.hue = h_prime * 60.f;
        v.value = M;

        if (M != 0) {
            v.saturation = chroma * 1.f / M;
        } else {
            v.saturation = 0.f;
        }
        return v;
    }

    /**
     * It seems to work.
     * Could have been a static member, but this is convenient.
     * @param value
     * @return
     */
    svg_color from_hsv(hsv value) {
        if (value.value > 255.0)
            value.value = 255.0;
        auto V = value.value * 1.0f / 255;
        auto S = value.saturation;
        auto C = V * S;
        auto H_prime = std::fmod(value.hue, 360) / 60.f;
        auto X = C * (1 - std::fabs(std::remainder(H_prime, 2.f) - 1));
        X *= 255;
        C *= 255;
        float R1, G1, B1;
        H_prime < 1 ? (R1 = C, G1 = X, B1 = 0.f) :
        H_prime < 2 ? (R1 = X, G1 = C, B1 = 0.f) :
        H_prime < 3 ? (R1 = 0.f, G1 = C, B1 = X) :
        H_prime < 4 ? (R1 = 0.f, G1 = X, B1 = C) :
        H_prime < 5 ? (R1 = X, G1 = 0.f, B1 = C) :
        (R1 = C, G1 = 0.f, B1 = X);
        auto m = V * 255 - C;
        rgb = unsigned(R1 + m) << 16 | unsigned(G1 + m) << 8 | unsigned(B1 + m);
        return *this;
    }
    /**
     * Saturated alpha channel.
     * @return
     */
    [[nodiscard]] uint32_t rgba() const {
        return rgb << 8u | 0xFF;
    }

    /**
     * Not really sure what happens here. The color is darker after the call.
     * darken(-1) has the same effect as brighten(1).
     *
     * @param steps
     * @return *this
     */
    svg_color darken(int steps = 1) {
        auto hsv = hsv_value();
        hsv.value -= steps;
        from_hsv(hsv);
        return *this;
    }

    /**
     * The opposite of darken. darken(-1) has the same effect as brighten(1).
     * @param steps
     * @return
     */
    svg_color brighten(int steps = 1) {
        return darken(-steps);
    }

    // I wonder who wrote all of dis stuf
    static constexpr int aliceblue = 0xf0f8ff;
    static constexpr int antiquewhite = 0xfaebd7;
    static constexpr int aqua = 0x00ffff;
    static constexpr int aquamarine = 0x7fffd4;
    static constexpr int azure = 0xf0ffff;
    static constexpr int beige = 0xf5f5dc;
    static constexpr int bisque = 0xffe4c4;
    static constexpr int black = 0x000000;
    static constexpr int blanchedalmond = 0xffebcd;
    static constexpr int blue = 0x0000ff;
    static constexpr int blueviolet = 0x8a2be2;
    static constexpr int brown = 0xa52a2a;
    static constexpr int burlywood = 0xdeb887;
    static constexpr int cadetblue = 0x5f9ea0;
    static constexpr int chartreuse = 0x7fff00;
    static constexpr int chocolate = 0xd2691e;
    static constexpr int coral = 0xff7f50;
    static constexpr int cornflowerblue = 0x6495ed;
    static constexpr int cornsilk = 0xfff8dc;
    static constexpr int crimson = 0xdc143c;
    static constexpr int cyan = 0x00ffff;
    static constexpr int darkblue = 0x00008b;
    static constexpr int darkcyan = 0x008b8b;
    static constexpr int darkgoldenrod = 0xb8860b;
    static constexpr int darkgray = 0xa9a9a9;
    static constexpr int darkgreen = 0x006400;
    static constexpr int darkgrey = 0xa9a9a9;
    static constexpr int darkkhaki = 0xbdb76b;
    static constexpr int darkmagenta = 0x8b008b;
    static constexpr int darkolivegreen = 0x556b2f;
    static constexpr int darkorange = 0xff8c00;
    static constexpr int darkorchid = 0x9932cc;
    static constexpr int darkred = 0x8b0000;
    static constexpr int darksalmon = 0xe9967a;
    static constexpr int darkseagreen = 0x8fbc8f;
    static constexpr int darkslateblue = 0x483d8b;
    static constexpr int darkslategray = 0x2f4f4f;
    static constexpr int darkslategrey = 0x2f4f4f;
    static constexpr int darkturquoise = 0x00ced1;
    static constexpr int darkviolet = 0x9400d3;
    static constexpr int deeppink = 0xff1493;
    static constexpr int deepskyblue = 0x00bfff;
    static constexpr int dimgray = 0x696969;
    static constexpr int dimgrey = 0x696969;
    static constexpr int dodgerblue = 0x1e90ff;
    static constexpr int firebrick = 0xb22222;
    static constexpr int floralwhite = 0xfffaf0;
    static constexpr int forestgreen = 0x228b22;
    static constexpr int fuchsia = 0xff00ff;
    static constexpr int gainsboro = 0xdcdcdc;
    static constexpr int ghostwhite = 0xf8f8ff;
    static constexpr int gold = 0xffd700;
    static constexpr int goldenrod = 0xdaa520;
    static constexpr int gray = 0x808080;
    static constexpr int grey = 0x808080;
    static constexpr int green = 0x008000;
    static constexpr int greenyellow = 0xadff2f;
    static constexpr int honeydew = 0xf0fff0;
    static constexpr int hotpink = 0xff69b4;
    static constexpr int indianred = 0xcd5c5c;
    static constexpr int indigo = 0x4b0082;
    static constexpr int ivory = 0xfffff0;
    static constexpr int khaki = 0xf0e68c;
    static constexpr int lavender = 0xe6e6fa;
    static constexpr int lavenderblush = 0xfff0f5;
    static constexpr int lawngreen = 0x7cfc00;
    static constexpr int lemonchiffon = 0xfffacd;
    static constexpr int lightblue = 0xadd8e6;
    static constexpr int lightcoral = 0xf08080;
    static constexpr int lightcyan = 0xe0ffff;
    static constexpr int lightgoldenrodyellow = 0xfafad2;
    static constexpr int lightgray = 0xd3d3d3;
    static constexpr int lightgreen = 0x90ee90;
    static constexpr int lightgrey = 0xd3d3d3;
    static constexpr int lightpink = 0xffb6c1;
    static constexpr int lightsalmon = 0xffa07a;
    static constexpr int lightseagreen = 0x20b2aa;
    static constexpr int lightskyblue = 0x87cefa;
    static constexpr int lightslategray = 0x778899;
    static constexpr int lightslategrey = 0x778899;
    static constexpr int lightsteelblue = 0xb0c4de;
    static constexpr int lightyellow = 0xffffe0;
    static constexpr int lime = 0x00ff00;
    static constexpr int limegreen = 0x32cd32;
    static constexpr int linen = 0xfaf0e6;
    static constexpr int magenta = 0xff00ff;
    static constexpr int maroon = 0x800000;
    static constexpr int mediumaquamarine = 0x66cdaa;
    static constexpr int mediumblue = 0x0000cd;
    static constexpr int mediumorchid = 0xba55d3;
    static constexpr int mediumpurple = 0x9370db;
    static constexpr int mediumseagreen = 0x3cb371;
    static constexpr int mediumslateblue = 0x7b68ee;
    static constexpr int mediumspringgreen = 0x00fa9a;
    static constexpr int mediumturquoise = 0x48d1cc;
    static constexpr int mediumvioletred = 0xc71585;
    static constexpr int midnightblue = 0x191970;
    static constexpr int mintcream = 0xf5fffa;
    static constexpr int mistyrose = 0xffe4e1;
    static constexpr int moccasin = 0xffe4b5;
    static constexpr int navajowhite = 0xffdead;
    static constexpr int navy = 0x000080;
    static constexpr int oldlace = 0xfdf5e6;
    static constexpr int olive = 0x808000;
    static constexpr int olivedrab = 0x6b8e23;
    static constexpr int orange = 0xffa500;
    static constexpr int orangered = 0xff4500;
    static constexpr int orchid = 0xda70d6;
    static constexpr int palegoldenrod = 0xeee8aa;
    static constexpr int palegreen = 0x98fb98;
    static constexpr int paleturquoise = 0xafeeee;
    static constexpr int palevioletred = 0xdb7093;
    static constexpr int papayawhip = 0xffefd5;
    static constexpr int peachpuff = 0xffdab9;
    static constexpr int peru = 0xcd853f;
    static constexpr int pink = 0xffc0cb;
    static constexpr int plum = 0xdda0dd;
    static constexpr int powderblue = 0xb0e0e6;
    static constexpr int purple = 0x800080;
    static constexpr int red = 0xff0000;
    static constexpr int rosybrown = 0xbc8f8f;
    static constexpr int royalblue = 0x4169e1;
    static constexpr int saddlebrown = 0x8b4513;
    static constexpr int salmon = 0xfa8072;
    static constexpr int sandybrown = 0xf4a460;
    static constexpr int seagreen = 0x2e8b57;
    static constexpr int seashell = 0xfff5ee;
    static constexpr int sienna = 0xa0522d;
    static constexpr int silver = 0xc0c0c0;
    static constexpr int skyblue = 0x87ceeb;
    static constexpr int slateblue = 0x6a5acd;
    static constexpr int slategray = 0x708090;
    static constexpr int slategrey = 0x708090;
    static constexpr int snow = 0xfffafa;
    static constexpr int springgreen = 0x00ff7f;
    static constexpr int steelblue = 0x4682b4;
    static constexpr int tan = 0xd2b48c;
    static constexpr int teal = 0x008080;
    static constexpr int thistle = 0xd8bfd8;
    static constexpr int tomato = 0xff6347;
    static constexpr int turquoise = 0x40e0d0;
    static constexpr int violet = 0xee82ee;
    static constexpr int wheat = 0xf5deb3;
    static constexpr int white = 0xffffff;
    static constexpr int whitesmoke = 0xf5f5f5;
    static constexpr int yellow = 0xffff00;
    static constexpr int yellowgreen = 0x9acd32;
};

#endif //GCRAZYSPINNER