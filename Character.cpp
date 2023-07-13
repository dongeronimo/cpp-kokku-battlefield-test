#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include "Character.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "Dikstra.h"
using namespace std;
Character::Character(Types::CharacterClass characterClass)
{

}

Character::~Character() 
{

}

bool Character::TakeDamage(float amount) 
{
	if ((Health -= BaseDamage) <= 0) 
	{
		Die();
		return true;
	}
	return false;
}

void Character::Die() 
{
	// TODO >> kill
	//TODO >> end the game?
}

void Character::WalkTo(bool CanWalk) 
{

}



void Character::StartTurn(Grid* battlefield) {
    std::cout<<"Start turn"<<std::endl;
    if (CheckCloseTargets(battlefield)) {
        Attack(target);
    }
    else {
        // if there is no target close enough, calculates in which direction 
        // this character should move to be closer to a possible target
        vector<Pair> path = dijkstraShortestPath(battlefield,
            currentBox->Line(), currentBox->Column(),
            target->currentBox->Line(), target->currentBox->Column());
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
        battlefield->drawBattlefield();
    }
}

bool Character::CheckCloseTargets(Grid* battlefield)
{
    return false;
}

void Character::Attack(shared_ptr<Character> target)
{
    cout << "TODO: Implementar ataque" << std::endl;
}

