/*
 tests made with GoogleTest

*/

#include "objects.h"
#include "gtest/gtest.h"


//Author: Javier Garcia Fernandez

TEST(comprobacionesYaMatriculado, comprobaciones){
	
	Participante p = Participante("i12cacrm@uco.es", "1231231", "Javier Garcia Fernandez",
	 "46072134", "// Grado en Mecanica", "67576567", "04012003", "CURSO DE PILOTO");
		
	
	Curso c1 = Curso("Curso de cocina", "Curso de cocina", "Karlos algiñano y Dolores modales",
	 "Karlos algiñano: karlos@uco.es y Dolores modales: d.mor@uco.es,","Sobre cocina",
	  "// Grado en Ingeniería Informática", "10", "04/03/2023", "03/05/2023", "0");
	  list<Curso> listas = {c1};

	EXPECT_FALSE(p.comprobaciones(1, listas));//ya matriculado
};


TEST(Usuarioregistrado, registrarUsuario){
	Usuario u("i12gafej@uco.es", "12344");
	EXPECT_FALSE(u.registrarUsuario("i12gafej@uco.es", "12344")); //user ya registrado, por lo que se espera false
}






//Author: Manuel Cabrera Crespo

TEST(Curso, eliminarCurso){

	Curso c1 = Curso("004", "Curso de cocina", "Karlos algiñano y Dolores modales",
	 "Karlos algiñano: karlos@uco.es y Dolores modales: d.mor@uco.es,","Sobre cocina",
	  "// Grado en Ingeniería Informática", "10", "04/03/2023", "03/05/2023", "0");
	
	list<Curso> listas = {c1};

	Ccurso cc("r@uco.es", "4", listas);


	EXPECT_FALSE(cc.eliminarCurso(2));  //el curso no esta en la bbdd ya que no se ha hecho un crear curso
}


TEST(Usuario, iniciarSesion){
	Usuario u("i12gafej@uco.es", "12344");
	int rol=1; //ROL 1=participante
	EXPECT_TRUE(u.iniciarSesion("i12gafej@uco.es", "12344", &rol)); //user ya registrado en la bbdd
}







//Author: Juan Manuel Delafuente Jurado




TEST(arrobacomprobacion, arroba){
	

	EXPECT_FALSE(arroba(".ss@uco.es")); //formato incorrecto
	EXPECT_FALSE(arroba("sdfs@sdf.es"));//dominio no valido(no es de la uco)
	EXPECT_FALSE(arroba("ssuco.es")); //carece de arroba
	EXPECT_FALSE(arroba("ss@uco..es")); //formato incorrecto
	EXPECT_FALSE(arroba("i.12dd@ucoes")); //formato incorrecto
	EXPECT_FALSE(arroba("i.12dd@uco")); //falta el .es
	EXPECT_FALSE(arroba("i.12dd@uco.com")); //dominio no valido(uco.es)
	EXPECT_FALSE(arroba("i@dd@uco.es")); //formato incorrecto
	EXPECT_TRUE(arroba("werwe@uco.es"));
}




TEST(Ccurso, crearCurso){
	Curso c1 = Curso("005", "Curso de peluqueria", "Paco Gonzalez y Juan Marin",
	 "Paco Gonzalez: paco@uco.es y Juan Marin: jmarins@uco.es,","Sobre peluqueria",
	  "// Grado en Ingeniería Informática", "10", "04/03/2023", "03/05/2023", "0");
	
	list<Curso> listas = {c1};

	Ccurso cc("r@uco.es", "4", listas);

	EXPECT_TRUE(cc.crearCurso(c1));

}



/* MAS TEST QUE FUNCIONAN Y QUE PODRIAN INCLUIRSE EN EL PROYECTO, ESTAN COMENTADOS PORQUE SE DEBEN ENTREGAR 6
 
TEST(comprobacionesPERFECTO, comprobaciones){
	Participante p = Participante("", "", "", "", "", "", "", "");
		
	p.set_correo("i12cacrm@uco.es"); 
	p.set_contra("1231231"); 
	p.set_nombre("Javier Garcia Fernandez");
	p.set_dni("46072134");
	p.set_estudios("// Grado en Ingeniería Informática");
	p.set_telefono("Telefono");
	p.set_nacimiento("04012003");
	p.set_cmatriculados("CURSO DE PILOTO");
	
	Curso c1 = Curso("", "", "", "", "", "", "", "", "", "");
	
	c1.set_id("Curso de cocina");
	c1.set_nombre("Karlos algiñano y Dolores modales.");
	c1.set_docentes("Karlos algiñano: karlos@uco.es y Dolores modales: d.mor@uco.es,");
	c1.set_contactos("Sobre cocina");
	c1.set_estudios("// Grado en Ingeniería Informática");
	c1.set_aforo("10");
	c1.set_inicio("04/03/2023");
	c1.set_fin("03/05/2023");
	c1.set_participantes("0");
	list<Curso> listas = {c1};
	EXPECT_TRUE(p.comprobaciones(1, listas));
};
TEST(comprobacionesAforoCompleto, comprobaciones){
	
	Participante p = Participante("", "", "", "", "", "", "", "");
		
	p.set_correo("i12cacrm@uco.es"); 
	p.set_contra("1231231"); 
	p.set_nombre("Javier Garcia Fernandez");
	p.set_dni("46072134");
	p.set_estudios("// Grado en Mecanica");
	p.set_telefono("Telefono");
	p.set_nacimiento("04012003");
	p.set_cmatriculados("CURSO DE PILOTO // Curso de cocina //");
	
	Curso c1 = Curso("", "", "", "", "", "", "", "", "", "");
	
	c1.set_id("Curso de cocina");
	c1.set_nombre("Karlos algiñano y Dolores modales.");
	c1.set_docentes("Karlos algiñano: karlos@uco.es y Dolores modales: d.mor@uco.es,");
	c1.set_contactos("Sobre cocina");
	c1.set_estudios("// Grado en Ingeniería Informática");
	c1.set_aforo("10");
	c1.set_inicio("04/03/2023");
	c1.set_fin("03/05/2023");
	c1.set_participantes("10");
	list<Curso> listas = {c1};

	EXPECT_FALSE(p.comprobaciones(1, listas));//aforo completo
};

TEST(comprobacionesFechaPasada, comprobaciones){
	
	Participante p = Participante("", "", "", "", "", "", "", "");
		
	p.set_correo("i12cacrm@uco.es"); 
	p.set_contra("1231231"); 
	p.set_nombre("Javier Garcia Fernandez");
	p.set_dni("46072134");
	p.set_estudios("// Grado en Mecanica");
	p.set_telefono("Telefono");
	p.set_nacimiento("04012003");
	p.set_cmatriculados("CURSO DE PILOTO // Curso de cocina //");
	
	Curso c1 = Curso("", "", "", "", "", "", "", "", "", "");
	
	c1.set_id("Curso de cocina");
	c1.set_nombre("Karlos algiñano y Dolores modales.");
	c1.set_docentes("Karlos algiñano: karlos@uco.es y Dolores modales: d.mor@uco.es,");
	c1.set_contactos("Sobre cocina");
	c1.set_estudios("// Grado en Ingeniería Informática");
	c1.set_aforo("10");
	c1.set_inicio("04/03/2022");
	c1.set_fin("03/05/2023");
	c1.set_participantes("0");
	list<Curso> listas = {c1};

	EXPECT_FALSE(p.comprobaciones(1, listas));//fecha pasada
};

TEST(comprobacionesNoEstudiosRequeridos, comprobaciones){
	
	Participante p = Participante("", "", "", "", "", "", "", "");
		
	p.set_correo("i12cacrm@uco.es"); 
	p.set_contra("1231231"); 
	p.set_nombre("Javier Garcia Fernandez");
	p.set_dni("46072134");
	p.set_estudios("// Grado en Mecanica");
	p.set_telefono("Telefono");
	p.set_nacimiento("04012003");
	p.set_cmatriculados("CURSO DE PILOTO // Curso de cocina //");
	
	Curso c1 = Curso("", "", "", "", "", "", "", "", "", "");
	
	c1.set_id("Curso de cocina");
	c1.set_nombre("Karlos algiñano y Dolores modales.");
	c1.set_docentes("Karlos algiñano: karlos@uco.es y Dolores modales: d.mor@uco.es,");
	c1.set_contactos("Sobre cocina");
	c1.set_estudios("// Grado en Ingeniería Informática");
	c1.set_aforo("10");
	c1.set_inicio("04/03/2023");
	c1.set_fin("03/05/2023");
	c1.set_participantes("0");
	list<Curso> listas = {c1};

	EXPECT_FALSE(p.comprobaciones(1, listas));//estudio requerido no valido
};


TEST(Usuariodominiofalso, registrarUsuario){
	Usuario u("i12efe@sdo.es", "1231231");
	EXPECT_FALSE(u.registrarUsuario("i12efe@sdo.es", "1231231")); //no cumple el dominio de la uco
}



*/
