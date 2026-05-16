#include <iostream>
#include <raylib.h>
#include <vector>
#include <math.h>
#include <raymath.h>
using namespace std;

const int screenWidth = 1200;
const int screenHeight = 900;
struct Slider
{
    float x, y;
    float width, height;
    float minVal, maxVal;
    float currentVal;
    bool isDragging;
};

float map(float value, float inMin, float inMax, float outMin, float outMax)
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
void drawBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
    // Bottom face
    DrawLine3D({minX, minY, minZ}, {maxX, minY, minZ}, GRAY);
    DrawLine3D({maxX, minY, minZ}, {maxX, minY, maxZ}, GRAY);
    DrawLine3D({maxX, minY, maxZ}, {minX, minY, maxZ}, GRAY);
    DrawLine3D({minX, minY, maxZ}, {minX, minY, minZ}, GRAY);

    // Top face
    DrawLine3D({minX, maxY, minZ}, {maxX, maxY, minZ}, GRAY);
    DrawLine3D({maxX, maxY, minZ}, {maxX, maxY, maxZ}, GRAY);
    DrawLine3D({maxX, maxY, maxZ}, {minX, maxY, maxZ}, GRAY);
    DrawLine3D({minX, maxY, maxZ}, {minX, maxY, minZ}, GRAY);

    // Vertical edges
    DrawLine3D({minX, minY, minZ}, {minX, maxY, minZ}, GRAY);
    DrawLine3D({maxX, minY, minZ}, {maxX, maxY, minZ}, GRAY);
    DrawLine3D({maxX, minY, maxZ}, {maxX, maxY, maxZ}, GRAY);
    DrawLine3D({minX, minY, maxZ}, {minX, maxY, maxZ}, GRAY);

    DrawLine3D({0, minY, 0}, {0, maxY, 0}, GRAY);
    DrawLine3D({minX, 0, 0}, {maxX, 0, 0}, GRAY);
    DrawLine3D({0, 0, minZ}, {0, 0, maxZ}, GRAY);
}
Vector3 lorenz(float &x, float &y, float &z, float rho, float beta, float sigma, float dt)
{
    float dxdt = sigma * (y - x);
    float dydt = x * (rho - z) - y;
    float dzdt = x * y - beta * z;

    x += dxdt * dt;
    y += dydt * dt;
    z += dzdt * dt;

    Vector3 point = {x, z - 25.0f, y};
    return point;
}
int main()
{

    // these values will be affected by slider later
    float sigma = 10.0;
    float rho = 28.0;
    float beta = 8.0 / 3;
    float x = 0.1, y = 0.0, z = 0.0; // initial values
    float dt = 0.01;

    Slider sigmaSlider;
    sigmaSlider.x = 20.0f;
    sigmaSlider.y = 100.0f;
    sigmaSlider.width = 200.0f;
    sigmaSlider.height = 6.0f;
    sigmaSlider.minVal = 0.0f;
    sigmaSlider.maxVal = 30.0f;
    sigmaSlider.currentVal = sigma;
    sigmaSlider.isDragging = false;

    Slider rhoSlider;
    rhoSlider.x = 20.0f;
    rhoSlider.y = 150.0f;
    rhoSlider.width = 200.0f;
    rhoSlider.height = 6.0f;
    rhoSlider.minVal = 0.0f;
    rhoSlider.maxVal = 30.0f;
    rhoSlider.currentVal = rho;
    rhoSlider.isDragging = false;

    Slider betaSlider;
    betaSlider.x = 20.0f;
    betaSlider.y = 200.0f;
    betaSlider.width = 200.0f;
    betaSlider.height = 6.0f;
    betaSlider.minVal = 0.0f;
    betaSlider.maxVal = 30.0f;
    betaSlider.currentVal = beta;
    betaSlider.isDragging = false;

    float minX = -50, maxX = 50;
    float minY = -50, maxY = 50;
    float minZ = -50, maxZ = 50;

    vector<Vector3> trail;
    trail.reserve(100000);
    // Drawing will be here
    InitWindow(screenWidth, screenHeight, "LORENZ ATTRACTOR");
    SetTargetFPS(60);

    Camera camera;
    camera.position = {120.0f, 120.0f, 200.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose())
    {

        UpdateCamera(&camera, CAMERA_ORBITAL);
        float prevSigma = sigma;
        float prevRho = rho;
        float prevBeta = beta;

        updateSlider(sigmaSlider);
        updateSlider(rhoSlider);
        updateSlider(betaSlider);

        sigma = sigmaSlider.currentVal;
        rho = rhoSlider.currentVal;
        beta = betaSlider.currentVal;

        if (sigma != prevSigma || rho != prevRho || beta != prevBeta)
        {
            trail.clear();
            x = 0.1f;
            y = 0.0f;
            z = 0.0f;
        }
        // calculating dxdt, dydt, dzdt in each update
        Vector3 points = lorenz(x, y, z, rho, beta, sigma, dt);
        trail.push_back(points);

        if (trail.size() > 50000)
        {
            trail.erase(trail.begin());
        }
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
        for (int i = 1; i < trail.size(); i++)
        {
            Color c;
            float t = (float)i / (float)trail.size();
            c = ColorLerp(GREEN, RED, t);
            DrawLine3D(trail[i - 1], trail[i], c);
        }

        // Labelling Axes
        drawBox(minX, minY, minZ, maxX, maxY, maxZ);
        EndMode3D();
        drawSlider(betaSlider, "Beta");
        drawSlider(rhoSlider, "Rho");
        drawSlider(sigmaSlider, "Sigma");
        EndDrawing();
    }

    CloseWindow();
    return 0;
}