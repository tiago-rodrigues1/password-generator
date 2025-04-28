#include "../zxcvbn-c/zxcvbn.h"  // <-- certo pro seu caso
#include <iostream>
#include <string>

int main() {
    std::string password;
    std::cout << "Digite uma senha: ";
    std::getline(std::cin, password);

    double result = ZxcvbnMatch(password.c_str(), nullptr, nullptr);

    std::cout << "Força (entropia): " << result << "\n";

    //double result = ZxcvbnMatch(password.c_str(), nullptr, nullptr);
    std::cout << "The quality of your password is ";

    if(result < 20){
      std::cout << "very very weak, you are in danger!\n";}

    if(result > 20 && result < 70){
      std::cout << "weak \n";}
    
    if(result > 70 && result < 120 ){
      std::cout << "medium\n";}

    if(result > 120 && result < 160  ){
       std::cout << "good\n";}   
    
    if(result > 160){
      std::cout << "excellent\n";}
      


    return 0;
}
#include "../include/enums/CharGroupEnum.h"
#include "../include/PassgenUtils.h"
#include "../include/zxcvbn-c/zxcvbn.h"