#ifndef INPUT_HPP // include guard
#define INPUT_HPP

#include <map>

class InputState {
    public:
        std::map<std::string, bool> keys;

        InputState () {
            keys["W"] = false;
            keys["A"] = false;
            keys["S"] = false;
            keys["D"] = false;
            keys["Left"] = false;
            keys["Right"] = false;
            keys["Escape"] = false;
        }
};


#endif /* INPUT_HPP */