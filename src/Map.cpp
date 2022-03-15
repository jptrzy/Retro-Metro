#include "Map.hpp"

Map::Map(){}
Map::~Map(){}

void Map::load(std::string path){
    this->size = this->width * this->height;
    this->tiles = new int[this->size];

    for(int i=0; i<this->size; i++){
        this->tiles[i]=0;
    }
    this->tiles[0]=1;
}