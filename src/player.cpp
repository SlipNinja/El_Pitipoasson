#include "../dep/raylib/raylib.h"
#include "player.h"
#include "constants.h"

#include <cmath>
#include <map>


Player::Player(){}

void Player::init(Vector2 pos){
	sprite = LoadTexture("./data/poasson_v2.png");
	frameRec = { 0.0f, 0.0f, (float)sprite.width/4, (float)sprite.height };
	position = pos;
	radius = 10.0f;

	currentFrame = 0;
	framesCounter = 0;
	framesSpeed = 12;// Number of spritesheet frames shown by second

	moveSpeed = 5;
	diagonalMoveSpeed = std::sqrt((moveSpeed*moveSpeed)*2)/2;
	rotation = 0.0f;
	scale = 1.0f;

	moving = {0.0f, 0.0f};
	verticalOffset = 10.0f;

	//UI values
	values = {
		{Values::life, MAX_LIFE},
		{Values::hunger, MAX_HUNGER},
		{Values::money, STARTING_MONEY}
	};
}

Vector2 Player::getPosition(){
	return position;
}

float Player::getRadius(){
	return radius;
}

std::map<Values, float>& Player::getValues(){
	return values;
}

void Player::move(){

	moving = {0.0f, 0.0f};

	if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_DOWN)){
		rotation = 45.0f;
		moving.x = diagonalMoveSpeed;
		moving.y = diagonalMoveSpeed;

	} else if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_UP)){
		rotation = -45.0f;
		moving.x = diagonalMoveSpeed;
		moving.y = -diagonalMoveSpeed;

	} else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_DOWN)){
		rotation = 135.0f;
		moving.x = -diagonalMoveSpeed;
		moving.y = diagonalMoveSpeed;

	} else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_UP)){
		rotation = -135.0f;
		moving.x = -diagonalMoveSpeed;
		moving.y = -diagonalMoveSpeed;

	} else if (IsKeyDown(KEY_DOWN)){
		rotation = 90.0f;
		moving.y = moveSpeed;
	} else if (IsKeyDown(KEY_UP)){
		rotation = -90.0f;
		moving.y = -moveSpeed;
	} else if (IsKeyDown(KEY_RIGHT)){
		rotation = 0.0f;
		moving.x = moveSpeed;
	} else if (IsKeyDown(KEY_LEFT)){
		rotation = 180.0f;
		moving.x = -moveSpeed;
	}

	// Bounds borders
	if(moving.x + position.x - (float)sprite.width/8 > 0.0f && moving.x + position.x + (float)sprite.width/8 < SCREEN_WIDTH){
		position.x += moving.x;
	}
	if(moving.y + position.y - verticalOffset - (float)sprite.height/8 > 0.0f && moving.y + position.y + (float)sprite.height/8 + verticalOffset < SCREEN_HEIGHT){
		position.y += moving.y;
	}
}

void Player::updateValues(){
	values[Values::hunger] -= HUNGER_DEGEN;
	if(values[Values::hunger] > 0.0f){
		values[Values::life] += LIFE_REGEN;
	} else {
		values[Values::life] -= LIFE_DEGEN;
	}
}

void Player::normalizeValues(){
	//Life
	if (values[Values::life] > MAX_LIFE) values[Values::life] = MAX_LIFE;
	if (values[Values::life] < 0.0f) values[Values::life] = 0.0f;

	//Hunger
	if (values[Values::hunger] > MAX_HUNGER) values[Values::hunger] = MAX_HUNGER;
	if (values[Values::hunger] < 0.0f) values[Values::hunger] = 0.0f;

	//Money
	if (values[Values::money] < 0.0f) values[Values::money] = 0.0f;
}

void Player::update(){

	move();
	updateValues();
	normalizeValues();

	framesCounter++;

	if (framesCounter >= (60/framesSpeed))
	{
		framesCounter = 0;
		currentFrame++;

		if (currentFrame > 3) currentFrame = 0;

		frameRec.x = (float)currentFrame*(float)sprite.width/4;
	}
}

void Player::draw(){
	//DrawCircleLines(position.x, position.y, radius, RED);
	DrawTextureTiled(sprite,
		frameRec,//source
		(Rectangle){position.x, position.y, (float)sprite.width/4, (float)sprite.height},//dest
		//(Vector2){0.0f, 0.0f},
		(Vector2){((float)sprite.width/4)*0.75f, ((float)sprite.height)/2},//origin for rotation
		rotation,
		scale,
		RAYWHITE);
}

Player::~Player(){
	UnloadTexture(sprite);
}