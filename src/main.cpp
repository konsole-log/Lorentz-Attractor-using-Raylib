#include<iostream>
#include<raylib.h>
#include<vector>
using namespace std;

const int screenWidth=900;
const int screenHeight=600;

Vector3 lorenz(float &x,float &y,float &z,float rho,float beta,float sigma,float dt){
    float dxdt=sigma*(y-x);
    float dydt=x*(rho-z)-y;
    float dzdt=x*y-beta*z;
        
    x+=dxdt*dt;
    y+=dydt*dt;
    z+=dzdt*dt;
        
    Vector3 point={x,y,z};
    return point;
}
int main(){    
    //these values will be affected by slider later

    float sigma=10.0;
    float rho=28.0;
    float beta=8.0/3;
    float x=0.1,y=0.0,z=0.0;//initial values
    float dt=0.01;

    vector<Vector3> trail;
    trail.push_back({x,y,z});
    //Drawing will be here
    InitWindow(screenWidth,screenHeight,"LORENZ ATTRACTOR");
    SetTargetFPS(60);

    Camera camera = { 0 };
    camera.position   = {60.0f, 30.0f, 60.0f};
    camera.target     = {0.0f,  0.0f,  0.0f};
    camera.up         = {0.0f,  1.0f,  0.0f};
    camera.fovy       = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    while(!WindowShouldClose()){
        
        UpdateCamera(&camera,CAMERA_ORBITAL);
        //calculating dxdt, dydt, dzdt in each update
        Vector3 points=lorenz(x,y,z,rho,beta,sigma,dt);
        trail.push_back(points);

        if(trail.size()>500000){
            trail.erase(trail.begin());
        }
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode3D(camera);

                for(int i=1;i<trail.size();i++){
                    DrawLine3D(trail[i-1],trail[i],ColorLerp(RED,BLUE,3.0f));
                }
            
            //Labelling Axes
            DrawLine3D({0,0,0}, {60,0,0}, RED);   // X
            DrawLine3D({0,0,0}, {0,60,0}, GREEN); // Y
            DrawLine3D({0,0,0}, {0,0,60}, BLUE);  // Z
            EndMode3D();

        EndDrawing();
    }



    CloseWindow();
    return 0;
}