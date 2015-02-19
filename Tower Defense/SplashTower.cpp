#include "SplashTower.h"
#include "Tower.h"
#include "CritterGroup.h"
#include "MapEntity.h"
#include<string>
#include <stddef.h>

SplashTower::SplashTower() {

}

//SplashTower::SplashTower(int cost, int range, int power, int initialLevelUpCost, int fireRate, int maxNumOfEffects, int splashRange, char dispChar, std::string name) : Tower(cost, range, power, initialLevelUpCost, fireRate, maxNumOfEffects, dispChar, name) {
//    if(splashRange < 0)
//        this->splashRange = 0;
//    else
//        this->splashRange = splashRange;
//}


//SplashTower::SplashTower(const SplashTower& orig) : Tower(orig) {
//    this->splashRange = orig.splashRange;
//}

SplashTower::~SplashTower() {
}

bool SplashTower::TryToAttackCritter(CritterGroup& cg) {

    //If the tower is not attacking or if the critter it was attacking is dead
	//bool res = false;
 //   if (this->NeedNewTarget()) {
 //       if (this->FindFirstCritterInRange(cg)) {
 //           res = this->AttackCritter(*this->GetCurrentCritter(), cg);
 //       }
 //   } else {
 //       res = AttackCritter(*this->GetCurrentCritter(), cg);
 //   }

	////Reset the current critter to NULL to have a proper view
	//if (this->GetCurrentCritter() != NULL && this->GetCurrentCritter()->GetState() == CritterState::Dead){
	//	this->SetCurrentCritter(NULL);
	//}
	////Not to abuse the notofications to the view
	//if (!res){
	//	if (this->getDisplayChar() != this->GetInitialDisplayChar() ){
	//		this->setDisplayChar(this->GetInitialDisplayChar());
	//	}
	//}

	//return res;
}

bool SplashTower::AttackCritter(Critter& crit, CritterGroup& cg) {

    /*if (this->CanTowerHit()) {
		this->setDisplayChar('*');
        int maxNumOfCritter = cg.GetMaxNumOfCritters();
        Critter** critters = cg.GetCritters();
        
        for(int i = 0; i < maxNumOfCritter; i++){
            if(critters[i]->GetState() == CritterState::Alive){
                if (crit.isInRange(*critters[i], this->splashRange)){
                    this->ApplyEffectsAndDamage(*critters[i]);
                }
            }
        }
        return true;
    } else {
        return false;
    }
*/
}


