/*

Effect class
--------------
Represents an effect that a tower attack could apply on a certain critter

*/

#ifndef EFFECT_H
#define	EFFECT_H
#include "Critter.h"

class Effect { 
public:
    Effect();
    Effect(int sm, int hm, int ed, CritterType sa, EffectType et, std::string name);
    Effect(const Effect& orig);
    virtual ~Effect();
    void ApplyEffect(Critter& ) const;
    void LevelUp();
	EffectType getType() const { return this->type; }
	std::string GetName() const { return name; }
private:
    const int LEVEL_UP_MODIFIER  = 1;
    int level;
    int speedModifier;
    int healthModifier;
    int extraDamage;
    CritterType enhancedAgainst;
    EffectType type;
	std::string name;
    
};

#endif	/* EFFECT_H */

