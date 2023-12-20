#include "Actor.h"
#include <algorithm>
#include "Game.h"
#include "Component.h"

Actor::Actor() :
	state(Actor::ActorState::Active),
	position(Vector2::zero),
	scale(1.0f),
	rotation(0.0f),
	game(Game::instance()) {
	game.addActor(this);
}

Actor::~Actor() {
	game.removeActor(this);
	while (!components.empty()) {
		delete components.back();
	}
}

void Actor::setPosition(Vector2 positionP)
{
	position = positionP;
}

void Actor::setScale(float scaleP)
{
	scale = scaleP;
}

void Actor::setRotation(float rotationP)
{
	rotation = rotationP;
}

void Actor::update(float dt)
{
	if (state == Actor::ActorState::Active)
	{
		updateComponent(dt);
		updateActor(dt);
	}
}

void Actor::updateComponent(float dt)
{
	for (auto component : components)
	{
		component->update(dt);
	}
}

void Actor::updateActor(float dt)
{
}

void Actor::addComponent(Component* component)
{
	int myOrder = component->getUpdateOrder();
	auto iter = begin(components);
	for (; iter != end(components); ++iter)
	{
		if (myOrder < (*iter)->getUpdateOrder())
		{
			break;
		}
	}

	components.insert(iter, component);
}

void Actor::removeComponent(Component* component)
{
	auto iter = std::find(begin(components), end(components), component);
	if (iter != end(components))
	{
		components.erase(iter);
	}
}