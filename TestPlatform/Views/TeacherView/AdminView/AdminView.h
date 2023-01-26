#pragma once
#include "Views/View.h"

class AdminView :
    public View
{
	public:
	void update() override;
	void render() override;
	private:
        bool Button000Pressed = false;
        bool Button001Pressed = false;
        bool Button002Pressed = false;
        bool Button003Pressed = false;
        bool Button004Pressed = false;
        bool Button005Pressed = false;
        bool Button006Pressed = false;

        Rectangle layoutRecs[7] = {
            { 24, 144, 240, 48 },
            { 336, 144, 240, 48 },
            { 648, 144, 240, 48 },
            { 1584, 144, 240, 48 },
            { 960, 144, 240, 48 },
            { 1272, 144, 240, 48 },
			{ 24, 220, 240, 48 },

        };
};

