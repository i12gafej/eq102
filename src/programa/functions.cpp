/*
 * functions.cpp
 *
 *  Created on: 11 dic 2022
 *      Author: USUARIO
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "objects.h"
#include <unistd.h>

using namespace std;

//Constructor usuario
Usuario::Usuario(string correo, string contra){
	correo_ = correo;
	contra_ = contra;
}
//constructor coordinador de curso
Ccurso::Ccurso(string correo, string contra, list<Curso> listas):Usuario(correo, contra){}
//constructor participante
Participante::Participante(string correo,
		string contra,
		string nombre = "null",
		string dni = "null",
		string estudios = "null",
		string telefono = "null",
		string nacimiento = "null",
		string cmatriculados = "null"):Usuario(correo, contra){}
//COnstructor visitante
Visitante::Visitante(string correo, string contra):Usuario(correo, contra){}
Curso::Curso(string id, 
		string nombre, 
		string docentes, 
		string contactos, 
		string descripcion, 
		string estudios, 
		string aforo, 
		string inicio, 
		string fin, 
		string participantes){}
//FUNCIONES DE USUARIO Y VISITANTE
bool arroba(string cor){
	int c = 0, dot = 0, posi;
	vector<int> dist;//guarda la distancia entre puntos
	dist.push_back(0);
	for(int i = 0; i < cor.length(); i++){
		if(cor[i]=='@'){
			c++;
			posi = i;

		}
		else if(cor[i]=='.'){
			if(i != 0){//si se encuentra el punto en una posicion que no sea la primera
				if(dist[0] == 0){//si se encuentra el primero lo gaurda en dist[0]
					dist[0] = i;
					dot++;
				}
				else{//si no es el primero que guarda
					dist.push_back(dot);//añade el calor de distancia entre el anterior y el siguiente
					dist[dot] = dist[dot] - dist[dot-1]; //y hace que el valor sea la anterior distancia menos la actual encontrada
					dot++;
				}
			}
			else if(i == 0){// si es la primera letra el punto no se hace comprobacion porque es erroneo
				cout<<"FORMATO NO VALIDO <No puedes poner ese punto al principio>"<<endl;
				return false;
			}
			else if(c == 1){//si ya ha encontrado un arroba
				dot++;
				cout<<"HAY ."<<endl;
			}
		}
	}
	int dis = dist.size();
	for(int i = 0; i < dis; i++){
		if(dist[i] == 1 && i != 0){
			cout<<"FORMATO NO VALIDO <dot separation :"<<dist[i]<<">"<<endl;
			return false;
		}
	}
		//cout<<"Correo: "+ cor + " y substring " + cor.substr(posi, 7)<<endl;
	if(c == 1 && (dot >= 1 && dot == dis)){
		if(cor.substr(posi, 7) != "@uco.es"){
			cout<<"No es un correo de la uco"<<endl;
			return false;
		}
		else{
			return true;
		}
	}
	else{
		cout<<"Eso no es un correo valido"<<endl;
	}
	return false;
}
struct Us introducirUsuarioyContrasenia(){
	system("clear");
	struct Us usuario;
    cout<<"Introducir correo: ";
    cin>>usuario.correo;
    cout<<"Introducir contrasenya: ";
    cin>>usuario.contra;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    return usuario;

}
bool Usuario::iniciarSesion(string cor, string contra, int *role){
    system("clear");
	if(comprobar_coincidencia(cor,contra, &role)==true){
        set_correo(cor);
        set_contra(contra);

        cout<<"Inicio de sesion con exito"<<endl;
		sleep(2);
        return true;
    }
    else{
        cout<<"No se ha podido iniciar sesion."<<endl;
		sleep(2);
        return false;
    }

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
bool comprobar_coincidencia(string cor, string con, int **rol){
	ifstream fich;
	int c = 0;
    if(arroba(cor) == false){
        return false;
    }
	string arriba, abajo, us;
	fich.open("logs.txt", ios::in);//abrimos en modo lectura
	if(fich.fail()){
		cout<<"Error al abrir fichero"<<endl;
		return false;
	}
	while(!fich.eof()){
		getline(fich, arriba);//hago esto porque la estructura de la base de datos va a ser linea de correo y la siguiente linea de contraseña
		getline(fich, abajo);
		getline(fich, us);
		if(arriba == cor && abajo == con){
			c++;
			**rol = stoi(us);
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
int Usuario::verPagina(int vez, list<Curso> listas){
	if(vez == 0){
		cout<<"BIENVENIDO A NUESTRA PAGINA WEB"<<endl;
		cout<<"-------------------------------------------------"<<endl;
	}
	
	int c, d = 0, rol;
    struct Us usuario;
	cout<<"Que desea hacer?"<<endl;
	menu();
	cin>>c;
	//while(d == 0){
		switch(c){
		case 1:
			usuario = introducirUsuarioyContrasenia();
            if(iniciarSesion(usuario.correo, usuario.contra, &rol) == true){
				if(rol == 1){
                    return 1;//participante
                }
                else if(rol == 2){
                    return 2;//coordinador de curso
                }
            }
            else{
                return 0;
            }
		break;
		case 2:
			verListas(listas);
			cout<<endl;
			cout<<endl;
			cout<<endl;
			cout<<endl;
			return 3;
		break;
		case 3:
			usuario = introducirUsuarioyContrasenia();
			if(registrarUsuario(usuario.correo, usuario.contra) == true){
				registrar(usuario.correo, usuario.contra);//lo pone en el fichero logs.txt
				return 1;
			}
		break;
		default:
			cout<<"Argumento no valido";
		}
	//}
	return -1;
}

void menu(){
	cout<<"1. Iniciar Sesion"<<endl;
	cout<<"2. Ver cursos de extension"<<endl;
	cout<<"3. Registrar Usuario"<<endl;
}

bool Usuario::registrarUsuario(string cor, string cotra){
	//tengo que comprobar que el correo sea bueno y que no este ya registrado
	if(arroba(cor)== false){//no sea correo de la uco y no tenga el @ ni .
		return false;
	}
	if(comprobar_correo(cor) == true){
		cout<<"Este correo ya ha sido introducido"<<endl;
		return false;
	}
	else{
		system("clear");
		cout<<"Usuario registrado con exito"<<endl;
		set_correo(cor);
        set_contra(cotra);
		return true;
	}
}
bool distancia(string cor){
	int posi = 0, dot = 0, comprobantes = 0;
	for(int i = 0; i < cor.length(); i++){
		if(cor[i]=='@')
			posi = i;
		}
	for(int i = posi; i < cor.length(); i++){
		if(cor[i] == '.')
			dot = i;
	}
	if((dot - posi) > 4){
		cout<<"Dominio no válido"<<endl;
		return false;
	}
	if(cor.substr(posi, 7) != "@uco.es"){
		cout<<"Correo: "+ cor + " y substring " + cor.substr(posi, 7)<<endl;
		cout<<"No es un correo de la uco"<<endl;
		return false;
	}
	return true;
}

int contarUsuarios(){
	ifstream f;
	string linea;
	int c = 0;
	f.open("logs.txt", ios::in);
	if(f.fail()){
		cout<<"Error de abrir fichero"<<endl;
		return -1;
	}
	while(!f.eof()){
		getline(f, linea);
		c++;
	}
	f.close();
	return c/3;
}
void registrar(string cor, string con){
    int i = 0, n = contarUsuarios();
    ifstream re;
    ofstream wr;
    string a, b, rol;
    vector<string> v;
	re.open("logs.txt", ios::in);//abrimos en modo lectura
	if(re.fail()){
		cout<<"Error al abrir fichero de lectura"<<endl;
		exit(1);
	}
	while(!re.eof() && i < n){//hasta que no llegue al numero de usuarios no para
			getline(re, a);
	        getline(re, b);
	        getline(re, rol);
	        v.push_back(a);
	        v.push_back(b);
	        v.push_back(rol);
	        i++;
	}
	v.push_back(cor);
	v.push_back(con);
	v.push_back("1");
	n++; //aumenta uno porque añadimos a una persiona

	re.close();
	/*for(int i = 0; i < n*2; i++){
		cout<<v[i]<<endl;
	}*/
    wr.open("logs.txt", ios::out);//abrimos en modo escritura
    if(wr.fail()){
		cout<<"Error al abrir fichero de escritura"<<endl;
		exit(1);
	}
	i = 0;
    for(int j = 0; j < n*3; j++){//hasta que no llegue al numero de usuarios no para
    	if(j == n*3 -1)
    		wr<<v[j]; //en la ultima impresion no mete un enter de mas
    	else
    		wr<<v[j]<<endl;//fila a fila
    }
    wr.close();
}
void Usuario::verListas(list<Curso> listas){//cada curso ocupara varias lineas
	
	int n = contarlineas(), c = 1;
	if(n <= 1){
		cout<<"No hay cursos disponibles"<<endl;
	}
	
	list<Curso>::iterator it;
	for(it = listas.begin(); it != listas.end(); it++){
		//nombre
		cout<<c<<". "<<it->get_nombre()<<endl;
		//ID
		cout<<"ID: "<<it->get_id()<<endl;
		//Docentes
		cout<<"Docentes:"<<it->get_docentes()<<endl;
		//Contacto
		cout<<"Contacto de docentes"<<it->get_contactos()<<endl;
		//Descripcion
		cout<<"Descripcion: "<<it->get_descripcion()<<endl;
		//estudios requeridoss
		cout<<"Estudios requeridos"<<it->get_estudios()<<endl;
		//Aforo
		cout<<"Aforo maximo: "<<it->get_aforo()<<endl;
		//Fecha de Inicio
		cout<<"Fecha de Inicio del Curso: "<<it->get_inicio()<<endl;
		//Fecha de Final
		cout<<"Fecha de finalizacion del Curso: "<<it->get_fin()<<endl;
		//N participantes cursando
		cout<<"Participantes del curso: "<<it->get_participantes()<<endl;
		cout<<"-------------------------------------------------"<<endl;
		c++;
	}
}
int contarlineas(){
	ifstream d;
	string ausi;
	int c = 0;
	d.open("open.txt", ios::in);
	if(d.fail()){
		cout<<"Error al abrir fichero de cursos"<<endl;
		exit(1);
	}
	while(!d.eof()){
		getline(d, ausi);//lee todas las lineas hasta topar con el titulo
		//cout<<"Linea "<<c<<": "+ausi<<endl;
		c++;
	}
	d.close();
	return c;
}
int contarMatricula(){
	ifstream d;
	string ausi;
	int c = 0;
	d.open("matriculas.txt", ios::in);
	if(d.fail()){
		cout<<"Error al abrir fichero de cursos"<<endl;
		exit(1);
	}
	while(!d.eof()){
		getline(d, ausi);//lee todas las lineas hasta topar con el titulo
		//cout<<"Linea "<<c<<": "+ausi<<endl;
		c++;
	}
	d.close();
	return c;
}
bool Participante::globalset(string cor){
	
	ifstream f, g;
	string linea, atribs[5], a,b,rol;
	vector<string> v;
	v.push_back("");
	int ncmat = 0, iters, flag = 0, n = contarMatricula(), contador = 0;
	f.open("matriculas.txt", ios::in);
	g.open("logs.txt", ios::in);
	if(f.fail() || g.fail()){
		cout<<"Error al obtener datos en fichero matricula."<<endl;
		return false;
	}
	while(contador < n){
		getline(f, linea);//escanea cada linea hasta dar con el correo
		
		if(linea == cor){
			flag++;
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
		contador++;
	}
		
	if(flag == 0){
		while(!g.eof()){
			getline(g, a);
			getline(g, b);
			getline(g, rol);
			if(cor == a){
				if(rol == "2"){//si tenemos a un coordinador de curso pasamos de aniadir sus datos
					flag = 1;
				}
			}
		}
	}
	f.close();
	g.close();
	if(flag == 0){//no se ha encontrado el correo en los perfiles, no esta registrado
		cout<<"No tienes datos en la base de datos"<<endl;
		cout<<"Vas a introducir tus datos personales"<<endl;
		sleep(2);
		//dni
		system("clear");
		cout<<"Introduce tu DNI: ";
		cin>>atribs[0];
		cout<<endl;
		system("clear");
		cout<<"Introduce Tu nombre completo: ";
		getline(cin,atribs[1]);
		getline(cin,atribs[1]);
		cout<<endl;
		system("clear");
		cout<<"Elige tus estudios: "<<endl;
		atribs[2] = estudiosPosibles() ;
		cout<<endl;
		system("clear");
		cout<<"Introduce numero de telefono: ";
		cin>>atribs[3];
		cout<<endl;
		system("clear");
		cout<<"Seleccione su Fecha de nacimiento: "<<endl;
		atribs[4] = fechaPosible();
	}
	iters = v.size();
	set_dni(atribs[0]);
	set_nombre(atribs[1]);
	set_estudios(atribs[2]);
	set_telefono(atribs[3]);
	set_nacimiento(atribs[4]);
	if(flag != 0){
		string cursos;
		cursos = concatenar(v, iters-1);
		cout<<"ESTA MATRICULAO EN "<<cursos<<endl;
		set_cmatriculados(cursos);
		return true;
	}
	else if(flag == 0){
		if(imprimirPerfilNuevo(cor, atribs)==true){
			cout<<"ENORABUENA, Registrado con exito"<<endl;
			sleep(2);
			return true;
		}
	}
	return true;
}
//FUNCIONES DE PARTICIPANTE
bool imprimirPerfilNuevo(string cor, string w[]){
	ifstream re;
	vector<string> v;
	string linea;
	int lines = 0;
	re.open("matriculas.txt", ios::in);
	if(re.fail()){
		cout<<"Error de abrir fichero de lectura."<<endl;
		return false;
	}
	while(!re.eof()){
		getline(re, linea);
		v.push_back(linea);
		lines++;
	}
	if(v[v.size()-1] != "-"){ //Si no es un gion el ulitmo elemento del fichero eliminamos el ultimo elemento del vector para no crear espacios en blanco
		v.pop_back();
	}
	//cout<<"Numero de lineas: "<<lines<<endl;
	//cout<<"Numero de elementos de v: "<<v.size()<<endl;
	re.close();
	ofstream wr;
	wr.open("matriculas.txt", ios::out);//machaca matriculas con los datos actualizados
	if(wr.fail()){
		cout<<"Error de abrir fichero de escritura."<<endl;
		return false;
	}
	int i = 0;
	while(i < v.size()){
		wr<<v[i]<<endl;
		i++;
	}
	//cout<<"COR "<<cor<<endl;
	wr<<cor<<endl;
	wr<<w[0]<<endl;
	wr<<w[1]<<endl;
	wr<<w[2]<<endl;
	wr<<w[3]<<endl;
	wr<<w[4]<<endl;;
	wr<<"-";

	wr.close();
	return true;
}

string fechaPosible(){
	//Ano
	int ano = 0, anoFlag = 0, mesFlag=0, mes, dayFlag = 0, dia;
	bool visiesto = false;
	string sano, smes, sdia;
	while(anoFlag == 0){
		system("clear");
		if(ano == 0)
			cout<<"Introduce el anio de tu nacimiento: ";
		else
			cout<<"Introduce de nuevo tu anio de nacimiento: ";
		cin>>ano;
		if(ano < 1915 || ano > 2013){ //Ni mas de 107 ni menos de 9 anios xd
			cout<<"Fecha de nacimiento no valida"<<endl;
			sleep(2);
		}
		else{
			sano = to_string(ano);
			if(ano % 4 == 0){
				visiesto = true;
			}
			anoFlag = 1;
		}
	}
	//Mes
	while(mesFlag == 0){
		system("clear");
		cout<<"Mes: "<<endl;
		cout<<"1. Enero"<<endl;
		cout<<"2. Febrero"<<endl;
		cout<<"3. Marzo"<<endl;
		cout<<"4. Abril"<<endl;
		cout<<"5. Mayo"<<endl;
		cout<<"6. Junio"<<endl;
		cout<<"7. Julio"<<endl;
		cout<<"8. Agosto"<<endl;
		cout<<"9. Septiembre"<<endl;
		cout<<"10. Octubre"<<endl;
		cout<<"11. Noviembre"<<endl;
		cout<<"12. Diciembre"<<endl;
		cout<<"Introduce el mes de tu nacimiento: ";
		cin>>mes;
		if(mes > 0 && mes < 13){
			switch(mes){
				case 1:
					mes = 1;
					smes = "01";
				break;
				case 2:
					mes = 2;
					smes = "02";
				break;
				case 3:
					mes = 3;
					smes = "03";
				break;
				case 4:
					mes = 4;
					smes = "04";
				break;
				case 5:
					mes = 5;
					smes = "05";
				break;
				case 6:
					mes = 6;
					smes = "06";
				break;
				case 7:
					mes = 7;
					smes = "07";
				break;
				case 8:
					mes = 8;
					smes = "08";
				break;
				case 9:
					mes = 9;
					smes = "09";
				break;
				case 10:
					mes = 10;
					smes = "10";
				break;
				case 11:
					mes = 11;
					smes = "11";
				break;
				case 12:
					mes = 12;
					smes = "12";
				break;
			}
			mesFlag = 1;
		}
		else{
			cout<<"Fecha no valida"<<endl;
			sleep(2);
		}
	}

	while(dayFlag == 0){
		system("clear");
		cout<<"DIA: "<<endl;
		cout<<"01  ";cout<<"02  ";cout<<"03  ";cout<<"04  ";cout<<"05  ";cout<<"06  ";	cout<<"07  "<<endl;
		cout<<"08  ";cout<<"09  ";cout<<"10  ";cout<<"11  ";cout<<"12  ";cout<<"13  ";	cout<<"14  "<<endl;
		cout<<"15  ";cout<<"16  ";cout<<"17  ";cout<<"18  ";cout<<"19  ";cout<<"20  ";	cout<<"21  "<<endl;
		cout<<"22  ";cout<<"23  ";cout<<"24  ";cout<<"25  ";cout<<"26  ";cout<<"27  ";	cout<<"28  "<<endl;
		cout<<"29  ";cout<<"30  ";cout<<"31  "<<endl;
		cout<<"Introduce el dia: ";
		cin>>dia;
		if(dia > 0 && dia < 32){ //dia valido
			if(mes == 2 && dia < 30){//si es febrero
				if(dia == 29 && visiesto == true){//es 29 y es visiesto
					cout<<"Dia 29 de febrero valido"<<endl;
					sdia = "29";
					dayFlag = 1;
				}
				else if(dia == 29 && visiesto != true){ //si es 29 y no es visiesto
					cout<<"No puede ser posible"<<endl;
					sleep(2);
				}
				else if(dia != 29){//si no es 29 y me da igual que sea visiesto
					cout<<"Dia valido"<<endl;
					sdia = to_string(dia);
					dayFlag = 1;
				}
			}
			else if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
				if(dia == 31){
					cout<<"Error, este 31 no existe"<<endl;
					sleep(2);
				}
				else{
					cout<<"Dia valido"<<endl;
					sdia = to_string(dia);
					dayFlag = 1;
				}
			}
			else if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
				cout<<"Dia valido"<<endl;
				sdia = to_string(dia);
				dayFlag = 1;
			}
			else{
				cout<<"Dia no valido porque no existe el 30 o 31 de febrero"<<endl;
				sleep(2);
			}
		}
	}
	if(dayFlag == 1){
		if(sdia.length() == 1){
			return "0"+sdia + smes + sano;
		}
		else
			return sdia + smes + sano;
	}
	return "";
}
string estudiosPosibles(){
	int flag = 0, i = 0, c;
	string value = "";
	while(flag != -1){
		system("clear");
		cout<<"1. Grado en Administración y Dirección de Empresas"<<endl;
		cout<<"2. Grado en Biología"<<endl;
		cout<<"3. Grado en Bioquímica"<<endl;
		cout<<"4. Grado en Ciencias Ambientales"<<endl;
		cout<<"5.Grado en Ciencia y Tecnología de los Alimentos"<<endl;
		cout<<"6.Grado en Cine y Cultura"<<endl;
		cout<<"7.Grado en Derecho"<<endl;
		cout<<"8.Grado en Educación Infantil"<<endl;
		cout<<"9.Grado en Educación Infantil (Itinerario Bilingüe)"<<endl;
		cout<<"10.Grado en Educación Primaria"<<endl;
		cout<<"11.Grado en Educación Primaria (Itinerario Bilingüe)"<<endl;
		cout<<"12.Grado en Educación Social"<<endl;
		cout<<"13.Grado en Enfermería"<<endl;
		cout<<"14.Grado en Estudios Ingleses"<<endl;
		cout<<"15.Grado en Filología Hispánica"<<endl;
		cout<<"16.Grado en Física"<<endl;
		cout<<"17.Grado en Fisioterapia"<<endl;
		cout<<"18.Grado en Gestión Cultural"<<endl;
		cout<<"19.Grado en Historia"<<endl;
		cout<<"20.Grado en Historia del Arte"<<endl;
		cout<<"21.Grado en Psicología"<<endl;
		cout<<"22.Grado en Ingeniería Civil (2 tecnologías)"<<endl;
		cout<<"23.Grado en Ingeniería Eléctrica"<<endl;
		cout<<"24.Grado en Ingeniería Electrónica Industrial"<<endl;
		cout<<"25.Grado en Ingeniería Forestal"<<endl;
		cout<<"26.Grado en Ingeniería Informática"<<endl;
		cout<<"27.Grado en Ingeniería Mecánica"<<endl;
		cout<<"28.Grado en Veterinaria"<<endl;
		cout<<"29.Grado en Medicina"<<endl;
		cout<<"30.Grado en Química"<<endl;
		cout<<"31.Grado en Relaciones Laborales y Recursos Humanos"<<endl;
		cout<<"32.Grado en Traducción e Interpretación"<<endl;
		cout<<"33.Grado en Turismo"<<endl;
		cout<<"34.Grado en Ingeniería de Recursos Energéticos y Mineros"<<endl;
		cout<<"35.Grado en Ingeniería Agroalimentaria y del Medio Rural"<<endl;
		cout<<"---------------------------------------------------------"<<endl;
		if(flag == 0){
			cout<<"Cual es tu grado?-->";
			cin>>c;
			flag++;
		}
		else{
			i = 0;
            cout<<"Llevas seleccionados los siguientes grados: "<<value<<endl;
			cout<<"Otro grado al que pertenezcas o tengas?-->"<<endl;
			cout<<"1. Si"<<endl;
			cout<<"2. No"<<endl;
			cin>>i;
			if(i == 1){
				cout<<"Cual?-->";
				cin>>c;
			}
			else{
				flag = -1;
                return value;
			}
		}
		switch(c){
			case 1:
				value = value + "// " + "Grado en Administración y Dirección de Empresas";
			break;
			case 2:
				value = value + "// " + "Grado en Biología";
			break;
			case 3:
				value = value + "// " + "Grado en Bioquímica";
			break;
			case 4:
				value = value + "// " + "Grado en Ciencias Ambientales";
			break;
			case 5:
				value = value + "// " + "Grado en Ciencia y Tecnología de los Alimentos";
			break;
			case 6:
				value = value + "// " + "Grado en Cine y Cultura";
			break;
			case 7:
				value = value + "// " + "Grado en Derecho";
			break;
			case 8:
				value = value + "// " + "Grado en Educación";
			break;
			case 9:
				value = value + "// " + "Grado en Educación Infantil (Itinerario Bilingüe)";
			break;
			case 10:
				value = value + "// " + "Grado en Educación Primaria";
			break;
			case 11:
				value = value + "// " + "Grado en Educación Primaria (Itinerario Bilingüe)";
			break;
			case 12:
				value = value + "// " + "Grado en Educación Social";
			break;
			case 13:
				value = value + "// " + "Grado en Enfermería";
			break;
			case 14:
				value = value + "// " + "Grado en Estudios Ingleses";
			break;
			case 15:
				value = value + "// " + "Grado en Filología Hispánica";
			break;
			case 16:
				value = value + "// " + "Grado en Física";
			break;
			case 17:
				value = value + "// " + "Grado en Fisioterapia";
			break;
			case 18:
				value = value + "// " + "Grado en Gestión Cultural";
			break;
			case 19:
				value = value + "// " + "Grado en Historia";
			break;
			case 20:
				value = value + "// " + "Grado en Historia del Arte";
			break;
			case 21:
				value = value + "// " + "Grado en Psicología";
			break;
			case 22:
				value = value + "// " + "Grado en Ingeniería Civil";
			break;
			case 23:
				value = value + "// " + "Grado en Ingeniería Eléctrica";
			break;
			case 24:
				value = value + "// " + "Grado en Ingeniería Electrónica Industrial";
			break;
			case 25:
				value = value + "// " + "Grado en Ingeniería Forestal";
			break;
			case 26:
				value = value + "// " + "Grado en Ingeniería Informática";
			break;
			case 27:
				value = value + "// " + "Grado en Ingeniería Mecánica";
			break;
			case 28:
				value = value + "// " + "Grado en Veterinaria";
			break;
			case 29:
				value = value + "// " + "Grado en Medicina";
			break;
			case 30:
				value = value + "// " + "Grado en Química";
			break;
			case 31:
				value = value + "// " + "Grado en Relaciones Laborales y Recursos Humanos";
			break;
			case 32:
				value = value + "// " + "Grado en Traducción e Interpretación";
			break;
			case 33:
				value = value + "// " + "Grado en Turismo";
			break;
			case 34:
				value = value + "// " + "Grado en Ingeniería de Recursos Energéticos y Mineros";
			break;
			case 35:
				value = value + "// " + "Grado en Ingeniería Agroalimentaria y del Medio Rural";
			break;
			default:
				value = value + "";
                cout<<"No existe este"<<endl;
			break;
		}
	}
    return value;
}
//funcion recursiva que concatena los nombres de los cursos matriculados
string concatenar(vector<string> v, int n){
	string resul;
    if(n < 0){
		return resul;
	}
    else if(n == 0)
        resul = v[n] +  concatenar(v, n-1);
    else{
        resul = v[n] + " // " + concatenar(v, n-1);
    }
    return resul;
}
bool Participante::comprobaciones(int curso, list<Curso> listas){
	size_t m = listas.size();
	bool valid = false;
	string aforo, date, estudios, linea, participantes, nombre;
	int  ticks = 0, partips, afor, contador = 1, cual = static_cast<int>(m);
	list<Curso>::iterator it;
	 //el curso existe
		
		for(it = listas.begin(); it != listas.end(); it++){
			if(curso == contador){
				nombre = it->get_nombre();
				
				string cmat = get_cmatriculados();
				
				cout<<endl;
				size_t found = cmat.find(nombre);//en found se guarda la posicion de encontrar
				if(found != string::npos){
					cout<<"Este alumno ya esta registrado en el curso. //"<<found<<endl;
					return false;
				}
				estudios = it->get_estudios();
				string cestudios = get_estudios();
				vector<string> studis = desglosar(cestudios, 2);
				int nestcontaos = 0;
				while(nestcontaos <= studis.size() - 1){
					found = estudios.find(studis[nestcontaos]);
					if(found != string::npos){//3. si se tienen los estudios requeridos
						cout<<ticks + 1<<". ESTUDIOS VALIDOS"<<endl;
						ticks++;
						nestcontaos = studis.size();
					}
					else{
						nestcontaos++;
					}
				}
				
				date = it->get_inicio();
				auto now = chrono::system_clock::now();//semilla reloj activa
				time_t end_time = chrono::system_clock::to_time_t(now);//semilla parada y guarda hora
				string aus = ctime(&end_time); //guardamos fecha en ahora
				string ahora = aus.substr(4);//quitamos parte del string

				if(comprobarFecha(ahora, date)==true){//4. si es antes de la fecha de inicio
					ticks++;
					cout<<ticks + 1<<". FECHA VALIDA"<<endl;
				}
				else{
					return false;
				}

				aforo = it->get_aforo();
				linea = it->get_fin();//fecha fin
				participantes = it->get_participantes();//participantes
				partips = stoi(participantes);
				//cout<<"Hay "<<partips<<" participantes ";
				afor = stoi(aforo);
				//cout<<"para un aforo de "<<afor<<" estudiantes"<<endl;
				if(partips < afor){//2. si el curso tienee aforo
					ticks++;
					cout<<ticks + 1<<". AFORO DISPONIBLE"<<endl;
					partips++;
					participantes = to_string(partips);
				}
				else{
					cout<<"Aforo completo"<<endl;
					return false;
				}
				
				if(ticks == 3){
					//if(actualizarCursos(partips, cual, curso)==true){
						it->set_participantes(participantes);
						set_listas(listas);
						//cursos actualizados
						linea = get_cmatriculados();
						nombre = nombre + " // " + linea;
						set_cmatriculados(nombre);
						//matricula actualizada
						return true;

				}
				else{
					cout<<"No cumples requisitos"<<endl;
					return false;
				}

				
			}
			contador++;
		}
		
	return false;
}

bool Participante::matricularse(int curso, int cuantos){
	if(comprobaciones(curso, get_listas()) == true){
		system("clear");
		cout<<"Has sido matriculado con exito en el curso"<<endl;
		sleep(1);
		return true;
	}
	else{
		system("clear");
		cout<<"No has podido ser matriculado en el curso, no cumples los requisitos"<<endl;
		sleep(1);
		return false;
	}

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
            //cout<<"Posicion de la linea del dni que buscamos aqui <"<<posi<<">"<<endl;
		}
        //cout<<"v["<<lines<<"]= "<<linea<<endl;
		lines++;
	}
    if(v[v.size()-1] != "-"){ //Si no es un gion el ulitmo elemento del fichero eliminamos el ultimo elemento del vector para no crear espacios en blanco
        v.pop_back();
    }
   
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
            //cout<<"v["<<iter<<"]= "<<nombre<<endl;
            flag++;
            iter++;
        }
		else{
			wr<<v[i]<<endl;
            //cout<<"v["<<i<<"]= "<<v[i]<<endl;
            i++;
            iter++;
        }
	}
	wr.close();
	return true;
}

bool comprobarFecha(string ahora, string date){//traduce la fecha chrono a la de la bbdd
	//Comparar año
	int yearA, yearB, checks = 0;
	string anoActual = ahora.substr(ahora.length()-5, 4);
	string anoInicio = date.substr(date.length()-4,4);

	yearB = stoi(anoInicio);

	yearA = stoi(anoActual);





	if(yearA == yearB){ //Si el año es el mismo años tenemos que averiguar el mes y el dia
		checks++;
		//Comparar Mes
		int nmesA, nmesB;
		string dicciMeses[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; //Diccionario meses
		string mesActual = ahora.substr(0, 3);
		string mesInicio = date.substr(3,2);
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
			string diaActual;
			if(ahora[6] == ' '){
					diaActual = "0"+ ahora.substr(5,1);
				}
				else{
					diaActual = ahora.substr(5,2);
				}
			string diaInicio = date.substr(9,9);
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
bool buscarCurso(int **curso, list<Curso> listas){
	
	list<Curso>::iterator it;
	int cual = static_cast<int>(listas.size()), contador = 1, c;
	for(it = listas.begin(); it != listas.end(); it++){
		if(**curso == contador){
			cout<<"Es <"<<it->get_nombre()<<"> el curso donde te quieres matricular?"<<endl;
			cout<<"1. Si"<<endl;
			cout<<"2. No"<<endl;
			cin>>c;
			if(c == 1){
				return true;
			}
			else{
				return false;
			}
		}
		contador++;
	}
	return false;
}void seleccionarCurso(int *curso, int *cual, list<Curso> listas){
	bool valid = false;
	while(valid != true){

		cout<<"En que curso de extension de los "<<*cual<<" desea matricularse?"<<endl;
		cout<<"--->";
		cin>>*curso;
		if(*curso < 1 || *curso > *cual){
			cout<<"Curso no valido, prueba de nuevo."<<endl;
		}
		else{
			if(buscarCurso(&curso, listas) == true){
				return;
			}
		}
	}
}

void Participante::paginaParticipante(int vez){
	cout<<endl;
	cout<<endl;
	cout<<endl;
	vector<string> cmats;
	list<Curso> listas = get_listas();
	size_t m;
	system("clear");
	if(vez == 0){ //Si es la primera vez que entra pone vienbenido
		cout<<"BIENVENIDO <"<<get_nombre()<<">."<<endl;
		cout<<"-------------------------------------------------"<<endl;
	}
	int c, curso, cual;
	bool mat;
	cout<<"Que desea hacer?"<<endl;
	menuParticipante();
	cin>>c;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	switch(c){
	case 1:
		verListas(listas);
		m = listas.size();
		cual = static_cast<int>(m);
		if(opcionaMatricula() == true){
			system("clear");
			verListas(listas);
			seleccionarCurso(&curso, &cual, listas);
			mat = matricularse(curso, cual);
			if(mat == false || mat == true){
				if(mat == true){
					cmats = desglosar(get_cmatriculados(), 2);
					if(actualizarMatricula(get_dni(), cmats[0]) == true){
						cout<<"Inscripcion con exito"<<endl;
						cout<<get_correo()<<endl;
						globalset(get_correo());
					}
					else{
						cout<<"error al actualizar bbdd"<<endl;
					}
				}
				cout<<endl;
				cout<<endl;
				cout<<endl;
				imprimirListas(get_listas());
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
		cout<<endl;
		cout<<endl;
		cout<<endl;
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
//FUNCIONES COORDINADOR DE CURSOS
int Ccurso::modificarCurso(){
	system("clear");
	int m, n, curso;
	while(1){
		list<Curso> l = get_listas();
		verListas(l);
		vector<string> atribs;
		Curso cur = Curso("", "", "", "", "", "", "", "", "", "");
		opcionMod();
		cin>>m;
		switch(m){
		case 1:
			atribs = atributos();
			cur.set_id(atribs[0]);
			cur.set_nombre(atribs[1]);
			cur.set_docentes(atribs[2]);
			cur.set_contactos(atribs[3]);
			cur.set_descripcion(atribs[4]);
			cur.set_estudios(atribs[5]);
			cur.set_aforo(atribs[6]);
			cur.set_inicio(atribs[7]);
			cur.set_fin(atribs[8]);
			cur.set_participantes(atribs[9]);
			cout<<cur.get_id()<<endl;
			cout<<cur.get_nombre()<<endl;
			cout<<cur.get_docentes()<<endl;
			cout<<cur.get_contactos()<<endl;
			cout<<cur.get_descripcion()<<endl;
			cout<<cur.get_estudios()<<endl;
			cout<<cur.get_aforo()<<endl;
			cout<<cur.get_inicio()<<endl;
			cout<<cur.get_fin()<<endl;
			cout<<cur.get_participantes()<<endl;
			
			if(crearCurso(cur) == true){
				l = get_listas();
				imprimirListas(get_listas());
				return 1;
			}
			else{
				cout<<"Curso no creado"<<endl;
				paginaCcurso(1);
			}
			break;
		case 2:{
			if(editarCurso() == true){
				l = get_listas();
				imprimirListas(get_listas());
				return 2;
			}
			else{
				cout<<"Curso no editado"<<endl;
				paginaCcurso(1);
			}
		}
		break;
		case 3:
		system("clear");
		verListas(l);
			cout<<"Introduce el curso que quieres modificar: ";
			cin>>curso;
			if(eliminarCurso(curso) == true){
				l = get_listas();
				imprimirListas(get_listas());
				return 3;
			}
			else{
				cout<<"Curso no elimminado"<<endl;
				sleep(1);
				system("clear");
				paginaCcurso(1);
			}
			break;
		case 4:
			return 0;
			break;
		default:
			return 0;
			break;
		}
	}
	return 0;
}
void Ccurso::paginaCcurso(int vez){
	int c, ope;
	system("clear");
	if(vez == 0){
		cout<<"HOLA COORDINADOR DE CURSO"<<endl;
		cout<<"_-----------------------------------_"<<endl;
	}
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"Que desea haces?"<<endl;
	cout<<"1. Modificar Curso"<<endl;
	cout<<"2. Salirse"<<endl;
	cin>>c;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	switch(c){
	case 1:
			system("clear");
			ope = modificarCurso();
			if(ope == 1 || ope == 2 || ope == 3){
				if(ope == 1){
					cout<<"Creacion con exito"<<endl;
					sleep(2);
				}
				else if(ope == 2){
					cout<<"Edicion con exito"<<endl;
					sleep(2);
				}
				else if(ope == 3){
					cout<<"Eliminacion con exito"<<endl;
					sleep(2);
				}
			}
			system("clear");
		paginaCcurso(1);
		break;
	case 2:
		cout<<"Hasta la proxima"<<endl;
		return;
		break;
	default:
		return;
		break;
	}
}
void opcionMod(){
	cout<<"Que quieres hacer?"<<endl;
	cout<<"1. Crear Curso"<<endl;
	cout<<"2. Editar Curso Existente"<<endl;
	cout<<"3. Eliminar Curso Existente"<<endl;
	cout<<"4. Salirte"<<endl;
}
vector<string> atributos(){
	string curso[10];
    vector<string> c;
	string linea;
	bool buc = false, docFlag = false;
	int x, n = 0, get = 0;
	vector<string> docentes;
	system("clear");
	while(buc != true){
		cout<<"Como quiere que se llame el curso?"<<endl;
		cout<<"--> ";

		getline(cin, curso[1]);
		getline(cin, curso[1]);
		cout<<endl;
		cout<<endl;
		cout<<endl;
		cout<<"El curso se llamara <"+curso[1]+">"<<endl;
		cout<<"Sera este su nombre definitivo?"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cout<<"--> ";
		cin>>x;
		if(x == 1){
			if(comprobarExistencia(curso[1]) != -1){
				cout<<"Lo sentimos, este curso ya esta registrado."<<endl;
				cout<<"Intentelo de nuevo"<<endl;
			}
			else{
				buc = true;
			}
		}
	}
	system("clear");
	buc = false;
	while(buc != true){
		cout<<"Id del curso: "<<endl;
		cout<<"--> ";
		cin>>curso[0];
		system("clear");
		cout<<"El ID seria <"<<curso[0]<<">"<<endl;
		cout<<"Estas seguro"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cout<<"--> ";
		cin>>x;
		if(x == 1){
			if(comprobarExistencia(curso[0]) != -1){
				cout<<"Lo sentimos, este ID ya esta siendo utilizado."<<endl;
				sleep(1);
				system("clear");
				cout<<"Ingrese otro id"<<endl;
			}
			else{
				buc = true;
			}
		}
	}
	system("clear");
	buc = false;
	bool encontrado = false;
	int ndoc = 0, ncon = 0, y;
	while(buc != true){
		cout<<"Ahora aniada los docentes que impartiran el curso: "<<endl;
		while(docFlag != true){
			cout<<"Introduzca el nombre del docente"<<endl;
				getline(cin, curso[2]);
				getline(cin, curso[2]);
				system("clear");
			cout<<"El docente seria <"<<curso[2]<<">"<<endl;
			cout<<"Estas seguro"<<endl;
			cout<<"1. Si"<<endl;
			cout<<"2. No"<<endl;
			cout<<"--> ";
			cin>>x;
			if(x == 1){
				for(int i = 0 ; i < ndoc; i++){
					size_t found = docentes[i].find(curso[2]);//en found se guarda la posicion de encontrar
					if(found != string::npos){//si lo encuentra
						encontrado = true;
					}
				}
				if(encontrado == false){
					docentes.push_back(curso[2]);
					ndoc++;
					system("clear");
					cout<<"Quiere aniadir a mas docentes?"<<endl;
					cout<<"1. Si"<<endl;
					cout<<"2. No"<<endl;
					cout<<"--> ";
					cin>>y;
					if(y == 2){
						docFlag = true;
					}
				}
				else{
					cout<<"El docente ya fue aniadido"<<endl;
					sleep(1);
					system("clear");
					encontrado = false;
				}
			}
		}
		curso[2] = docentes[0];
		for(int i = 1; i < ndoc; i++){
			if(i == ndoc -1)
				curso[2] = curso[2] +" y " + docentes[i];
			else
				curso[2] = curso[2] +", "+ docentes[i];
		}
		buc = true;
	}
	cout<<curso[2]<<" son "<<ndoc<<" docentes."<<endl;
	system("clear");
	buc = false;
	docFlag = false;
	encontrado = false;
	vector<string> contactos;
	while(buc != true){
		cout<<"Ahora vamos a introducir los contactos de los docentes"<<endl;
		for(int i = 0; i < ndoc; i++){
			docFlag = false;
			while(docFlag != true){
				cout<<"Cual va a ser el contacto de "<<docentes[i]<<" ?"<<endl;
					getline(cin, curso[3]);
					getline(cin, curso[3]);
					system("clear");
				cout<<"El contacto de <"<<docentes[i]<<"> seria <"<<curso[3]<<">"<<endl;
				cout<<"Estas seguro"<<endl;
				cout<<"1. Si"<<endl;
				cout<<"2. No"<<endl;
				cout<<"--> ";
				cin>>x;
				if(x == 1){//hay que ver que no sea el mismo que el de otra persona ya que es unico
					for(int j = 0 ; j < ncon; j++){
						cout<<"p1"<<endl;
						size_t found = contactos[j].find(curso[3]);//en found se guarda la posicion de encontrar
						if(found != string::npos){//si lo encuentra en el el vector actual
							encontrado = true;
						}
					}
					if(encontrado == false){
						//un profesor puede impartir varios cursos, entonces tenemos que comprobar
						//que si ese contacto está en la bbdd pertenezca al profesor
						//comprobamo la existencia del correo
						//si existe comprobamos la existencia del profesor
						//y calculamos relacion con [posicion de contacto = docente.length()+2(el : y el espacio) -1 (ya que es posicion y no tamanio)]
						//con lo que if(exiCon!=-1){if(exiCon == exiDoc + docentes[i] + 1 ){ corresponde}
						size_t exiCon = comprobarExistencia(curso[3]);
						size_t exiDoc = comprobarExistencia(docentes[i]);

						//cout<<"Posicion del contacto "<<exiCon<<" Posicion de docentes "<<exiDoc<<" Posicion relativa (si es == exiCon) "<< exiDoc + docentes[i].length() + 2<<endl;

						if(exiCon == -1){//el contacto no esta en la bbdd
							contactos.push_back(curso[3]);
							cout<<"Valido"<<endl;
							ncon++;
							docFlag = true;
						}
						else if(exiDoc != -1 && exiCon == -1){//el docente esta en bbdd pero con otro contacto
							contactos.push_back(curso[3]);
							cout<<"Valido"<<endl;
							ncon++;
							docFlag = true;
						}
						else if(exiCon != 1 && exiDoc != -1){//estan en la bbdd
							if(exiCon == (exiDoc + docentes[i].length() + 2)){//comprobamos si corresponde al docente
								cout<<"Esta en la base de datos pero es valida"<<endl;
								contactos.push_back(curso[3]);
								ncon++;
								docFlag = true;
							}
							else{
								cout<<"Este contacto no esta correspondiendo con el profesor"<<endl;
								sleep(1);
								system("clear");
								encontrado = false;
							}
						}
					}
					else{//esta en el vector actual
						cout<<"El contacto lo acabas de aniadir, no se puede duplicar"<<endl;
						sleep(1);
						system("clear");
						encontrado = false;
					}
				}
			}
		}
		buc = true;
	}
	curso[3] = docentes[0] + ": " + contactos[0];
		for(int i = 1; i < ndoc; i++){
			if(i == ndoc -1)
				curso[3] = curso[3] +" y " + docentes[i] +": "+ contactos[i]+",";
			else
				curso[3] = curso[3] +", "+ docentes[i] +": "+ contactos[i];
		}
	cout<<curso[3]<<endl;
	system("clear");
	buc = false;
	y = 0;
	while(buc != true){
		if(y == 0)
			cout<<"Ahora vamos a introducir la descripcion del curso"<<endl;
		cout<<"Descricion del curso:"<<endl;
		getline(cin, curso[4]);
		getline(cin, curso[4]);
		system("clear");
		cout<<"La descripcion del curso seria <"<<curso[4]<<">"<<endl;
		cout<<"Estas seguro"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cout<<"--> ";
		cin>>x;
		if(x == 1){
			buc = true;
		}
		else{
			y = 1;
		}
	}
	cout<<curso[4]<<endl;
	system("clear");
	buc = false;
	y = 0;
	while(buc != true){
		system("clear");
		if(y == 0)
			cout<<"Ahora vamos a introducir aforo maximo"<<endl;
		cout<<"Aforo:"<<endl;
		getline(cin, curso[6]);
		getline(cin, curso[6]);
		system("clear");
		cout<<"El aforo maximo del curso seria <"<<curso[6]<<">"<<endl;
		cout<<"Estas seguro"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cout<<"--> ";
		cin>>x;
		if(x == 1){
			buc = true;
		}
		else{
			y = 1;
		}
	}
	system("clear");
	buc = false;
		cout<<"Ahora vamos a introducir los estudios requeridos"<<endl;
		curso[5] = estudiosRequeridos();
		system("clear");
		cout<<curso[5]<<endl;
		cout<<"Ahora vamos a introducir la fecha de INICIO del curso"<<endl;
		curso[7] = fecha(0);
		system("clear");
		cout<<curso[7]<<endl;
		cout<<"Ahora vamos a introducir la fecha de FIN del curso"<<endl;
		system("clear");
		curso[8] = fecha(1);
		cout<<curso[8]<<endl;

	curso[9] = "0";//hay 0 participantes
    for(int i = 0 ; i < 10 ; i++ ){
        c.push_back(curso[i]);
    }
	return c;
}
bool Ccurso::crearCurso(Curso c1){
	
	list<Curso> l = get_listas();
	l.push_back(c1);
	set_listas(l);
	return true;
}
bool Ccurso::editarCurso(){
	list<Curso> listas = get_listas();
	list<Curso>::iterator it;
	size_t nc = listas.size();
	int curso, c = 1, ncur = static_cast<int>(nc);
	string linea = "", id, datos[10][ncur];
	bool elec = false, buc = false;
	system("clear");
	verListas(listas);
	cout<<"Introduce el curso que quieres modificar: ";
	cin>>curso;
   
	int contador = 1;
	if(curso <= ncur && curso > 0){
		for(it = listas.begin(); it != listas.end(); it++){
			if(contador == curso){
				id = it->get_id();
				system("clear");
				cout<<"ID DEL CURSO ES "<<id<<endl;
				cout<<"Es el curso que quieres editar el que tiene este id <"<<id<<">?"<<endl;
				cout<<"1. Si"<<endl;
				cout<<"2. No"<<endl;
				int x, y;
				cin>>x;
				if(x != 1){
					system("clear");
					return false;
				}
				string atribs[10];
				//id
				system("clear");
				cout<<"El id es <" + id + ">."<<endl;
				cout<<"Quieres modificar el id?"<<endl;
				cout<<"1. Si"<<endl;
				cout<<"2. No"<<endl;
				cin>>x;
				if(x == 1){
					system("clear");
					while(buc != true){
						cout<<"Id del curso: "<<endl;
						cout<<"--> ";
						cin>>atribs[0];
						system("clear");
						cout<<"El ID seria <"<<atribs[0]<<">"<<endl;
						cout<<"Estas seguro"<<endl;
						cout<<"1. Si"<<endl;
						cout<<"2. No"<<endl;
						cout<<"--> ";
						cin>>x;
						if(x == 1){
							if(comprobarExistencia(atribs[0]) != -1){
								system("clear");
								cout<<"Lo sentimos, este ID ya esta siendo utilizado."<<endl;
								cout<<"Ingrese otro id"<<endl;
								sleep(1);
								system("clear");
							}
							else{
								buc = true;
								it->set_id(atribs[0]);
							}
						}
					}
				}
				system("clear");
				buc = false;
				atribs[1] = it->get_nombre();//nombre
				cout<<"El nombre del curso es <"+atribs[1]+">."<<endl;
				cout<<"Quieres modificarlo?"<<endl;
				cout<<"1. Si"<<endl;
				cout<<"2. No"<<endl;
				cin>>x;
				if(x == 1){
					system("clear");
					while(buc != true){
						cout<<"Nombre del curso: "<<endl;
						cout<<"--> ";
						getline(cin, atribs[1]);
						getline(cin, atribs[1]);
						system("clear");
						cout<<"El nombre seria <"<<atribs[1]<<">"<<endl;
						cout<<"Estas seguro"<<endl;
						cout<<"1. Si"<<endl;
						cout<<"2. No"<<endl;
						cout<<"--> ";
						cin>>x;
						if(x == 1){
							if(comprobarExistencia(atribs[1]) != -1){
								system("clear");
								cout<<"Lo sentimos, este nombre ya esta siendo utilizado."<<endl;
								cout<<"Ingrese otro nombre"<<endl;
								sleep(1);
								system("clear");
							}
							else{
								it->set_nombre(atribs[1]);
								buc = true;
							}
						}
					}
				}
				system("clear");
				buc = false;
				bool docFlag = false, encontrado = false, docsMod = false;
				int ndoc = 0, d, z;
				vector<string> docentes;
				atribs[2] = it->get_docentes();//Docentes
				cout<<"Los docentes del curso son <"+atribs[2]+">."<<endl;
				cout<<"Quieres modificarlo?"<<endl;
				cout<<"1. Si (los eliminaras todos)"<<endl;
				cout<<"2. No"<<endl;
				cin>>x;
				if(x == 1){
					system("clear");
					while(buc != true){
						system("clear");
						while(docFlag != true){
							system("clear");
							cout<<"Introduzca el nombre del docente"<<endl;
								getline(cin, linea);
								getline(cin, linea);
								system("clear");
							cout<<"El docente seria <"<<linea<<">"<<endl;
							cout<<"Estas seguro"<<endl;
							cout<<"1. Si"<<endl;
							cout<<"2. No"<<endl;
							cout<<"--> ";
							cin>>y;
							if(y == 1){
								for(int i = 0 ; i < ndoc; i++){
									size_t found = docentes[i].find(linea);//en found se guarda la posicion de encontrar
									if(found != string::npos){//si lo encuentra
										encontrado = true;
									}
								}
								if(encontrado == false){
									docentes.push_back(linea);
									ndoc++;
									system("clear");
									cout<<"Quiere aniadir a mas docentes?"<<endl;
									cout<<"1. Si"<<endl;
									cout<<"2. No"<<endl;
									cout<<"--> ";
									cin>>y;
									if(y == 2){
										docFlag = true;
									}
								}
								else{
									system("clear");
									cout<<"El docente ya fue aniadido"<<endl;
									sleep(1);
									encontrado = false;
								}
							}
						}
						linea = docentes[0];
						for(int i = 1; i < ndoc; i++){
							if(i == ndoc -1)
								linea = linea +" y " + docentes[i] + ".";
							else
								linea = linea +", "+ docentes[i];
						}
						atribs[2] = linea;
						it->set_docentes(atribs[2]);
						buc = true;
						docsMod = true;
					}
				}
				else if(x == 2){
					docentes = desglosar(atribs[2], 0);
				}
				system("clear");
				buc = false;
				docFlag = false;
				encontrado = false;
				vector<string> contactos;
				int ncon = 0;
				atribs[3] = it->get_contactos();//contactos
				if(docsMod == true){//si docentes ha sido modificado
					while(buc != true){
					cout<<"Ahora vamos a introducir los contactos de los docentes"<<endl;
					for(int i = 0; i < ndoc; i++){
						docFlag = false;
						system("clear");
						while(docFlag != true){
							system("clear");
							//cout<<"Ncons = "<<ncon<<endl;
							cout<<"Cual va a ser el contacto de "<<docentes[i]<<" ?"<<endl;
								getline(cin, atribs[3]);
								getline(cin, atribs[3]);
								system("clear");
							cout<<"El contacto de <"<<docentes[i]<<"> seria <"<<atribs[3]<<">"<<endl;
							cout<<"Estas seguro"<<endl;
							cout<<"1. Si"<<endl;
							cout<<"2. No"<<endl;
							cout<<"--> ";
							cin>>x;
							if(x == 1){
								//hay que ver que no sea el mismo que el de otra persona ya que es unico
								for(int j = 0 ; j < ncon; j++){
									//cout<<"p1"<<endl;
									size_t found = contactos[j].find(atribs[3]);//en found se guarda la posicion de encontrar
									if(found != string::npos){//si lo encuentra en el el vector actual
										encontrado = true;
									}
								}
								if(encontrado == false){
									//un profesor puede impartir varios cursos, entonces tenemos que comprobar
									//que si ese contacto está en la bbdd pertenezca al profesor
									//comprobamo la existencia del correo
									//si existe comprobamos la existencia del profesor
									//y calculamos relacion con [posicion de contacto = docente.length()+2(el : y el espacio) -1 (ya que es posicion y no tamanio)]
									//con lo que if(exiCon!=-1){if(exiCon == exiDoc + docentes[i] + 1 ){ corresponde}
									size_t exiCon = comprobarExistencia(atribs[3]);
									size_t exiDoc = comprobarExistencia(docentes[i]);

									//cout<<"Posicion del contacto "<<exiCon<<" Posicion de docentes "<<exiDoc<<" Posicion relativa (si es == exiCon) "<< exiDoc + docentes[i].length() + 2<<endl;
									//cout<<"p2"<<endl;
									if(exiCon == -1){//el contacto no esta en la bbdd
										contactos.push_back(atribs[3]);
										cout<<"Valido"<<endl;
										ncon++;
										docFlag = true;
									}
									else if(exiDoc != -1 && exiCon == -1){//el docente esta en bbdd pero con otro contacto
										contactos.push_back(atribs[3]);
										system("clear");
										cout<<"Valido"<<endl;
										ncon++;
										docFlag = true;
									}
									else if(exiCon != 1 && exiDoc != -1){//estan en la bbdd
										if(exiCon == (exiDoc + docentes[i].length() + 2)){//comprobamos si corresponde al docente
											system("clear");
											cout<<"Esta en la base de datos pero es valida"<<endl;
											contactos.push_back(atribs[3]);
											ncon++;
											docFlag = true;
										}
										else{
											system("clear");
											cout<<"Este contacto no esta correspondiendo con el profesor"<<endl;
											sleep(1);
											encontrado = false;
										}
									}
								}
								else{//esta en el vector actual
									system("clear");
									cout<<"El contacto lo acabas de aniadir, no se puede duplicar"<<endl;
									encontrado = false;
								}
							}
						}
					}
					buc = true;
					}
					ndoc = docentes.size();
					atribs[3] = docentes[0] + ": " + contactos[0];
					if(ndoc == 1){
						atribs[3] = atribs[3] + ",";
					}
					for(int i = 1; i < ndoc; i++){
						if(i == ndoc - 1){
							atribs[3] = atribs[3] +" y " + docentes[i] + ": "+contactos[i] + ",";
						}
						else
							atribs[3] = atribs[3] +", "+ docentes[i] +": " + contactos[i];
					}
				}
				else{//no ha sido modificado el contacto
					contactos = desglosar(atribs[3], 1);
					system("clear");
					cout<<"Quieres modificar los contactos"<<endl;
					cout<<"1. si"<<endl;
					cout<<"2. no"<<endl;
					cin>>x;
					string cp;
					buc = false;
					if(x == 1){
						while(buc != true){
							system("clear");
							for(int l = 0; l < contactos.size(); l++){
								cout<<l+1<<". "+docentes[l] + ": "+contactos[l]<<endl;
							}
							//cout<<"Contactos size "<<contactos.size()<<endl;

							cout<<"Cual quieres cambiar?"<<endl;
							cin>>d;
							if(d > 0 && d <= contactos.size()){
								cout<<"Introduzca el contacto nuevo de " + docentes[d-1]<<endl;
								getline(cin, cp);
								getline(cin, cp);
								system("clear");
								cout<<"Quieres que "+cp+" sea el nuevo contacto de "+ docentes[d-1]+"?"<<endl;
								cout<<"1. si"<<endl;
								cout<<"2. no"<<endl;
								cin>>y;
								if(y == 1){
									contactos[d-1] = cp;
									cout<<"quieres editar otro contacto mas?"<<endl;
									cout<<"1. si"<<endl;
									cout<<"2. no"<<endl;
									cin>>z;
									if(z != 1){
										system("clear");
										buc = true;
									}
								}
							}
						}
						ndoc = docentes.size();
						atribs[3] = docentes[0] + ": " + contactos[0];
						if(ndoc == 1){
							atribs[3] = atribs[3] + ",";
						}
						for(int i = 1; i < ndoc; i++){
							if(i == ndoc - 1){
								atribs[3] = atribs[3] +" y " + docentes[i] + ": "+contactos[i] + ",";
							}
							else
								atribs[3] = atribs[3] +", "+ docentes[i] +": " + contactos[i];
						}
					}
				}
				
				//cout<<atribs[3]<<endl;
				it->set_contactos(atribs[3]);
				system("clear");
				buc = false;
				atribs[4] = it->get_descripcion();//descripcion
				cout<<"La descipcion del curso es <"+atribs[4]+">."<<endl;
				cout<<"Quieres modificarla?"<<endl;
				cout<<"1. Si"<<endl;
				cout<<"2. No"<<endl;
				cin>>x;
				if(x == 1){
					while(buc != true){
						system("clear");
						cout<<"Descripcion: "<<endl;
						cout<<"--> ";
						cin>>atribs[1];
						system("clear");
						cout<<"La descripcion seria <"<<atribs[4]<<">"<<endl;
						cout<<"Estas seguro"<<endl;
						cout<<"1. Si"<<endl;
						cout<<"2. No"<<endl;
						cout<<"--> ";
						cin>>x;
						if(x == 1){
							it->set_descripcion(atribs[4]);
							buc = true;
						}
					}
				}
				system("clear");
				buc = false;
				y = 0;
				atribs[6] = it->get_aforo();//aforo
				cout<<"El aforo del curso es <"+atribs[6]+">."<<endl;
				cout<<"Quieres modificarlo?"<<endl;
				cout<<"1. Si"<<endl;
				cout<<"2. No"<<endl;
				cin>>z;
				if(z == 1){
					while(buc != true){
						system("clear");
						if(y == 0)
							cout<<"Ahora vamos a introducir aforo maximo"<<endl;
						cout<<"Aforo:"<<endl;
						getline(cin, atribs[6]);
						getline(cin, atribs[6]);
						system("clear");
						cout<<"El aforo maximo del curso seria <"<<atribs[6]<<">"<<endl;
						cout<<"Estas seguro"<<endl;
						cout<<"1. Si"<<endl;
						cout<<"2. No"<<endl;
						cout<<"--> ";
						cin>>x;
						if(x == 1){
							system("clear");
							it->set_aforo(atribs[6]);
							buc = true;
						}
						else{
							y = 1;
						}
					}
				}
				atribs[5] = it->get_estudios();//grados
				system("clear");
				buc = false;
				cout<<"Los estudios requeridos del curso son <"+atribs[5]+">."<<endl;
				cout<<"Quieres modificarlos?"<<endl;
				cout<<"1. Si"<<endl;
				cout<<"2. No"<<endl;
				cin>>x;
				if(x == 1){
					system("clear");
					cout<<"Ahora vamos a introducir los estudios requeridos"<<endl;
					atribs[5] = estudiosRequeridos();
				}
				
				cout<<atribs[5]<<endl;
				system("clear");
				it->set_estudios(atribs[5]);
				atribs[7] = it->get_inicio();//fecha inicio
				cout<<"La fecha de inicio del curso es <"+atribs[7]+">."<<endl;
				cout<<"Quieres modificarla?"<<endl;
				cout<<"1. Si"<<endl;
				cout<<"2. No"<<endl;
				cin>>x;
				if(x == 1){
					system("clear");
					cout<<"Ahora vamos a introducir la fecha de INICIO del curso"<<endl;
					atribs[7] = fecha(0);
				}
				cout<<atribs[7]<<endl;
				system("clear");
				it->set_inicio(atribs[7]);
				buc = false;
				atribs[8] = it->get_fin();//fecha final
				system("clear");
				cout<<"La fecha de final del curso es <"+atribs[8]+">."<<endl;
				cout<<"Quieres modificarla?"<<endl;
				cout<<"1. Si"<<endl;
				cout<<"2. No"<<endl;
				cin>>x;
				if(x == 1){
					system("clear");
					cout<<"Introduzca la fecha de FIN del curso"<<endl;
					while(buc != true){
						atribs[8] = fecha(1);
						if(stoi(atribs[7].substr(6,4)) >  stoi(atribs[8].substr(6,4))){
							cout<<"El curso debe terminar despues de la fecha de inicio(a)"<<endl;
						}
						else{
							if(stoi(atribs[7].substr(3,2)) >  stoi(atribs[8].substr(3,2))){
							cout<<"El curso debe terminar despues de la fecha de inicio(m)"<<endl;
							}
							else{
								if(stoi(atribs[7].substr(0,2)) >  stoi(atribs[8].substr(0,2))){
									cout<<"El curso debe terminar despues de la fecha de inicio(d)"<<endl;
								}
								else{
									buc = true;
								}
							}
						}
					}
				}
				cout<<atribs[8]<<endl;
				it->set_fin(atribs[8]);
			}
			contador++;
		}
	}
	else{
		cout<<"Ese curso no existe"<<endl;
		return false;
	}
	set_listas(listas);
	return true;	
	//ahora vamos a imprimir en la pagina
	
	
}

bool Ccurso::eliminarCurso(int curso){
	list<Curso> listas = get_listas();
	list<Curso>::iterator it;
	size_t nc = listas.size();
	int c = 1, ncur = static_cast<int>(nc)/*, x, cont=0*/;
	//bool sel = false;
	vector<string> datos;
	
	if(curso <= ncur && curso > 0){
		for(it = listas.begin(); it != listas.end(); it++){
			if(curso == c){
				listas.erase(it);
				set_listas(listas);
				return true;
			}
			c++;
		}
	}
	else{
		//cout<<"Este curso no existe"<<endl;
		return false;
	}
	return false;
	
}
size_t comprobarExistencia(string c){
	ifstream f;
	string linea;
	size_t found;
	f.open("open.txt", ios::in);
	if(f.fail()){
		cout<<"Error al abrir fichero de cursos"<<endl;
		exit(1);
	}
	while(!f.eof()){
		getline(f, linea);
		size_t found = linea.find(c);
		if(found != string::npos){
			return found;
		}
	}
	f.close();
	return -1;
}
string fecha(int mod){
		auto now = chrono::system_clock::now();
		time_t end_time = chrono::system_clock::to_time_t(now);
		string aus = ctime(&end_time);
		string anoActual = aus.substr(aus.length()-5, 4);
		cout<<"Ano actual: "+ anoActual<<endl;
		int anoA = stoi(anoActual);
		//capto el anio actual para ver si el curso se esta creando en el pasado o en una fecha realista
	int ano = 0, anoFlag = 0, mesFlag=0, mes, dayFlag = 0, dia;
	int nmesA, ndiaA;
	string dicciMeses[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; //Diccionario meses
	string mesActual = aus.substr(4, 3);
	for(int i = 0; i < 12; i++){
		if(mesActual == dicciMeses[i]){
			nmesA = i+1;
			
			cout<<"Mes actual : "<<nmesA<<endl;
		}
	}
	string diaActual = aus.substr(8, 1);
	if(diaActual == " "){
		diaActual = aus.substr(9, 1);
	}
	else{
		diaActual = aus.substr(8, 2);
	}
	cout<<"El dia actual es: "+diaActual<<endl;
	ndiaA = stoi(diaActual);
	bool visiesto = false;
	string sano, smes, sdia;
	while(anoFlag == 0){
		if(ano == 0){
			if(mod == 0)
				cout<<"Introduce el anio de la fecha de inicio del curso: ";
			else
				cout<<"Introduce el anio de la fecha de final del curso: ";
		}
		else
			cout<<"Introduce de nuevo el anio: ";
		cin>>ano;
		if(ano < anoA ){ //que el curso sea el mismo anio de creacion o posterior
			cout<<"Fecha no valida"<<endl;
			sleep(1);
			system("clear");
		}
		else{
			sano = to_string(ano);
			if(ano % 4 == 0){
				visiesto = true;
			}
			anoFlag = 1;
		}
	}
	//Mes
	while(mesFlag == 0){
		system("clear");
		cout<<"Mes: "<<endl;
		cout<<"1. Enero"<<endl;
		cout<<"2. Febrero"<<endl;
		cout<<"3. Marzo"<<endl;
		cout<<"4. Abril"<<endl;
		cout<<"5. Mayo"<<endl;
		cout<<"6. Junio"<<endl;
		cout<<"7. Julio"<<endl;
		cout<<"8. Agosto"<<endl;
		cout<<"9. Septiembre"<<endl;
		cout<<"10. Octubre"<<endl;
		cout<<"11. Noviembre"<<endl;
		cout<<"12. Diciembre"<<endl;
		cout<<"Introduce el mes: ";
		cin>>mes;
		if(mes < nmesA && ano == anoA){
			cout<<"Fecha pasada, introduzca otra por favor"<<endl;
			sleep(1);
		}
		else{
			if(mes > 0 && mes < 13){
				switch(mes){
					case 1:
						mes = 1;
						smes = "01";
					break;
					case 2:
						mes = 2;
						smes = "02";
					break;
					case 3:
						mes = 3;
						smes = "03";
					break;
					case 4:
						mes = 4;
						smes = "04";
					break;
					case 5:
						mes = 5;
						smes = "05";
					break;
					case 6:
						mes = 6;
						smes = "06";
					break;
					case 7:
						mes = 7;
						smes = "07";
					break;
					case 8:
						mes = 8;
						smes = "08";
					break;
					case 9:
						mes = 9;
						smes = "09";
					break;
					case 10:
						mes = 10;
						smes = "10";
					break;
					case 11:
						mes = 11;
						smes = "11";
					break;
					case 12:
						mes = 12;
						smes = "12";
					break;
				}
				mesFlag = 1;
			}
			else{
				cout<<"Fecha no valida"<<endl;
				sleep(1);
				system("clear");
			}
		}
	}

	while(dayFlag == 0){
		system("clear");
		cout<<"DIA: "<<endl;
		cout<<"01  ";cout<<"02  ";cout<<"03  ";cout<<"04  ";cout<<"05  ";cout<<"06  ";	cout<<"07  "<<endl;
		cout<<"08  ";cout<<"09  ";cout<<"10  ";cout<<"11  ";cout<<"12  ";cout<<"13  ";	cout<<"14  "<<endl;
		cout<<"15  ";cout<<"16  ";cout<<"17  ";cout<<"18  ";cout<<"19  ";cout<<"20  ";	cout<<"21  "<<endl;
		cout<<"22  ";cout<<"23  ";cout<<"24  ";cout<<"25  ";cout<<"26  ";cout<<"27  ";	cout<<"28  "<<endl;
		cout<<"29  ";cout<<"30  ";cout<<"31  "<<endl;
		cout<<"Introduce el dia: ";
		cin>>dia;
		if(dia > 0 && dia < 32){ //dia valido
			if(nmesA == mes && dia <= ndiaA && ano == anoA){ //el curso ha de empezar un dia despues de su creacion como minimo
				cout<<"Fecha tardia, no es posible"<<endl;
				sleep(1);
			}
			else{
				if(mes == 2 && dia < 30){//si es febrero
					if(dia == 29 && visiesto == true){//es 29 y es visiesto
						cout<<"Dia 29 de febrero valido"<<endl;
						sdia = "29";
						dayFlag = 1;
					}
					else if(dia == 29 && visiesto != true){ //si es 29 y no es visiesto
						cout<<"No puede ser, no me la cuelas"<<endl;
						system("clear");
					}
					else if(dia != 29){//si no es 29 y me da igual que sea visiesto
						cout<<"Dia valido"<<endl;
						sdia = to_string(dia);
						dayFlag = 1;
					}
				}
				else if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
					if(dia == 31){
						cout<<"Error, este 31 no existe"<<endl;
						system("clear");
					}
					else{
						cout<<"Dia valido"<<endl;
						sdia = to_string(dia);
						dayFlag = 1;
					}
				}
				else if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
					cout<<"Dia valido"<<endl;
					sdia = to_string(dia);
					dayFlag = 1;
				}
				else{
					cout<<"Dia no valido porque no existe el 30 o 31 de febrero"<<endl;
					sleep(1);
					system("clear");
				}
			}
		}
	}
	if(dayFlag == 1){
		if(sdia.length() == 1){
			return "0"+sdia +"/"+ smes+"/" + sano;
		}
		else
			return sdia +"/"+ smes+"/" + sano;
	}
	return "";
}
string estudiosRequeridos(){
	int flag = 0, i = 0, c;
	string value = "";
	while(flag != -1){
		cout<<"1. Grado en Administración y Dirección de Empresas"<<endl;
		cout<<"2. Grado en Biología"<<endl;
		cout<<"3. Grado en Bioquímica"<<endl;
		cout<<"4. Grado en Ciencias Ambientales"<<endl;
		cout<<"5.Grado en Ciencia y Tecnología de los Alimentos"<<endl;
		cout<<"6.Grado en Cine y Cultura"<<endl;
		cout<<"7.Grado en Derecho"<<endl;
		cout<<"8.Grado en Educación Infantil"<<endl;
		cout<<"9.Grado en Educación Infantil (Itinerario Bilingüe)"<<endl;
		cout<<"10.Grado en Educación Primaria"<<endl;
		cout<<"11.Grado en Educación Primaria (Itinerario Bilingüe)"<<endl;
		cout<<"12.Grado en Educación Social"<<endl;
		cout<<"13.Grado en Enfermería"<<endl;
		cout<<"14.Grado en Estudios Ingleses"<<endl;
		cout<<"15.Grado en Filología Hispánica"<<endl;
		cout<<"16.Grado en Física"<<endl;
		cout<<"17.Grado en Fisioterapia"<<endl;
		cout<<"18.Grado en Gestión Cultural"<<endl;
		cout<<"19.Grado en Historia"<<endl;
		cout<<"20.Grado en Historia del Arte"<<endl;
		cout<<"21.Grado en Psicología"<<endl;
		cout<<"22.Grado en Ingeniería Civil (2 tecnologías)"<<endl;
		cout<<"23.Grado en Ingeniería Eléctrica"<<endl;
		cout<<"24.Grado en Ingeniería Electrónica Industrial"<<endl;
		cout<<"25.Grado en Ingeniería Forestal"<<endl;
		cout<<"26.Grado en Ingeniería Informática"<<endl;
		cout<<"27.Grado en Ingeniería Mecánica"<<endl;
		cout<<"28.Grado en Veterinaria"<<endl;
		cout<<"29.Grado en Medicina"<<endl;
		cout<<"30.Grado en Química"<<endl;
		cout<<"31.Grado en Relaciones Laborales y Recursos Humanos"<<endl;
		cout<<"32.Grado en Traducción e Interpretación"<<endl;
		cout<<"33.Grado en Turismo"<<endl;
		cout<<"34.Grado en Ingeniería de Recursos Energéticos y Mineros"<<endl;
		cout<<"35.Grado en Ingeniería Agroalimentaria y del Medio Rural"<<endl;
		cout<<"---------------------------------------------------------"<<endl;
		if(flag == 0){
			cout<<"Que grado corresponde con los estudios requeridos?-->";
			cin>>c;
			flag++;
		}
		else{
			i = 0;
            cout<<"Llevas aniadido "<<value<<endl;
			cout<<"Otro grado que quieras aniadir?-->"<<endl;
			cout<<"1. Si"<<endl;
			cout<<"2. No"<<endl;
			cin>>i;
			if(i == 1){
				cout<<"Cual?-->";
				cin>>c;
			}
			else{
				flag = -1;
                return value;
			}
		}
		switch(c){
			case 1:
				value = value + "// " + "Grado en Administración y Dirección de Empresas";
			break;
			case 2:
				value = value + "// " + "Grado en Biología";
			break;
			case 3:
				value = value + "// " + "Grado en Bioquímica";
			break;
			case 4:
				value = value + "// " + "Grado en Ciencias Ambientales";
			break;
			case 5:
				value = value + "// " + "Grado en Ciencia y Tecnología de los Alimentos";
			break;
			case 6:
				value = value + "// " + "Grado en Cine y Cultura";
			break;
			case 7:
				value = value + "// " + "Grado en Derecho";
			break;
			case 8:
				value = value + "// " + "Grado en Educación";
			break;
			case 9:
				value = value + "// " + "Grado en Educación Infantil (Itinerario Bilingüe)";
			break;
			case 10:
				value = value + "// " + "Grado en Educación Primaria";
			break;
			case 11:
				value = value + "// " + "Grado en Educación Primaria (Itinerario Bilingüe)";
			break;
			case 12:
				value = value + "// " + "Grado en Educación Social";
			break;
			case 13:
				value = value + "// " + "Grado en Enfermería";
			break;
			case 14:
				value = value + "// " + "Grado en Estudios Ingleses";
			break;
			case 15:
				value = value + "// " + "Grado en Filología Hispánica";
			break;
			case 16:
				value = value + "// " + "Grado en Física";
			break;
			case 17:
				value = value + "// " + "Grado en Fisioterapia";
			break;
			case 18:
				value = value + "// " + "Grado en Gestión Cultural";
			break;
			case 19:
				value = value + "// " + "Grado en Historia";
			break;
			case 20:
				value = value + "// " + "Grado en Historia del Arte";
			break;
			case 21:
				value = value + "// " + "Grado en Psicología";
			break;
			case 22:
				value = value + "// " + "Grado en Ingeniería Civil";
			break;
			case 23:
				value = value + "// " + "Grado en Ingeniería Eléctrica";
			break;
			case 24:
				value = value + "// " + "Grado en Ingeniería Electrónica Industrial";
			break;
			case 25:
				value = value + "// " + "Grado en Ingeniería Forestal";
			break;
			case 26:
				value = value + "// " + "Grado en Ingeniería Informática";
			break;
			case 27:
				value = value + "// " + "Grado en Ingeniería Mecánica";
			break;
			case 28:
				value = value + "// " + "Grado en Veterinaria";
			break;
			case 29:
				value = value + "// " + "Grado en Medicina";
			break;
			case 30:
				value = value + "// " + "Grado en Química";
			break;
			case 31:
				value = value + "// " + "Grado en Relaciones Laborales y Recursos Humanos";
			break;
			case 32:
				value = value + "// " + "Grado en Traducción e Interpretación";
			break;
			case 33:
				value = value + "// " + "Grado en Turismo";
			break;
			case 34:
				value = value + "// " + "Grado en Ingeniería de Recursos Energéticos y Mineros";
			break;
			case 35:
				value = value + "// " + "Grado en Ingeniería Agroalimentaria y del Medio Rural";
			break;
			default:
				value = value + "";
                cout<<"No existe este";
			break;
		}
	}
    return value;
}
vector<string> desglosar(string linea, int tipo){
	int lastPos = 0, j = 0;
	bool coma = false, done = false;
	vector<string> v;
	if(tipo == 0){//docente
		for(int i = 0; i < linea.length(); i++){
			if(linea[i] == ','){
				v.push_back(linea.substr(lastPos, i - lastPos));
				//cout<<linea.substr(lastPos, i - lastPos)<<endl;
				lastPos = i + 2;
			}
			else if(linea[i] == 'y' && linea[i+1] == ' ' && linea[i-1] == ' '){
				v.push_back(linea.substr(lastPos, i - lastPos - 1));
				//cout<<linea.substr(lastPos, i - lastPos -1)<<endl;
				lastPos = i + 2;
			}
			else if(linea[i] == '.'){
				v.push_back(linea.substr(lastPos, i - lastPos));
				//cout<<linea.substr(lastPos, i - lastPos)<<endl;
			}
		}
	}
	else if(tipo == 1){//contactos
		while(j < linea.length()){
			if(linea[j] == ':'){
				lastPos = j + 2;
			}
			if(lastPos < j && linea[j] == ','){
				v.push_back(linea.substr(lastPos, j - lastPos));
				//cout<<linea.substr(lastPos, j - lastPos)<<"yeaaaah"<<endl;
			}
			else if(lastPos < j && linea[j] == 'y' && linea[j+1] == ' ' && linea[j-1] == ' '){
				v.push_back(linea.substr(lastPos, j - lastPos - 1));
				//cout<<linea.substr(lastPos, j - lastPos - 1)<<"yeaaah"<<endl;
			}
			j++;
		}
	}
	else if(tipo == 2){//estudios
		while(j < linea.length()){
			if(linea[j] == '/' && linea[j+1] =='/'){
				lastPos = j;
			}
			if(lastPos < j && linea[j + 1] == '/' && linea[j+2] =='/'){
				v.push_back(linea.substr(lastPos, j - lastPos+1));
				//cout<<linea.substr(lastPos, j - lastPos)<<"yeaaaah"<<endl;
			}
			else if(lastPos < j && j == linea.length()-1){
				v.push_back(linea.substr(lastPos, j - lastPos +1));
				//cout<<linea.substr(lastPos, j - lastPos - 1)<<"yeaaah"<<endl;
			}
			j++;
		}
	}
	return v;
}
list<Curso> listaCursos(){
	Curso c("", "", "", "", "", "", "", "", "", "");
	list<Curso> listas;
	int n = contarlineas() - 1, contador = 1;
	string atribs[10];
	if(n <= 1){
		listas.push_back(c);
		cout<<"No hay cursos"<<endl;
		return listas;
	}
	ifstream re;
	re.open("open.txt", ios::in);
	if(re.fail()){
		cout<<"Error de lectura"<<endl;
	}
	
	while(/*!re.eof() && */(contador <= n)){
		for(int i = 0; i < 10; i++){
			getline(re, atribs[i]);
			contador++;
		}
		c.set_id(atribs[0]);
		//cout<<c.get_id() + "finlinea"<<endl;
		c.set_nombre(atribs[1]);
		//cout<<c.get_nombre() + "finlinea"<<endl;
		c.set_docentes(atribs[2]);
		//cout<<c.get_docentes() + "finlinea"<<endl;
		c.set_contactos(atribs[3]);
		//cout<<c.get_contactos() + "finlinea"<<endl;
		c.set_descripcion(atribs[4]);
		//cout<<c.get_descripcion() + "finlinea"<<endl;
		c.set_estudios(atribs[5]);
		//cout<<c.get_estudios() + "finlinea"<<endl;
		c.set_aforo(atribs[6]);
		//cout<<c.get_aforo() + "finlinea"<<endl;
		c.set_inicio(atribs[7]);
		//cout<<c.get_inicio() + "finlinea"<<endl;
		c.set_fin(atribs[8]);
		//cout<<c.get_fin() + "finlinea"<<endl;
		c.set_participantes(atribs[9]);
		//cout<<c.get_participantes() + "finlinea"<<endl;
		listas.push_back(c);
		//cout<<"UNO"<<endl;
	}
	re.close();
	return listas;
}
void imprimirListas(list<Curso> listas){
	list<Curso>::iterator it;
	ofstream wr;
	wr.open("open.txt", ios::out);
	if(wr.fail()){
		cout<<"Error de escritura open"<<endl;
		return;
	}
	size_t n = listas.size();
	int m = static_cast<int>(n), contador = 1;
	for(it = listas.begin(); it != listas.end(); ++it){
			wr<<it->get_id()<<endl;
			//ID
			wr<<it->get_nombre()<<endl;
			//Docentes
			wr<<it->get_docentes()<<endl;
			//Contacto
			wr<<it->get_contactos()<<endl;
			//Descripcion
			wr<<it->get_descripcion()<<endl;
			//estudios requeridoss
			wr<<it->get_estudios()<<endl;
			//Aforo
			wr<<it->get_aforo()<<endl;
			//Fecha de Inicio
			wr<<it->get_inicio()<<endl;
			//Fecha de Final
			wr<<it->get_fin()<<endl;
		if(contador == m){
			//N participantes cursando
			wr<<it->get_participantes();
		}
		else{
			wr<<it->get_participantes()<<endl;
		}
		contador++;
	}
	
	wr.close();
}
