/* Kayla Humphrey
   Pseudo-code from Dr. Mike Rogers
   Statistics Connector, generates statistics and sends them on to Queue
   11/2/2025
*/
#include "statisticsConnector.hpp"

int main(){
    statistics_connector();
    return 0;
    
}

void statistics_connector(){
    std::string program = "/bin/bash", progOut, converted = " ";
    std::vector<std::string> args;
    args.push_back("-c"); 
    args.push_back("while [ 1 ]; do grep Available /proc/meminfo; sleep 1; done");  
    bp::ipstream child_stdout; //this is the child's output stream
    int convertedLength;

    try{
        //create child running our command
        bp::child child(bp::exe = program, bp::args = args, bp::std_out > child_stdout);
        //create pub socket and context
        zmq::context_t ctx(1);   
        zmq::socket_t pubSocket(ctx, zmq::socket_type::pub);
        //connect to queue
        pubSocket.connect("tcp://localhost:5556");
        //read from child
        while(std::getline(child_stdout, progOut)) {
            //send to adapter
            convertedLength = adapter_meminfo_to_message(progOut, &converted);
            //send to queue
            pubSocket.send(zmq::buffer(converted), zmq::send_flags::none);
        }
        //wait for child
        child.wait();
        pubSocket.close();
        ctx.close();
    }catch(const bp::process_error& e){
        std::cerr << "Error spawning process: " << e.what() << std::endl;
        return;
    }
    return;
}

int adapter_meminfo_to_message(std::string line, std::string* converted){
    //remove extra stuff from line like "Memavailable 800000 kB"
    int i = 0;
    while(!isdigit(line.at(i))){
        i++;
    }
    line = line.substr(i, line.length() - i - 2); //here i don't read 2 characters from the end (kB) LINE IS NOW LIKE: "800000 "
    //buiild message structure
    line = "MSG_MEMSTAT," + std::to_string(time(0)) + "," + line; //LINE IS NOW LIKE: "MSG_MEMSTAT,1237471823,800000 "
    line.push_back('\0'); //LINE IS NOW: 0 terminated for sure
    converted->assign(line);
    return converted->length();
}