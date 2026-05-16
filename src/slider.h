#pragma once
#include <raylib.h>

struct Slider
{
    float x, y;
    float width, height;
    float minVal, maxVal;
    float currentVal;
    bool isDragging;
};

void drawSlider(Slider s, const char *label);
void updateSlider(Slider &s);