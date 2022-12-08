/*
 * main.cpp
 *
 *  Created on: 6 dic 2022
 *      Author: USUARIO
 */
#include "participante/participante.h"
#include "participante/participante.cpp"
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int main(){
	int user;
	string correo, contra;
	Usuario uno = Usuario("","");
	Participante tres = Participante("","","","","","","","");
	//CoordinadorC cuatro = CoordinadorC("","");
	user = uno.verPagina(0);
	cout<<"Orden de usuario: "<<user<<endl;
	if(user == 1){
		correo = uno.get_correo();
		contra = uno.get_contra();
		tres = Participante(correo, contra,"","","","","","");
		tres.globalset(correo);
		tres.paginaParticipante(0);
	}
}



