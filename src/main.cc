#include "parser.h"

int main()
{
    parser parseTree;
    std::string input = {};
    
    while (std::getline(std::cin >> std::ws, input) && input != "exit" && input != "e"){
        parseTree.createTree(input);
        // parseTree.calculate();
    }

    return 0;
}
