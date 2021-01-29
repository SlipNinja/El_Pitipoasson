#include "effect.h"
#include "enum_values.h"

#include <iostream>
#include <map>


Values Effect::getValue(){
	return  this->value;
}

void Effect::apply(std::map<Values, float> &values){
	//std::cout << "VALUE : " << static_cast<std::underlying_type<Values>::type>(this->value) << "(" << this->strength << ")" << std::endl;

	switch(this->value){
		case Values::life:
			values[Values::life] += this->strength;
			break;
		case Values::hunger:
			values[Values::hunger] += this->strength;
			break;
		case Values::money:
			values[Values::money] += this->strength;
			break;
	}
}


Effect::Effect(Values n, float str) : value(n), strength(str){}

Effect::~Effect(){}