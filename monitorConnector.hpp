/*
    Kayla Humphrey
    Header file for monitorConnector
    11/9/2025
*/
#ifndef MONITORCONNECTOR_HPP
#define MONITORCONNECTOR_HPP
    #include <iostream>
    #include <boost/process.hpp>
    #include <zmq.hpp>
    #include <string>
    #include <queue>
    #include <ctime>
    namespace bp = boost::process;

    /*
     func: monitor_connector
     purpose:
    */
   void monitor_connector();

   /*
    func: adapter_csv_to_plot
    parameters: LINE- to be converted
               CONVERTED- the converted line
    return: int, length of converted line
   */  
    int adapter_csv_to_plot(std::string, std::string*);
#endif