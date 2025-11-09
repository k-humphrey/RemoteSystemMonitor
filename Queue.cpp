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

    //PUBLISHERS : 5555, SUBSCRIBERS : 5556
    xpubSocket.bind("tcp://*:5555");
    xsubSocket.bind("tcp://*:5556");

    zmq::proxy(xsubSocket, xpubSocket);


}