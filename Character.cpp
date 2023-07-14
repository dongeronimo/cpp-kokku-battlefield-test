#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include "Character.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "Dikstra.h"
#include "BattleField.h"
using namespace std;
Character::Character(Types::CharacterClass characterClass, BattleField* bf, Team t):
    isDead(false), battlefield(bf), team(t)
{

}

Character::~Character() 
{

}

bool Character::TakeDamage(float amount) 
{
    Health = Health - amount;
    if (Health <= 0) {
        Die();
        return true;
    }
    return false;
}

void Character::Die() 
{
    isDead = true;
}

void Character::StartTurn(Grid* battlefield) {
    //abandona alvo morto.
    if (target != nullptr && target->IsDead()) {
        target = nullptr;
    }
    if (target == nullptr) {
        
    }
    if (CheckCloseTargets(battlefield)) {
        Attack(target);
    }
    else {
        // if there is no target close enough, calculates in which direction 
        // this character should move to be closer to a possible target

        vector<Pair> path = dijkstraShortestPath(battlefield,
            currentBox->Line(), currentBox->Column(),
            target->currentBox->Line(), target->currentBox->Column());
        if (path.size() >= 1) {
            Pair nextPosition = path[0];
            string directionWalked = "";
            if (nextPosition.first == currentBox->Line() - 1)
                directionWalked = "down";
            if (nextPosition.first == currentBox->Line() + 1)
                directionWalked = "up";
            if (nextPosition.second == currentBox->Column() - 1)
                directionWalked = "left";
            if (nextPosition.second == currentBox->Column() + 1)
                directionWalked = "right";
            //troca as box
            currentBox->ocupied = false;
            currentBox = battlefield->grids[
                battlefield->CalculateIndex(nextPosition.first, nextPosition.second)];
            currentBox->ocupied = true;
            cout << "Player " << PlayerIndex << " walked " << directionWalked << endl;
        }
    }
}

bool Character::CheckCloseTargets(Grid* battlefield)
{
    //está acima
    auto above = (target->currentBox->Line() == currentBox->Line() &&
        target->currentBox->Column() == currentBox->Column() - 1);
    //está abaixo
    auto below = (target->currentBox->Line() == currentBox->Line() &&
        target->currentBox->Column() == currentBox->Column() + 1);
    //esta à esq
    auto left = (target->currentBox->Line() == currentBox->Line()-1 &&
        target->currentBox->Column() == currentBox->Column() );
    //esta à direita
    auto right = (target->currentBox->Line() == currentBox->Line() + 1 &&
        target->currentBox->Column() == currentBox->Column());
    return above || below || left || right;
}

void Character::Attack(shared_ptr<Character> target)
{
    auto damage = this->BaseDamage * this->DamageMultiplier;
    cout << "Player " << PlayerIndex << " did " << damage << " to Player " << target->PlayerIndex << endl;
    target->TakeDamage(damage);
}

