#include "raylib.h"
#include <vector>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

// Joystick Durumu
Vector2 joyCenter = { 150, 570 };
Vector2 joyKnob = { 150, 570 };
bool isDragging = false;

void UpdateDrawFrame(void *arg) {
    // Dokunmatik Kontrol (Touch)
    Vector2 touchPos = GetMousePosition();
    
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        // Joystick Alanı Kontrolü
        if (CheckCollisionPointCircle(touchPos, joyCenter, 80) || isDragging) {
            isDragging = true;
            joyKnob = touchPos;
            // Oyuncuyu hareket ettir (Yön hesaplama)
            // playerPos.x += (joyKnob.x - joyCenter.x) * 0.001f;
        }
    } else {
        isDragging = false;
        joyKnob = joyCenter; // Bırakınca merkeze dön
    }

    BeginDrawing();
        ClearBackground(RAYWHITE);
        // ... 3D Çizimler ...

        // UI: Görsel Joystick
        DrawCircleV(joyCenter, 60, Fade(GRAY, 0.5f));
        DrawCircleV(joyKnob, 30, BLACK); // Hareket eden top
    EndDrawing();
}

