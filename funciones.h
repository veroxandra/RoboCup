#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <thread> // Para std::this_thread::sleep_for
#include <chrono> // Para std::chrono::seconds
using namespace std;

inline vector<string> vectorpalabras(string const &ejercicio){
  vector<string> resultado;
  string aux=ejercicio;
  int pos=aux.find(' ');
    if(pos!=-1)
      resultado.push_back(aux.substr(0,pos));
  for(int i=0;i<ejercicio.size();i++){
    if(ejercicio.at(i)==' '){
      aux=ejercicio.substr(i+1,ejercicio.size());
      pos=aux.find(' ');
      if(pos!=-1)
        resultado.push_back(aux.substr(0,pos));
    }
  }
  resultado.push_back(aux);
  return resultado;
}
struct Posicion{
    int x;
    int y;
};
inline std::string obtenerPrimeraPalabra(string& str) {
    auto pos = str.find(' ');
    string primeraPalabra;
    if (pos != -1) {
        primeraPalabra = str.substr(0, pos);
        str = str.substr(pos + 1); // Actualiza str para que contenga la parte restante de la cadena
    } else {
        primeraPalabra = str;
        str.clear(); // Vacía str ya que no hay más palabras después de esta
    }
    return primeraPalabra;
}

inline vector<string> dividir_en_palabras_parentesis(string const &s){
  vector<string> palabras;
  string palabra;
  char token1 = '(';
  int count_parentesis = 0;
  char token2 = ')';

  for(int i = 0; i<s.length(); i++){
    if(s.at(i) == token1)
    {
      count_parentesis++;
      if(count_parentesis > 1)
        palabra.push_back(s.at(i));
    }
    else if (s.at(i) == token2)
    {
      count_parentesis--;
      if(count_parentesis > 0)
        palabra.push_back(s.at(i));
    }
    else{
      palabra.push_back(s.at(i));
    }
    if (count_parentesis == 0){
      palabras.push_back(palabra);
      palabra.clear();
    }
  }
  return palabras;
}

inline string crearMove(Posicion pos){
    string movimiento="(move "+to_string(pos.x)+" "+to_string(pos.y)+")";
    return movimiento;
}

vector<string> encontrarStringConPrefijo(const string& str, const string& prefijo) {//va
    size_t pos = str.find(prefijo);
    if (pos != -1) {
        cout <<"Encontrado"<<endl;
    for(auto d:vectorpalabras(str.substr(pos))){
        cout << d<<endl;
    }
        return vectorpalabras(str.substr(pos));
    }
    return vectorpalabras(""); // Retorna una cadena vacía si no se encuentra el prefijo
}

#endif // FUNCIONES_H
