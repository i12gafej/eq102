/*
 * visitante.h
 *
 *  Created on: 5 dic 2022
 *      Author: JAVIER
 */

#ifndef VISITANTE_H_
#define VISITANTE_H_

#include "../usuario/usuario.h"
#include <string>

using namespace std;
class Visitante: public Usuario{
private:
		string correo_;
		string contra_;
	public:
		Visitante(string, string);


};




#endif /*VISITANTE_H_ */
