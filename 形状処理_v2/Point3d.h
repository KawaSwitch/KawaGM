#pragma once

// Vector3dの残骸 一応残してる
struct Point3d
{
    double X, Y, Z;

    operator Vector3d()
    {
        return Point3d(X, Y, Z);
    }

    Point3d() { X = 0; Y = 0; Z = 0; }
    Point3d(double x, double y, double z) { X = x; Y = y; Z = z; }
};