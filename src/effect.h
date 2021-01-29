#include "../dep/raylib/raylib.h"
#include "enum_values.h"

#include <map>

#ifndef EFFECT_H
#define EFFECT_H

class Effect{

	Values value;
	float strength;

	public:

		Values getValue();

		void apply(std::map<Values, float>&);

		Effect(Values, float);

		~Effect();

};

#endif //EFFECT_H