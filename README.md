# so_long
A really simple 2d game made as a project for 42 school paris

# features
This game have mouse interactions for the menu, the tank controls and camera movement.\
It does vector arithmetic and more using a small library i wrote along with the [gcc/clang] vector extension.\
The engine i wrote allow the use of the delta time between frames to calibrate all calculations.\
It displays, updates and destroys entities using an oop approach.\
There is circle to circle collisions and circle to square collisions with pressure calculations going on between every entities.\
Only the entities close to the camera viewpoint are updated and displayed, nevertheless all the entities are destroyed at the end of the mainloop if the tag 'entity->alive' is set to '0'.\
The tank is painted by the blood of its crushed ennemies.

# Screenshots:
![MENU](https://github.com/ForAbby-X/so_long/blob/main/github_image/menu.png?raw=true)
![GAMEPLAY_1](https://github.com/ForAbby-X/so_long/blob/main/github_image/gameplay_1.png?raw=true)
![GAMEPLAY_2](https://github.com/ForAbby-X/so_long/blob/main/github_image/gameplay_2.png?raw=true)
