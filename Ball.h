#pragma once
#include <cstdlib>  // rand()
#include <ctime>    // srand()
#include <cmath>    // sqrt(), atan2()
using namespace System;
using namespace System::Drawing;

class Ball {
private:
    int _x, _y;             
    float _dX, _dY;         
    int _size;              
    int _frameWidth, _frameHeight;  
    int _color;             

public:
    Ball(int frameWidth, int frameHeight) {
        _size = 20;
        _frameWidth = frameWidth;
        _frameHeight = frameHeight;
        _x = frameWidth / 2;
        _y = frameHeight / 2;
        _color = Color::Red.ToArgb();

        srand(time(0));
        do {
            _dX = (rand() % 21 - 10);
            _dY = (rand() % 21 - 10);
        } while (_dX == 0 && _dY == 0);
    }

    void setPos(int x, int y) { _x = x; _y = y; }
    float getdX() { return _dX; }
    float getdY() { return _dY; }
    void setSpeed(float dX, float dY) { _dX = dX; _dY = dY; }

    void move() {
        _x += _dX;
        _y += _dY;

        if (_x - _size < 0 || _x + _size > _frameWidth) {
            _dX = -_dX;
        }
        if (_y - _size < 0 || _y + _size > _frameHeight) {
            _dY = -_dY;
        }
    }

    void draw(Graphics^ g) {
        SolidBrush^ brush = gcnew SolidBrush(Color::FromArgb(_color));
        g->FillEllipse(brush, _x - _size, _y - _size, 2 * _size, 2 * _size);
    }
};
