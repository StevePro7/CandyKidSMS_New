#include "main.h"

void main (void)
{
	// Global variables.
	//static bool global_pause;
	unsigned char open_screen_type;

	engine_asm_manager_clear_VRAM();
	devkit_SMS_init();
	devkit_SMS_displayOff();

	devkit_SMS_setSpriteMode( devkit_SPRITEMODE_NORMAL() );
	devkit_SMS_useFirstHalfTilesforSprites_False();
	devkit_SMS_VDPturnOnFeature( devkit_VDPFEATURE_HIDEFIRSTCOL() );

	engine_content_manager_load_tiles_font();
	engine_content_manager_load_tiles_game();
	//engine_content_manager_load_tiles_main();
	engine_content_manager_load_sprites_game();

	engine_hack_manager_init();
	engine_hack_manager_invert();

	//open_screen_type = screen_type_intro;
	//open_screen_type = screen_type_func;
	open_screen_type = screen_type_test;
	//open_screen_type = screen_type_dead;
	//open_screen_type = screen_type_over;
	//open_screen_type = screen_type_cont;
	open_screen_type = screen_type_play;

	engine_screen_manager_init( open_screen_type );
	devkit_SMS_displayOn();
	for( ;;)
	{
		devkit_SMS_initSprites();
		engine_input_manager_update();
		engine_screen_manager_update();

		devkit_SMS_finalizeSprites();
		devkit_SMS_waitForVBlank();
		devkit_SMS_copySpritestoSAT();

		// TODO if want to play music while game plays then would need to ROM bank before PSG frame
		devkit_SMS_mapROMBank( 7 );
		devkit_PSGFrame();
		devkit_PSGSFXFrame();
	}
}