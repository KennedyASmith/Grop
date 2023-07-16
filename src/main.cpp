/**
 * main.cpp
 *
 *      Driver for grop
 *
 * Kennedy Smith
 *
 */
#include <iostream>
#include <fstream>
#include <exception>
#include <string>

#include "DirNode.h"
#include "FSTree.h"
#include "Index.h"

#define DIE(x)                    \
    do                            \
    {                             \
        std::cerr << (x) << "\n"; \
        return 1;                 \
    } while (0)

/**
 * @brief Runs grop
 *
 * @param ind       The index to use for queries
 * @param output    The name of the file to which results sould be printed
 *
 * @return 0 if there are no errors, nonzero otherwise
 */
int run(Index &ind, std::ofstream &output);

int main(int argc, char *argv[])
{


    Hashtable<std::string> offices;
    offices.insert("Ozan Erat", "AKW 010");
    offices.insert("Borak SEn", "AKW 011");
    

    /* Index ind;

    if (argc != 3)
    {
        DIE("Usage: " + std::string(argv[0]) +
            " inputDirectory outputFile");
    }

    std::ofstream output(argv[2]);

    if (!output.is_open())
        DIE("Could not open output file");

    // Try to build index
    try
    {
        ind.init(argv[1]);
    }
    catch (std::exception &e)
    {
        DIE("Could not build index because \"" + std::string(e.what()) + "\"");
        //DIE("Could not build index, exiting.");
    }

    std::cout << "Here" << std::endl;
    return run(ind, output); */

    return 0;
}

int run(Index &ind, std::ofstream &output)
{
    std::string input;
    // While loop condition prints query, then reads from cin and evaluates
    // cin as the loop condition
    // Uses comma-operator
    
    while ((std::cout << "Query? "), std::cin >> input)
    {

        if (input == "@q" || input == "@quit")
        {
            std::cout << "\n";
            break;
        }

        ind.clean_string(input);

        ind.query(input, output);

        std::cout << "\n";
    }

    std::cout << "Goodbye! Thank you and have a nice day.\n";
    return 0;
}
