#ifndef Cono_H_
#define Cono_H_

#include "Malla.h"

class Cono : public Malla {
public:
	Cono(int numVertices, int radio, int altura);
	~Cono(void);
	void dibuja();
private:
	float m_radio, m_altura;
	bool modo;
};
#endif
