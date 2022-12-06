/*
 * visitante.cpp
 *
 *  Created on: 5 dic 2022
 *      Author: JAVIER
 */


#include "../usuario/usuario.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "../usuario/usuario.cpp"

#include "visitante.h"

using namespace std;

Visitante::Visitante(string correo, string contra):Usuario(correo, contra){
}

bool Visitante::registrarUsuario(){
	string c, p;
	int flag = 0;
		bool ccorr=false; //condicionadores para hacer un bucle por si falla el correo
		bool ccontra=false; //condicionadores para hacer un bucle por si falla la contraseña
		while(ccontra != true){ //si falla la contraseña se repite todo el bucle
			while(ccorr != true){ //si falla el correo se repite el bucle del correo
				if(flag == 0)
					cout<<"Introducir correo: "<<endl;
				else
					cout<<"Introducir correo, esta vez uno no registrado: "<<endl;
				cin>>c;
				set_correo(c);
				bool al = arroba(c);
				if(al == true){ //comprueba que el correo tenga arroba y punto
					bool dis = distancia(c);
					if(dis == true){//comprueba que el dominio sea realista
						cout<<"Correo valido";
						if(comprobar_correo(c) == true){
							cout<<", pero ya esta registrado." <<endl;
							flag = 1;
						}
						else{
							flag = 0;
							ccorr = true; //se termina el while del correo
						}
					}
				}
				else{
					cout<<"Correo no valido, prueba con otro correo."<<endl;
				}
			}
			cout<<endl;
			cout<<"Introducir contrasenya: "<<endl;
			cin>>p;
			set_contra(p);
			cout<<"Contraseña valida"<<endl;
			ccontra = true; //se termina el while grande
			registrar(c,p);
			return true;
		}
		return false;
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
	if((dot - posi) > 10){
		cout<<"Dominio no válido"<<endl;
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
	return c/2;
}
void registrar(string cor, string con){
    int i = 0, n = contarUsuarios();
    cout<<"Usuarios hay "<<n<<endl;
    ifstream re;
    ofstream wr;
    string a, b;
    vector<string> v;
	re.open("logs.txt", ios::in);//abrimos en modo lectura
	if(re.fail()){
		cout<<"Error al abrir fichero de lectura"<<endl;
		exit(1);
	}
	while(!re.eof() && i < n){//hasta que no llegue al numero de usuarios no para
			getline(re, a);
	        getline(re, b);
	        v.push_back(a);
	        v.push_back(b);
	        i++;
	}
	v.push_back(cor);
	v.push_back(con);
	n++; //aumenta uno porque añadimos a una persiona

	re.close();
	for(int i = 0; i < n*2; i++){
		cout<<v[i]<<endl;
	}
    wr.open("logs.txt", ios::out);//abrimos en modo escritura
    if(wr.fail()){
		cout<<"Error al abrir fichero de escritura"<<endl;
		exit(1);
	}
	i = 0;
    for(int j = 0; j < n*2; j++){//hasta que no llegue al numero de usuarios no para
        wr<<v[j]<<endl;//fila a fila
    }
    wr.close();
}
