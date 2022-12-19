/*
 * main.cpp
 *
 *  Created on: 6 dic 2022
 *      Author: USUARIO
 */


#include <iostream>
#include <stdlib.h>
#include <string>
#include "objects.h"

using namespace std;

int main(){
	int user = 0;
	string correo, contra;
	Usuario uno = Usuario("","");
	Participante tres = Participante("","","","","","","","");
	list<Curso> listas = listaCursos();
	Ccurso cuatro = Ccurso("","", listas);

		system("clear");
	while(user != 1 && user != 2 && (user == 0|| user == 3)){
		if(user == 0)
			user = uno.verPagina(0, listas);
		else if(user == 3)
			user = uno.verPagina(3, listas);
	}
	correo = uno.get_correo();
	contra = uno.get_contra();
	if(user == 1){
		tres = Participante(correo, contra,"","","","","","");
		system("clear");
		tres.globalset(correo);
		tres.set_listas(listas);

		system("clear");
		tres.paginaParticipante(0);
	}
	if(user == 2){
		
		cuatro = Ccurso(uno.get_correo(), uno.get_contra(), listas);
		cuatro.set_listas(listas);
		//ver por que ahi hay error(no muestra listas)

		system("clear");
		cuatro.paginaCcurso(0);
	}
	
}



