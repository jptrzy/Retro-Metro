
#include <string>

class Map{
public:
    Map();
    ~Map();
public:
    int width;
    int height;
    int size;

    int *tiles = nullptr;
public:
    void load(std::string path);
};
