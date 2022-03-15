#pragma once

class Object{
public:
    Object();
    ~Object();
protected:
    float x;
    float y;
    float rot;
    float x_delta;
    float y_delta;

public:
    void move(int vect_x, int vect_y);
    void rotate(int vect_rot);
    void render();
};
