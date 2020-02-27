#include "actor_manager.h"
#include "enemy_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "function_manager.h"
#include "gamer_manager.h"

// Public methods.
void engine_actor_manager_update()
{
}

void engine_actor_manager_exec_gamer_mover( unsigned char args )
{
	engine_gamer_manager_move( args );
}
void engine_actor_manager_exec_enemy_mover( unsigned char args )
{
	unsigned char direction;
	unsigned char enemy;

	engine_function_manager_convertByteToNibbles( args, &direction, &enemy );
	engine_enemy_manager_move( enemy, direction );
}
void engine_actor_manager_exec_gamer_speed( unsigned char args )
{
	args = 0;
}
void engine_actor_manager_exec_enemy_speed( unsigned char args )
{
	args = 0;
}