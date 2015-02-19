#include "CritterFactory.h"

void CritterFactory::createCritter(int waveLevel) {

	cm->spawnCritter(grid, waveLevel);

}