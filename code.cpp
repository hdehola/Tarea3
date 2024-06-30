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
        int hash(string rol) {
            int hash_value = 0;
            for (char c : rol) {
                hash_value = (hash_value * 31 + c) % ranuras;
                return hash_value;
            }
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

cuenta registro_cuentas::obtener(string rol){
    int contador = 0;
    int hashing = hash(rol);
    while(contador < ranuras){
        if (tabla[hashing].rol == rol){
            return tabla[hashing];
        }
        else{
            contador++;
            hashing = p(rol, contador);
        }
    }
    return { "" , "" , "" };
}

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
            contador++;
            hashing = p(c.rol, contador);
        }
    }
}

void registro_cuentas::eliminar(string rol){
    int contador = 0;
    int hashing = hash(rol);
    while(true){
        if (tabla[hashing].rol == rol){
            tabla[hashing].rol = "";
            usados--;
            break;
        } else if (contador == ranuras) {
            break;
        }else{
            contador++;
            hashing = p(rol, contador);
        }
    }
}

void registro_cuentas::modificar(string rol, string descripcion){
    int hashing = hash(rol);
    int contador = 0;
    while(true){
        if (tabla[hashing].rol == rol){
            tabla[hashing].descripcion = descripcion;
            break;
        } else if (contador == ranuras) {
            cout << "Rol no existente" << endl;
            break;
        }else{
            contador++;
            hashing = p(rol, contador);
        }
    }
}

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

void registro_cuentas::estadisticas(){
    factor_de_carga = (usados+0.0)/ranuras;
    cout << "RANURAS OCUPADAS: "<< usados  << endl;
    cout << "RANURAS TOTALES: " << ranuras << endl;
    cout << "FACTOR DE CARGA: "<< factor_de_carga << endl;
}

int main() {
    ifstream archivo("prueba.txt");
    string linea, funcion, rol, nombre, descripcion;
    registro_cuentas regis;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        istringstream iss(linea);
        iss >> funcion >> rol >> nombre >> descripcion;

        cuenta c = { rol, nombre, descripcion };

        if (funcion == "OBTENER") {
            cuenta c2 = regis.obtener(c.rol);
            if (c2.rol != "") {
                cout << c2.nombre << " " << c2.descripcion << endl;
            } else {
                cout << "Rol no existente" << endl;
            }
        } else if (funcion == "AGREGAR") {
            regis.agregar(c);
        } else if (funcion == "QUITAR") {
            regis.eliminar(c.rol);
        } else if (funcion == "MODIFICAR") {
            regis.modificar(c.rol, c.descripcion);
        } else if (funcion == "ESTADISTICAS") {
            regis.estadisticas();
        }
    }

    archivo.close();
    return 0;
}