#include "../dep/raylib/raylib.h"
#include "enum_values.h"

#include <map>


#ifndef MAIN_H
#define MAIN_H

void AddItems();

void UpdateItems();

bool IsOutOfBounds(Vector2);

void DrawUI(std::map<Values, float>);

void DrawFillingBox(int, int, float, Color);

void DrawMoneyCounter(int, int, int);

#endif //MAIN_H