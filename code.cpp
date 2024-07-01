#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct cuenta {
    // El rol es el identificador de la persona.
    // El nombre y la descripcion son valores asociados al rol
    string rol, nombre, descripcion;
};

class registro_cuentas {
    private:
        float factor_de_carga = 0.0;
        cuenta* tabla; // Aca se almacenaran los elementos de la tabla
        int ranuras = 15; // Cuantas ranuras tiene la tabla hash (inicialmente)
        int usados = 0;  //se usa para contar cuantas casillas hay usadas///////////////////////////////////////////
        int hash(string rol){  // Se obtiene el hash dado el rol   //sumar con el cogdigo ascii el primer y ultimo digito por el "k" 
            int N2 = int(rol[8]);
            int resto = N2 % ranuras;
            return resto;
        }
        int p(string rol, int i){ // Se obtiene la ranura a revisar en caso de colisión dado el rol y el intento i, 1, 13, 14
            int hashing = hash(rol); 
            int p = ((i*i)+i+hashing) % ranuras;
            return p;
        }
    public:
        registro_cuentas() {   // (Recuerde que puede crear con distintos parametros)
            tabla = new cuenta[ranuras];
            cuenta c;
            c.rol = "";
            for (int i = 0; i < ranuras; i++){
                tabla[i].rol = "";
            }
        }
        ~registro_cuentas(){
            delete [] tabla;
        }
        cuenta obtener(string rol); // Dado el rol, devuelve la cuenta con ese rol
        void agregar(cuenta c); // Se agrega una cuenta a la tabla
        void eliminar(string rol); // Se elimina la cuenta 
        void modificar(string rol, string descripcion); // Se modifica la descripcion del rol
        void redimensionar(int n); // Se redimensiona la tabla a n espacios
        void estadisticas(); // Debe mostrar las estadisticas
};

/*****
* cuenta registro_cuentas::obtener()
******
* Esta funcion recibe un rol en forma de string, luego busca dentro de la tabla hash la cuenta asignada con dicho rol y retorna esta.
******
* Input:
* string rol: Se le entrega un rol para encontrar la cuenta a la que este asignada dicho rol.
* .......
******
* Returns:
* cuenta, retorna la cuenta a la que esta asignado el rol que fue entrago como parametro.
*****/

cuenta registro_cuentas::obtener(string rol){
    int contador = 0;
    int hashing = hash(rol);
    while(contador < ranuras){
        if (tabla[hashing].rol == rol) {
            return tabla[hashing];
        }
        else{
            contador++;
            hashing = p(rol, contador);
        }
    }
    return { "" , "" , "" };
}

/*****
* void registro_cuentas::agregar()
******
* Esta funcion recibe una cuenta para ser agregada en la tabla hash.
******
* Input:
* cuenta c: Se le entrega la cuenta que sera agregada en la tabla hash.
* .......
******
* Returns:
* No retorna nada.
*****/
void registro_cuentas::agregar(cuenta c){
    int contador = 0;
    int hashing = hash(c.rol);
    while(true){
        if (usados >= int(ranuras*0.7)){
            redimensionar(ranuras+15);
        }else if (tabla[hashing].rol == ""){
            tabla[hashing].rol = c.rol;
            tabla[hashing].nombre = c.nombre;
            tabla[hashing].descripcion = c.descripcion;
            usados++;
            break;
        }else if (tabla[hashing].rol == c.rol) {
            cout << "Rol ya existente" <<endl;
            break;
        }else{
            hashing = p(c.rol, contador);
            contador++;
        }
    }
}

/*****
* void registro_cunentas::eliminar()
******
* Esta funcion recibe una cuenta para ser eliminada de la tabla hash.
******
* Input:
* string rol: Se le entrega un rol para encontrar la cuenta a la que este asignada dicho rol.
* .......
******
* Returns:
* No retorna nada.
*****/
void registro_cuentas::eliminar(string rol){
    int contador = 0;
    int hashing = hash(rol);
    while(true){
        cout << tabla[hashing].rol << endl;
        cout << rol << endl;
        cout <<""<<endl;
        if (tabla[hashing].rol == rol){
            tabla[hashing].rol = "";
            usados--;
            cout << "si se borro" << endl;
            break;
        } else if (contador == ranuras) {
            cout << "Rol no" << endl;
            break;
        }else{
            contador++;
            hashing = p(rol, contador);
        }
    }
}

/*****
* void registro_cunentas::modificar()
******
* Esta funcion recibe un rol y una descripcion para modificar la descripcion de la cuenta que tiene asignado el rol entregado.
******
* Input:
* string rol, descripcion: Se le entrega un rol para encontrar la cuenta que posee dicho rol y la nueva descripcion que sera modificada.
* .......
******
* Returns:
* No retorna nada.
*****/
void registro_cuentas::modificar(string rol, string descripcion){
    int hashing = hash(rol);
    int contador = 0;
    while(true){
        if (tabla[hashing].rol == rol){
            tabla[hashing].descripcion = descripcion;
            break;
        } else if (contador == ranuras) {
            break;
        }else{
            contador++;
            hashing = p(rol, contador);
        }
    }
    cout << "Rol no existente" << endl;
}

/*****
* void registro_cunentas::redimensionar()
******
* Esta funcion recibe un entero y crea una nueva tabla hash con cantidad de ranuras n agregando en esta los datos de la anterior y eliminandola.
******
* Input:
* int n : Se le entrega un entero que indica la cantida de ranuras que tendra la nueva tabla hash.
* .......
******
* Returns:
* No retorna nada.
*****/
void registro_cuentas::redimensionar(int n){
    cuenta *tabla_v = tabla;
    delete []tabla;
    ranuras = n;
    cuenta *tabla = new cuenta[n];
    for (int M = 0; M < n; M++){
        tabla[M].rol = "";
    }
    for (int i = 0; i < usados; i++){
        if (tabla_v[i].rol != ""){
            agregar(tabla_v[i]);
        }
    }
    delete []tabla_v;
}

/*****
* void registro_cunentas::estadisticas()
******
* Esta funcion muestra en la consola las estadisticas correspondientes a la cantidada de ranuras totales, la cantida de ranuras usadas y el factor de carga.
******
* Input:
* No recibe nada.
* .......
******
* Returns:
* No retorna nada.
*****/
void registro_cuentas::estadisticas(){
    factor_de_carga = float(usados)/float(ranuras);
    cout << "RANURAS OCUPADAS: "<< usados  << endl;
    cout << "RANURAS TOTALES: " << ranuras << endl;
    cout << "FACTOR DE CARGA: "<< factor_de_carga << endl;
}

int main() {
    ifstream archivo;
    int i;
    string linea, aux;
    string funcion, rol, nombre, descripcion;
    registro_cuentas regis;
    cuenta c;
    //char caracter;
    archivo.open("prueba.txt", ios::in);
    if (archivo.fail()){
        cout << "No se pudo abrir el archivo"<< endl;
        exit(1);
    };
    while (!archivo.eof()){
        getline(archivo, linea);
        if (linea[linea.size()-1] == '\r') {
            linea.erase(linea.size()-1);
        }
        for (i = 0; i < int(linea.length()) + 1; i++){
            if (linea[i] == ' '|| i == int(linea.length())){
                if (funcion == ""){
                    funcion = aux;
                    cout << funcion << endl;
                    aux = "";
                }
                else if (rol == ""){
                    rol = aux;
                    aux = "";
                }   
                else if (nombre == ""){
                    nombre = aux;
                    aux = "";
                }
                else if (descripcion == ""){
                    descripcion = aux;
                    aux = "";
                }
                }else if (linea[i] != ' '){  
                    aux += linea[i];     
                }
        }
        i = 0;
        c.rol = rol;
        c.nombre = nombre;
        c.descripcion = descripcion;
        if (funcion == "OBTENER"){
            cuenta c2  = regis.obtener(c.rol);


            if (c2.rol != ""){
                cout << c2.nombre << " " << c2.descripcion << endl;
            }else{
                cout << "Rol no existente" << endl;
            }
        }
        else if (funcion == "AGREGAR"){
            regis.agregar(c);
        }
        else if(funcion == "QUITAR"){
            regis.eliminar(c.rol);
        }
        else if (funcion == "MODIFICAR"){
            regis.modificar(c.rol, c.nombre);
        }
        else{
            cout << "entra" << endl;
            regis.estadisticas();
        }

        funcion = "";
        rol = ""; 
        nombre = "";
        descripcion = "";
    }
    archivo.close();
    return 0;
}