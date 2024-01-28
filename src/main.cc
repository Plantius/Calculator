#include "parser.h"
#include <iostream>

inline void startMenu()
{
    std::cout << "Calculator" << std::endl;
    std::cout << "Exit with \"end\" or \"exit\"" << std::endl;
    std::cout << "Enter a mathematical expression: ";
} // startMenu

int main()
{
    parser parseTree;
    std::string input = {};
    
    try
    {
        startMenu();
        while (std::getline(std::cin >> std::ws, input) && 
               input != "exit" && input != "e" && input != "end"){
            parseTree.clearTree();
            try
            {
                if (input.empty()){
                    throw inputError("Input cannot be empty. Please enter a valid mathematical expression.");
                }
                if (!legalInput(input)){
                    throw inputError("Invalid input: " + input);
                }
                parseTree.createTree(input);
            }
            catch(const parseError error){
                error.printError();
                continue;
            }catch(const inputError error){
                error.printError();
                continue;
            }
        }
    }
    catch(const memoryError error){
        error.printError();
        return EXIT_FAILURE;
    }catch(const tokenError error){
        error.printError();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
