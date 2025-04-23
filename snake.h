#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>
#include <vector>

extern std::vector<SDL_Rect> snake;

bool test_out2(char kitu);
bool test_out3();
void velai(SDL_Renderer* renderer, SDL_Texture* background);
void themdot();

#endif
