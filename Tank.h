#pragma once

namespace Tmpl8
{
class grid;

enum allignments
{
    BLUE,
    RED
};

class Tank
{
  public:
    Tank(float pos_x, float pos_y, allignments allignment, Sprite* tank_sprite, Sprite* smoke_sprite, float tar_x, float tar_y, float collision_radius, int health, float max_speed, grid* grid);

    ~Tank();

    void Tick();

    vec2 Get_Position() const { return position; };
    float Get_collision_radius() const { return collision_radius; };
    bool Rocket_Reloaded() const { return reloaded; };

    void Reload_Rocket();

    void Deactivate();
    bool hit(int hit_value);

    void Draw(Surface* screen);

    int CompareHealth(const Tank& other) const;

    void Push(vec2 direction, float magnitude);

    void move(double x, double y);

    vec2 position;
    vec2 speed;
    vec2 target;

    int health;

    float collision_radius;
    vec2 force;

    float max_speed;
    float reload_time;

    bool reloaded;
    bool active;

    allignments allignment;

    int current_frame;
    Sprite* tank_sprite;
    Sprite* smoke_sprite;

    Tank* prev_;
    Tank* next_;

    grid* Grid;
};

}; // namespace Tmpl8