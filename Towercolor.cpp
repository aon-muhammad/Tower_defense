#include "Path.h"
#include "Entity.h"
#include "Tower.h"
#include "Enemy.h"
#include "Player.h"
#include "raylib.h"

void tower::color(Path& p, player& pl) {

    Vector2 mouse = GetMousePosition();
    int grid = 40;

    // snap to grid
    mouse.x = (float)((int)(mouse.x / grid) * grid);
    mouse.y = (float)((int)(mouse.y / grid) * grid);

    Color c = GREEN;

    // now ONLY one path check
    if (pl.isonpath(mouse.x, mouse.y) || pl.overlapping(mouse.x, mouse.y)) {
        c = RED;
    }

    DrawRectangle(
        (int)mouse.x - 15,
        (int)mouse.y - 15,
        30,
        30,
        Fade(c, 0.5f)
    );
}