#pragma once

namespace math
{
    constexpr float e = 2.718281828459f;
    constexpr float pi = 3.1415926535897931f;
    constexpr float ln2 = 0.693147182464599609375f;
    constexpr float sqrt2 = 1.41421356237f;
    constexpr float pi_2 = pi * 0.5f;
    constexpr float pi_4 = pi * 0.25f;
    constexpr float tau = 2.0f * pi;
    constexpr float deg2rad = pi / 180.0f;
    constexpr float rad2deg = 180.0f / pi;

    float dot(FVector2f a, FVector2f b);
    float dot(FVector3f a, FVector3f b);
    float dot(FVector4f a, FVector4f b);
    float saturate(float v);
    float map01(float value, float min, float max);
    float invert_map_xy(float value, float min, float max, float new_min, float new_max);

    float inverse_lerp(float x, float y, float v);
    FVector3f cross(FVector3f a, FVector3f b);
    FVector2D xo(FVector2D v);
    FVector2D oy(FVector2D v);
    float angle_dir(FVector a, FVector b);

    FVector get_clamped_velocity_xz(FVector velocity, float clamped_size);

    float angle_between(FVector a, FVector b);
    FVector fvector_xy(FVector v);
    FVector normalize(FVector v);
    float quadratic(float v);
    float cubic(float v);
    float sqrt(float v);
    float linear(float v);
}
