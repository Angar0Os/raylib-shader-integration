#include <raylib.h>
#include <raymath.h>

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

int main(void)
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 450;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cone Light");

    Camera camera = { 0 };
    camera.position = (Vector3){ 2.0f, 4.0f, 6.0f };   
    camera.target = (Vector3){ 0.0f, 0.5f, 0.0f };     
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };         
    camera.fovy = 45.0f;                               
    camera.projection = CAMERA_PERSPECTIVE;     

    
    Shader shader = LoadShader(
        "resources/shaders/glsl460/lighting.vs",
        "resources/shaders/glsl460/lighting.fs"
    );

    Model model = LoadModel("resources/model/traffic_cone/traffic_cone.gltf");
    Vector3 position = { 0.0f, 0.0f, 0.0f };

    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]){ 0.1f, 0.1f, 0.1f, 1.0f }, SHADER_UNIFORM_VEC4);

    Light lights[MAX_LIGHTS] = { 0 };
    lights[0] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, -2 }, Vector3Zero(), YELLOW, shader);
    lights[1] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, 2 }, Vector3Zero(), RED, shader);
    lights[2] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, 2 }, Vector3Zero(), GREEN, shader);
    lights[3] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, -2 }, Vector3Zero(), BLUE, shader);
    
    float time = 0.0f;

    Vector3 resolution = { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f };

    int timeUniformLoc = GetShaderLocation(shader, "iTime");
    int resolutionUniformLoc = GetShaderLocation(shader, "iResolution");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

        if (IsKeyPressed(KEY_Y)) { lights[0].enabled = !lights[0].enabled; }
        if (IsKeyPressed(KEY_R)) { lights[1].enabled = !lights[1].enabled; }
        if (IsKeyPressed(KEY_G)) { lights[2].enabled = !lights[2].enabled; }
        if (IsKeyPressed(KEY_B)) { lights[3].enabled = !lights[3].enabled; }

        for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(shader, lights[i]);

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                BeginShaderMode(shader);
                    DrawPlane(Vector3Zero(), (Vector2) { 10.0, 10.0 }, WHITE);
                    DrawModel(model, position, 1.0f, WHITE);
                EndShaderMode();
        
                for (int i = 0; i < MAX_LIGHTS; i++)
                {
                    if (lights[i].enabled) DrawSphereEx(lights[i].position, 0.2f, 8, 8, lights[i].color);
                    else DrawSphereWires(lights[i].position, 0.2f, 8, 8, ColorAlpha(lights[i].color, 0.3f));
                }

                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawFPS(10, 10);

            DrawText("Use keys [Y][R][G][B] to toggle lights", 10, 40, 20, DARKGRAY);

        EndDrawing();
    }

    UnloadModel(model);
    UnloadShader(shader); 

    CloseWindow();         

    return 0;
}
