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
		bool registrarUsuario();
};
bool distancia(string cor);
void registrar(string cor, string con);
int contarUsuarios();



#endif /*VISITANTE_H_ */
