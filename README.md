# DeadCityNights

**DeadCityNights** is a pixel art adventure game/platformer developed in C++ using raylib.  

## Features
- **Multiple Locations**: City streets, apartment, a cemetery, and more.
- **Combat**: Shoot zombies with guns.
- **Inventory System**: Collect items like car keys and a shovel.
- **NPC Dialog**: Randomized phrases from NPCs you encounter on the street.
- **Take Drugs**: Buy drugs off of a dealer on the street.
- **Shader Effect**: Different shader effects will play depending on the situation.
- **Voice Acting**: Custom made zombie grunts and moans.

![Screenshot of the game](ScreenShot0.png)

## Installation
The release is a very early alpha version. Unzip and run game.exe. Windows only for now. 

## Controls
Arrow keys left and right or A and D to move. Press up to interact with environment. Press up or click on NPCs to talk to them. Right click or F to aim. Left click or space while aiming to shoot. 1 selects handgun. 2 selects shotgun. 3 selects mac10. 

## Notes
I've been programming in python and making games in Godot with gd script for like 3 years. I've always wanted to learn C++ so I could eventually make bigger and better things. I thought a good way to learn C++ would be to make a game in it. I've seen people on the internet using raylib and I thought it would be perfect for my needs. I have used pygame a little in the past and knew how a game loop worked. I knew how classes worked from programming in python, so all this knowledge transfered over to cpp and raylib. The syntax is a little different but I'm still doing the same things I did in Godot I just dont have a GUI to place things in the world, and all the classes and structures I need to make myself, but I find that to be the fun part. Since this is my first thing in cpp I wanted to keep it simple and do what I know. So this game is like minimalist art. I started by taking a pixel art image I had made and slowly made it more and more interactive. I added a player character and a camera, then pedestrians, then other areas, and so on. 

There are eight different areas you can visit so far. The player character has an apartment and a car. You can use the car to drive to different areas like the park, or the cemetery. You encounter zombies in the cemetery as part of a story arc I'm working on. You combat zombies with two different types of guns. The revolver and the shotgun. Zombies rise from their grave on either side of the player when spawning in. This makes the combat a bit tricky and fun. I think at some point I want to add human enemies. Dudes with guns. But I'm still thinking about it. 

Besides the combat there are also NPCs to interact with. On main street of the game there are generic NPCs of different types that walk back and forth to different randomly set destinations. They will give one line greeting to the player. There are also special NPCs. Like the drug dealer, fortune teller, and police man. There is also a story character. A hobo who lives in the vacant lot by your apartment. He warns you about the zombies and gives you certain needed items. 

I make good use of shaders in the game. I've spent a lot of time experimenting with different effects. There is a vignette shader to give the game more atmosphere. A glitch shader that plays whenever zombies are spawning to give it some tension. When you take drugs from the drug dealer NPC there is a glow shader that gets activated to imply drug use. 

All the animations are done by using a big sprite sheet for each character. With different rows for each animation. I can then use code to select the correct row and cycle through the frames horizontally based on the animation state. The rest of the game is just a bunch of hand drawn textures rendered to the screen. I thought making a game with no engine would be harder, but it's not so bad. I miss being able to use a mouse to place things in the world. Other than that I sort of enjoy making it all with code from scratch.


I post about making the game on twitter. https://x.com/J_Hyde_
Check out the other games I have made. https://jhyde.itch.io