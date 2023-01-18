#pragma once
class Mouse
{
    private:
    struct mouse {
        Vector2 position;
        int state;
    }mouseState;
    public:
    Mouse();
    void update();
    mouse input();



};
