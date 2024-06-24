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
        int hash(string rol){  // Se obtiene el hash dado el rol   //sumar con el cogdigo ascii el primer y ultimo digito por el "k" 
            int N2 = int(rol[9]);
            int resto = N2 % ranuras;
            return resto;
        }
        int p(string rol, int i){ // Se obtiene la ranura a revisar en caso de colisión dado el rol y el intento i

        }
    public:
        registro_cuentas() {   // (Recuerde que puede crear con distintos parametros)
            tablas = new cuenta[ranuras];
        }
        ~registro_cuentas(){
            delete tablas[];
        }
        cuenta obtener(string rol); // Dado el rol, devuelve la cuenta con ese rol
        void agregar(cuenta c); // Se agrega una cuenta a la tabla
        void eliminar(string rol); // Se elimina la cuenta
        void modificar(string rol, string descripcion); // Se modifica la descripcion del rol
        void redimensionar(int n); // Se redimensiona la tabla a n espacios
        void estadisticas(); // Debe mostrar las estadisticas
};


void registro_cuentas::agregar(cuenta c){
    int hashing = hash(c.rol);
    if (tablas[hashing] == null){
        tablas[hashing] = c;
    }else{
        int colisión = p(c.rol, )

    }
}



int main() {

    ifstream archivo;
    int i;
    string linea, aux;
    string funcion, inf2, inf3, inf4;
    //char caracter;

    archivo.open("prueba.txt", ios::in);
    if (archivo.fail()){
        cout << "No se pudo abrir el archivo"<< endl;
        exit(1);
    };

    while (!archivo.eof()){
        getline(archivo, linea);
        for (i = 0; i < linea.length() + 1; i++){
            if (linea[i] == ' '|| i == linea.length()){
                if (funcion == ""){
                    funcion = aux;
                    aux = "";
                }
                else if (inf2 == ""){
                    inf2 = aux;
                    aux = "";
                }   
                else if (inf3 == ""){
                    inf3 = aux;
                    aux = "";
                }
                else if (inf4 == ""){
                    inf4 = aux;
                    aux = "";
            }
        }
            else if (linea[i] != ' '){  
                aux += linea[i];     
            }
    }
        
        if(funcion = "AGREGAR"){
            c1.agregar(inf2, inf3, inf4);
        }
        funcion = "";
        inf2 = "";
        inf3 = "";
        inf4 = "";
    }
    archivo.close();
    return 0;
}