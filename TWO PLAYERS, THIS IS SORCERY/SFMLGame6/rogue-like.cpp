#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "draw_tile.h"

class tile
{
public:
	int colour;
	int xmin;
	int xmax;
	int ymin;
	int ymax;
	int xmin2;
	int xmax2;
	int ymin2;
	int ymax2;
};

int direction;
int direction2;

class sprite //the sprite class
{
public:

	int tilex;
	int tiley;
	int xmin;
	int ymin;
	sf::Sprite sprite_s;
	sf::Texture sprite_t;

};

class spritaroo
{
public:

	int tilex2;
	int tiley2;
	int xmin2;
	int ymin2;
	sf::Sprite sprite_d;
	sf::Texture sprite_y;

};

const int grid_x = 16;
const int grid_y = 16;
tile grid[grid_x][grid_y];
int maze_[16][16];

int main()
{

	int maze[] =
	{
		12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
		12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,
		12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,
		12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,
		12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,
		12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,
		12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,
		12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,
		12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,
		12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,
		12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,
		12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,
		12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,
		12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,
		12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,
		12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
	};

	for (int x = 0; x < grid_x; x++) {
		for (int y = 0; y < grid_y; y++) {
			grid[x][y].xmin = ((x % 16)) * 16;
			grid[x][y].xmax = ((x % 16) + 1) * 16;
			grid[x][y].ymin = ((y % 16) * 16);	///gets tile position
			grid[x][y].ymax = (((y % 16) + 1) * 16);
			grid[x][y].xmin2 = ((x % 16)) * 16;
			grid[x][y].xmax2 = ((x % 16) + 1) * 16;
			grid[x][y].ymin2 = ((y % 16) * 16);
			grid[x][y].ymax2 = (((y % 16) + 1) * 16);
		}
	}

	for (int i = 0; i < (grid_x*grid_y); i++) {
		int j = i%grid_x;
		grid[j][(i - j) / grid_y].colour = maze[i];
	}
	sprite mc;
	spritaroo mc2;
	if (!mc.sprite_t.loadFromFile("basictiles.png", sf::IntRect(0, 144, 128, 16)))
		mc.tilex = 5;
	if (!mc2.sprite_y.loadFromFile("basictiles.png", sf::IntRect(0, 144, 128, 16)))
		mc.tiley = 14;
	mc.tilex = 1; //for some reason the first assignment does not register
	mc.tiley = 14;
	mc2.tiley2 = 12;
	mc2.tilex2 = 2;
	mc.xmin = grid[1][14].xmin;
	mc.ymin = grid[1][14].ymin;
	mc2.xmin2 = grid[1][14].xmin2;
	mc2.ymin2 = grid[1][14].ymin2;
	mc.sprite_s.setTexture(mc.sprite_t);
	mc.sprite_s.setTextureRect(sf::IntRect(32, 0, 16, 16));
	mc2.sprite_d.setTexture(mc2.sprite_y);
	mc2.sprite_d.setTextureRect(sf::IntRect(32, 0, 16, 16));
	sf::RenderWindow window(sf::VideoMode(512, 256), "Maze");
	window.setFramerateLimit(13);

	int turn = 3; //turns to change texture based on direction
	int turn2 = 3;
	mc2.xmin2 = mc2.xmin2 + 16;
	mc2.ymin2 = mc2.ymin2 - 32;

	draw_tile map;
	if (!map.load("basictiles.png", sf::Vector2u(16, 16), maze, 16, 16))
		return -1;
	// run the main loop
	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::W){
				if ((mc.tiley - 1 >= 0) && (grid[mc.tilex][mc.tiley - 1].colour == 11)){
					if (direction == 1)
					{
						mc.tiley--;
						mc.ymin = mc.ymin - 16;
						mc.sprite_s.setTexture(mc.sprite_t);
					}
					if (turn != 0) { mc.sprite_s.setTextureRect(sf::IntRect(64, 0, 16, 16)); turn = 0; };  //changes to appropiate texture at a turn
					direction = 1;
				}
			}
			else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::S){
				if ((mc.tiley + 1 <= grid_y) && (grid[mc.tilex][mc.tiley + 1].colour == 11)){
					if (direction == 2)
					{
						mc.tiley++;
						mc.ymin = mc.ymin + 16;
						mc.sprite_s.setTexture(mc.sprite_t);
					}
					if (turn != 1) { mc.sprite_s.setTextureRect(sf::IntRect(0, 0, 16, 16)); turn = 1; };
					direction = 2;
				}
			}
			else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::A){
				if ((mc.tilex - 1 >= 0) && (grid[mc.tilex - 1][mc.tiley].colour == 11)){
					if (direction == 3)
					{
						mc.tilex--;
						mc.xmin = mc.xmin - 16;
						mc.sprite_s.setTexture(mc.sprite_t);
					}
					if (turn != 2) { mc.sprite_s.setTextureRect(sf::IntRect(96, 0, 16, 16)); turn = 2; };
					direction = 3;
				}
			}
			else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::D){
				if ((mc.tilex + 1 <= grid_x) && (grid[mc.tilex + 1][mc.tiley].colour == 11)){
					if (direction == 4)
					{
						mc.tilex++;
						mc.xmin = mc.xmin + 16;
						mc.sprite_s.setTexture(mc.sprite_t);
					}
					if (turn != 3) { mc.sprite_s.setTextureRect(sf::IntRect(32, 0, 16, 16)); turn = 3; };
					direction = 4;
				}
			}
			if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Up){
				if ((mc2.tiley2 - 1 >= 0) && (grid[mc2.tilex2][mc2.tiley2 - 1].colour == 11)){
					if (direction2 == 1)
					{
						mc2.tiley2--;
						mc2.ymin2 = mc2.ymin2 - 16;
						mc2.sprite_d.setTexture(mc2.sprite_y);
					}
					if (turn2 != 0) { mc2.sprite_d.setTextureRect(sf::IntRect(64, 0, 16, 16)); turn2 = 0; };  //changes to appropiate texture at a turn
					direction2 = 1;
				}
			}
			else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Down){
				if ((mc2.tiley2 + 1 <= grid_y) && (grid[mc2.tilex2][mc2.tiley2 + 1].colour == 11)){
					if (direction2 == 2)
					{
						mc2.tiley2++;
						mc2.ymin2 = mc2.ymin2 + 16;
						mc2.sprite_d.setTexture(mc2.sprite_y);
					}
					if (turn2 != 1) { mc2.sprite_d.setTextureRect(sf::IntRect(0, 0, 16, 16)); turn2 = 1; };
					direction2 = 2;
				}
			}
			else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Left){
				if ((mc2.tilex2 - 1 >= 0) && (grid[mc2.tilex2 - 1][mc2.tiley2].colour == 11)){
					if (direction2 == 3)
					{
						mc2.tilex2--;
						mc2.xmin2 = mc2.xmin2 - 16;
						mc2.sprite_d.setTexture(mc2.sprite_y);
					}
					if (turn2 != 2) { mc2.sprite_d.setTextureRect(sf::IntRect(96, 0, 16, 16)); turn2 = 2; };
					direction2 = 3;
				}
			}
			else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Right){
				if ((mc2.tilex2 + 1 <= grid_x) && (grid[mc2.tilex2 + 1][mc2.tiley2].colour == 11)){
					if (direction2 == 4)
					{
						mc2.tilex2++;
						mc2.xmin2 = mc2.xmin2 + 16;
						mc2.sprite_d.setTexture(mc2.sprite_y);
					}
					if (turn2 != 3) { mc2.sprite_d.setTextureRect(sf::IntRect(32, 0, 16, 16)); turn2 = 3; };
					direction2 = 4;
				}
			}


			if (event.type == sf::Event::Closed)
				window.close();

		}

		// draw the map
		window.clear(sf::Color::White);
		mc.sprite_s.setPosition(mc.xmin, mc.ymin);
		mc2.sprite_d.setPosition(mc2.xmin2, mc2.ymin2);
		window.draw(map);
		window.draw(mc.sprite_s);
		window.draw(mc2.sprite_d);
		window.display();
	}

	return 0;
}
