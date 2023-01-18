#pragma once
#include "Utilities/Mouse.h"
class Button
{
    Rectangle rectangle;
    int state;
    public:
        Button();
        Button(int x, int y, int szer, int wys);
        Button(int x, int y, int szer, int wys,Color color);
        void Edit(int x, int y, int szer, int wys);
        bool Click(Mouse m);
        void DrawButton();
};