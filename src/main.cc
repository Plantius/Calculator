#include "parser.h"

int main()
{
    parser parseTree;
    std::string input = {};
    
    try
    {
        while (std::getline(std::cin >> std::ws, input) && input != "exit" && input != "e"){
            try
            {
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
