#pragma once
#pragma once
#include "../View.h"

#include <System.h>
class TeacherMenu :
    public View
{

public:
    virtual void update() override;
	virtual void render() override;
    TeacherMenu();
	private:
       //----------------------------------------------------------------------------------
    bool Button000Pressed = false;
    bool Button001Pressed = false;
    bool Button002Pressed = false;
    bool Button003Pressed = false;
    bool Button004Pressed = false;
    bool Button005Pressed = false;

    Rectangle layoutRecs[6] = {
        { 24, 144, 240, 48 },
        { 336, 144, 240, 48 },
        { 648, 144, 240, 48 },
        { 1584, 144, 240, 48 },
        { 960, 144, 240, 48 },
        { 1272, 144, 240, 48 },
    };
};