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
    namespace bp = boost::process;

    /*
        func: statistics_connector
        parameters: ?
        return: ?
        purpose: ?
    */
   void statistics_connector();

   /*
        func: adapter_vmstat_to_message()
        parameters: LINE- a string of the line to be parsed and wrapped into an appropriate message for Queue
                    CONVERTED - a string that will contain the converted line
        return: an int that describes the length of CONVERTED
        purpose: ?
   */
  int adapter_vmstat_to_message(std::string, std::string);
#endif
