/*
 * usuario.cc
 *
 *  Created on: 5 dic 2022
 *      Author: JAVIER
 */
#include <fstream>
#include <iostream>
#include "usuario.h"
#include <stdlib.h>
#include <string>


using namespace std;

Usuario::Usuario(string correo, string contra){
	correo_ = correo;
	contra_ = contra;
}
bool arroba(string cor){
	int c = 0;
	for(int i = 0; i < cor.length(); i++){
		if(cor[i]=='@')
			c++;
		else if(cor[i]=='.')
			c++;
	}
	if(c == 2){
		return true;
	}
	return false;
}
bool Usuario::iniciarSesion(){
	string c, p;
	bool ccorr=false; //condicionadores para hacer un bucle por si falla el correo
	bool ccontra=false; //condicionadores para hacer un bucle por si falla la contraseña
	while(ccontra != true){ //si falla la contraseña se repite todo el bucle
		while(ccorr != true){ //si falla el correo se repite el bucle del correo
			cout<<"Introducir correo: "<<endl;
			cin>>c;
			set_correo(c);
			bool al = arroba(c);
			if(comprobar_correo(c) == true){ //comprueba que el correo esté en el fichero
				if(al == true){
					cout<<"Correo valido"<<endl;
					ccorr = true; //se termina el while del correo
				}
			}
			else{
				cout<<"Correo erroneo, prueba de nuevo."<<endl;
			}
		}
		cout<<"Introducir contrasenya: "<<endl;
		cin>>p;
		set_contra(p);
		if(comprobar_coincidencia(c,p)==true){//comprobamos que la contraseña y el correo casan
			cout<<"Inicio en la sesión con exito"<<endl;
			ccontra = true; //se termina el while grande
			return true;
		}
		else{
			ccorr = false; //volvemos a dar como error el correo para que el usuario lo tenga que volver a escribir
			cout<<"No hay coincidencia entre la contrasenia y el correo proporcionados"<<endl;
		}
	}
	return false;
}
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
bool comprobar_coincidencia(string cor, string con){
	ifstream fich;
	int c = 0;
	string arriba, abajo;
	fich.open("logs.txt", ios::in);//abrimos en modo lectura
	if(fich.fail()){
		cout<<"Error al abrir fichero"<<endl;
		return false;
	}
	while(!fich.eof()){
		getline(fich, arriba);//hago esto porque la estructura de la base de datos va a ser linea de correo y la siguiente linea de contraseña
		getline(fich, abajo);
		if(arriba == cor && abajo == con){
			c++;
		}
	}
	if(c == 1){
		return true;
	}
	fich.close();
	return false;
}
void imprimir(){
	ifstream fich;
	string arriba, abajo;
	fich.open("logs.txt", ios::in);//abrimos en modo lectura
	if(fich.fail()){
		cout<<"Error al abrir fichero"<<endl;

	}
	while(!fich.eof()){
		getline(fich, arriba);//hago esto porque la estructura de la base de datos va a ser linea de correo y la siguiente linea de contraseña
		getline(fich, abajo);
		cout<<arriba<<" "<<abajo;
		cout<<endl;
	}
	fich.close();
}
void Usuario::verPagina(){
	cout<<"BIENVENIDO A NUESTRA PAGINA WEB"<<endl;
	cout<<"-------------------------------------------------"<<endl;
	int c;
	cout<<"Que desea hacer?"<<endl;
	menu();
	cin>>c;
	switch(c){
	case 1:
		iniciarSesion();
	break;
	case 2:
		//vercursos();
	break;
	default:
		cout<<"Argumento no valido";
	}
}
void menu(){
	cout<<"1. Iniciar Sesion(opcional pero hecho)"<<endl;
	cout<<"2. Ver cursos de extension"<<endl;
	cout<<"3. Registrar Usuario(opcional)"<<endl;
}



