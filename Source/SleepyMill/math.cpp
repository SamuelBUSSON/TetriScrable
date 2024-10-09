#include "math.h"

namespace math
{
    float dot(FVector2f a, FVector2f b)
    {
        return a.X * b.X + a.Y * b.Y;
    }

    float dot(FVector3f a, FVector3f b)
    {
        return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
    }

    float dot(FVector4f a, FVector4f b)
    {
        return a.X * b.X + a.Y * b.Y + a.Z * b.Z + a.W * b.W;
    }

    FVector3f cross(FVector3f a, FVector3f b)
    {
        return FVector3f(
            a.Y * b.Z - a.Z * b.Y,
            a.Z * b.X - a.X * b.Z,
            a.X * b.Y - a.Y * b.X);
    }

    float angle_dir(FVector a, FVector b)
    {
        return -a.X * b.Y + a.Y * b.X;
    }

    FVector get_clamped_velocity_xz(FVector velocity, float clamped_size)
    {
        FVector velocity_xy = FVector(velocity.X, velocity.Y, 0);
        FVector velocity_z = velocity.Z * FVector::UpVector;
        velocity_xy = velocity_xy.GetClampedToMaxSize(clamped_size);
        return velocity_xy + velocity_z;
    }

    float saturate(float v)
    {
        return v < 0.0f ? 0.0f : (v > 1.f ? 1.f : v);
    }

    float map01(float value, float min, float max)
    {
        float value01 = (value - min) / (max - min);
        return saturate(value01);
    }

    float invert_map_xy(float value, float min, float max, float new_min, float new_max)
    {
        return (((value - min) / (max - min)) * (new_min - new_max)) + new_max;
    }

    float inverse_lerp(float x, float y, float v)
    {
        return (v - x) / (y - x);
    }

    FVector2D xo(FVector2D v)
    {
        return {v.X, 0};
    }

    FVector2D oy(FVector2D v)
    {
        return {0, v.Y};
    }

    float angle_between(FVector a, FVector b)
    {
        a.Normalize();
        b.Normalize();

        float cos_diff = a.X * b.X + a.Y * b.Y;
        float sin_diff = a.Y * b.X - a.X * b.Y;

        return FMath::Atan2(sin_diff, cos_diff);
    }

    FVector fvector_xy(FVector v)
    {
        v.Z = 0;
        return v;
    }

    FVector normalize(FVector v)
    {
        return v.GetSafeNormal();
    }

    float quadratic(float v)
    {
        return v * v;
    }

    float cubic(float v)
    {
        return v * v * v;
    }

    float sqrt(float v)
    {
        return FMath::Sqrt(v);
    }

    float linear(float v)
    {
        return v;
    }
}
