
#include "Object.hpp"
#include "main.hpp"

Object::Object(){}
Object::~Object(){}

void Object::move(int vect_x, int vect_y){
    int map_i = ((int) (this->y + vect_y)) * map->width + ((int) (this->x + vect_x));
    if(map_i<map->size && map_i>-1 && map->tiles[map_i]!=0){
        this->y+=vect_y;
        this->x+=vect_x;
    }
}

void Object::rotate(int vect_rot){
    
}