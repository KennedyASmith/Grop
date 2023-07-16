/*
 * Filename: hashExample.cpp
 * Contains: Example program to show use of std::hash funciton.
 *
 * Kennedy Smith
 */
#include <iostream>
#include <string>
#include <functional>

const int RAYSIZE = 7;

int main()
{
    // setup
    std::string inputRay[RAYSIZE] = {"penguins",
                                     "harpseals",
                                     "polarbears",
                                     "seagulls",
                                     "walruses",
                                     "articfoxes",
                                     "narwhals"};

    std::string animalRay[RAYSIZE]; // initalized to all "-1"
    for (int i = 0; i < RAYSIZE; i++)
    {
        animalRay[i] = "-1";
    }

    // showing hash and compressed
    std::cout << "string_tohash\thash\t\t\tcompressed" << std::endl;
    for (int i = 0; i < RAYSIZE; i++)
        std::cout << inputRay[i] << "\t"                             // input
                  << std::hash<std::string>{}(inputRay[i]) << "\t"   // hashing
                  << std::hash<std::string>{}(inputRay[i]) % RAYSIZE // compression
                  << std::endl;

    std::cout << std::endl;

    // inserting if and only if no collision
    for (int i = 0; i < RAYSIZE; i++)
    {
        int index = std::hash<std::string>{}(inputRay[i]) % RAYSIZE;
        if (animalRay[index] == "-1")
        {
            std::cout << "inserting " << inputRay[i]
                      << "\t at " << index << std::endl;
            animalRay[index] = inputRay[i];
        }
        else
            std::cout << "unable to insert " << inputRay[i] << " at " << index
                      << " -- collision with " << animalRay[index] << std::endl;
    }

    std::cout << std::endl;

    // final array print
    std::cout << "Final array: ";
    for (int i = 0; i < RAYSIZE; ++i)
    {
        std::cout << animalRay[i];
        if (i < RAYSIZE - 1)
            std::cout << " | ";
        else
            std::cout << std::endl;
    }
    return 0;
}
