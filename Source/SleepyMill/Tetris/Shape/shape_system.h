#pragma once
#include "SleepyMill/flecs/flecs.h"
namespace flecs::ue
{
	struct entity_link_t;
}

namespace tetris
{
	struct shape_t;
	struct cell_t;
	struct cell_scale_t;
	struct cell_material_intensity_t;
}

namespace tetris
{	
	void shape_init(flecs::iter it, tetris::shape_t* shape_a, flecs::ue::entity_link_t* link_a);
	void cell_rotation(flecs::iter it, tetris::cell_t* cell_a, flecs::ue::entity_link_t* link_a);
	void cell_scale(flecs::iter it, tetris::cell_scale_t* cell_scale_a, flecs::ue::entity_link_t* link_a);
	void cell_material_intensity(flecs::iter it,  tetris::cell_t* cell_a, tetris::cell_material_intensity_t* cell_scale_a, flecs::ue::entity_link_t* link_a);
}
