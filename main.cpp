#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

#include <MinimalSocket/udp/UdpSocket.h>

int main(int argc, char* argv[])
{
    int num;
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
        udp_socket.sendTo("(init pOESIAC++(version 19))", other_recipient_udp);
        cout << "Message sent" << endl;
        // receive a message from another udp reaching this one
        std::size_t message_max_size = 1000;
        cout << "Waiting for a message" << endl;
        auto received_message = udp_socket.receive(message_max_size);
        // check the sender address
        MinimalSocket::Address other_sender_udp = received_message->sender;
        // access the received message
        // resized to the nunber of bytes
        // actually received
        std::string received_message_content = received_message->received_message;
        cout << received_message_content << endl;
        int jugador=int(received_message_content.at(8))-int('0');
        cout << "El jugador es: "<<jugador <<endl;
        MinimalSocket::Address server_upd = MinimalSocket::Address{"127.0.0.1", other_sender_udp.getPort()};
        switch(jugador){
            case 1:{
            udp_socket.sendTo("(move -50 0)", server_upd);
            cout << "Pa la posi 0 0" << endl;
                break;
            }
            case 2:{
            udp_socket.sendTo("(move -35 -20)", server_upd);
            cout << "Pa la posi 50 50" << endl;
                break;
            }
            case 3:{
            udp_socket.sendTo("(move -35 0)", server_upd);
            cout << "Pa la posi 25 25" << endl;

                break;
            }
            case 4:{
            udp_socket.sendTo("(move -35 20)", server_upd);
            cout << "Pa la posi 10 10" << endl;

                break;
            }
            case 5:{
            udp_socket.sendTo("(move -20 -25)", server_upd);
                break;
            }
            case 6:{
            udp_socket.sendTo("(move -18 -9)", server_upd);
                break;
            }
            case 7:{
            udp_socket.sendTo("(move  -18 5)", server_upd);
                break;
            }
            case 8:{
            udp_socket.sendTo("(move -20 20)", server_upd);
                break;
            }
            case 9:{
            udp_socket.sendTo("(move -2 -18)", server_upd);
                break;
            }
            case 10:{
            udp_socket.sendTo("(move 2 2)", server_upd);
                break;
            }
            case 11:{
            udp_socket.sendTo("(move 2 2)", server_upd);
                break;
            }
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

