#include "geometry.h"

#include "math.h"

FVector3f geometry::closest_point_to_direction(FVector3f pointOrigin, FVector3f dir, FVector3f p)
{
    dir.Normalize();
    FVector3f toPoint = p - pointOrigin;
    return pointOrigin + dir * math::dot(toPoint, dir);
}

FVector2f geometry::rotate(FVector2f v, float radian)
{
    float sin = FMath::Sin(radian);
    float cos = FMath::Cos(radian);

    float tx = v.X;
    float ty = v.Y;
    v.X = (cos * tx) - (sin * ty);
    v.Y = (sin * tx) + (cos * ty);
    return v;
}

FIntVector2 operator*(const FIntVector2& Lhs, int RHS)
{
    return {Lhs.X * RHS, Lhs.Y * RHS};
}

FIntVector2 geometry::world_to_grid_pos(FVector3f world_pos, int cell_size)
{
    FVector2f world_pos_xy = {world_pos.X, world_pos.Y};
    world_pos_xy /= cell_size;

    FIntVector2 world_pos_xy_round = geometry::round_to_int(world_pos_xy);
    return world_pos_xy_round * cell_size;
}

FIntVector2 geometry::round_to_int(FVector2f world_pos_xy)
{
    return {FMath::RoundToInt(world_pos_xy.X), FMath::RoundToInt(world_pos_xy.Y)};
}
