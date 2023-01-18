#include "ptpch.h"
#include "Button.h"

Button::Button()
{
    state = 0;
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.width = 0;
    rectangle.height = 0;
}

Button::Button(int x, int y, int szer, int wys)
{
    state = 0;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.width = szer;
    rectangle.height = wys;
}

Button::Button(int x, int y, int szer, int wys, Color color)
{
    state = 0;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.width = szer;
    rectangle.height = wys;
}


void Button::Edit(int x, int y, int szer, int wys)
{
    state = 0;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.width = szer;
    rectangle.height = wys;
}

bool Button::Click(Mouse m)
{
    if (CheckCollisionPointRec(m.input().position, rectangle))
    {
        switch (m.input().state) {
            case 0:
            case 1: state = 1; return false;
            case 2: state = 2; return true;
        }
    }
    else { state = 0; return false; };
}

void Button::DrawButton()
{
    if (state == 0) DrawRectangleRec(rectangle, WHITE);
    else if (state == 1) DrawRectangleRec(rectangle, DARKGRAY);
    else if (state == 2) DrawRectangleRec(rectangle, BLACK);
}
