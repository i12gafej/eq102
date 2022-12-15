/*
 * tests.cpp
 *
 *  Created on: 15 dic 2022
 *      Author: USUARIO
 */

#include "gtest/gtest.h"
#include "objects.h"

TEST(Ccurso, Matricularse){
	Ccurso cc1("pepe@uco.es", "unodos");
	EXPECT_EQ("pepe@uco.es", cc1.get_correo());
}


