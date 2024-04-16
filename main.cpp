#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

#include <MinimalSocket/udp/UdpSocket.h>

int main(int argc, char* argv[])
{
    int num;
    //cin >> num;
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
        /*
        switch(jugador){
            case 1:{
            udp_socket.sendTo("(1 1", other_recipient_udp);
                break;
            }
            case2:{
                break;
            }
        }
    */
        udp_socket.sendTo("(move 1 1)", other_recipient_udp);

    while(true){
        if(true){
            cout << "Waiting for a message" << endl;
            auto received_message = udp_socket.receive(message_max_size);
            // check the sender address
            MinimalSocket::Address other_sender_udp = received_message->sender;
            // access the received message
            // resized to the nunber of bytes
            // actually received
            std::string received_message_content = received_message->received_message;
            cout << received_message_content << endl;
        }
    };
    return 0;
}
