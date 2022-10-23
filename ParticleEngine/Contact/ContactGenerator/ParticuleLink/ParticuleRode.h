#ifndef PARTICULERODE_H
#define PARTICULERODE_H

#include "ParticuleLink.h"

class ParticuleRode : public ParticuleLink{

	private:
	float m_length;

	public:

	ParticuleRode(Particule* particule1, Particule* particule2,float length);

	int addContact(ParticuleContact* particuleContact,unsigned int limit,unsigned int current);
};
#endif // !PARTICULELINK_H