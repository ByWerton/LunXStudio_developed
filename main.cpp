#include "raylib.h"
#include <emscripten.h>

// Değişkenler
Camera3D camera = { 0 };
Vector3 gunPos = { 0.5f, -0.5f, 1.5f };

void UpdateDrawFrame() {
    // Mobil Dokunuş / Mouse Kontrolü
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Ateş etme efekti: Silahı geri tepme yaptır
        gunPos.z = 1.2f; 
    }
    gunPos.z = Lerp(gunPos.z, 1.5f, 0.1f); // Silahı geri yerine getir

    BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);
            // Yer düzlemi
            DrawPlane((Vector3){ 0, 0, 0 }, (Vector2){ 50, 50 }, DARKGRAY);
            // Hedefler (Kutular)
            DrawCube((Vector3){ 0, 1, 5 }, 2, 2, 2, RED);
            DrawCubeWires((Vector3){ 0, 1, 5 }, 2, 2, 2, MAROON);
        EndMode3D();

        // 2D Arayüz (Silah)
        DrawRectangle(GetScreenWidth()/2 + 20, GetScreenHeight() - 150, 40, 150, GRAY); // Basit silah temsili
        DrawCircle(GetScreenWidth()/2, GetScreenHeight()/2, 5, GREEN); // Crosshair
        
        DrawText("ATES ETMEK ICIN DOKUN", 10, 50, 20, RAYWHITE);
    EndDrawing();
}

int main() {
    InitWindow(800, 450, "LunX 3D Game");
    
    // Kamera ayarları
    camera.position = (Vector3){ 0.0f, 2.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Tarayıcı döngüsü
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
    return 0;
}
