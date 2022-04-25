#ifndef DATABASE_H
#define DATABASE_H
#include "grassUI.h"
#include "cowUI.h"
#include "tigerUI.h"

struct D{
    grassUI* grassWidget;
    cowUI* cowWidget;
    tigerUI* tigerWidget;
};
#endif