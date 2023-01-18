
#include "ptpch.h"
#include "Text.h"
Text::Text()
{
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.width = 0;
    rectangle.height = 0;
    letterCount = 0;
    key = 0;
    fontsize = 0;
    this->color = GRAY;
    state = false;
}
Text::Text(int x, int y, int szer, int wys, int fontSize)
{
    rectangle.x = x;
    rectangle.y = y;
    rectangle.width = szer;
    rectangle.height = wys;
    letterCount = 0;
    key = 0;
    fontsize = fontSize;
    this->color = GRAY;

}
Text::Text(int x, int y, int szer, int wys, int fontSize, std::string Text)
{
    rectangle.x = x;
    rectangle.y = y;
    rectangle.width = szer;
    rectangle.height = wys;
    letterCount = 0;
    key = 0;
    fontsize = fontSize;
    strcpy_s(text, Text.c_str());
    this->color = GRAY;
}
Text::Text(int x, int y, int szer, int wys, int fontSize, std::string Text, Color color)
{
    rectangle.x = x;
    rectangle.y = y;
    rectangle.width = szer;
    rectangle.height = wys;
    letterCount = 0;
    key = 0;
    fontsize = fontSize;
    strcpy_s(text, Text.c_str());
    this->color = color;

}
void Text::Edit(int x, int y, int szer, int wys, int fontSize, std::string Text)
{
    rectangle.x = x;
    rectangle.y = y;
    rectangle.width = szer;
    rectangle.height = wys;
    letterCount = 0;
    key = 0;
    fontsize = fontSize;
    this->color = GRAY;

    strcpy_s(text, Text.c_str());
}
void Text::ChangeString(std::string Text)
{
    strcpy_s(text, Text.c_str());
}
std::string Text::StringReturn()
{
    std::string str(text);
    return str;
}
void Text::setColor(Color color)
{
    this->color = color;
}
void Text::Write(Mouse m)
{
    if (CheckCollisionPointRec(m.input().position, rectangle))
    {
        key = GetCharPressed();
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (letterCount < 4999))
            {
                text[letterCount] = (char)key;
                text[letterCount + 1] = '\0';
                letterCount++;
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            text[letterCount] = '\n';
            text[letterCount + 1] = '\0';
            letterCount++;
        }
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            text[letterCount] = '\0';
        }
    }
}

void Text::Highlighting(Mouse m)
{
    if (CheckCollisionPointRec(m.input().position, rectangle))
    {
        if (m.input().state == 2 && state == true)
        {
            color = GREEN;
            state = false;
        }
        else if (m.input().state == 2 && state == false)
        {
            color = GRAY;
            state = true;
        }
    }
}

bool Text::IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();
    if ((key >= 32) && (key <= 126)) keyPressed = true;
    return keyPressed;
}

void Text::DrawText()
{
    //DrawRectangleRec(rectangle, LIGHTGRAY);
    DrawTextBoxedSelectable(GetFontDefault(), text, rectangle, fontsize, 2.0f, true, color, 0, 0, WHITE, BLACK);
}

void Text::DrawTextBoxedSelectable(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint)
{
    int length = TextLength(text);  // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0;          // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    float scaleFactor = fontSize / (float)font.baseSize;     // Character rectangle scaling factor

                                                             // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap ? MEASURE_STATE : DRAW_STATE;

    int startLine = -1;         // Index where to begin drawing (where a line begins)
    int endLine = -1;           // Index where to stop drawing (where a line ends)
    int lastk = -1;             // Holds last value of the character position

    for (int i = 0, k = 0; i < length; i++, k++)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n')
        {
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width * scaleFactor : font.glyphs[index].advanceX * scaleFactor;

            if (i + 1 < length) glyphWidth = glyphWidth + spacing;
        }


        if (state == MEASURE_STATE)
        {

            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth) > rec.width)
            {
                endLine = (endLine < 1) ? i : endLine;
                if (i == endLine) endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n') state = !state;

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        }
        else
        {
            if (codepoint == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width))
                {
                    textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize * scaleFactor) > rec.height) break;

                // Draw selection background
                bool isGlyphSelected = false;
                if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength)))
                {
                    Rectangle r = { rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize * scaleFactor };
                    DrawRectangleRec(r, selectBackTint);
                    isGlyphSelected = true;
                }

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                    Vector2 v = { rec.x + textOffsetX, rec.y + textOffsetY };
                    DrawTextCodepoint(font, codepoint, v, fontSize, isGlyphSelected ? selectTint : tint);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' ')) textOffsetX += glyphWidth;  // avoid leading spaces
    }
}
