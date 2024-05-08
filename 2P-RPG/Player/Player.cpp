//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(char _name[], int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;

    health-= trueDamage;

    if(trueDamage > 0){
        cout << name << " took " << trueDamage << " damage!" << endl;
    } else {
        cout<< name << " didn't received damage." << endl;
    }


    if(health <= 0) {
        cout << name << " has been defeated!" << endl;
    }
}

void Player::levelUp() {
    int opc;
    cout<<"\n\tHas subido de nivel!"<<endl;
    level++;
    cout<<"\tSu nivel es: "<<level<<endl<<endl;

    cout<<"\t1. Ataque."<<endl;
    cout<<"\t2. Defensa."<<endl;
    cout<<"\t3. Vida Maxima."<<endl;
    cout<<"\t4. Velocidad."<<endl;
    cout<<"\tElija una stat para aumentar:"; cin>>opc;

    switch (opc)
    {
    case 1:
        upAttack(1);
        break;
    case 2:
        upInitialDefense(1);
            upDefense(1);
        break;
    case 3:
        upInitialHealth(1);
        upHealth(1);
        break;
    case 4:
        upSpeed(1);
        break;
    default:
        break;
    }
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 100-experience;
    }
}

Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout<<endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". ";
        possibleTargets[i]->printName();
    }
    cout << "Select a target:"; cin >> selectedTarget;
    //TODO: Add input validation
    cout<<endl;
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(vector<Enemy*> enemies) {
    int action = 0;
    cout << "1. Attack" << endl
    << "2. Defend" << endl
    << "Select an action:"; cin >> action;
    //TODO: Validate input

    Action currentAction;
    Character* target = nullptr;

    // Se reinicia la defensa cada que le toca volver a elegir

    undefend();

    switch(action) {
        case 1:
            target = selectTarget(enemies);
            currentAction.target = target;
            currentAction.action = [this, target, enemies](){
                doAttack(target);
                if(target->getHealth()<=0){
                    Enemy* enemigo = ((Enemy*)target);
                    gainExperience(enemigo->getExperience());
                    if(enemigo->getExperience() + experience >= 100){
                        for (int i = 0; i < enemies.size(); i++) {
                            if(enemies[i]->getId() != enemigo->getId() && enemies.size() > 1) {
                                enemies[i]->upAttack(1);
                            }
                        }
                    }
                }
            };
            currentAction.speed = getSpeed();
            break;
        case 2:
            currentAction.action = [this]() {
                defend();
            };
            currentAction.speed = getSpeed();
            break;
        default:
            cout << "Invalid action" << endl;
            break;

    }

    return currentAction;
}

char* serialize() {

}