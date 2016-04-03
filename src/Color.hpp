#ifndef __COLOR_HPP_INCLUDED
#define __COLOR_HPP_INCLUDED

class Color {
public:
    Color(int color = Color::EMPTY);

    void setColor(int color);
    int getColor();
    bool isValid();
    static bool isValid(int color);

    operator int() const;
    operator char() const;

    enum ColorTypes {
        BLACK = 'B',
        EMPTY = 'E',
        WHITE = 'W',
    };

private:
    int m_color;
};

#endif
