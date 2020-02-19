# CandyKidSMS_New
New Candy Kid for the Sega Master System


14/02/2020
move manager
storage manager integrate w/o the commands save??
splash screen integrate as before			DONE
board + level manager consolidate tiles to move		used by move manager
actor speed, gamer boost, enemy 2x vels
undo mid update()
score mgr	boost, lives, score, hiscore
NB: allow long for HI into storage mgr
sprites and alter ego	i.e. alternative sprites
beat screen						DONE


15/02/2020
load screen	regression test all the levels
score mgr implement
title screen ressurrect from graphics test
refactor the delay / frame mgr in game play to debug mgr??

IMPORTANT
I need to change the coll_type for trees if there are death trees
because if CK hits one and dies then tree [in maze] will disappear
AND now the CMs can navigate to this tile because coll_type = 0

Therefore, will have to put check in place for CMs to ensure they
don't go outside or hit border by comparing tile X+Y rather than
check the coll_type with trees on the border


TODO
simple - add state Mgr that sets the default hi score if none saved before

Difficulty
easy
lives	4
boost	slow

hard
lives	3
boost	fast depletion


Game speed
CK
CM


16/02/2020
Today did the storage manager
don't forget to put in a cheat that will allow you to reset / erase the store object


19/02/2020
TODO
remove the code that determines all the tiles that can be moved to from this tile
In theory, this is now no longer required because I use the collision type to determine this
In fact - I don't need to set the collision type because I can just check if the tile = '1'
i.e. is a tree then an actor should not go into that tile...
