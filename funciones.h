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
struct Lectura{
   string tipo;
   string porteria_der;
   string porteria_der_dist;
   string porteria_izq;
   string porteria_izq_dist;
   string pelota;
   string pelota_angle;
   vector<string> direccionamigo;
   vector<string> direccionamigo2;
   vector<string> distamigo;
   vector<string> distamigo2;
};
struct Decision{
    string direccion;
    string distancia;
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




template<typename T>
Lectura ClasificaDatos (string &tipo, vector<string>  &cadenas) {
    vector<string> valor,vectoria,valor2,valor3,valor4,valor5;
    Lectura lectura;
    if(tipo=="see"){
        lectura.tipo="see";
        for(auto parentesis:cadenas){
            valor=encontrarStringConPrefijo(parentesis,"(b)");//Buscar en todos los parentesis el de (b)
            valor2=encontrarStringConPrefijo(parentesis,"(g r)");//Buscar en todos los parentesis el de (g r)
            valor3=encontrarStringConPrefijo(parentesis,"(g l)");//Buscar en todos los parentesis el de (g l)
            valor4 = encontrarStringConPrefijo(parentesis, "\"pOESIACA\" ");
            valor5 = encontrarStringConPrefijo(parentesis, "\"pOESIAC\" ");


            if(valor2.size()>1){
                lectura.porteria_der=(valor2.at(3));
                lectura.porteria_der_dist=(valor2.at(2));
            }
            if(valor3.size()>1){
                lectura.porteria_izq=(valor3.at(3));
                lectura.porteria_izq_dist=(valor3.at(2));
            }
            if(valor.size()>1){
                lectura.pelota=(valor.at(1));
                lectura.pelota_angle=(valor.at(2));
            }
            if(valor4.size()>1){
                lectura.direccionamigo.push_back(valor4.at(3));
                lectura.distamigo.push_back(valor4.at(2));
            }
            if(valor5.size()>1){
                lectura.direccionamigo2.push_back(valor5.at(3));
                lectura.distamigo2.push_back(valor5.at(2));

            }
        }
    }else{
        lectura.porteria_der="";
        lectura.porteria_izq="";
        lectura.pelota="";
        lectura.pelota_angle="";
        lectura.tipo="";
        lectura.direccionamigo.clear();
        lectura.direccionamigo2.clear();
        lectura.distamigo2.clear();
        lectura.distamigo2.clear();

        lectura.porteria_der_dist="";
        lectura.porteria_izq_dist="";
    }
    return lectura;
}

void PosicionarJugador(Jugador jugador, MinimalSocket::Address server_udp,MinimalSocket::udp::Udp<true>& udp_socket,string argumentoString) {
    vector<Posicion> posiciones={{50,0},{35,-20},{35,20},{20,-25},{18,-9},{18,5},{20,20},{2,-18},{28,-18},{35,11},{5,0}};
    for(auto &p:posiciones){
        p.x=-p.x;
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

Decision DetectarMasCercano(vector<string> direcciones, vector<string> distancias){
    Decision MasCercano;
    double dist=1000;
    int i=0;
        for(auto elem:direcciones){
            if(stod(elem)<dist){
                MasCercano.distancia=elem;
                MasCercano.direccion=direcciones.at(i);
            }
            i++;
        }
    return MasCercano;
}

bool MasCercaBola(vector<string> direcciones, vector<string> distancias,double dist){
        for(auto elem:distancias){
            if(stod(elem)-dist<dist){
                return false;
            }
        }
    return true;
}



void Accion (const Jugador &jugador,Lectura const &Data, MinimalSocket::Address server_udp,MinimalSocket::udp::Udp<true>& udp_socket){
    string vectoria,valor2,valor3, porteria,valorpase,distPor;
    Decision pase;
    if(Data.tipo=="see"){
        bool bola=false;
            if(jugador.equipo==-1){
                pase=DetectarMasCercano(Data.direccionamigo2,Data.distamigo2);
                valor2=Data.porteria_der;//Buscar en todos los parentesis el de (g r)
                valorpase=pase.direccion;//Funcion para obtener el mas cercano
                valor3=Data.porteria_der_dist;//Buscar en todos los parentesis el de (g r)
            }else if(jugador.equipo==1){
                pase=DetectarMasCercano(Data.direccionamigo,Data.distamigo);
                valor2=Data.porteria_izq;//Buscar en todos los parentesis el de (g l)
                valorpase=pase.direccion;;//Funcion para obtener el mas cercano
                valor3=Data.porteria_izq_dist;//Buscar en todos los parentesis el de (g r)
            }
            if(valor2!=""){
                porteria=valor2;
                distPor=valor3;
            }
            if(Data.pelota!=""){
                bola = true;
                double variable=stod(Data.pelota);
                if(variable<0.6&&porteria!=""&&stod(distPor)<50){
                    cout<<"Patadon a la direccion:"<<porteria<<endl;
                    udp_socket.sendTo("(kick 30 "+porteria+")", server_udp);
                }else if(variable<0.6&&porteria==""){//Tengo el balon y no veo la porteria
                    udp_socket.sendTo("(kick 50 180)", server_udp);
                    this_thread::sleep_for(std::chrono::milliseconds(150));
                    udp_socket.sendTo("(turn 180)", server_udp);
                    this_thread::sleep_for(std::chrono::milliseconds(150));}
                else if(variable<0.6&&valorpase!=""){
                    cout<<"Pasecito a la direccion:"<<valorpase<<endl;
                    udp_socket.sendTo("(kick 50 "+valorpase+")", server_udp);
                }else if(variable<0.6&&porteria!=""){//Tengo el balon y veo la porteria
                    udp_socket.sendTo("(kick 50 "+porteria+")", server_udp);
                }
                else if(abs(stod(Data.pelota_angle))>20){
                    udp_socket.sendTo("(turn "+Data.pelota_angle+")", server_udp);
                }else if(jugador.equipo==-1&&MasCercaBola(Data.direccionamigo2,Data.distamigo2,variable)){
                    udp_socket.sendTo("(dash 50 "+Data.pelota_angle+")", server_udp);
                }else if(jugador.equipo==1&&MasCercaBola(Data.direccionamigo,Data.distamigo,variable)){
                    udp_socket.sendTo("(dash 50 "+Data.pelota_angle+")", server_udp);
                }
            }
        if(!bola){
            udp_socket.sendTo("(turn 30)", server_udp);
        }
    }
}

#endif // FUNCIONES_H

