# Proyecto del equipo 102
## Javier Garcia Fernandez, Manuel Cabrera Crespo, Juan Manuel de la Fuente Jurado

**Enlace del repo**
(https://github.com/i12gafej/eq102)

### Objetos en nuestra página
* Usuario
  * Participante
  * Coordinador de Curso
 * Curso
 
 ### Codigo de clases y contructores
 #### Usuario:
 ***Clase***
 '''class Usuario{
	private:
		string correo_;
		string contra_;
	public:

		Usuario(string, string);
		//setters
		inline void set_correo(string correo){correo_ = correo;}
		inline void set_contra(string contra){contra_ = contra;}
		//Getters
		inline string get_correo(){return correo_;}
		inline string get_contra(){return contra_;}
		//User's operations
		bool iniciarSesion(string cor, string contra, int *role);
		int verPagina(int vez, list<Curso> listas);
		bool registrarUsuario(string cor, string cotra);
		void verListas(list<Curso> listas);
};'''
  ***Constructor***
  '''Usuario::Usuario(string correo, string contra){
     correo_ = correo;
     contra_ = contra;
  }'''
 
 #### Participante:
 ***Clase***
 '''class Participante : public Usuario{
	private:
		string nombre_, dni_, estudios_, telefono_, nacimiento_, cmatriculados_;
		list<Curso> listas_;
	public:
		Participante(string, string, string, string, string, string, string, string);
		//setters
		inline void set_nombre(string nombre){nombre_ = nombre;}
		inline void set_dni(string dni){dni_ = dni;}
		inline void set_estudios(string estudios){estudios_ = estudios;}
		inline void set_telefono(string telefono){telefono_ = telefono;}
		inline void set_nacimiento(string nacimiento){nacimiento_ = nacimiento;}
		inline void set_cmatriculados(string cmatriculados){cmatriculados_ = cmatriculados;}
		inline void set_listas(list<Curso> listas){listas_ = listas;};
		//getters
		inline list<Curso> get_listas(){return listas_;};
		inline string get_nombre(){return nombre_;}
		inline string get_dni(){return dni_;}
		inline string get_estudios(){return estudios_;}
		inline string get_telefono(){return telefono_;}
		inline string get_nacimiento(){return nacimiento_;}
		inline string get_cmatriculados(){return cmatriculados_;}
		//funcionalidades
		bool matricularse(int curso, int cuantos);
		bool globalset(string cor);
		void paginaParticipante(int vez);
		bool comprobaciones(int curso, list<Curso> listas);

};'''
 
 ***Constructor***
 
 '''Participante::Participante(string correo,
		string contra,
		string nombre = "null",
		string dni = "null",
		string estudios = "null",
		string telefono = "null",
		string nacimiento = "null",
		string cmatriculados = "null"):Usuario(correo, contra){}'''
 
 #### Coordinador de Cursos:
 ***Clase***
 '''class Ccurso : public Usuario{
	private:
	list<Curso> listas_;
	public:
	Ccurso(string, string, list<Curso>);
	//setter
	inline void set_listas(list<Curso> listas){listas_ = listas;};
	//getters
	inline list<Curso> get_listas(){return listas_;};
	int modificarCurso();
	void paginaCcurso(int vez);
	bool crearCurso(Curso c1);
	bool editarCurso();
	bool eliminarCurso(int curso);
};'''
 ***Constructor***
 '''Ccurso::Ccurso(string correo, string contra, list<Curso> listas):Usuario(correo, contra){}'''
 #### Curso:
 ***Clase***
 '''class Curso{
	private:
		string id_, nombre_, docentes_, contactos_, descripcion_, estudios_, aforo_, inicio_, fin_, participantes_;
	public:
		Curso(string, string, string, string, string, string, string, string, string, string); 
		//setters
		inline void set_id(string id){id_ = id;};
		inline void set_nombre(string nombre){nombre_ = nombre;};
		inline void set_docentes(string docentes){docentes_ = docentes;};
		inline void set_contactos(string contactos){contactos_ = contactos;};
		inline void set_descripcion(string descripcion){descripcion_ = descripcion;};
		inline void set_estudios(string estudios){estudios_ = estudios;};
		inline void set_aforo(string aforo){aforo_ = aforo;};
		inline void set_inicio(string inicio){inicio_ = inicio;};
		inline void set_fin(string fin){fin_ = fin;};
		inline void set_participantes(string participantes){participantes_ = participantes;};
		//getters
		inline string get_id(){return id_;};
		inline string get_nombre(){return nombre_;};
		inline string get_docentes(){return docentes_;};
		inline string get_contactos(){return contactos_;};
		inline string get_descripcion(){return descripcion_;};
		inline string get_estudios(){return estudios_;};
		inline string get_aforo(){return aforo_;};
		inline string get_inicio(){return inicio_;};
		inline string get_fin(){return fin_;};
		inline string get_participantes(){return participantes_;};
		//funcionalidades
};'''
 ***Constructor***
 '''Curso::Curso(string id, 
		string nombre, 
		string docentes, 
		string contactos, 
		string descripcion, 
		string estudios, 
		string aforo, 
		string inicio, 
		string fin, 
		string participantes){}'''
 ### Casos de uso abordados
 1. Iniciar Sesion
 2. Registrarse
 3. Ver lista de cursos
 4. Modificar curso


