/*
    Kayla Humphrey
    Message Queue
    11/4/2025
*/
#include <zmq.hpp>

int main(){
    //create context
    zmq::context_t ctx(1);  

    //create xub and xsub sockets
    zmq::socket_t xpubSocket(ctx, zmq::socket_type::xpub);
    zmq::socket_t xsubSocket(ctx, zmq::socket_type::xsub);

    //PUBLISHERS CONNECT TO : 5556, SUBSCRIBERS CONNECT TO: 5555
    xpubSocket.bind("tcp://*:5555");
    xsubSocket.bind("tcp://*:5556");

    //publishers (xsubSocket) connect, and the message is fowarded to the subscribers (xpubsocket)
    zmq::proxy(xsubSocket, xpubSocket);
}