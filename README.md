# Proyecto del equipo 102
## Javier Garcia Fernandez, Manuel Cabrera Crespo, Juan Manuel de la Fuente Jurado

**Enlace del repo**
(https://github.com/i12gafej/eq102)

**Enlace del video explicativo del programa**
(https://www.youtube.com/watch?v=feJ4mAaixUw)

### Instalacion
1. Clonar repositorio  
`git clone https://github.com/i12gafej/eq102.git`  
`cd eq102`  
  
2. Borramos la carpeta build  
`rm -r build`  
  
3. Creamos la carpeta build y accedemos a ella  
`mkdir build`  
`cd build`  
  
4. Iniciamos Cmake  
`cmake ..`  
  
5. Compilamos el proyecto con MakeFile  
`make`  
  
6. Copiamos los ficheros de datos en los ejecuatables del main y del test  
`cd ../src/programa`  
`echo ../../build/src/programa/ ../../build/tests/ | xargs -n 1 cp logs.txt matriculas.txt open.txt`  
  
7. Ejecutar el programa  
`cd ../../build/src/programa`  
`./main`  
  
8. Ejecutar los tests (en eq102/build)  
***ejecuta todos los tests***  
> * `ctest`  
***ejecuta cada test***
> * `cd tests`  
> * `./tests`  
  
  
### Objetos en nuestra página
* Usuario
  * Participante
  * Coordinador de Curso
 * Curso
 
 ### Codigo de clases y contructores
 #### Usuario:
 ***Clase***
 
 ```
 class Usuario{
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
		bool iniciarSesion(string cor, string contra, int *role);	//permite iniciar sesion a un usuario
		int verPagina(int vez, list<Curso> listas);			//permite ver la pagina de inicio a un usuario
		bool registrarUsuario(string cor, string cotra);		//permite registrar a un nuevo usuario
		void verListas(list<Curso> listas);				//permite ver la lista de cursos disponibles
};
```
  ***Constructor***
  ```
  Usuario::Usuario(string correo, string contra){
     correo_ = correo;
     contra_ = contra;
  }
  ```
 
 #### Participante:
 ***Clase***
 ```
 class Participante : public Usuario{
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
		bool matricularse(int curso, int cuantos);			//permite a un participante matricularse en un curso
		bool globalset(string cor);					//permite hacer todos los set al participante
		void paginaParticipante(int vez);				//permite mostrar la página al participante
		bool comprobaciones(int curso, list<Curso> listas);		//permite comprobar los datos del alumno para entrar
										//en el curso que desea acceder

};
 ```
 
 ***Constructor***
  ```
 Participante::Participante(string correo,
		string contra,
		string nombre = "null",
		string dni = "null",
		string estudios = "null",
		string telefono = "null",
		string nacimiento = "null",
		string cmatriculados = "null"):Usuario(correo, contra){}
 ```
 
 #### Coordinador de Cursos:
 ***Clase***
  ```
 class Ccurso : public Usuario{
	private:
	list<Curso> listas_;
	public:
	Ccurso(string, string, list<Curso>);
	//setter
	inline void set_listas(list<Curso> listas){listas_ = listas;};
	//getters
	inline list<Curso> get_listas(){return listas_;};
	
	int modificarCurso();				//permite realizar las funcionalidades de modificacion de cursos
	void paginaCcurso(int vez);			//permite ver la página al coordinador de curso
	bool crearCurso(Curso c1);			//permite crear un curso
	bool editarCurso();				//permite editar un curso
	bool eliminarCurso(int curso);			//permite eliminar un curso
};
 ```
 ***Constructor***
  ```
 Ccurso::Ccurso(string correo, string contra, list<Curso> listas):Usuario(correo, contra){}
  ```
 #### Curso:
 ***Clase***
  ```
 class Curso{
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
};
 ```
 ***Constructor***
  ```
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
 ```
 ### Funciones no metódicas:
 #### Curso
 ```
 list<Curso> listaCursos(); 			//carga los cursos en una lista
void imprimirListas(list<Curso> listas);	//imprime la lista de cursos en un fichero de texto
```
#### Usuario
```
bool comprobar_coincidencia(string cor, string con, int **rol); 		//comprueba la relacion entre usuario, contraseña y rol
bool comprobar_correo(string cor);						//comprueba la existencia del correo
bool arroba(string cor);							//comprueba la validez del formato del correo
void imprimir();								//imprime los logs.txt
void menu();									//despliega un menu
struct Us introducirUsuarioyContrasenia();					//permite introducir correo y contraseña

bool distancia(string cor);							//permite conocer la distancia entre @ y .
void registrar(string cor, string con);						//imprime el nuevo usuario registrado en logs.txt
int contarUsuarios();								//cuenta los usuarios de la pagina

int contarlineas();								//cuenta las lineas del fichero open.txt
```
#### Participante
```
void seleccionarCurso(int *curso, int *cual, list<Curso> listas);		//sirve para seleccionar un curso
void menuParticipante();							//muestra menu 
bool opcionaMatricula();							//pregunta si quieres matricularte
bool buscarCurso(int **curso, list<Curso> listas);				//busca un curso en la lista
bool comprobarFecha(string ahora, string date);					//comprueba si la fecha es valida
bool actualizarMatricula(string dni, string nombre);				//actualiza el fichero matriculas.txt al registrar a alguien
string concatenar(vector<string> v, int n);					//concatena un vector
string estudiosPosibles();							//menu de eleccion de grado universitario
string fechaPosible();								//menu de seleccion de fecha
bool imprimirPerfilNuevo(string cor, string w[]);				//imprime una matricula nueva
```
#### Coordinador de Cursos
```
void opcionMod();								//muestra menu
vector<string> atributos();							//pide atributos cuando se quiere crear curso

size_t comprobarExistencia(string c);						//devuelve la posicion de la linea donde se encuentra el elemento existente 
										//y -1 si no existe
string estudiosRequeridos();							//menu de seleccion de estudios requeridos por curso
string fecha(int mod);								//menu de eleccion de fecha de inicio y fin de curso
vector<string> desglosar(string linea, int tipo);				//desglosa un string concatenado segun sea string de docentes, contactos o estudios
```
 ### Casos de uso abordados
 1. Iniciar Sesion
 2. Registrarse
 3. Ver lista de cursos
 4. Modificar curso
