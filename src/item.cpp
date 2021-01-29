#include "../dep/raylib/raylib.h"
#include "item.h"
#include "enum_values.h"

#include <iostream>
#include <map>

Vector2 Item::getPosition(){
	return  this->position;
}

float Item::getRadius(){
	return  this->radius;
}

void Item::move(){
	this->position.y += this->fallSpeed;
}

void Item::applyEffect(std::map<Values, float> &values){
	this->effect.apply(values);
}

bool Item::checkCollide(Vector2 pos, float rad){
	return CheckCollisionCircles(this->position, this->radius, pos, rad);
}

void Item::update(){
	move();
}

void Item::draw(){
	DrawTextureEx(sprite, (Vector2){position.x-radius, position.y-radius}, 0.0f, scale, WHITE);
	//DrawCircleLines(position.x, position.y, radius, color);
}

Item::Item(Vector2 pos, float scale, Effect eff, float speed) : position(pos), scale(scale), effect(eff), fallSpeed(speed){

	switch(eff.getValue()){
		case Values::life:
			this->color = RED;
			sprite = LoadTexture("./data/pomme.png");
			break;
		case Values::hunger:
			this->color = GREEN;
			sprite = LoadTexture("./data/radis_vert.png");
			break;
		case Values::money:
			this->color = ORANGE;
			sprite = LoadTexture("./data/coin_v2.png");
			break;
	}

	radius = scale*(sprite.width/2);
}

Item::~Item(){}