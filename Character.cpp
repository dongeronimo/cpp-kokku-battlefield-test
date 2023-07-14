#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "Dikstra.h"
#include "BattleField.h"
#include <queue>
#include <functional>
#include <cmath>
#include "SpecialAbility.h"
using namespace std;

Character::Character(Types::CharacterClass characterClass, BattleField* bf, Team t) :
    isDead(false), battlefield(bf), team(t)
{
    switch (characterClass) {
    case Types::Archer:
        break;
    case Types::Cleric:
        break;
    case Types::Paladin:
        break;
    case Types::Warrior:
        auto x = make_shared<StrongAttack>(*this);
        SpecialAbilities.push_back(x);
        break;
    }
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
void Character::ClearTargetIfDead()
{
    if (target != nullptr && target->IsDead()) {
        target = nullptr;
    }
}
bool Character::RollSpecialAbilities() {
    for (auto ability : SpecialAbilities) {
        if (ability->ConditionsAreMet() && ability->RollDice()) {
            ability->Execute();
            return true;
        }
    }
    return false;
}
void Character::StartTurn(Grid* grid) {
    typedef shared_ptr<Character> PCharacter;
    ClearTargetIfDead();
    if (RollSpecialAbilities())
        return; //A ação do turno foi uma special ability;
    
    //se não tem alvo, busca
    if (target == nullptr) {
        //Só me interessa quem n tá morto e for do time inimigo.
        vector<PCharacter> notDead;
        if (team == TeamA) {
            std::copy_if(battlefield->EnemyTeam.begin(), battlefield->EnemyTeam.end(), std::back_inserter(notDead),
                [](auto opponent) {return !opponent->IsDead(); });
        }
        if (team == TeamB) {
            std::copy_if(battlefield->PlayerTeam.begin(), battlefield->PlayerTeam.end(), std::back_inserter(notDead),
                [](auto opponent) {return !opponent->IsDead(); });
        }
        //ordena por distancia
        priority_queue<PCharacter, vector<PCharacter>, function<bool(PCharacter, PCharacter)>> myEnemiesOrderedByDistance(
            [this](PCharacter a, PCharacter b) { 
                int distanceA = std::abs(this->currentBox->Line() - a->currentBox->Line()) + std::abs(this->currentBox->Column() - a->currentBox->Column());
                int distanceB = std::abs(this->currentBox->Line() - b->currentBox->Line()) + std::abs(this->currentBox->Column() - b->currentBox->Column());
                return distanceA > distanceB; // priority queue retorna o maior elemento, isso faz o maior ser o menor?
            }
        );
        for (auto alive : notDead) {
            myEnemiesOrderedByDistance.push(alive);
        }
        if (myEnemiesOrderedByDistance.size() > 0) {
            target = myEnemiesOrderedByDistance.top();
        }
    }
    if (CheckCloseTargets(grid)) {
        Attack(target);
    }
    else if(target!=nullptr) { //É possivel que aqui tenha target null se todos do time inimigo estiverem mortos.
        // if there is no target close enough, calculates in which direction 
        // this character should move to be closer to a possible target

        vector<Pair> path = dijkstraShortestPath(grid,
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
            currentBox = grid->grids[grid->CalculateIndex(nextPosition.first, nextPosition.second)];
            currentBox->ocupied = true;
            cout << "Player " << PlayerIndex << " walked " << directionWalked << endl;
        }
    }
}

bool Character::CheckCloseTargets(Grid* grid)
{
    if (target == nullptr)
        return false;
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

