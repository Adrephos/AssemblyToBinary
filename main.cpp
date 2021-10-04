#include <iostream>
#include <fstream>
#include "include/Init.h"
#include "include/Parser.h"
#include "include/SymbolTable.h"
#include "include/Code.h"

using namespace std;
using std::ifstream;
using std::ofstream;

int main(int argc, char* argv[]){
  if (argc == 2) {
    string inPath = argv[1];
    string extension = inPath.substr(inPath.find_last_of(".") + 1);
	
	//Verificar que la extension del archivo de input sea correcta
    if (extension != "asm") {
      cerr << "Error de Assembler archivo \".asm\" esperado"
           << extension << "." << endl;
      return -1;
    }
  
    if(ifstream inFile{argv[1]}) {
      stringstream outBuffer;
	  //Se instancia un objeto de la clase init, incializando las diferentes clases que van a ser utilizadas.
      Init init{inFile, outBuffer};
      
	  //Realiza la primer y segunda pasada
      try {
        init.execute();
      } catch (const runtime_error& e) {
        cerr << "Assembler error: " << e.what() << endl;
        return -1;
      }
      
      string outPath = inPath.substr(0,inPath.find_last_of('.')) + ".hack";
    
	  //Crea un archivo de salida en la ruta "outPath"
      if(ofstream outFile{outPath}) {
		//Vuelca la informacion del buffer en el archivo
        outFile << outBuffer.str();
      } else {
        cerr << "Assembler error: No se pudo crear el archivo de salida " << outPath << "." << endl;
        return -1;
      }
    } else {
      cerr << "Assembler error: No se pudo abrir el archivo " << inPath << "." << endl;
      return -1;
    }

    return 0;
  }
}
