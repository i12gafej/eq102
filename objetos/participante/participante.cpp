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
			bool tri = false;
			while(tri != true){//o si hay guion no escanea nada
				if(linea != "-"){
					v.push_back(linea);
					getline(f, linea);
				}
				else
					tri = true;
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
//funcion recursiva que concatena los nombres de los cursos matriculados
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
		cout<<"En que curso de extension de los "<<cual<<" desea matricularse?"<<endl;
		cin>>curso;
		if(curso < 1 || curso > cual){
			cout<<"Curso no valido, prueba de nuevo."<<endl;
		}
		else{
			if(buscarCurso(curso, cual) == true){ //el curso existe
				cout<<"EN PROCESO DE IMPRESION"<<endl;
				//tenemos que hacer 4 comprobaciones,
				//antes que nada ver si el alumno esta matriculado ya
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
				string cmat = get_cmatriculados();
				cout<<cmat<<endl;
				if(cmat.find(nombre)){
					cout<<"Este alumno ya esta registrado en el curso"<<endl;
					return false;
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
				cout<<"Hay "<<partips<<" participantes ";
				afor = stoi(aforo);
				cout<<"para un aforo de "<<afor<<" estudiantes"<<endl;
				if(partips < afor)
					ticks++;
				else{
					cout<<"Aforo completo"<<endl;
				}

				f.close();
				if(ticks == 3){
					if(actualizarCursos(partips, cual, curso)==true){
						cout<<"Base de datos actualizada."<<endl;
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
						cout<<"Error al actualizar base de datos de cursos."<<endl;
						return false;
					}

				}
				else{
					cout<<"No puedes matricularte en este curso, ya que no se cumplen los requerimientos posibles para ello."<<endl;
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
        v.push_back(linea);
		if(linea == dni){
			posi = lines; //guardamos la posicion del dni del alumno matriculado
            cout<<"Posicion de la linea del dni que buscamos aqui <"<<posi<<">"<<endl;
		}
        cout<<"v["<<lines<<"]= "<<linea<<endl;
		lines++;
	}
    if(v[v.size()-1] != "-"){ //Si no es un gion el ulitmo elemento del fichero eliminamos el ultimo elemento del vector para no crear espacios en blanco
        v.pop_back();
    }
    cout<<"Numero de lineas: "<<lines<<endl;
    cout<<"Numero de elementos de v: "<<v.size()<<endl;
	re.close();
	ofstream wr;
	wr.open("matriculas.txt", ios::out);//machaca open con los datos actualizados
	if(wr.fail()){
		cout<<"Error de abrir fichero de escritura."<<endl;
		return false;
	}
	int i = 0, flag = 0, iter = 0;
	while(i < v.size()){
		if(i == posi + 5 && flag == 0){		//si estamos en 5 posiciones del dni
			wr<<nombre<<endl;   //escribimos el curso al que se ha matriculado
            cout<<"v["<<iter<<"]= "<<nombre<<endl;
            flag++;
            iter++;
        }
		else{
			wr<<v[i]<<endl;
            cout<<"v["<<i<<"]= "<<v[i]<<endl;
            i++;
            iter++;
        }
	}
	wr.close();
	return true;
}
bool actualizarCursos(int p, int ncursos, int curso){
	//bolcar datos en vector e imprimirlos en open.txt
	string a[10][ncursos], ausi;
    curso--;
	ifstream re;
	int c = 0, lines = 0;
	re.open("open.txt", ios::in);
	if(re.fail()){
		cout<<"Error de abrir fichero de lectura."<<endl;
		return false;
	}
    string participantes = to_string(p+1);
	while(!re.eof() && c < ncursos){
		for(int i = 0 ; i < 10 ; i++){
			if(i == 9 && c == curso){
				a[9][c] = participantes;
                cout<<"a["<<i<<"]["<<c<<"] = "<<a[i][c]<<endl;
                getline(re, ausi);
            }
			else{
				getline(re, a[i][c]);
                cout<<"a["<<i<<"]["<<c<<"] = "<<a[i][c]<<endl;

            }
            lines++;
		}
		c++;
        cout<<"c = "<<c<<endl;
	}

    c = 0;
	re.close();
    cout<<"TAMOS BIEEEEEEN"<<endl;
    cout<<"---------------------------------"<<endl;
	ofstream wr;
	wr.open("open.txt", ios::out);//machaca open con los datos actualizados
	if(wr.fail()){
		cout<<"Error de abrir fichero de escritura."<<endl;
		return false;
	}
    cout<<"TAMOS CHULITOO"<<endl;
    cout<<"---------------------------------"<<endl;
	while(!wr.eof() && c < ncursos){
		for(int i = 0 ; i < 10 ; i++){
			if(i == 9 && c == ncursos - 1){
                wr<<a[i][c];
                cout<<"a["<<i<<"]["<<c<<"] = "<<a[i][c]<<endl;
            }
            else{
                wr<<a[i][c]<<endl;
                cout<<"a["<<i<<"]["<<c<<"] = "<<a[i][c]<<endl;
            }
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
	while(i < curso && i < ncursos){
		for(int j = 0; j < 10 ; j++){
			getline(fichero, linea);//escaneamos un curso completo
			cout<<linea<<endl;
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
		cout<<"No se ha podido acceder al curso(f)"<<endl;
		return false;
	}
	else{
		cout<<"No se ha podido acceder al curso(otro)"<<endl;
		return false;
	}
	return false;
}
void Participante::paginaParticipante(int vez){
	if(vez == 0){ //Si es la primera vez que entra pone vienbenido
		cout<<"BIENVENIDO <"<<get_nombre()<<">."<<endl;
		cout<<"-------------------------------------------------"<<endl;
	}
	int c;
	bool mat;
	cout<<"Que desea hacer?"<<endl;
	menuParticipante();
	cin>>c;
	switch(c){
	case 1:
		verListas();
		if(opcionaMatricula() == true){
			mat = matricularse();
			if(mat == false || mat == true){
				if(mat == true)
					cout<<"Inscripcion con exito"<<endl;
				paginaParticipante(1);
			}

		}
		else{
			paginaParticipante(1);
		}
	break;
	case 2:
		exit(1);
	default:
		cout<<"Argumento no valido";
	}
}
void menuParticipante(){
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

