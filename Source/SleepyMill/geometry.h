#pragma once

namespace geometry
{
    FVector3f closest_point_to_direction(FVector3f pointOrigin, FVector3f dir, FVector3f p);
    FVector2f rotate(FVector2f v, float radian);
    FIntVector2 world_to_grid_pos(FVector3f world_pos, int cell_size);
    FIntVector2 round_to_int(FVector2f world_pos_xy);
}
    
