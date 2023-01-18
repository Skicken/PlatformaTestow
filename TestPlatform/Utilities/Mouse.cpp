#include "ptpch.h"
#include "Mouse.h"

Mouse::Mouse()
{
    mouseState.position = { 0.0, 0.0 };
    mouseState.state = 0;
}

void Mouse::update()
{
    mouseState.position = GetMousePosition();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) mouseState.state = 1;
    else  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) mouseState.state = 2;
    else mouseState.state = 0;
}

Mouse::mouse Mouse::input() { return mouseState; }
