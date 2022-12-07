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
void Participante::globalget(string cor){
	ifstream f;
	string linea, atribs[5];
	vector<string> v;
	v.push_back("");
	int ncmat = 0, iters;
	f.open("matriculas.txt", ios::in);
	if(f.fail()){
		cout<<"Error al obtener datos en fichero matricula."<<endl;
		return;
	}
	while(!f.eof()){
		getline(f, linea);//escanea cada linea hasta dar con el correo
		if(linea == cor){
			for(int i = 0 ; i < 5 ; i++){
				getline(f, linea);//escaneamos dni, nombre, estudios, telefono y nacimiento
				atribs[i] = linea;
			}
			getline(f, linea); //escaneamos los cursos
			while(linea != '-'){//o si hay guion no escanea nada
				v.push_back(linea);
				getline(f, linea);
			}
		}
	}
	iters = v.size();
	set_dni(atribs[0]);
	set_nombre(atribs[1]);
	set_estudios(atribs[2]);
	set_telefono(atribs[3]);
	set_nacimiento(atribs[4]);
	string cursos;
	cursos = concatenar(v, iters-1);
	set_cmatriculados(cursos);


}
string concatenar(vector<string> v, int n){
	string resul;
    if(n < 0){
		return resul + ".";
	}
    else if(n == 0)
        resul = v[n] +  concatenar(v, n-1);
    else{
        resul = v[n] + ", " + concatenar(v, n-1);
    }
    return resul;
}
bool Participante::matricularse(){
	bool valid = false;
	string aforo, date, estudios, linea, participantes, nombre;
	int cual, curso, ticks = 0, partips, afor;
	while(valid != true){
		cual = Usuario::verListas();
		cout<<"En que curso de extension desea matricularse?"<<endl;
		cin>>curso;
		if(curso < 1 || curso > cual){
			cout<<"Curso no valido, prueba de nuevo."<<endl;
		}
		else{
			if(buscarCurso(curso, cual) == true){ //el curso existe
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
					//recorre de ID a descripcion
					if(i == 1){
						getline(f, nombre);
					}
					else
						getline(f, linea);
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
				f.close();
				if(actualizarCursos(partips, cual, curso)==true){
					cout<<"Base de datos actualizada."<<endl;
				}
				else{
					cout<<"Error al actualizar base de datos de cursos."<<endl;
					return false;
				}
				if(actualizarMatricula(get_dni(), nombre)==true){
					cout<<"Base de datos de matriculas acctuaalizada."<<endl;
					valid = true;
					return true;
				}
				else{
					cout<<"Error al actualizar base de datos de matriculas."<<endl;
					return false;
				}

			}
			else{
				cout<<"No te matriculas en nada."<<endl;
				valid = true;
			}
		}
	}
	return false;
}
bool actualizarMatricula(string dni, string nombre){
	ifstream re;
	int posi = 0, lines = 0;
	vector<string> v;
	string linea;
	re.open("matriculas.txt", ios::in);
	if(re.fail()){
		cout<<"Error de abrir fichero de lectura."<<endl;
		return false;
	}
	while(!re.eof()){
		getline(re, linea);
		if(linea == dni){
			posi = lines; //guardamos la posicion del dni del alumno matriculado
		}
		v.push_back(linea);
		lines++;
	}
	lines++;
	re.close();
	ofstream wr;
	wr.open("matriculas.txt", ios::out);//machaca open con los datos actualizados
	if(wr.fail()){
		cout<<"Error de abrir fichero de escritura."<<endl;
		return false;
	}
	int i = 0;
	while(!wr.eof() || i <= lines){
		if(i == posi + 5)		//si estamos en 5 posiciones del dni
			wr<<nombre<<endl;   //escribimos el curso al que se ha matriculado
		else
			wr<<v[i]<<endl;
		i++;
	}
	wr.close();
	return true;
}
bool actualizarCursos(int p, int ncursos, int curso){
	//bolcar datos en vector e imprimirlos en open.txt
	string a[10][ncursos];
	ifstream re;
	int c = 0;
	re.open("open.txt", ios::in);
	if(re.fail()){
		cout<<"Error de abrir fichero de lectura."<<endl;
		return false;
	}
	while(!re.eof() && c < ncursos){
		for(int i = 0 ; i < 10 ; i++){
			if(i == 9 && c == curso)
				a[i][c] = p;
			else
				getline(re, a[i][c]);
		}
		c++;
	}
	re.close();
	ofstream wr;
	wr.open("open.txt", ios::out);//machaca open con los datos actualizados
	if(wr.fail()){
		cout<<"Error de abrir fichero de escritura."<<endl;
		return false;
	}
	while(!wr.eof() && c < ncursos){
		for(int i = 0 ; i < 10 ; i++){
			wr<<a[i][c]<<endl;
		}
		c++;
	}
	wr.close();
	return true;
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
bool buscarCurso(int curso, int ncursos){
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
	if(i == curso && i <= ncursos){//si la posicion está en el curso y no supera los ncursos estamos bien
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
	else{
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

