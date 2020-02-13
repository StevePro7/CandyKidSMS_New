#ifndef _COMMAND_MANAGER_H_
#define _COMMAND_MANAGER_H_

// Public methods.
void engine_command_manager_init();
// TODO do I need this method to determine the command type?
//unsigned char engine_command_manager_type( unsigned int frame, unsigned char command_type );
void engine_command_manager_add( unsigned int frame, unsigned char command_type, unsigned char args );

void engine_command_manager_execute( unsigned int frame );
void engine_command_manager_undo( unsigned int frame );
void engine_command_manager_play( unsigned int frame );
//void engine_command_manager_undoX( unsigned int frame );

void engine_command_manager_load( unsigned int* frames, unsigned char* commands, unsigned char* args );

#endif//_COMMAND_MANAGER_H_