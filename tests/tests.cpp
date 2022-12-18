#include "objects.h"
#include "gtest/gtest.h"

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

TEST(comprobacionesYaMatriculado, comprobaciones){
	
	Participante p = Participante("", "", "", "", "", "", "", "");
		
	p.set_correo("i12cacrm@uco.es"); 
	p.set_contra("1231231"); 
	p.set_nombre("Javier Garcia Fernandez");
	p.set_dni("46072134");
	p.set_estudios("// Grado en Mecanica");
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

	EXPECT_FALSE(p.comprobaciones(1, listas));//ya matriculado
};
