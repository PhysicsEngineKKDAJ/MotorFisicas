#ifndef FalsoTetraedro_H_
#define FalsoTetraedro_H_

#include "Malla.h"

class FalsoTetraedro : public Malla {
	public:
		FalsoTetraedro(void);
		~FalsoTetraedro(void);
		void dibuja();
private:
	bool modo;
};
#endif
