#include <stdio.h>
#include "main.hpp"

Destructible::Destructible(float maxHp, float defense, const char *corpseName) :
	maxHp(maxHp), hp(maxHp), defense(defense), corpseName(corpseName) {
}

EnemyDestructible::EnemyDestructible(float maxHp, float defense, const char *corpseName) :
	Destructible(maxHp, defense, corpseName) {
}

PlayerDestructible::PlayerDestructible(float maxHp, float defense, const char *corpseName) :
	Destructible(maxHp, defense, corpseName) {
}


float Destructible::takeDamage(Actor *owner, float damage) {
	damage -= defense;
	if (damage > 0) {
		hp -= damage;
		if (hp <= 0) {
			die(owner);
		}
	}
	else {
		damage = 0;
	}
	return damage;
}

void Destructible::die(Actor *owner) {
	// Transform the actor into a corpse! Yay!
	owner->ch = '%';
	owner->col = TCODColor::lightRed;
	owner->name = corpseName;
	owner->blocks = false;

	// Make sure the corpses are drawn behind living actors
	engine.sendToBack(owner);
}

void EnemyDestructible::die(Actor *owner) {
	// Transform it into a corpse!
	printf("The %s is dead. \n", owner->name);
	Destructible::die(owner);
}

void PlayerDestructible::die(Actor *owner) {
	printf("You have met your end. \n");
	Destructible::die(owner);
	engine.gameStatus = Engine::DEFEAT;
}