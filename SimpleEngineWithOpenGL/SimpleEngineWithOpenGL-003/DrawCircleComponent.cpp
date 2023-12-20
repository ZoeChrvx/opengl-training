#include "DrawCircleComponent.h"
#include "Actor.h"
#include <SDL.h>
#include "Renderer.h"
#include "Game.h"

DrawCircleComponent::DrawCircleComponent(Actor* ownerP, int radiusP) :
	Component(ownerP),
	radius{ radiusP } {
	owner.getGame().getRenderer().addCircle(this);
}

DrawCircleComponent::~DrawCircleComponent() {
	owner.getGame().getRenderer().removeCircle(this);
}

void DrawCircleComponent::draw(Renderer& renderer) {
	drawCircle(renderer);
}

void DrawCircleComponent::drawCircle(Renderer& renderer) {
	SDL_Renderer* SDLRenderer = renderer.toSDLRenderer();
	const int centreX = owner.getPosition().x;
	const int centreY = owner.getPosition().y;

	
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	SDL_SetRenderDrawColor(SDLRenderer, 115, 26, 138, 255);

	while (x >= y) {
		SDL_RenderDrawPoint(SDLRenderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(SDLRenderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(SDLRenderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(SDLRenderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(SDLRenderer, centreY + y, centreY - x);
		SDL_RenderDrawPoint(SDLRenderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(SDLRenderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(SDLRenderer, centreX - y, centreY + x);

		if (error <= 0) {
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0) {
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}