/*
 * participante.cpp
 *
 *  Created on: 6 dic 2022
 *      Author: USUARIO
 */
#include "../usuario/usuario.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "../usuario/usuario.cpp"

#include "participante.h"

using namespace std;


Participante::Participante(string correo,
		string contra,
		string nombre = "null",
		string dni = "null",
		string estudios = "null",
		string telefono = "null",
		string nacimiento = "null",
		string cmatriculados = "null"):Usuario(correo, contra){}

bool Participante::matricularse(){

}
void Participante::globalset(){

}
void Participante::paginaParticipante(){
	cout<<"BIENVENIDO <"<<get_nombre()<<">."<<endl;
	cout<<"-------------------------------------------------"<<endl;
	int c;
	cout<<"Que desea hacer?"<<endl;
	menu();
	cin>>c;
	switch(c){
	case 1:
		verListas();
		if(opcionaMatricula() == true){
			matricularse();
		}
	break;
	default:
		cout<<"Argumento no valido";
	}
}
void menu(){
	cout<<"1. Ver cursos de extension"<<endl;
	cout<<"2. Salirse"<<endl;
}

