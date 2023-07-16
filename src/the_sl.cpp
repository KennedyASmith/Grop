/*
 * Filename: the_sl.cpp
 * Contains: Simple driver to demonstrate behavior of FSTree.
 *
 * Kennedy Smith
 */

#include <iostream>
#include <filesystem>
#include <string>

#include "FSTree.h"
#include "DirNode.h"

namespace fs = std::filesystem;

#ifndef TAB
#define TAB (2)
#endif

void print_DirNode(DirNode *root, int indentation)
{
    std::cout << std::string(indentation, ' ') << root->get_name() << "/" << std::endl;
    for (int i = 0; i < root->num_subdirectories(); i++)
    {
        print_DirNode(root->get_subdirectory(i), indentation + TAB);
    }
    for (int i = 0; i < root->num_files(); i++)
    {
        std::cout << std::string(indentation + TAB, ' ') << root->get_file(i) << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << std::string(argv[0]) << " directory" << std::endl;
        return 1;
    }

    std::string root = std::string(argv[1]);
    FSTree t(root);

    print_DirNode(t.get_root(), 0);
}