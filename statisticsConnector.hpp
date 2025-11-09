/*
    Kayla Humphrey
    Header file for statisticsConnector
    11/2/2025
*/
#ifndef STATISTICSCONNECTOR_HPP
#define STATISTICSCONNECTOR_HPP
    #include <iostream>
    #include <string>
    #include <vector>
    #include <boost/process.hpp>
    #include <zmq.hpp>
    namespace bp = boost::process;

    /*
        func: statistics_connector
        purpose: Connects to a message forwarding queue via zmq
                 and spawns a child process to get free memory data to
                 send to the queue.
    */
   void statistics_connector();

   /*
        func: adapter_vmstat_to_message()
        parameters: LINE- a string of the line to be parsed and wrapped into an appropriate message for Queue
                    CONVERTED - a string that will contain the converted line
        return: an int that describes the length of CONVERTED
        purpose: Takes an unparsed line from meminfo and structures it into this format
                 MSG_MEMSTAT,time,freememory 
   */
  int adapter_meminfo_to_message(std::string, std::string*);
#endif
