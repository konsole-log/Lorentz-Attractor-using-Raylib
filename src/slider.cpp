#include "slider.h"
#include <raylib.h>
#include <raymath.h>
static float map(float value, float inMin, float inMax, float outMin, float outMax)
{
    if (inMax - inMin == 0)
        return outMin;
    return (value - inMin) / (inMax - inMin) * (outMax - outMin) + outMin;
}
void drawSlider(Slider s, const char *label)
{
    float handleX = map(s.currentVal, s.minVal, s.maxVal, s.x, s.x + s.width);
    float handleRadius = 8.0f;
    DrawRectangle(s.x, s.y, s.width, s.height, DARKGRAY);
    DrawRectangle(s.x, s.y, handleX - s.x, s.height, WHITE);
    DrawCircle(handleX, s.y + s.height / 2, handleRadius, WHITE);
    DrawText(label, s.x, s.y - 20, 20, WHITE);
    DrawText(TextFormat("%.2f", s.currentVal), s.x + s.width + 10, s.y - 5, 20, WHITE);
}
void updateSlider(Slider &s)
{
    Vector2 mouse = GetMousePosition();
    float trackLeft = s.x;
    float trackRight = s.x + s.width;
    float trackCenterY = s.y + s.height / 2;

    bool mouseInRange = (mouse.x >= trackLeft - 5 &&
                         mouse.x <= trackRight + 5 &&
                         mouse.y >= trackCenterY - 10 && mouse.y <= trackCenterY + 10);
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && (mouseInRange || s.isDragging))
    {
        s.isDragging = true;
        s.currentVal = map(mouse.x, trackLeft, trackRight, s.minVal, s.maxVal);
        s.currentVal = Clamp(s.currentVal, s.minVal, s.maxVal);
    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        s.isDragging = false;
    }
}