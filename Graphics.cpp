#include "raylib.h"
#include <cmath>
#include <cstdlib>

#include "Map.h"
#include "wave.h"
#include "Player.h"
#include "Tower.h"
#include "Enemy.h"

#include "Basicenemy.h"
#include "fastenemy.h"
#include "Tankenemy.h"
#include "peka.h"

#include "Canontower.h"
#include "Machinegun.h"
#include "Wizardtower.h"
#include "archertower.h"

int main() {
    InitWindow(800, 600, "Tower Defense");
    InitAudioDevice();
    SetTargetFPS(60);

    Texture2D texStart = LoadTexture("start_screen.png");
    Texture2D texBg = LoadTexture("map_background.png");
    Texture2D texTowerInfo = LoadTexture("tower_info.png");

    Texture2D texBarb = LoadTexture("enemy_barbarian.png");
    Texture2D texHog = LoadTexture("enemy_hogrider.png");
    Texture2D texCanonE = LoadTexture("enemy_canon.png");
    Texture2D texPeka = LoadTexture("enemy_peka.png");

    Texture2D texTCanon = LoadTexture("tower_canon.png");
    Texture2D texTMgun = LoadTexture("tower_machinegun.png");
    Texture2D texTWiz = LoadTexture("tower_wizard.png");
    Texture2D texTArch = LoadTexture("tower_archer.png");

    Music background = LoadMusicStream("background_music.mp3");
    PlayMusicStream(background);

    Rectangle btnStart = { 248, 230, 304, 44 };//x,y,width,height
    Rectangle btnMap = { 248, 316, 304, 44 };
    Rectangle btnInfo = { 248, 406, 304, 44 };

    int curScreen = 0;

    while (!WindowShouldClose()) {
        UpdateMusicStream(background);
        if (!IsMusicStreamPlaying(background)) {
            PlayMusicStream(background);
        }

        Vector2 mouse = GetMousePosition();
        bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        // ──────────── START SCREEN ────────────────────────────
        if (curScreen == 0) {
            if (IsKeyPressed(KEY_ENTER) || (click && CheckCollisionPointRec(mouse, btnStart)) || (click && CheckCollisionPointRec(mouse, btnMap))) {
                curScreen = 2;
            }

            if (IsKeyPressed(KEY_T) || (click && CheckCollisionPointRec(mouse, btnInfo))) {
                curScreen = 1;
            }
            BeginDrawing();
            DrawTexture(texStart, 0, 0, WHITE);
            EndDrawing();
            continue;//leave everything and go back the while
        }
        if (curScreen == 1) {
            Rectangle btnBack = { 300, 550, 200, 36 };

            if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE) || (click && CheckCollisionPointRec(mouse, btnBack))) {
                curScreen = 0;
            }

            BeginDrawing();
            DrawTexture(texTowerInfo, 0, 0, WHITE);

            bool hov = CheckCollisionPointRec(mouse, btnBack);
            Color backColor = hov ? Color{ 80, 60, 130, 230 } : Color{ 40, 30, 80, 220 };

            DrawRectangleRec(btnBack, backColor);
            DrawRectangleLinesEx(btnBack, 2, Color{ 212, 175, 55, 200 });

            const char* btnTxt = "< MAIN MENU";
            int tw = MeasureText(btnTxt, 18);
            DrawText(btnTxt, (int)btnBack.x + ((int)btnBack.width - tw) / 2, (int)btnBack.y + 9, 18, Color{ 240, 220, 100, 255 });

            EndDrawing();
            continue;
        }

        if (curScreen == 2) {
            int selectedMap = 0;

            while (!WindowShouldClose() && selectedMap == 0) {
                UpdateMusicStream(background);
                if (!IsMusicStreamPlaying(background)) {
                    PlayMusicStream(background);
                }

                if (IsKeyPressed(KEY_ONE)) selectedMap = 1;
                if (IsKeyPressed(KEY_TWO)) selectedMap = 2;
                if (IsKeyPressed(KEY_THREE)) selectedMap = 3;

                BeginDrawing();
                ClearBackground(BLACK);
                DrawText("SELECT MAP", 270, 80, 40, GOLD);
                DrawText("1 - Straight", 300, 190, 28, WHITE);
                DrawText("Short S-curve, easy", 300, 225, 16, GRAY);
                DrawText("2 - Zigzag", 300, 290, 28, WHITE);
                DrawText("Classic winding road", 300, 325, 16, GRAY);
                DrawText("3 - Spiral", 300, 390, 28, WHITE);
                DrawText("Long spiral, hardest", 300, 425, 16, GRAY);
                DrawText("Press 1, 2 or 3", 300, 520, 20, GREEN);
                EndDrawing();
            }

            if (WindowShouldClose()) break;

            Map map(selectedMap);
            wave w(&map);
            player pl(&map);

            int selectedTower = 1;
            bool gameOver = false;
            bool gameWon = false;

            while (!WindowShouldClose()) {
                UpdateMusicStream(background);
                if (!IsMusicStreamPlaying(background)) {
                    PlayMusicStream(background);
                }

                if (!gameOver && !gameWon) {
                    w.update();

                    enemy** enemies = w.getEnemies();
                    int total = w.getTotal();

                    tower** towers = pl.gettower();
                    int towerCount = pl.gettowercount();

                    // ── Enemy movement ──
                    for (int i = 0; i < total; i++) {
                        if (!enemies[i] || !enemies[i]->isalive()) continue;

                        if (enemies[i]->hasreachedend()) {
                            pl.loselife();
                            enemies[i]->takedamage(99999);
                            continue;
                        }

                        bool attacked = false;

                        for (int j = 0; j < towerCount; j++) {
                            if (!towers[j] || !towers[j]->isalive()) continue;

                            if (enemies[i]->towerinrange(towers[j])) {
                                enemies[i]->stop(towers[j]);
                                attacked = true;
                                break;
                            }
                        }

                        if (!attacked) {
                            enemies[i]->setstop();
                            enemies[i]->move();
                        }
                    }

                    pl.update(enemies, total);

                    if (IsKeyPressed(KEY_ONE)) selectedTower = 1;
                    if (IsKeyPressed(KEY_TWO)) selectedTower = 2;
                    if (IsKeyPressed(KEY_THREE)) selectedTower = 3;
                    if (IsKeyPressed(KEY_FOUR)) selectedTower = 4;

                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        Vector2 m = GetMousePosition();

                        if (m.y > 40 && m.y < 570) {
                            int grid = 40;
                            float sx = (float)((int)(m.x / grid) * grid + grid / 2);
                            float sy = (float)((int)(m.y / grid) * grid + grid / 2);

                            tower* t = nullptr;

                            if (selectedTower == 1) t = new canontower(sx, sy);
                            else if (selectedTower == 2) t = new machineguntower(sx, sy);
                            else if (selectedTower == 3) t = new wizardtower(sx, sy);
                            else if (selectedTower == 4) t = new archertower(sx, sy);

                            if (t && !pl.placetower(sx, sy, t)) delete t;
                        }
                    }

                    if (IsKeyPressed(KEY_U)) {
                        Vector2 m = GetMousePosition();
                        tower** t2 = pl.gettower();
                        int tc2 = pl.gettowercount();

                        for (int i = 0; i < tc2; i++) {
                            if (!t2[i] || !t2[i]->isalive()) continue;

                            float dx = t2[i]->getx() - m.x;
                            float dy = t2[i]->gety() - m.y;
                            float distance = sqrtf(dx * dx + dy * dy);

                            if (distance <= 30.0f) {
                                t2[i]->update(pl);
                                break;
                            }
                        }
                    }

                    if (pl.gameover()) gameOver = true;
                    if (w.getWave() > 4) gameWon = true;
                }

                // ─────────────── DRAW ────────────────────────
                BeginDrawing();

                if (gameOver) {
                    ClearBackground(BLACK);
                    DrawText("GAME OVER", 220, 220, 60, RED);
                    DrawText("Press ESC to quit", 270, 310, 24, GRAY);
                }
                else if (gameWon) {
                    ClearBackground(BLACK);
                    DrawText("YOU WIN!", 240, 220, 60, GREEN);
                    DrawText("All waves cleared!", 240, 310, 24, WHITE);
                    DrawText("Press ESC to quit", 270, 350, 24, GRAY);
                }
                else {
                    DrawTexture(texBg, 0, 0, WHITE);

                    // ── Path ──
                    const int pw = 40;
                    const int phw = pw / 2;
                    Color pathCol = { 139, 90, 43, 255 };
                    Color pathEdge = { 100, 60, 20, 180 };

                    for (int pi = 0; pi < map.getcount(); pi++) {
                        Path& mainpath = map.getpath(pi);

                        for (int j = 0; j < mainpath.size() - 1; j++) {
                            coor a = mainpath.get(j);
                            coor b = mainpath.get(j + 1);

                            int ax = a.getxaxis();
                            int ay = a.getyaxis();
                            int bx = b.getxaxis();
                            int by = b.getyaxis();

                            if (ay == by) {
                                int minX = (ax < bx) ? ax : bx;
                                int maxX = (ax > bx) ? ax : bx;
                                DrawRectangle(minX - phw, ay - phw, maxX - minX + pw, pw, pathCol);
                            }
                            else {
                                int minY = (ay < by) ? ay : by;
                                int maxY = (ay > by) ? ay : by;
                                DrawRectangle(ax - phw, minY - phw, pw, maxY - minY + pw, pathCol);
                            }
                        }

                        for (int j = 0; j < mainpath.size() - 1; j++) {
                            coor a = mainpath.get(j);
                            coor b = mainpath.get(j + 1);

                            int ax = a.getxaxis();
                            int ay = a.getyaxis();
                            int bx = b.getxaxis();
                            int by = b.getyaxis();

                            if (ay == by) {
                                int minX = (ax < bx) ? ax : bx;
                                int maxX = (ax > bx) ? ax : bx;
                                DrawLine(minX - phw, ay - phw, maxX + phw, ay - phw, pathEdge);
                                DrawLine(minX - phw, ay + phw, maxX + phw, ay + phw, pathEdge);
                            }
                            else {
                                int minY = (ay < by) ? ay : by;
                                int maxY = (ay > by) ? ay : by;
                                DrawLine(ax - phw, minY - phw, ax - phw, maxY + phw, pathEdge);
                                DrawLine(ax + phw, minY - phw, ax + phw, maxY + phw, pathEdge);
                            }
                        }
                    }

                    // ── Placement preview ──
                    Vector2 m = GetMousePosition();
                    if (m.y > 40 && m.y < 570) {
                        int grid = 40;
                        int mx = (int)(m.x / grid) * grid + grid / 2;
                        int my = (int)(m.y / grid) * grid + grid / 2;

                        Color c = GREEN;
                        if (pl.isonpath((float)mx, (float)my) || pl.overlapping((float)mx, (float)my) || pl.isoutofbounds((float)mx, (float)my)) {
                            c = RED;
                        }
                        DrawRectangle(mx - 15, my - 15, 30, 30, Fade(c, 0.45f));
                    }

                    // ── Enemies ──
                    enemy** enemies = w.getEnemies();
                    int total = w.getTotal();

                    for (int i = 0; i < total; i++) {
                        if (!enemies[i] || !enemies[i]->isalive()) continue;

                        float ex = enemies[i]->getx();
                        float ey = enemies[i]->gety();

                        Texture2D etex = texPeka;
                        string ename = enemies[i]->getname();
                        if (ename == "BARBARIAN") etex = texBarb;
                        else if (ename == "HOGRIDER") etex = texHog;
                        else if (ename == "CANON") etex = texCanonE;

                        DrawTextureEx(etex, { ex - 20, ey - 20 }, 0.0f, 0.3125f, WHITE);

                        float hpRatio = (float)enemies[i]->gethp() / enemies[i]->getmaxhp();
                        DrawRectangle((int)ex - 18, (int)ey - 28, 36, 5, DARKGRAY);
                        DrawRectangle((int)ex - 18, (int)ey - 28, (int)(36 * hpRatio), 5, GREEN);
                    }

                    tower** towers = pl.gettower();
                    int towerCount = pl.gettowercount();
                    Vector2 mpos = GetMousePosition();

                    for (int i = 0; i < towerCount; i++) {
                        if (!towers[i] || !towers[i]->isalive()){
                            continue;
                            }
                        float tx = towers[i]->getx();
                        float ty = towers[i]->gety();

                        Texture2D ttex = texTArch;
                        string tname = towers[i]->getname();
                        if (tname == "Canons") ttex = texTCanon;
                        else if (tname == "Machine Gun") ttex = texTMgun;
                        else if (tname == "WizardTower") ttex = texTWiz;

                        DrawTextureEx(ttex, { tx - 20, ty - 20 }, 0.0f, 0.3125f, WHITE);
                        DrawCircleLines((int)tx, (int)ty, (float)towers[i]->getrange(), Fade(SKYBLUE, 0.2f));

                        float dx = tx - mpos.x;
                        float dy = ty - mpos.y;
                        float distanceToTower = sqrtf(dx * dx + dy * dy);

                        if (distanceToTower <= 30.0f) {
                            DrawText(TextFormat("Lvl %d [U] upgrade", towers[i]->getlevel()), (int)tx - 30, (int)ty + 22, 10, YELLOW);
                        }
                    }

                    // ── HUD ──
                    DrawRectangle(0, 0, 800, 40, { 0, 0, 0, 200 });

                    DrawText(TextFormat("Gold:  %d", pl.getgold()), 10, 10, 20, GOLD);
                    DrawText(TextFormat("Lives: %d", pl.getlives()), 160, 10, 20, RED);
                    DrawText(TextFormat("Wave:  %d/5", w.getWave() + 1), 310, 10, 20, WHITE);

                    const char* towerNames[] = { "", "Canon", "MachineGun", "Wizard", "Archer" };
                    int towerCosts[] = { 0, 100, 75, 150, 80 };

                    DrawText(TextFormat("[%s %dg]", towerNames[selectedTower], towerCosts[selectedTower]), 460, 10, 18, GREEN);
                    DrawText("1-4 pick | U upgrade | click place", 580, 22, 11, LIGHTGRAY);
                }

                EndDrawing();

                if (WindowShouldClose()) goto cleanup;

            } // end game loop

            if (gameOver || gameWon) {
                while (!WindowShouldClose()) {
                    if (IsKeyPressed(KEY_ESCAPE)) break;

                    BeginDrawing();

                    if (gameOver) {
                        ClearBackground(BLACK);
                        DrawText("GAME OVER", 220, 220, 60, RED);
                        DrawText("Press ESC to quit", 270, 310, 24, GRAY);
                    }
                    else {
                        ClearBackground(BLACK);
                        DrawText("YOU WIN!", 240, 220, 60, GREEN);
                        DrawText("All waves cleared!", 240, 310, 24, WHITE);
                        DrawText("Press ESC to quit", 270, 350, 24, GRAY);
                    }

                    EndDrawing();
                }
            }

            curScreen = 0;

        } 
    } 

cleanup:

    UnloadTexture(texStart);
    UnloadTexture(texBg);
    UnloadTexture(texTowerInfo);
    UnloadTexture(texBarb);
    UnloadTexture(texHog);
    UnloadTexture(texCanonE);
    UnloadTexture(texPeka);
    UnloadTexture(texTCanon);
    UnloadTexture(texTMgun);
    UnloadTexture(texTWiz);
    UnloadTexture(texTArch);
    UnloadMusicStream(background);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}