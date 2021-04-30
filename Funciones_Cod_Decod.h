#ifndef FUNCIONES_COD_DECOD_H
#define FUNCIONES_COD_DECOD_H

#include<string>
using namespace std;


void Decimal_Binario(int , string &);
int Binario_Decimal(string );
void Lectura_Archivos(string &, string);
void Escritura_Archivos(string, string);
void Codificacion_Metodo1(string &, string, unsigned int);
void Codificacion_Metodo2(string &, string, unsigned int);
void Codificar(unsigned int, unsigned int, string, string);
void Decodificacion_Metodo1(string &, string, unsigned int);
void Decodificacion_Metodo2(string &, string, unsigned int);
void Decodificar(unsigned int, unsigned int, string, string);

#endif // FUNCIONES_COD_DECOD_H
