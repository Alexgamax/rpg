//
// Created by Victor Navarro on 15/02/24.
//

#ifndef RPG_ENEMY_H
#define RPG_ENEMY_H

#pragma once
#include "../Character/Character.h"
#include "../Player/Player.h"
#include <vector>
#include "../Combat/Action.h"

class Player;

class Enemy: public Character{
private:
    int experience;
    int id;
public:
    Enemy(char _name[], int _health, int _attack, int _defense, int _speed, int _experience, int id);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    int getId();
    Character* selectTarget(vector<Player*> possibleTargets);
    Action takeAction(vector<Player*> partyMembers);

    void printName();
    int getExperience();
};


#endif //RPG_ENEMY_H
