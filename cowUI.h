#include "creatureUI.h"

class cowUI : public creatureUI{
    Q_OBJECT
public:
    cowUI(){
        setNumberOfCreature(10);
    }

};