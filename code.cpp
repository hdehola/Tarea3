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

cuenta registro_cuentas::obtener(string rol){
    int contador = 0;
    int hashing = hash(rol);
    while(true){
        if (tabla[hashing].rol == rol) {
            return tabla[hashing];
        }else if (contador == ranuras){
            break;
        }else{
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
        if (tabla[hashing].rol == ""){
            tabla[hashing] = c;
            usados++;
            factor_de_carga = float (usados/ranuras);
            break;
        } else if (tabla[hashing].rol == c.rol) {
            cout << "Rol ya existente" <<endl;
            break;
        }else{
            hashing = p(c.rol, contador);
            contador++;
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
            factor_de_carga = float (usados/ranuras);
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
        for (i = 0; i < int(linea.length()) + 1; i++){
            if (linea[i] == ' '|| i == int(linea.length())){
                if (funcion == ""){
                    funcion = aux;
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
            cuenta c = regis.obtener(c.rol);
            if (c.rol != ""){
                cout << c.nombre << " " << c.descripcion << endl;
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
        funcion = "";
        rol = ""; 
        nombre = "";
        descripcion = "";
    }
    archivo.close();
    return 0;
}