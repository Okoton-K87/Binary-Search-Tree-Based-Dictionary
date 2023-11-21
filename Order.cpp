/********************************************************************************* 
* Roman Luo, yluo111
* 2023 Winter CSE101 PA# 7
* Order.cpp 
* Main program
*********************************************************************************/ 
//-----------------------------------------------------------------------------
// FileIO.cpp
// Illustrates file input-output commands and text processing using the
// string functions find_first_of(), find_first_not_of() and substr().
// 
// compile:
//
//      g++ -std=c++17 -Wall -o FileIO FileIO.cpp
//
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include "Dictionary.h" // assuming Dictionary.h is the header file for your Dictionary

int main(int argc, char * argv[]){
   // check command line for correct number of arguments
   if( argc != 3 ){
      std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
      return(EXIT_FAILURE);
   }

   // open input file for reading 
   std::ifstream in(argv[1]);
   if( !in.is_open() ){
      std::cerr << "Unable to open file " << argv[1] << " for reading" << std::endl;
      return(EXIT_FAILURE);
   }

   // open output file for writing
   std::ofstream out(argv[2]);
   if( !out.is_open() ){
      std::cerr << "Unable to open file " << argv[2] << " for writing" << std::endl;
      return(EXIT_FAILURE);
   }

   // Create a dictionary
   Dictionary dict;

   // Read lines from the input file, insert them into the dictionary
   std::string line;
   int line_num = 1;
   while (std::getline(in, line)) {
      dict.setValue(line, line_num++);
   }

   // Write the dictionary to the output file in alphabetical order
   out << dict << std::endl;

   // Write the dictionary to the output file in pre-order
   out << dict.pre_string() << std::endl;

   // cout << "A.size() = " << A.size() << endl  << A << endl;
   // cout << A.pre_string() << endl;

   // Close files
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}

