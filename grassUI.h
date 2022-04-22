#include "creatureUI.h"

class grassUI : public creatureUI{
    Q_OBJECT
public:
    grassUI(){
        setNumberOfCreature(100);
    }

};