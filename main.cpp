/**Este programa es capaz de codificar o decodificar un texto.
Forma de ejecuatar el programa.
    Al momento de correr el programa usted debera ingresar los datos de la siguiente manera:

    *Archivo fuente: En ese espacio usted ingresara el nombre de un archivo de texto con su
    extencion correspondiente. Si usted lo que desea es codificar, el archivo de texto debe de
    tener la informacion que usted desea codificar, si por el contrario usted desea decodificar, el
    archivo debera de contener informacion previamente codificada.

    *Archivo salida: En este espacio usted ingresara el nombre del archivo de texto con su respectiva
    extencion donde desee que se almacene la informacion codificada o decodificada. Puede ingresar el
    nombre de un archivo ya existente o el nombre de un archivo nuevo y el programa se lo creara por
    defecto.

    *Codificar o Decodificar: En este espacio usted le dira al programa la accion que desa tomar, siendo
    1 codificar y 2 decodificar.

    *Metodo : En este espacio usted decidira el metodo que desea tomar para hacer la codificacion o decodificacion,
    siendo 1 codificar y 2 decodificar. Tenga en cuenta que si desea decodificar usted debera elegir el metodo
    con el cual codifico el archivo previamente.

    *Semilla : En este espacio usted ingresara la semilla con la cual quiere codificar o decodificar el archivo.
    Si usted desea decodificar debera de poner la misma semilla con la cual codifico el archivo de texto.

**/




#include <iostream>
#include <fstream>
#include<string>
#include<math.h>
#include"Funciones_Cod_Decod.h"

using namespace std;

int main()
{
    string fuente;
    string salida;
    string codificado;
    unsigned int semilla = 0, metodo = 0, accion = 0;

    cout << "Ingrese el nombre del archivo fuente con su extencion (ejemplo: prueba.txt) -> ";
    getline(cin, fuente);

    cout << "Ingrese el nombre del archivo salida con su extencion (ejemplo: pruebadec.txt) -> ";
    getline(cin, salida);
    cin.ignore();

    cout << "Ingrese 1 si desa codificar o 2 si desa decodificar -> ";
    cin >> accion;

    cout << "Ingrese 1 si desa utilizar el primer metodo o 2 si desa utilizar el segundo -> ";
    cin >> metodo;

    cout << "Ingrese la semilla -> ";
    cin >> semilla;

    if(accion == 1){
        Codificar(semilla, metodo, fuente, salida);
    }
    else if(accion == 2){
        Decodificar(semilla, metodo, fuente, salida);
    }

    return 0;
}

