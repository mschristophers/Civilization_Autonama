#include "Person.h"

#include "../Util/Random.h"

#include <iostream>

void Person::init(const DescendantData& data)
{
    strength = data.strength;
    empire = data.empire;
    isDiseased = data.isDiseased;
    isAlive = true;
    isSwimming = false;
    age = 0;
    productionCount = 0;
    stopSwimCount = 0;
}

void Person::startSwim(Vect2 dir)
{
    swimDir = dir;
    isSwimming = true;
}

void Person::endSwim()
{
    if (stopSwimCount++ > 10) {
        stopSwimCount = 0;
        isSwimming = false;
    }
}

void Person::turnAround()
{
    swimDir.x *= -1;
    swimDir.y *= -1;
}

void Person::update()
{
    age++;
    productionCount++;

    if (age > strength) {
        kill();
    }

    if (isDiseased) {
        age *= 1.5;
    }
}

void Person::fight(Person& other)
{
    if (other.empire == 0)
        return;

    if (other.strength >= strength) {
        kill();
    }
    else {
        other.kill();
    }
}

Vect2 Person::getNextMove() const
{
    if (isSwimming)
        return swimDir;
    else
        return { (int8_t)Random::get().intInRange(-1, 1),
                (int8_t)Random::get().intInRange(-1, 1) };
}

void Person::kill()
{
    age = 0;
    strength = 0;
    empire = 0;
    productionCount = 0;
    stopSwimCount = 0;

    isDiseased = false;
    isAlive = false;
    isSwimming = false;
}

void Person::giveDisease()
{
    isDiseased = true;
}

DescendantData Person::getDescendant()
{
    productionCount = 0;

    DescendantData descendant;
    descendant.empire = empire;
    descendant.strength = strength;

    // Probability of the descendant getting cured from the disease
    if (isDiseased) {
        descendant.isDiseased = Random::get().intInRange(0, 100) >= 85;
    }

    // Probability of the descendant getting a mutation
    int mutation = Random::get().intInRange(0, 1000000);

    if (mutation >= 999000) {
        descendant.isDiseased = true;
        descendant.strength *= 0.65;
    }
    else if (mutation >= 750000) { // Small mutation
        descendant.strength *= Random::get().floatInRange(0.0, 1);
    }

    return descendant;
}