#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <vector>
#include <string>

#include "io.h"

struct Space {
    char ch;
    Color fgColor;
    Color bgColor;
    Space() {
        ch = ' ';
        fgColor = COLOR_RESET;
        bgColor = COLOR_RESET;
    }
    Space(char ch, Color fgColor, Color bgColor):
        ch(ch), fgColor(fgColor), bgColor(bgColor) {}
};

class Screen {
    std::vector< std::vector<Space> > buffer;
    int width;
    int height;
public:
    Screen(int width, int height);
    ~Screen();
    void DrawBox(Color color, int x, int y);
    void DrawChar(Color color, int x, int y, char ch);
    void DrawString(Color color, int x, int y, const std::string & content);
    void Reset();
    void Render();
};

#endif