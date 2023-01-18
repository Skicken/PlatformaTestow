#pragma once
#include "MainMenu.h"
class StudentMenu :
    public MainMenu
{

    public:
    virtual void update() override;
    virtual void render() override;
    StudentMenu() = default;
    private:
};

