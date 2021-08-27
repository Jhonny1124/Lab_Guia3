#include <iostream>
#include <fstream>
#include<string>
#include<math.h>

using namespace std;

void Decimal_Binario(int decimal, string &binario1){

    /**Esta funcion convierte un numero decimal a su representacion binario
      *recibe como parametro un int decimal que es el numero que se va a representar como binario
      *y un strign binario que es la clase donde se va a almacenar la representacion binaria
    **/

    unsigned short int prueba = 0;
    unsigned short int *dir_prueba = &prueba;

    for(int i = 7; i >= 0; i--){
        *dir_prueba = pow(2,i);
        if( prueba <= decimal ){
            decimal -= prueba;
            binario1 += '1';
        }
        else{
            binario1 += '0';
        }
    }

}



int Binario_Decimal(string binario){

    /**Esta funcion recibe como parametro un string que contine una representacion
     * binaria de 8 bits y lo que hace es convertir esa representacion a un numero decimal
    **/

    int suma = 0;

    for(int i = 7; i >= 0; i--){
        if(binario.at(7-i) == '1' && binario.at(7-i) != '\n' ){
            suma += pow(2,i);
        }
    }
    return suma;
}

void Lectura_Archivos(string &texto, string nombre){

    /**Esta funcion lee el contenido de un archivo de texto
     * recibe como parametros dos variables tipo string
     * la variable texto es la que va a almacenar el contenido del archivo de texto
     * la variable nombre contiene el nombre del archivo de texto y nos permite localizar
     * donde se encuentra el archivo
    **/

    string add;

    ifstream archivo;

    archivo.open("../Codificar_Decodificar/BD/"+nombre);

    if(!archivo.is_open()){
        cout << "El archivo " << nombre << " no pudo ser abierto" << endl;
        exit(1);
    }

    getline(archivo, add);
    while(getline(archivo, add)){
        texto += add+'\n';
        getline(archivo, add);
    }
    archivo.close();
}


void Escritura_Archivos(string texto, string nombreopen){

    /**Esta funcion escribe en un archivo de texto
     * recibe como parametro dos variables tipo string
     * la variable texto tiene almacenada la informacion que se desea
     * escribir en el archivo
     * la variable nombreopen tiene almacenado el nombre del archivo
     * donde se desea escribir
    **/

    string ruta = "../Codificar_Decodificar/BD/";

    ofstream archivo;
    ruta += nombreopen;

    archivo.open(ruta);

    if(!archivo.is_open()){
        cout << "El archivo " << nombreopen << " no pudo ser abierto" << endl;
        exit(1);
    }

    archivo << texto << endl;

    archivo.close();

}

void Codificacion_Metodo1(string &codificado, string fuente, unsigned int semilla){
    /**Esta funcion permite codificar un archivo de texto
     * recibe como parametro dos variables tipo string y una variable tipo unsigned int
     * La variable codificado va a almacenar el archivo de texto totalmente codificado
     * la variable fuente contiene el nombre del archivo que deseamos codificar
     * La variable semilla contiene el tamaño de los bloques que deseamos tomar
     * Reglas de codificacion:
     * Primero se debe de leer el archivo y pasarlo por completo al codigo ASCII
     * despues se separa el archivo por bloques de numeros dependiendo del tamaño que indique la variable semilla
     * En el primer bloque se cambian todos los 1 por 0 y viceversa. Para los grupos
     * siguientes se debe contar el número de 1s y 0s en el grupo anterior y hacer cambios según la
     * siguiente regla:
            Si hay igual cantidad de 1s y 0s se invierte cada bit del grupo.
            Si hay mayor cantidad de 0s se invierte cada 2 bits.
            Si hay mayor cantidad de 1s se invierte cada 3 bits.
    **/

    unsigned int cont1 = 0, cont0 = 0, cambio = 1;
    string texto;
    string binario;
    string bloque1, bloque2;

    Lectura_Archivos(texto, fuente);

    unsigned int longi = texto.length()-1;

    for(unsigned int i = 0; i < (longi); i++){
        Decimal_Binario(int(texto.at(i)),binario);
    }

    for(unsigned int n = 0; n < (longi*8); n++){
        bloque1 = binario.substr((semilla*n),semilla);
        cont0 = 0;
        cont1 = 0;
        if(bloque1 == ""){
            break;
        }
        if(n == 0){
            for(unsigned int i = 0; i < bloque1.length(); i++){
                if(int(bloque1.at(i)) == 48){
                    codificado += '1';
                }
                else{
                    codificado += '0';
                }
            }
        }
        else{
            bloque2 = binario.substr((semilla*(n-1)),semilla);
            for(unsigned int i = 0; i < bloque2.length(); i++){
                   if(int(bloque2.at(i)) == 48){
                       cont0 ++;
                   }
                   else{
                       cont1++;
                   }
            }
           if(cont0 == cont1){
               cambio = 1;
           }
           else if(cont0 > cont1){
               cambio = 2;
           }
           else if(cont0 < cont1){
               cambio = 3;
           }
           for(unsigned int i = 1; i < bloque1.length()+1; i++){
               if((i%cambio) == 0){
                   if(int(bloque1.at(i-1)) == 48){
                       codificado += '1';
                   }
                   else{
                       codificado += '0';
                   }
               }
               else{
                   codificado += bloque1.at(i-1);
               }
           }
        }
        if(bloque1.length() < semilla){
            break;
        }
    }
}

void Codificacion_Metodo2(string &codificado, string fuente, unsigned int semilla){

    /**Esta funcion permite codificar un archivo de texto
     * recibe como parametro dos variables tipo string y una variable tipo unsigned int
     * La variable codificado va a almacenar el archivo de texto totalmente codificado
     * la variable fuente contiene el nombre del archivo que deseamos codificar
     * La variable semilla contiene el tamaño de los bloques que deseamos tomar
     * Reglas de codificacion:
     * Cada bit en cada bloque se desplazara una posicion a la derecha
    **/

    string texto;
    string binario;
    string bloque1;

    Lectura_Archivos(texto, fuente);

    unsigned int longi = texto.length()-1;

    for(unsigned int i = 0; i < (longi); i++){
        Decimal_Binario(int(texto.at(i)),binario);
    }

    for(unsigned int n = 0; n < (longi*8); n++){
        bloque1 = binario.substr((semilla*n),semilla);
        if(bloque1 == ""){
            break;
        }
        codificado+= bloque1.at((bloque1.length())-1);
        for(unsigned int i = 0; i < bloque1.length()-1; i++){
            codificado += bloque1.at(i);
        }
        if(bloque1.length() < semilla){
            break;
        }
    }
}

void Codificar(unsigned int semilla, unsigned int metodo, string fuente, string salida){

    /**Esta funcion permite codificar un archivo de texto y ademas guardar la codificacion en otro archivo
     * Tiene como parametros dos variables tipo unsigned int y dos variables tipo string
     * la variable semilla contiene el tamaño de los bloques que deseamos coger para la codificacion
     * la variable metodo contine un valor que nos permite saber cual metodo es el que se desea utilizar
     * la variable fuente tiene el nombre del archivo que se desea codificar
     * la variable salida tiene el nombre del archivo donde se guardara la codificacion
    **/

    string codificado;

    if(metodo == 1){
        Codificacion_Metodo1(codificado, fuente, semilla);
    }
    else if(metodo == 2){
        Codificacion_Metodo2(codificado, fuente, semilla);

    }
    Escritura_Archivos(codificado, salida);

    cout << endl<< "EL TEXTO HA SIDO CODIFICADO CON EXITO   " << endl;
}

void Decodificacion_Metodo1(string &decodificado, string fuente, unsigned int semilla){
    /**Esta funcion permite decodificar un archivo de texto previamente codificado
     * recibe como parametro dos variables tipo string y una variable tipo unsigned int
     * La variable decodificado va a almacenar el archivo de texto totalmente decodificado
     * la variable fuente contiene el nombre del archivo que deseamos decodificar
     * La variable semilla contiene el tamaño de los bloques que deseamos tomar
     * Reglas de decodificacion:
     * Ya que todo el archivo esta completamente en binario, lo que debemos hacer es
     * coger el primer bloque invertir los 1s por 0s y viceversa, a partir de este bloque aplicar
     * las reglas de codificacion para el resto del archivo, por ultimo coger bloques de a 8 bits
     * y pasar de binario a su representacion grafica
    **/

    unsigned int cont1 = 0, cont0 = 0, cambio = 1;
    string texto;
    string binario;
    string codificado1;
    string bloque1, bloque2;

    Lectura_Archivos(texto, fuente);

    unsigned int longi = texto.length()-1;

    for(unsigned int n = 0; n < (longi*8); n++){
        bloque1 = texto.substr((semilla*n),semilla);
        cont0 = 0;
        cont1 = 0;
        if(bloque1 == ""){
            break;
        }
        if(n == 0){
            for(unsigned int i = 0; i < bloque1.length(); i++){
                if(int(bloque1.at(i)) == 48){
                    codificado1 += '1';
                }
                else{
                    codificado1 += '0';
                }
            }
        }
        else{
            bloque2 = codificado1.substr((semilla*(n-1)),semilla);
            for(unsigned int i = 0; i < bloque2.length(); i++){
                   if(int(bloque2.at(i)) == 48){
                       cont0 ++;
                   }
                   else{
                       cont1++;
                   }
            }
           if(cont0 == cont1){
               cambio = 1;
           }
           else if(cont0 > cont1){
               cambio = 2;
           }
           else if(cont0 < cont1){
               cambio = 3;
           }
           for(unsigned int i = 1; i < bloque1.length()+1; i++){
               if((i%cambio) == 0){
                   if(int(bloque1.at(i-1)) == 48){
                       codificado1 += '1';
                   }
                   else{
                       codificado1 += '0';
                   }
               }
               else{
                   codificado1 += bloque1.at(i-1);
               }
           }
        }
        if(bloque1.length() < semilla){
            break;
        }
    }
    int decima = 0;
    for(unsigned int n = 0; n < (longi/8); n++){
        binario = codificado1.substr(n*8,8);
        decima = Binario_Decimal(binario);
        decodificado += char(decima);
    }
}

void Decodificacion_Metodo2(string &decodificado, string fuente, unsigned int semilla){

    /**Esta funcion permite decodificar un archivo de texto previamente codificado
     * recibe como parametro dos variables tipo string y una variable tipo unsigned int
     * La variable decodificado va a almacenar el archivo de texto totalmente decodificado
     * la variable fuente contiene el nombre del archivo que deseamos decodificar
     * La variable semilla contiene el tamaño de los bloques que deseamos tomar
     * Reglas de codificacion:
     * Cada bit en cada bloque se desplazara una posicion a la izquierda
    **/

    string texto;
    string binario;
    string bloque1;
    string codificado;

    Lectura_Archivos(texto, fuente);

    unsigned int longi = texto.length()-1;

    for(unsigned int n = 0; n < (longi*8); n++){
        bloque1 = texto.substr((semilla*n),semilla);
        if(bloque1 == "" || bloque1 == "\n"){
            break;
        }
        codificado+= bloque1.at(1);
        for(unsigned int i = 2; i < bloque1.length(); i++){
            if(bloque1.at(i) != '\n'){
                codificado += bloque1.at(i);
             }
        }
        codificado+= bloque1.at(0);
        if(bloque1.length() < semilla){
            break;
        }
    }
    int decima = 0;
    for(unsigned int n = 0; n < longi; n++){
        binario = codificado.substr(n*8,8);
        if(binario.length() < 8 || binario == ""){
            break;
        }
        decima = Binario_Decimal(binario);
        decodificado += char(decima);
    }
}

void Decodificar(unsigned int semilla, unsigned int metodo, string fuente, string salida){

    /**Esta funcion permite decodificar un archivo de texto y ademas guardar la decodificacion en otro archivo
     * Tiene como parametros dos variables tipo unsigned int y dos variables tipo string
     * la variable semilla contiene el tamaño de los bloques que deseamos coger para la decodificacion
     * la variable metodo contine un valor que nos permite saber cual metodo es el que se desea utilizar
     * la variable fuente tiene el nombre del archivo que se desea decodificar
     * la variable salida tiene el nombre del archivo donde se guardara la decodificacion
    **/

    string decodificado;

    if(metodo == 1){
        Decodificacion_Metodo1(decodificado, fuente, semilla);
    }
    else if(metodo == 2){
        Decodificacion_Metodo2(decodificado, fuente, semilla);

    }
    Escritura_Archivos(decodificado, salida);

    cout << endl<< "EL TEXTO HA SIDO CODIFICADO CON EXITO   " << endl;
}

