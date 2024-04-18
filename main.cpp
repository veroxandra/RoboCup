#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

#include <MinimalSocket/udp/UdpSocket.h>


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
struct Posicion{
    int x;
    int y;
};

string crearMove(Posicion pos){
    string movimiento="(move "+to_string(pos.x)+" "+to_string(pos.y)+")";
    return movimiento;
}

int main(int argc, char* argv[])
{
    int num;
    string argumentoString = argv[2];
    MinimalSocket::Port this_socket_port = atoi(argv[0]);
    cout << "Creating a UDP socket" << endl;
    MinimalSocket::udp::Udp<true> udp_socket(this_socket_port, MinimalSocket::AddressFamily::IP_V6);
    cout << "Socket created" << endl;
    bool success = udp_socket.open();
    if (!success)
    {
        cout << "Error opening socket" << endl;
        return 1;
    }
        // send a message to another udp
        MinimalSocket::Address other_recipient_udp = MinimalSocket::Address{"127.0.0.1", 6000};
        udp_socket.sendTo("(init "+argumentoString+"(version 19))", other_recipient_udp);
        //udp_socket.sendTo("(init pOESIAC(version 19))", other_recipient_udp);
        cout << "Message sent" << endl;
        // receive a message from another udp reaching this one
        std::size_t message_max_size = 10000;
        cout << "Waiting for a message" << endl;
        auto received_message = udp_socket.receive(message_max_size);
        // check the sender address
        MinimalSocket::Address other_sender_udp = received_message->sender;
        // access the received message
        // resized to the nunber of bytes
        // actually received
        std::string received_message_content = received_message->received_message;
        cout << received_message_content << endl;
        string jugador=vectorpalabras(received_message_content).at(2);
        vector <string>palabras=vectorpalabras(received_message_content);
        for(const auto &palabra : palabras) {
              cout << palabra << endl;
          }
        MinimalSocket::Address server_upd = MinimalSocket::Address{"127.0.0.1", other_sender_udp.getPort()};
        vector<Posicion> posiciones={{50,0},{35,-20},{35,20},{20,-25},{18,-9},{18,5},{20,20},{2,-18},{28,-18},{35,11},{5,0}};
        //if(vectorpalabras(received_message_content).at(1)=="l"){
            for(auto &p:posiciones){
                p.x=-p.x;
            //}
        }
        if (jugador == "1") {
              udp_socket.sendTo(crearMove(posiciones.at(0)), server_upd);
              cout << crearMove(posiciones.at(0)) << endl;
          } else if (jugador == "2") {
            udp_socket.sendTo(crearMove(posiciones.at(1)), server_upd);
            cout << crearMove(posiciones.at(1)) << endl;
          } else if (jugador == "3") {
            udp_socket.sendTo(crearMove(posiciones.at(2)), server_upd);
            cout << crearMove(posiciones.at(2)) << endl;
          } else if (jugador == "4") {
            udp_socket.sendTo(crearMove(posiciones.at(3)), server_upd);
            cout << crearMove(posiciones.at(3)) << endl;
          } else if (jugador == "5") {
            udp_socket.sendTo(crearMove(posiciones.at(4)), server_upd);
            cout << crearMove(posiciones.at(4)) << endl;
          } else if (jugador == "6") {
            udp_socket.sendTo(crearMove(posiciones.at(5)), server_upd);
            cout << crearMove(posiciones.at(5)) << endl;
          } else if (jugador == "7") {
            udp_socket.sendTo(crearMove(posiciones.at(6)), server_upd);
            cout << crearMove(posiciones.at(6)) << endl;
          } else if (jugador == "8") {
            udp_socket.sendTo(crearMove(posiciones.at(7)), server_upd);
            cout << crearMove(posiciones.at(7)) << endl;
          } else if (jugador == "9") {
            udp_socket.sendTo(crearMove(posiciones.at(8)), server_upd);
            cout << crearMove(posiciones.at(8)) << endl;
          } else if (jugador == "10") {
            udp_socket.sendTo(crearMove(posiciones.at(9)), server_upd);
            cout << crearMove(posiciones.at(9)) << endl;
          } else if (jugador == "11") {
            udp_socket.sendTo(crearMove(posiciones.at(10)), server_upd);
            cout << crearMove(posiciones.at(10)) << endl;
          }
        int i=0;
        while (true)
        {
            auto received_message = udp_socket.receive(message_max_size);
            std::string received_message_content = received_message->received_message;
            //cout << received_message_content << endl;

            // PROCESS THE DATA AND SEND A COMMAND TO THE SERVER

            udp_socket.sendTo("(turn 90)", server_upd);
        }
        return 0;
    }

