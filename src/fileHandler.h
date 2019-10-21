#pragma once

#include <stdio.h>
#include <string>


class FileHandler{
  FILE * pFile;

  FileHandler(std::string filename, std::string flags){
	  pFile = fopen(filename.c_str(), flags.c_str());
	  if (pFile == nullptr){
		  //???
	  }
  }


  FileHandler(FileHandler &&rhs){
	  *this->pFile = std::move(*rhs.pFile);
  }


  ~FileHandler(){
	  fclose(pFile);
  }

  bool hasError(){
	  return ferror(pFile);
  }

bool isValid(){
	return (pFile ==nullptr);
}



};
