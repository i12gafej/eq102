/*
 * usuario.h
 *
 *  Created on: 5 dic 2022
 *      Author: JAVIER
 */

#ifndef USUARIO_H
#define USUARIO_H
#include <stdlib.h>
#include <string>
using namespace std;

class Usuario{
	private:
		string correo_, contra_;
	public:
		Usuario(string, string);
		//setters
		inline void set_correo(string correo){correo_ = correo;}
		inline void set_contra(string contra){contra_ = contra;}
		//Getters
		inline string get_correo(){return correo_;}
		inline string get_contra(){return contra_;}
		//User's operations
		bool iniciarSesion();
		void verPagina();
};
bool comprobar_coincidencia(string cor, string con);
bool comprobar_correo(string cor);
bool arroba(string cor);
void imprimir();
void menu();


#endif /* OBJETOS_USUARIO_USUARIO_H_ */
