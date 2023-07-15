#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Grid.h"
#include "Character.h"
#include "Types.h"

using namespace std;
class BattleField;
class SpecialAbility;
class StatusEffect;
enum Team {TeamA, TeamB};
class Character
{
private:
    typedef shared_ptr<Character> PCharacter;
    bool isDead;
    const Team team;
    vector<shared_ptr<StatusEffect>> StatusEffects;
    vector<shared_ptr<SpecialAbility>> SpecialAbilities;
    /// <summary>
    /// Abandona o alvo morto.
    /// </summary>
    void ClearTargetIfDead();
    /// <summary>
    /// Percorre a lista de habilidades especiais e as rola. Se alguma procar
    /// a executa e retorna true senaõ retorna false. Pára de rodar assim que alguma
    /// procar.
    /// </summary>
    /// <returns></returns>
    bool RollSpecialAbilities();
    void ReevaluateTarget();
    void ApplyStatusEffects();
public:
    Character(Types::CharacterClass charcaterClass, 
        BattleField& battlefield, 
        Team t);
    ~Character();
    BattleField& battlefield;
    /// <summary>
    /// Não é responsabilidade do character saber o que fazer com quem
    /// tá morto mas sim do main loop do jogo, que está em battlefield.
    /// Isso aqui marca o character como morto pra que o Battlefield faça
    /// o que tiver que ser feito c ele.
    /// </summary>
    /// <returns></returns>
    const bool IsDead() const { return isDead; }
    void IsDead(bool d) { isDead = false; }
    float Health;
    float BaseDamage;
    float DamageMultiplier;

    int PlayerIndex;
    //Se eu estou usando shared_ptr não é correto passar a usar naked pointer
    //em um lugar onde shared_ptr daria na mesma pq n quero arriscar alguém dar
    //free.
    shared_ptr<Character> target;


    char Icon;

    Types::GridBox* currentBox;

    bool TakeDamage(float amount);
    //n é usada em lugar algum e n vi necessidade de sua existencia.
    //int getIndex(vector<Types::GridBox*> v, int index);

    void Die();

    void StartTurn(Grid* grid);

    bool CheckCloseTargets(Grid* grid);

    void Attack(shared_ptr<Character> target);

    void AddEffect(shared_ptr<StatusEffect> effect);

    bool HasEffect(const int typeId) const;

    const std::string MoveToTarget();

    const Team GetTeam()const {
        return team;
    }
};

