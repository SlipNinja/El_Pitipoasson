#include "../dep/raylib/raylib.h"
#include "enum_values.h"

#include <map>

#ifndef PLAYER_H
#define PLAYER_H

class Player{

	Texture2D sprite;
	Vector2 position;
	float radius;
	Rectangle frameRec;

	int currentFrame;
	int framesCounter;
	int framesSpeed;// Number of spritesheet frames shown by second
	float moveSpeed;
	float diagonalMoveSpeed;

	float rotation;
	float scale;

	Vector2 moving;
	float verticalOffset;
	std::map<Values, float> values;


	public:

		float getRadius();

		Vector2 getPosition();

		std::map<Values, float>& getValues();

		void update();

		void draw();

		void move();

		void updateValues();

		void normalizeValues();

		void init(Vector2);

		Player();

		~Player();

};

#endif //PLAYER_H