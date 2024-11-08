#include "../include/MTD.hpp"

int main() {
  MTD mtd;
  int option;
  std::string string;
  while(true) {
    std::cout << "MENÚ\n1. Introducir fichero con definición de la MTD\n2. Comprobar si una Cadena es reconocida por la MTD";
    std::cout << "\n3. Imprimir MTD por consola\n4. Salir\n";
    std::cout << "Introduzca una opción: ";
    std::cin >> option;
    std::cout << std::endl;
    if (option == 1) {
      std::string file_name;
      std::cout << "Introduzca el nombre del fichero con la definición de la MTD: ";
      std::cin >> file_name;
      MTD mtd2("Ficheros_de_Prueba/" + file_name);
      mtd = mtd2;
    } else if (option == 2) {
      std::cout << "Cadena: ";
      std::cin.ignore();
      std::getline(std::cin, string);
      mtd.check_string(string);
      if (mtd.recognized_string(string)) {
        std::cout << "La cadena es reconocida por la MTD\n";
      } else {
        std::cout << "La cadena no es reconocida por la MTD\n";
      }
    } else if (option == 3) {
      std::cout << mtd;      
    } else if (option == 4) {
      break;
    } else {
      std::cout << "Opción no válida\n";
      break;
    }
    std::cout << std::endl << std::endl;
  }
}