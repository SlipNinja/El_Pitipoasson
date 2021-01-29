
#include "../dep/raylib/raylib.h"
#include "../dep/randutils/randutils.hpp"

#include "player.cpp"
#include "item.cpp"
#include "enum_values.h"
#include "main.h"
#include "constants.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>

/*
TODO :
- add bad items ( remove life )
- add money/points sprite
- improve UI

- add defeat screen
- add ennemies ( AI ? )

- add music
- add sounds
- add background ( defilant-truc la )

LATER :
- in-game shop for spending points ?
- rogue-like ?
*/

static std::vector<Item> items;
static std::vector<int> items_to_delete;
static Player player;
static int frameCount;

int main()
{

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);// Initialize window and OpenGL context
	SetTargetFPS(FPS);

	//Player
	Vector2 startPosition = {100.0f, 200.0f};
	player.init(startPosition);

	frameCount = 0;

	// Check if KEY_ESCAPE pressed or Close icon pressed
	while(!WindowShouldClose()){

		AddItems();

		// Handles item gathering and oob
		UpdateItems();

		// Update
		player.update();

		// Draw
		BeginDrawing();

			//Clear
			ClearBackground(RAYWHITE);

			//Player
			player.draw();

			//Items
			for (Item item : items){
				item.draw();
			}

			//UI
			DrawUI(player.getValues());

		EndDrawing();
	}
	CloseWindow();// Close window and unload OpenGL context
	return 0;
}

void AddItems(){

	frameCount+=1;
	if (frameCount >= FRAMES_FOR_ITEM)
	//if (frameCount >= 20)
	{
		frameCount = 0;
		randutils::mt19937_rng rng;
		Values value = (Values)rng.uniform(0,int(Values::Count)-1);
		float scale = rng.uniform(SCALE_MIN, SCALE_MAX)/10.0f;
		float posx = rng.uniform(RADIUS_OFFSET, SCREEN_WIDTH-RADIUS_OFFSET);
		float speed = rng.uniform(SPEED_MIN, SPEED_MAX)/10.0f;
		float strength = BASE_STRENGHT*scale;

		// New item
		Effect effect (value, strength);
		Item item ({posx, -RADIUS_OFFSET}, scale, effect, speed);
		//Item item ({posx, 0}, scale, effect, speed);
		items.push_back(item);
	}

}

void UpdateItems(){
	items_to_delete.clear();
	for(int i=0; i < items.size(); i++){
		if(items[i].checkCollide(player.getPosition(), player.getRadius())){
			items[i].applyEffect(player.getValues());
			items_to_delete.push_back(i);
		} else if (IsOutOfBounds(items[i].getPosition())) {
			std::cout << "DELETE" << std::endl;
			items_to_delete.push_back(i);
		} else {
			items[i].update();
		}
	}

	//sort descending order
	std::sort(items_to_delete.begin(), items_to_delete.end(), std::greater<int>());

	for(int index_to_delete : items_to_delete){
		items.erase(items.begin() + index_to_delete);
	}
}

bool IsOutOfBounds(Vector2 pos){
	if (pos.x < -RADIUS_OFFSET*2
		|| pos.y < -RADIUS_OFFSET*2
		|| pos.x > SCREEN_WIDTH + RADIUS_OFFSET*2
		|| pos.y > SCREEN_HEIGHT + RADIUS_OFFSET*2
		){
		return true;
	} else {
		return false;
	}
}

void DrawUI(std::map<Values, float> values){

	DrawFillingBox(POS_UI.x, POS_UI.y, values[Values::life]/MAX_LIFE, RED);
	DrawFillingBox(POS_UI.x, POS_UI.y + 30.0f, values[Values::hunger]/MAX_HUNGER, GREEN);
	DrawMoneyCounter(POS_UI.x + 2.0f, POS_UI.y + 70.0f, (int)values[Values::money]);

}

void DrawFillingBox(int posx, int posy, float percent, Color color){

	int width = 200;
	int height = 20;
	int width_percent = (int)((float)width*percent);

	DrawRectangleLines(posx, posy, width, height, color);
	DrawRectangle(posx, posy, width_percent, height, color);
}

void DrawMoneyCounter(int posx, int posy, int money){
	std::string s = std::to_string(money);
	char const *text = s.c_str();
	DrawText(text, posx, posy, 20, ORANGE);
}