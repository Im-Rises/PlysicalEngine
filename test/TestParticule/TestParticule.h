#ifndef TESTPARTICULE_H
#define TESTPARTICULE_H

#include "../../PhysicalEngine/Scene/Components/Particule/Particule.h"

class TestParticule {

public:
    Particule m_testParticule;

    TestParticule();

    int TestCalculePosition();
};

#endif // !TESTPARTICULE_H
