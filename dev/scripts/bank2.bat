@echo off
REM echo Generate levels

cd ..
cd banks
cd bank2

:: Tiles
::bmp2tile.exe raw\font_tiles.bmp -savetiles "font_tiles (tiles).psgcompr" -noremovedupes -planar -tileoffset 0  -savetilemap "font_tiles (tilemap).bin" -savepalette "font_tiles (palette).bin" -fullpalette -exit
::bmp2tile.exe raw\game_tiles.png -savetiles "game_tiles (tiles).psgcompr" -noremovedupes -planar -tileoffset 64 -savetilemap "game_tiles (tilemap).bin" -savepalette "game_tiles (palette).bin" -fullpalette -exit
bmp2tile.exe raw\main_tiles.png -savetiles "main_tiles (tiles).psgcompr" -noremovedupes -planar -tileoffset 64 -savetilemap "main_tiles (tilemap).bin" -savepalette "main_tiles (palette).bin" -fullpalette -exit
bmp2tile.exe raw\splash.bmp -savetiles "splash (tiles).psgcompr" -removedupes -nomirror -planar -tileoffset 128 -savetilemap "splash (tilemap).stmcompr" -savepalette "splash (palette).bin" -fullpalette -exit
bmp2tile.exe raw\screen.png -savetiles "screen (tiles).psgcompr" -removedupes -nomirror -planar -tileoffset 224 -savetilemap "screen (tilemap).stmcompr" -savepalette "screen (palette).bin" -fullpalette -exit

:: Sprites
:: https://github.com/maxim-zhao/bmp2tile
::bmp2tile.exe raw\sprites.png -savetiles "sprites (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "sprites (palette).bin" -fullpalette  -spritepalette -exit

cd ..
folder2c bank2 bank2 2
sdcc -c --no-std-crt0 -mz80 --Werror --opt-code-speed --constseg BANK2 bank2.c

del *.asm > nul; del *.lst > nul; del *.sym > nul

cd ..
cd scripts