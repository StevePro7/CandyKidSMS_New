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

20/02/2020
01.
If invincible and death trees then allow to go on border but not wrap around
esp. if exits are closed - must only wrap around when exits public and in the exits

02.
Adi and Suz need to calc 2x tiles in front of CK - must ensure that these do not go outside
boundary of [0-13]



Tree rules
Avoid
Invincible or not
tree will block CK unless at exit and exits public he can go thru

Death
normal
he can go on any death tree and will die on stop
if exits and hes at public exit then can go thru like avoid

invincible
he can go thru all death trees in maze
however he will be blocked on border trees as they cannot kill him
have to do it this way otherwise the exits will not work as normal


IMPORTANT
I forgot about the gamer move + coll code in play screen that should be gamer Mgr
I forgot about the gamer move + coll code in play screen that should be gamer Mgr


22/02/2020
I updated all the move to Kid in cont screen and port to play screen
Just to check the performance I play the music and was slowing down on the stop() function
I thought this was because I implemented the basic collision checks there but
it was the code was printing out text onto the screen 3x
So just to bear this in mind when I integrate score this could potentially slow down the music...

TODO
Existing Suz attack algorithmn needs to factor in that Pro or Adi may not be moving
if that is the case then only use Kid as a guide OR
if Pro moving only then Kid or Pro OR
if Adi moving only then Kid or Adi


23/02/2020
Easy scatter option tiles = Pro, Adi, Suz
Hard scatter option tiles = Pro, Adi, Suz, Kid

Scatter rules:
enemy first scatter tile cannot be itself
i.e.
pro->scatter[0] != 0
adi->scatter[0] != 1
suz->scatter[0] != 2

TODO : test this point as *maybe* it might all be OK??
I don't believe that I want to have the same index for different Mamas to have the same target
i.e.
pro->scatter[1]	= 2
adi->scatter[1]	= 2

and finally the Mama previous scatter tile cannot be the same as the next one
including [0] and [3]

On Hard, Kid is a scatter tile option but let's not make it the first one...!
Also, am I going to have a wait option
wait,		// Warm up
tour,		// Scatter,
kill,		// Attack