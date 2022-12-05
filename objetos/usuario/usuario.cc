/*
 * usuario.c
 *
 *  Created on: 5 dic 2022
 *      Author: JAVIER
 */
#include <fstream>
#include <iostream>
#include "usuario.h"
#include <stdlib.h>
#include <string.h>


using namespace std;

bool comprobar_correo(string cor){
	ifstream fich;
	string linea;
	fich.open("logs.txt", ios::in);//abrimos en modo lectura
	if(fich.fail()){
		cout<<"Error al abrir fichero"<<endl;
		return false;
	}
	while(!fich.eof()){
		getline(fich, linea);
		if(linea == cor){
			return true;
		}
	}
	fich.close();
	return false;
}
bool comprobar_coincidencia(){
	ifstream fich;
	string arriba, abajo;
	fich.open("logs.txt", ios::in);//abrimos en modo lectura
	if(fich.fail()){
		cout<<"Error al abrir fichero"<<endl;
		return false;
	}
	while(!fich.eof()){
			getline(fich, arriba);
			getline(fich, abajo);
		}
		fich.close();
		return false;

	return false;
}
bool Usuario::iniciarSesion(){
	string c, p;
	bool ccorr=false, ccontra;
	while(ccorr!=true){
		cout<<"Introducir correo: "<<endl;
		cin>>c;
		set_correo(c);

		if(comprobar_correo(c) == true){
			cout<<"Correo valido"<<endl;
			ccorr = true;
		}
		else{
			cout<<"Correo erroneo, prueba de nuevo."<<endl;
		}
	}
	cout<<"Introducir contrasenya: "<<endl;
	cin>>p;
	set_contra(p);
	/*if(comprobar_coincidencia()==true){
		cout<<"Inicio en la sesión con exito"<<endl;
		return true;
	}
	else{
		cout<<"No hay coincidencia entre la contrasenia y el correo proporcionados"<<endl;
		return false;
	}*/
	return false;
}




