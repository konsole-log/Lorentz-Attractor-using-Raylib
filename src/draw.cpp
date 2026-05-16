#include "draw.h"
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