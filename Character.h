#pragma once
#include <vector>
#include <memory>
#include "Grid.h"
#include "Character.h"
#include "Types.h"

using namespace std;
class BattleField;
enum Team {TeamA, TeamB};
class Character
{
private:
    bool isDead;
    const BattleField* battlefield;
    const Team team;
public:

    Character(Types::CharacterClass charcaterClass, BattleField* battlefield, Team t);
    ~Character();
    /// <summary>
    /// N�o � responsabilidade do character saber o que fazer com quem
    /// t� morto mas sim do main loop do jogo, que est� em battlefield.
    /// Isso aqui marca o character como morto pra que o Battlefield fa�a
    /// o que tiver que ser feito c ele.
    /// </summary>
    /// <returns></returns>
    const bool IsDead() const { return isDead; }
    float Health;
    float BaseDamage;
    float DamageMultiplier;

    int PlayerIndex;
    //Se eu estou usando shared_ptr n�o � correto passar a usar naked pointer
    //em um lugar onde shared_ptr daria na mesma pq n quero arriscar algu�m dar
    //free.
    shared_ptr<Character> target;


    char Icon;

    Types::GridBox* currentBox;

    bool TakeDamage(float amount);
    //n � usada em lugar algum e n vi necessidade de sua existencia.
    //int getIndex(vector<Types::GridBox*> v, int index);

    void Die();

    void StartTurn(Grid* grid);

    bool CheckCloseTargets(Grid* grid);

    void Attack(shared_ptr<Character> target);


};

