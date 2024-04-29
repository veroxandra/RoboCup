#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <thread> // Para std::this_thread::sleep_for
#include <chrono> // Para std::chrono::seconds
#include "funciones.h"
#include <MinimalSocket/udp/UdpSocket.h>

using namespace std;

string Estado;
Jugador jugador;

int main(int argc, char* argv[])
{
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
        //cout << received_message_content << endl;

        jugador.numero = stoi(vectorpalabras(received_message_content).at(2));
        if (vectorpalabras(received_message_content).at(1) == "l"){
            jugador.equipo = -1;
        }else{
            jugador.equipo = 1;
        }

        vector <string>palabras=vectorpalabras(received_message_content);

        for(const auto &palabra : palabras) {
              //cout << palabra << endl;
          }
        MinimalSocket::Address server_udp = MinimalSocket::Address{"127.0.0.1", other_sender_udp.getPort()};

        PosicionarJugador(jugador, server_udp,udp_socket,argumentoString);
        // clock.tic();

        while (true)
        {
            // while (clock.toc() < 100){
            //     std::this_thread::sleep_for(std::crono:milliseconds(1));
            //     }
            // clock.tic();
            auto received_message = udp_socket.receive(message_max_size);
            std::string received_message_content = received_message->received_message;
            string contenido = received_message_content.substr(1, received_message_content.size() - 2);
            auto tipo=obtenerPrimeraPalabra(contenido);
            vector<string> cadenas = dividir_en_palabras_parentesis(contenido);
            //cadenas.push_back(tipo);
            cadenas.insert(cadenas.begin(), tipo); // Inserta la primera palabra al principio del vector

            auto Estructura = ClasificaDatos<string>(tipo, cadenas);
            vector<string> valor,vectoria,valor2,porteria;
            if(tipo=="see"&&jugador.numero!=1){
                bool bola=false;
                for(auto parentesis:cadenas){
                    //cout<<parentesis<<endl;
                    valor=encontrarStringConPrefijo(parentesis,"(b)");//Buscar en todos los parentesis el de (b)
                    if(jugador.equipo==-1){
                        valor2=encontrarStringConPrefijo(parentesis,"(g r)");//Buscar en todos los parentesis el de (g r)
                    }else{
                        valor2=encontrarStringConPrefijo(parentesis,"(g l)");//Buscar en todos los parentesis el de (g l)
                    }
                    if(valor2.size()>1){
                        porteria=valor2;
                        for(auto palabra:valor2){
                            cout <<palabra<<endl;
                        }
                    }
                    if(valor.size()>1){
                        bola=true;
                        vectoria=valor;//Guardar vector con los string del (b)
                        //cout <<vectoria[1]<<endl;
                        double variable=stod(vectoria[1]);
                        //cout <<"La variable transformada es:"<<variable<<endl;
                        if(variable<0.6&&porteria.size()>1){
                            cout<<"Patadon a la direccion:"<<porteria[3]<<endl;
                            udp_socket.sendTo("(kick 30 "+porteria[3]+")", server_udp);
                        }else if(stod(vectoria[2])>30){
                            udp_socket.sendTo("(turn "+vectoria[2]+")", server_udp);
                        }else{
                        //udp_socket.sendTo("(dash 50 "+vectoria[2]+")", server_udp);
                        udp_socket.sendTo("(dash 50 0)", server_udp);
                        }
                    }else{

                    }
                }
                if(!bola){
                    udp_socket.sendTo("(turn 30)", server_udp);
                    cout <<"No ve na"<<endl;
                }
                for(auto palabras:vectoria){
                    //cout<<"Palabra: "<<palabras<<endl;
                }
            }else{
                //cout << "El tipo es: "<<tipo<<endl;
            }
            //cout << contenido <<endl;//imprime mensaje entero(sin el tipo de mensaje)
            for (auto p : cadenas) {
                //cout << p << endl;//imprime los parentesis por separado
            }
            //std::this_thread::sleep_for(std::chrono::seconds(1)); // Espera 1 segundo


        }
        return 0;
    }

