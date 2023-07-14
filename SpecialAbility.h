#pragma once
#include <memory>

class Battlefield;
class Character;

using namespace std;
#define STRONG_ATTACK_PROC_CHANCE 0.33f
#define TELEPORT_PROC_CHANCE 0.33f
#define TELEPORT_PROC_DISTANCE 3
#define SELF_HEAL_PROC_CHANCE 0.33f
#define BOW_ATTACK_PROC_CHANCE 0.75f
#define BOW_ATTACK_PROC_MAX_DISTANCE 5 
#define SMITE_PROC_CHANCE 0.5f
#define SMITE_MAX_HP_PROC 30 
#define CHARGE_PROC_CHANCE 0.5f
#define CURSE_PROC_CHANCE 0.33f
#define CURSE_RANGE 3
#define REANIMATE_PROC_CHANCE 0.05f

#define MANHATTAN_DISTANCE_BETWEEN_ORIGINATOR_AND_TARGET ManhattanDistance(originator.currentBox->Line(), originator.currentBox->Column(),originator.target->currentBox->Line(), originator.target->currentBox->Column())
/// <summary>
/// Classe base de todas as habilidades especiais. Herdeiros tem que 
/// implementar ConditionsAreMet e Execute.
/// </summary>
class SpecialAbility
{
private:
	/// <summary>
	/// Chance do evento ocorrer, [0.0, 1.0].
	/// </summary>
	const float proc;
protected:
	/// <summary>
	/// Quem é que executa essa habilidade?
	/// </summary>
	Character& originator;
public:
	SpecialAbility(Character& originator, const float proc);
	/// <summary>
	/// Retorna true se o valor aleatório for menor ou igual que proc
	/// </summary>
	/// <returns></returns>
	bool RollDice();
	/// <summary>
	/// Retorna true se as condições para essa habilidade especial ocorrer são atendidas
	/// </summary>
	/// <returns></returns>
	virtual bool ConditionsAreMet() = 0;
	/// <summary>
	/// Executa-a.
	/// </summary>
	virtual void Execute() = 0;
};
/// <summary>
/// Habilidade do Warrior: causa dano dobrado no oponente 
/// </summary>
class StrongAttack :public SpecialAbility {
public:
	StrongAttack(Character& originator);
	/// <summary>
	/// Ela dispara se o oponente estiver colado no warrior
	/// </summary>
	/// <returns></returns>
	bool ConditionsAreMet() override;
	void Execute() override;
};
/// <summary>
/// Habilidade do Warrior: Ele anda 3 gridboxes ao invés de 1
/// </summary>
class Charge : public SpecialAbility {
public:
	Charge(Character& originator);
	/// <summary>
	/// Ela sempre pode acontecer
	/// </summary>
	/// <returns></returns>
	bool ConditionsAreMet() override;
	void Execute()override;
};
/// <summary>
/// O archer pode teleportar pelo mapa. Ele o faz se o alvo dele estiver muito parto 
/// dele.
/// </summary>
class Teleport : public SpecialAbility {
public:
	Teleport(Character& originator);
	bool ConditionsAreMet() override;
	void Execute() override;
};
/// <summary>
/// O ataque de longa distancia do archer
/// </summary>
class BowAttack : public SpecialAbility {
public:
	BowAttack(Character& originator);
	bool ConditionsAreMet() override;
	void Execute()override;
};
/// <summary>
/// O paladino cura a si mesmo. O StatusEffect de cura é aplicado a ele, com duração de 1 turno.
/// </summary>
class SelfHeal : public SpecialAbility {
public:
	SelfHeal(Character& originator);
	/// <summary>
	/// Se o paladino n tem nenhuma cura sobre ele ele pode ganhar essa cura
	/// </summary>
	/// <returns></returns>
	bool ConditionsAreMet() override;
	void Execute() override;
};
/// <summary>
/// O golpe do paladino empurra o inimigo para trás e o imobiliza por 2 turnos, aplicando o efeito
/// de stun. Para o paladino poder fazer isso ele tem que estar com menos de SMITE_MAX_HP_PROC
/// pontos de vida.
/// </summary>
class Smite : public SpecialAbility {
public:
	Smite(Character& originator);
	/// <summary>
	/// Tem que estar no corpo-a-corpo e o paladino tem que estar ferido para fazer isso.
	/// </summary>
	/// <returns></returns>
	bool ConditionsAreMet() override;
	void Execute()override;
};
/// <summary>
/// Todos os inimigos ao proximos do clerigo sofrem um dano por tempo durante alguns turnos e
/// todos os aliados proximos do clerigo ganham um efeito de cura ao longo do tempo.
/// </summary>
class Curse : public SpecialAbility {
public:
	Curse(Character& originator);
	bool ConditionsAreMet() override;
	void Execute()override;
};
/// <summary>
/// Reanima um aliado morto, perto do clerigo, com um mínimo de pontos de vida
/// </summary>
class Reanimate : public SpecialAbility {
public:
	Reanimate(Character& originator);
	bool ConditionsAreMet() override;
	void Execute()override;
};