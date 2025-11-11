/*
    Kayla Humphrey
    pseudocode from Dr. Mike Rogers
    monitor connector, recieves free memory data and plots it with gnuplot
    11/9/2025
*/
#include "monitorConnector.hpp"

int main(){
    monitor_connector();
    return 0;
}

void monitor_connector(){
    std::deque<std::string> pointsQueue; //local queue
    ///subscriber socket
    zmq::context_t ctx(1);
    zmq::socket_t subSocket(ctx, zmq::socket_type::sub); 
    //conect to message queue
    subSocket.connect("tcp://localhost:5555");
    subSocket.set(zmq::sockopt::subscribe, "MSG_MEMSTAT"); //subscribe to free memory messages only
     //input and output stream for child
    bp::ipstream child_stdout;
    bp::opstream child_stdin;

    //spawn child
    try{
        bp::child child(bp::exe("/usr/bin/gnuplot"), bp::std_out > child_stdout, bp::std_in < child_stdin);
        zmq::recv_result_t result;
        zmq::message_t message;
        std::string converted;
        int convertedSize;
        child_stdin << "set term x11\n" << std::endl;
        while(true){
            result = subSocket.recv(message, zmq::recv_flags::none); //recieve from publisher
            //call adapter
            convertedSize = adapter_csv_to_plot(message.to_string(), &converted);
            pointsQueue.push_back(converted);
            if(pointsQueue.size() > 20){
                pointsQueue.pop_front();
            }
            //plot queue
            child_stdin << "plot '-' with linespoints\n" << std::endl;
            for(const auto& point : pointsQueue){
                child_stdin << point << "\n" << std::endl; 
            }
            child_stdin << "e\n" << std::endl;
        }
    }catch(const bp::process_error& e){
        std::cerr << "Error spawning process: " << e.what() << std::endl;
        return;
    }
    return;
    
}

int adapter_csv_to_plot(std::string line, std::string* converted){
    int iTime;
    std::string memstat;

    //parse line into epoch and memstat
    int i = line.find(',');
    line = line.substr(i + 1); //chop off content descriptor. LINE IS NOW: EPOCH,MEMSTAT
    i = line.find(',');
    memstat = line.substr(0,i); //memstat is epoch time info as a string. MEMSTAT IS NOW: EPOCH(string)
    time_t epoch_time = static_cast<time_t>(std::stoll(memstat)); // convert string to time_t EPOCH_TIME IS NOW: MEMSTAT (time_t)
    memstat = line.substr(i + 1, line.length()); //now memstat is the actual free memory string. MEMSTAT IS NOW: MEMSTAT

    //lets get epoch in the right state
    struct tm* utc_time = gmtime(&epoch_time); //UTC_TIME IS NOW: GMTIME(EPOCH_TIME)
    iTime = utc_time->tm_hour * 3600 + utc_time->tm_min * 60 + utc_time->tm_sec; //ITIME IS NOW: all seconds in UCT_TIME (int)
    line = std::to_string(iTime) + " " + memstat; //construct converted
    //converted = epoch [space] mem
    converted->assign(line);
    return converted->size();
}