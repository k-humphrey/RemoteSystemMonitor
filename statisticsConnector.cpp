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
    //variables for child
    std::string program = "/usr/bin/vmstat", vmstatOut;
    std::vector<std::string> args;
    args.push_back("-n"); //supress repeated headers
    args.push_back("1");  //delay is 1 second
    bp::ipstream child_stdout; //this is the child's output stream
    
    try{
        //create child running vmstat
        bp::child child(bp::exe = program, bp::args = args, bp::std_out > child_stdout);
        
        //read from child (2 times to skip headers first)
        std::getline(child_stdout, vmstatOut);
        std::getline(child_stdout, vmstatOut);
        while(std::getline(child_stdout, vmstatOut)) {
            std::cout << "Parent received: '" << vmstatOut << "'" << std::endl; //debug
        }
        

        //wait for child
        child.wait();
    }catch(const bp::process_error& e){
        std::cerr << "Error spawning process: " << e.what() << std::endl;
        return;
    }
    // create pub socket and connect to queue
    //create input and output steam for child
    //spawn child
    //read out lines we don't need
    //for each next line read call adapter
    //call zmq_send to send converted message
    //close the streams
    //wait for child to exit
}

int adapter_vmstat_to_message(std::string line, std::string converted){
    //take the line given
    //extract free mem column
    //build string message
    //return length of converted
    return 0;
}