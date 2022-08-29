//
// Created by twalla on 2022/08/29.
//

#ifndef __RECTANGLE_H_
#define __RECTANGLE_H_

#include "Point.h"

class Rectangle {
private:
    Point upLeft;
    Point lowRight;

public:
    Rectangle(const int &x1, const int &y1, const int &x2, const int &y2);
    void ShowRecInfo() const;
};

#endif //__RECTANGLE_H_
