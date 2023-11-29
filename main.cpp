#include <iostream>
#include "Simulator/Application.h"

int main() {
    Application app;

    try{
        app.Run();
    }catch(std::exception& e){
        std::cout << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
