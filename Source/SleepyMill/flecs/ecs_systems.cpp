#include "ecs_systems.h"

#include "ue_flecs.h"
#include "SleepyMill/Tetris/tetris_system.h"
#include "SleepyMill/Tetris/tetris_type.h"
#include "SleepyMill/Tetris/Cell/cell_type.h"
#include "SleepyMill/Tetris/Shape/shape_system.h"
#include "SleepyMill/Tetris/Shape/shape_type.h"
#include "SleepyMill/UI/ui_system.h"
#include "SleepyMill/UI/ui_type.h"

void ecs::init_system(flecs::world* world)
{
	world->system<tetris::shape_t ,flecs::ue::entity_link_t>().without<tetris::shape_init_t>().iter(tetris::shape_init);
	world->system<tetris::current_shape_t>().iter(tetris::current_shape_movement_system);
	world->system<tetris::cell_t, flecs::ue::entity_link_t>().iter(tetris::cell_rotation);
	world->system<tetris::cell_scale_t, flecs::ue::entity_link_t>().iter(tetris::cell_scale);
	world->system<tetris::cell_t, tetris::cell_material_intensity_t, flecs::ue::entity_link_t>().iter(tetris::cell_material_intensity);
	world->system<ui_t>().iter(ui::update_game_ui);
	
	world->system<tetris::tetris_score_t>().iter(tetris::score_update);
}
