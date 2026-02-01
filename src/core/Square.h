#pragma once

#include <string>

class Square {
private:
    int index;
public:
    Square(int idx) ;
    int get_index() const;
    int get_rank() const ;
    int get_file() const;
    std::string to_string() const ;
};
