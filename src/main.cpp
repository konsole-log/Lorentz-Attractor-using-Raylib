#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "slider.h"
#include "lorenz.h"
#include "draw.h"
using namespace std;
const int screenWidth = 1200;
const int screenHeight = 900;
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