#include <iostream>

#include "screen.h"

Screen::Screen(int height, int width):
    width(width),
    height(height),
    buffer(height, std::vector<Space>(width)) {

    std::cout << "\x1b[2J"; // Clear terminal
}

Screen::~Screen() {

}

void Screen::DrawBox(Color color, int x, int y) {
    DrawChar(color, x, y, ' ');
    DrawChar(color, x, y + 1, ' ');
}

void Screen::DrawChar(Color color, int x, int y, char ch) {
    buffer[x][y] = Space(ch, color, color);
}

void Screen::DrawString(Color color, int x, int y, const std::string & content) {
    const int len = content.length();
    for (int i = 0; i < len; i++) {
        DrawChar(color, x, y + i, content[i]);
    }
}

void Screen::Reset() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            buffer[i][j] = Space();
        }
    }
}

void Screen::Render() {
    std::cout << "\x1b[H"; // Move cursor to top left
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            const Space & space = buffer[i][j];
            switchBackground(space.bgColor);
            switchForeground(space.fgColor);
            std::cout << space.ch;
        }
        std::cout << std::endl;
    }
}
