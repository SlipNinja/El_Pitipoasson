#include "../dep/raylib/raylib.h"
#include "effect.cpp"

#include <map>

#ifndef ITEM_H
#define ITEM_H

class Item{

	Texture2D sprite;
	Vector2 position;
	float radius;
	Effect effect;
	float fallSpeed;
	float scale;
	Color color;//debug

	public:

		Vector2 getPosition();

		float getRadius();

		void applyEffect(std::map<Values, float>&);

		void move();

		bool checkCollide(Vector2, float);

		void update();

		void draw();

		Item(Vector2, float, Effect, float);

		~Item();

};

#endif //ITEM_H