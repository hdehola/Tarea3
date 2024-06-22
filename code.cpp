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
        cuenta tabla*; // Aca se almacenaran los elementos de la tabla
        int ranuras = 15; // Cuantas ranuras tiene la tabla hash (inicialmente)
        int hash(string rol); // Se obtiene el hash dado el rol
        int p(string rol, int i); // Se otiene la ranura a revisar en caso de colisión dado el rol y el intento i
    public:
        registro_cuentas() {} // (Recuerde que puede crear con distintos parametros)
        cuenta obtener(string rol); // Dado el rol, devuelve la cuenta con ese rol
        void agregar(cuenta c); // Se agrega una cuenta a la tabla
        void eliminar(string rol); // Se elimina la cuenta
        void modificar(string rol, string descripcion); // Se modifica la descripcion del rol
        void redimensionar(int n); // Se redimensiona la tabla a n espacios
        void estadisticas(); // Debe mostrar las estadisticas
};


int main() {
    string linea;
    ifstream archivo("pruebas.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit (1);
    }
    while(getline(prueba, linea)){  
        string funcion = "";
        bool flag = true;
        for (int i = 0; i < int(linea.length()); i++) {  
            if (bandera){      
                funcion += linea[i];
            }
            if (funcion == "AGREGAR"){

            }else if (funcion == "QUITAR"){

            }else if (funcion == "MODIFICAR"){
                
            }else if (funcion == "OBTENER"){
                
            }else if (funcion == "ESTADISTICAS"){
                
            }

        }
    }
}