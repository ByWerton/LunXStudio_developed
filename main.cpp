#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <string>

// --- Sabitler ve Ayarlar ---
const int ScreenWidth = 1280;
const int ScreenHeight = 720;

// Obje Tipleri
enum BlockType { BASEPLATE, GRASS, WOOD, STONE, IRON, CONCRETE, WATER };

struct GameObject {
    Vector3 position;
    Vector3 size;
    BlockType type;
    Texture2D texture;
};

// --- Motor Sınıfı ---
class LunXEngine {
public:
    Camera3D camera;
    std::vector<GameObject> worldObjects;
    Texture2D textures[10]; // Dokuları tutan dizi

    void Initialize() {
        InitWindow(ScreenWidth, ScreenHeight, "LunX Studio Ultra - Engine");
        
        // Kamera Ayarları (Roblox Studio Stilinde)
        camera.position = (Vector3){ 20.0f, 20.0f, 20.0f };
        camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
        camera.fovy = 60.0f;
        camera.projection = CAMERA_PERSPECTIVE;

        // Dokuları Yükle (Burada senin linklerindeki dosyaların indirildiğini varsayıyoruz)
        LoadAssets();
        
        // Dünyayı Oluştur (Baseplate)
        worldObjects.push_back({(Vector3){0, -0.5f, 0}, (Vector3){100, 1, 100}, BASEPLATE, textures[0]});
        
        SetTargetFPS(60);
        DisableCursor(); // Fareyi kilitle (Studio modu)
    }

    void LoadAssets() {
        // Not: Gerçek projede bu dosyalar 'assets/' klasöründe olmalı
        textures[0] = LoadTexture("baseplate.png");
        textures[1] = LoadTexture("grass.png");
        textures[2] = LoadTexture("stone.png");
        textures[3] = LoadTexture("wood.png");
        textures[4] = LoadTexture("water_frame.png"); // GIF'in ilk karesi
    }

    void Update() {
        UpdateCamera(&camera, CAMERA_FREE); // WASD + Fare kontrolü
        
        // Obje Ekleme (Sol Tık - Roblox'taki gibi blok koyma simülasyonu)
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            worldObjects.push_back({camera.target, (Vector3){2, 2, 2}, GRASS, textures[1]});
        }
    }

    void Draw() {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode3D(camera);
            
            // Tüm objeleri çiz
            for (const auto& obj : worldObjects) {
                DrawCubeTexture(obj.texture, obj.position, obj.size.x, obj.size.y, obj.size.z, WHITE);
                DrawCubeWires(obj.position, obj.size.x, obj.size.y, obj.size.z, Fade(BLACK, 0.3f));
            }

            DrawGrid(100, 1.0f); // Kılavuz çizgileri

        EndMode3D();

        // --- ULTRA UI (Arayüz) ---
        DrawRectangle(10, 10, 250, 150, Fade(BLACK, 0.5f));
        DrawText("LunX Studio: Ultra Dev", 20, 20, 20, GOLD);
        DrawText(TextFormat("Objeler: %i", worldObjects.size()), 20, 50, 15, WHITE);
        DrawText("Hareket: WASD | Çıkış: ESC", 20, 80, 15, LIGHTGRAY);
        DrawCircle(ScreenWidth/2, ScreenHeight/2, 2, RED); // Crosshair

        EndDrawing();
    }

    void Shutdown() {
        for(int i=0; i<10; i++) UnloadTexture(textures[i]);
        CloseWindow();
    }
};

int main() {
    LunXEngine engine;
    engine.Initialize();

    while (!WindowShouldClose()) {
        engine.Update();
        engine.Draw();
    }

    engine.Shutdown();
    return 0;
}
