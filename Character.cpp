#include <functional>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include "Dikstra.h"
#include "BattleField.h"
#include "SpecialAbility.h"
#include "StatusEffect.h"
using namespace std;

Character::Character(Types::CharacterClass characterClass, BattleField& bf, Team t) :
    isDead(false), battlefield(bf), team(t)
{
    switch (characterClass) {
    case Types::Archer:
        SpecialAbilities.push_back(make_shared<Teleport>(*this));
        SpecialAbilities.push_back(make_shared<BowAttack>(*this));
        break;
    case Types::Cleric:
        SpecialAbilities.push_back(make_shared<Reanimate>(*this));
        SpecialAbilities.push_back(make_shared<Curse>(*this, 4, 5));
        break;
    case Types::Paladin:
        SpecialAbilities.push_back(make_shared<Smite>(*this));
        SpecialAbilities.push_back(make_shared <SelfHeal>(*this));
        break;
    case Types::Warrior:
        SpecialAbilities.push_back(make_shared<Charge>(*this));
        SpecialAbilities.push_back(make_shared<StrongAttack>(*this));
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

void Character::ApplyStatusEffects() {
    if (IsDead())
        return;
    //copia os status q ainda estão ativos para uma lista 
    vector<shared_ptr<StatusEffect>> activeEffects;
    std::copy_if(StatusEffects.begin(), StatusEffects.end(), std::back_inserter(activeEffects),
        [](auto effect) {return effect->IsFinished() == false; });
    //aplica eles
    for (auto effect : activeEffects) {
        effect->Apply();
    }
    //atualiza a lista
    StatusEffects = activeEffects;
}
void Character::ReevaluateTarget() {
    //if (target == nullptr) {
        //Só me interessa quem n tá morto e for do time inimigo.
        vector<PCharacter> notDead;
        if (team == TeamA) {
            std::copy_if(battlefield.EnemyTeam.begin(), battlefield.EnemyTeam.end(), std::back_inserter(notDead),
                [](auto opponent) {return !opponent->IsDead(); });
        }
        if (team == TeamB) {
            std::copy_if(battlefield.PlayerTeam.begin(), battlefield.PlayerTeam.end(), std::back_inserter(notDead),
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
    //}
}
void Character::StartTurn(Grid* grid) {
    
    ClearTargetIfDead();
    ApplyStatusEffects();
    //Se está stunado ele não age.
    if (HasEffect(Stun::TypeID))
        return;
    if (RollSpecialAbilities())
        return; //A ação do turno foi uma special ability;
    ReevaluateTarget();
    if (CheckCloseTargets(grid)) {
        Attack(target);
    }
    else if(target!=nullptr) { //É possivel que aqui tenha target null se todos do time inimigo estiverem mortos.
        auto directionWalked = MoveToTarget();
        cout << "Player " << PlayerIndex << " walked " << directionWalked << endl;
    }
}
const std::string Character::MoveToTarget() {
    vector<Pair> path = dijkstraShortestPath(battlefield.grid,
        currentBox->Line(), currentBox->Column(), target->currentBox->Line(),
        target->currentBox->Column());
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
        currentBox = battlefield.grid->grids[battlefield.grid->CalculateIndex(
            nextPosition.first, nextPosition.second)];
        currentBox->ocupied = true;
        return directionWalked;
    }
    else {
        return "";
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

void Character::AddEffect(shared_ptr<StatusEffect> effect) {
    StatusEffects.push_back(effect);
}

bool Character::HasEffect(const int typeId) const
{
    for (auto effect : StatusEffects) {
        if (effect->Type() == typeId)
            return true;
    }
    return false;
}
