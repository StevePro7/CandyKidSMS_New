#include "enemy_object.h"
#include "..\engine\enum_manager.h"

// DATA bank.
// Enemy Manager.
extern const unsigned char enemy_object_directions[] =
{
	direction_type_rght, direction_type_upxx, direction_type_down, direction_type_left,
	direction_type_rght, direction_type_down, direction_type_upxx, direction_type_left,
	direction_type_left, direction_type_upxx, direction_type_down, direction_type_rght,
	direction_type_left, direction_type_down, direction_type_upxx, direction_type_rght,
	direction_type_upxx, direction_type_rght, direction_type_left, direction_type_down,
	direction_type_down, direction_type_rght, direction_type_left, direction_type_upxx,
	direction_type_upxx, direction_type_left, direction_type_rght, direction_type_down,
	direction_type_down, direction_type_left, direction_type_rght, direction_type_upxx,
};