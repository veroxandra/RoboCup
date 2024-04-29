#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <thread> // Para std::this_thread::sleep_for
#include <chrono> // Para std::chrono::seconds
#include <MinimalSocket/udp/UdpSocket.h>

using namespace std;

struct Posicion{
    int x;
    int y;
};

struct Jugador{
    int numero;
    int equipo;
};


vector<string> vectorpalabras(string const &ejercicio){
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

string obtenerPrimeraPalabra(string& str) {
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

vector<string> dividir_en_palabras_parentesis(string const &s){
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

string crearMove(Posicion pos){
    string movimiento="(move "+to_string(pos.x)+" "+to_string(pos.y)+")";
    return movimiento;
}

vector<string> encontrarStringConPrefijo(const string& str, const string& prefijo) {//va
    size_t pos = str.find(prefijo);
    if (pos != -1) {
        //cout <<"Encontrado"<<endl;
    for(auto d:vectorpalabras(str.substr(pos))){
        //cout << d<<endl;
    }
        return vectorpalabras(str.substr(pos));
    }
    return vectorpalabras(""); // Retorna una cadena vacía si no se encuentra el prefijo
}

void PosicionarJugador(Jugador jugador, MinimalSocket::Address server_udp,MinimalSocket::udp::Udp<true>& udp_socket,string argumentoString) {
    vector<Posicion> posiciones={{50,0},{35,-20},{35,20},{20,-25},{18,-9},{18,5},{20,20},{2,-18},{28,-18},{35,11},{5,0}};
    //if(vectorpalabras(received_message_content).at(1)=="l"){
    for(auto &p:posiciones){
        p.x=-p.x;
        //}
    }

    switch(jugador.numero){
    case 1:
        udp_socket.sendTo(crearMove(posiciones.at(0)), server_udp);
        cout << crearMove(posiciones.at(0)) << endl;
        break;
    case 2:
        udp_socket.sendTo(crearMove(posiciones.at(1)), server_udp);
        cout << crearMove(posiciones.at(1)) << endl;

        break;
    case 3:
        udp_socket.sendTo(crearMove(posiciones.at(2)), server_udp);
        cout << crearMove(posiciones.at(2)) << endl;

        break;
    case 4:
        udp_socket.sendTo(crearMove(posiciones.at(3)), server_udp);
        cout << crearMove(posiciones.at(3)) << endl;

        break;
    case 5:
        udp_socket.sendTo(crearMove(posiciones.at(4)), server_udp);
        cout << crearMove(posiciones.at(4)) << endl;

        break;
    case 6:
        udp_socket.sendTo(crearMove(posiciones.at(5)), server_udp);
        cout << crearMove(posiciones.at(5)) << endl;
        break;
    case 7:
        udp_socket.sendTo(crearMove(posiciones.at(6)), server_udp);
        cout << crearMove(posiciones.at(6)) << endl;

        break;
    case 8:
        udp_socket.sendTo(crearMove(posiciones.at(7)), server_udp);
        cout << crearMove(posiciones.at(7)) << endl;

        break;
    case 9:
        udp_socket.sendTo(crearMove(posiciones.at(8)), server_udp);
        cout << crearMove(posiciones.at(8)) << endl;
        break;
    case 10:
        udp_socket.sendTo(crearMove(posiciones.at(9)), server_udp);
        cout << crearMove(posiciones.at(9)) << endl;
        break;
    case 11:
        udp_socket.sendTo(crearMove(posiciones.at(10)), server_udp);
        cout << crearMove(posiciones.at(10)) << endl;
        break;
    }
    if(jugador.equipo == 1){
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Espera 1 segundo
        udp_socket.sendTo("(turn 180)", server_udp);
    }

}

#endif // FUNCIONES_H

