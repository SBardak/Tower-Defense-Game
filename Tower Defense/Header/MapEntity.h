#ifndef MAPENTITY_H
#define	MAPENTITY_H
#include "BaseModel.h"

//Every MapEntity is considered a model. This will include the towers.
class MapEntity : public BaseModel {
public:
    MapEntity();
    MapEntity(const MapEntity& orig);
    virtual ~MapEntity();
      
    int getX() const { return x;}
    int getY() const { return y;}
	char getDisplayChar() const { return displayChar; }
	void setDisplayChar(char); 
    void SetPosition(int, int);
    bool isInRange(MapEntity, int) const;
    
private:
    int x;
    int y;
	char displayChar;
};

#endif	/* MAPENTITY_H */

