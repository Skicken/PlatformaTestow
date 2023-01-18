#pragma once
#include <Utilities/Mouse.h>
class Text
{
private:
    char text[5000] = "\n";
    int letterCount;
    int key;
    int fontsize;
    Rectangle rectangle;
    Color color;
    bool state;

public:

    Text();
    Text(int x, int y, int szer, int wys, int fontSize);
    Text(int x, int y, int szer, int wys, int fontSize, std::string Text);
    Text(int x, int y, int szer, int wys, int fontSize, std::string Text, Color color);

    void Edit(int x, int y, int szer, int wys, int fontSize, std::string Text);
    void ChangeString(std::string Text);
    std::string StringReturn();
    void setColor(Color color);
    void Write(Mouse m);
    void Highlighting(Mouse m);
    bool IsAnyKeyPressed();

    void DrawText();
    void DrawTextBoxedSelectable(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);
};