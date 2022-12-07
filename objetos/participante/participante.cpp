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
#include <chrono>
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
	bool valid = false;
	string aforo, date, estudios, linea, participantes;
	int cual, curso, ticks = 0, partips, afor;
	while(valid != true){
		cual = Usuario::verListas();
		cout<<"En que curso de extension desea matricularse?"<<endl;
		cin>>curso;
		if(curso < 1 || curso > cual){
			cout<<"Curso no valido, prueba de nuevo."<<endl;
		}
		else{
			if(buscarCurso(curso) == true){ //el curso existe
				cout<<"EN PROCESO DE IMPRESION"<<endl;
				//tenemos que hacer 3 comprobaciones,
				//la primera es si el curso tienee aforo
				//la segunda es ver si se tienen los estudios requeridos
				//la tercera es ver si es antes de la fecha de inicio
				ifstream f;
				f.open("open.txt", ios::in);
				if(f.fail()){
					cout<<"Error al leer fichero open"<<endl;
					exit(1);
				}
				for(int i = 1; i < curso; i++){//recorre cursos
					for(int l = 0; l < 10; l++){//recorre atributos de cada curso
						getline(f, linea);
					}
				}
				for(int i = 0; i < 5; i++){
					getline(f, linea);//recorre de ID a descripcion
				}
				getline(f, estudios);//capta estudios
				if(get_estudios() == estudios){//comprobacion estudios
					ticks++;
				}
				getline(f, aforo);//aforo
				getline(f, date);//fecha inicio
				auto now = chrono::system_clock::now();//semilla reloj activa
				time_t end_time = chrono::system_clock::to_time_t(now);//semilla parada y guarda hora
				string ahora = ctime(&end_time); //guardamos fecha en ahora
				if(comprobarFecha(ahora, date)==true){
					ticks++;
				}
				getline(f, linea);//fecha fin
				getline(f, participantes);//participantes
				partips = stoi(participantes);
				afor = stoi(aforo);
				if(partips < aforo)
					ticks++;
				//tengo que hacer la edicion de la bbdd y el resultado buleano
			}
			else{
				cout<<"No te matriculas en nada."<<endl;
				valid = true;
			}
		}

	}
	return false;
}
void Participante::globalset(){

}
bool comprobarFecha(string ahora, string date){
	//Comparar año
	int yearA, yearB, checks = 0;
	string anoActual, anoInicio;
	anoActual = ahora.substr(20,23);
	anoInicio = date.substr(20,23);
	yearA = stoi(anoActual);
	yearB = stoi(anoInicio);
	if(yearA == yearB){ //Si el año es el mismo años tenemos que averiguar el mes y el dia
		checks++;
		//Comparar Mes
		int nmesA, nmesB;
		string mesActual, mesInicio;
		string dicciMeses[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; //Diccionario meses
		mesActual = ahora.substr(4,6);
		mesInicio = date.substr(4,6);
		for(int i = 0; i < 12; i++){//pasamos los meses a numeros
			if(mesActual == dicciMeses[i])
				nmesA = i;
			else if(mesInicio == dicciMeses[i])
				nmesB = i;
		}
		if(nmesA == nmesB){//si estamos antes(<) o en el mismo mes (=) estamos bien
			checks++;
			//Comparar Dia
			int dayA, dayB;
			string diaActual, diaInicio;
			diaActual = ahora.substr(9,9);
			diaInicio = date.substr(9,9);
			dayA = stoi(diaActual);
			dayB = stoi(diaInicio);
			if(dayA < dayB){//si nos matriculamos un dia antes si podemos
				checks++;
			}
			else{
				cout<<"Este curso ya ha empezado(d)."<<endl;
				return false;
			}
		}
        else if(nmesA < nmesB) //si es el mismo año pero el mes de matricula es menor estamos bien
            return true;
		else{
			cout<<"Este curso ya ha empezado(m)."<<endl;
			return false;
		}
	}
    else if(anoActual < anoInicio)//si el año actual es menos que el inicial, directamente estamos en la fecha
        return true;
	else{
		cout<<"Este curso ya ha empezado(a)."<<endl;
		return false;

	}
	if(checks == 3){
		cout<<"!!!FECHA CORRECTA!!!"<<endl;
		return true;
	}
	else if(checks == 2){
		cout<<"LLEGAS UNOS DIAS TARDE"<<endl;
		return false;
	}
	else if(checks == 1){
		cout<<"LLEGAS UNOS MESES TARDE"<<endl;
		return false;
	}
	else if(checks == 0){
			cout<<"LLEGAS UNOS ANHITOS TARDE"<<endl;
			return false;
	}
	return false;
}
bool buscarCurso(int curso){
	int i = 1, c;
	string linea,nombre;
	ifstream fichero;
	fichero.open("open.txt", ios::in);
	if(fichero.fail()){
		cout<<"Error al acceder al fichero de cursos"<<endl;
		exit(1);
	}
	while(!fichero.eof() || i < curso){
		for(int j = 0; j < 10 ; j++){
			getline(fichero, linea);//escaneamos un curso completo
		}							//hasta llegar al que queremos
			i++;
	}
	if(i == curso){
		getline(fichero, nombre);//nombre del curso que queremos
		fichero.close();
		cout<<"Es <"<<nombre<<"> el curso donde te quieres matricular?"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cin>>c;
		if(c == 1)
			return true;
		else
			return false;

	}
	else if(fichero.eof()){
		cout<<"No se ha podido acceder al curso"<<endl;
		return false;
	}
	return false;
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
bool opcionaMatricula(){
	int c;
	cout<<"Desea matricularse en algun curso?"<<endl;
	cout<<"1. Si"<<endl;
	cout<<"2. No"<<endl;
	cin>>c;
	switch(c){
	case 1:
		return true;
		break;
	default:
		return false;
		break;
	}
	return false;
}

