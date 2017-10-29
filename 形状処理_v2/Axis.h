#pragma once

#include "GV.h"
#include "Object.h"

class Axis
{
protected:
    double _length; // ·³

public:
    Axis(double len) { _length = len; }
};

// CgglÌ²
class NormalAxis : public Axis
{
private:
    void DrawInternal();

public:
    NormalAxis(double len) : Axis(len) { }
    void Draw();
};