#include "screen.h"
#include <numeric>
#include <cmath>

struct vec3
{
    float x, y, z;
};

struct connection
{
    int a, b;
};

void rotate(vec3 &p, float ax, float ay, float az)
{
    // rotate around X
    {
        float rad = ax;
        float oldY = p.y, oldZ = p.z;
        p.y = cos(rad) * oldY - sin(rad) * oldZ;
        p.z = sin(rad) * oldY + cos(rad) * oldZ;
    }

    // rotate around Y
    {
        float rad = ay;
        float oldX = p.x, oldZ = p.z;
        p.x = cos(rad) * oldX + sin(rad) * oldZ;
        p.z = -sin(rad) * oldX + cos(rad) * oldZ;
    }

    // rotate around Z
    {
        float rad = az;
        float oldX = p.x, oldY = p.y;
        p.x = cos(rad) * oldX - sin(rad) * oldY;
        p.y = sin(rad) * oldX + cos(rad) * oldY;
    }
}

void line(Screen &screen, float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = std::sqrt(dx * dx + dy * dy);

    float angle = std::atan2(dy, dx);

    for (float i = 0; i < length; i++)
    {
        screen.pixel(x1 + std::cos(angle) * i,
                     y1 + std::sin(angle) * i);
    }
}

int SDL_main(int argc, char *argv[])
{
    Screen screen;

    std::vector<vec3> points{
        {100, 100, 100},
        {200, 100, 100},
        {200, 200, 100},
        {100, 200, 100},

        {100, 100, 200},
        {200, 100, 200},
        {200, 200, 200},
        {100, 200, 200}};

    std::vector<connection> connections{
        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7},

        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0},

        {4, 5},
        {5, 6},
        {6, 7},
        {7, 4}

    };

    // Caluclate centroid
    vec3 c{0, 0, 0};
    for (auto &p : points)
    {
        c.x += p.x;
        c.y += p.y;
        c.z += p.z;
    }
    c.x /= points.size();
    c.y /= points.size();
    c.z /= points.size();

    while (true)
    {
        for (auto &p : points)
        {
            p.x -= c.x;
            p.y -= c.y;
            p.z -= c.z;
            rotate(p, 0.02, 0.01, 0.04);
            p.x += c.x;
            p.y += c.y;
            p.z += c.z;
            screen.pixel(p.x, p.y);
        }
        for (auto &conn : connections)
        {
            line(screen,
                 points[conn.a].x,
                 points[conn.a].y,
                 points[conn.b].x,
                 points[conn.b].y);
        }
        screen.show();
        screen.clear();
        screen.input();
        SDL_Delay(30);
    }
    return 0;
}