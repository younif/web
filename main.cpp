//
// Created by youni on 22-6-14.
//
#include <iostream>

int main(int argc, char** argv){
  std::cout << argc << std::endl;
  for (int i = 0; i < argc; i++){
    std::cout << "%%->" << argv[i];
  }
}