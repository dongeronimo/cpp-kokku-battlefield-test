#pragma once
#include <vector>
#include <memory>
#include "Grid.h"
#include "Character.h"
#include "Types.h"

using namespace std;

class Character
{
public:

    Character(Types::CharacterClass charcaterClass);
    ~Character();

    
    float Health;
    float BaseDamage;
    float DamageMultiplier;
    //public GridBox currentBox;
    int PlayerIndex;
    //Se eu estou usando shared_ptr não é correto passar a usar naked pointer
    //em um lugar onde shared_ptr daria na mesma pq n quero arriscar alguém dar
    //free.
    shared_ptr<Character> target;

    bool IsDead;
    char Icon;

    Types::GridBox* currentBox;

    bool TakeDamage(float amount);

    int getIndex(vector<Types::GridBox*> v, int index);

    void Die();

    void WalkTo(bool CanWalk);

    void StartTurn(Grid* battlefield);

    bool CheckCloseTargets(Grid* battlefield);

    void Attack(shared_ptr<Character> target);


};

