#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <utility>

class Player
{
public:
    std::string name;
    int x, y;
    Player(std::string name, const int x, const int y): name(std::move(name)), x(x), y(y) {}
    Player(): x(0), y(0) {}

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(name, x, y);
    }
};

#endif //PLAYER_H
