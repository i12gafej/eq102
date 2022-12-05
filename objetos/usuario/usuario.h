/*
 * usuario.h
 *
 *  Created on: 5 dic 2022
 *      Author: JAVIER
 */

#ifndef USUARIO_H
#define USUARIO_H

#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class Usuario{
private:
	string correo_;
	string contra_;
public:
	Usuario(string correo = "empty", string contra = "empty"){};
	//setters
	inline void set_correo(string correo){correo_ = correo;}
	inline void set_contra(string contra){contra_ = contra;}
	//Getters
	inline string get_correo()const{return correo_;}
	inline string get_contra()const{return contra_;}
	//User's operations
	bool iniciarSesion();
	void verPagina();
};
bool comprobar_coincidencia();
bool comprobar_correo(string cor);



#endif /* OBJETOS_USUARIO_USUARIO_H_ */
