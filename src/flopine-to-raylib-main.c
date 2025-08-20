// #include <raylib.h>
// #include <raymath.h>
//
// int main(void)
// {
//     const int SCREEN_WIDTH = 800;
//     const int SCREEN_HEIGHT = 450;
//     InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Shader - Flopine");
//
//     Shader shader = LoadShader(
//         "resources/shaders/glsl460/flopine.vs",
//         "resources/shaders/glsl460/flopine.fs"
//     );
//
//     float time = 0.0f;
//     Vector3 resolution = { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f };
//
//     int timeUniformLoc = GetShaderLocation(shader, "iTime");
//     int resolutionUniformLoc = GetShaderLocation(shader, "iResolution");
//
//     SetTargetFPS(60);
//
//     while (!WindowShouldClose())
//     {
//         time += GetFrameTime();
//         SetShaderValue(shader, timeUniformLoc, &time, SHADER_UNIFORM_FLOAT);
//         SetShaderValue(shader, resolutionUniformLoc, &resolution, SHADER_UNIFORM_VEC3);
//
//         BeginDrawing();
//         ClearBackground(RAYWHITE);
//         BeginShaderMode(shader);
//         DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
//         EndShaderMode();
//         EndDrawing();
//     }
//
//     UnloadShader(shader);
//     CloseWindow();
//     return 0;
// }