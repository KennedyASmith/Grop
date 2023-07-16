/*
 * Filename: DirNode.h
 * Contains: Interface of the FSTree class
 *           This class contains an n-ary tree to represent a file system
 *
 * Kennedy Smith
 *
 */

#pragma once

#include "DirNode.h"
#include <string>

class FSTree
{

public:
    // creates an empty FSTree
    FSTree();

    // creates a file system representation of the folder passed.
    // The folder will be "root_name", and its contents will form the
    // rest of the tree
    FSTree(std::string root_name);

    // FSTree Copy constructor
    FSTree(const FSTree &other);

    // Deletes all alocated memory using a post order delete
    // algorithm
    ~FSTree();

    // Assignment overload for FSTree.
    FSTree &operator=(const FSTree &other);

    // returns the root of the tree in order to traverse it.
    // The destructor will still delete all the allocated data.
    // The user should not manually delete the data.
    DirNode *get_root() const;

    // returns true if tree is empty
    bool is_empty();

    // destroys the tree and deletes all the allocated data.
    void burn_tree();

private:
    // Root of the n-ary tree
    DirNode *root;

    // Helper Functions / Utilities

    // checks if the given string is the name of a file.
    // Throws an exception if a file is invalid or if stat has an error
    bool is_file(const std::string path);

    // Does: Determines if the given string is the name of a directory
    bool is_dir(const std::string path);

    std::string base_name(std::string const &path);

    // Recursive function to build the tree
    DirNode *buildTree(std::string root_name);

    // Recursive function to recursively delete the tree
    void burn_tree(DirNode *root);

    // Recursive function to copy the tree in preorder traversal
    DirNode *pre_order_copy(DirNode *curr_node, DirNode *parent_node)
    {

        DirNode *new_node = new DirNode();

        // copy data in curr_node to new_node
        new_node->set_name(curr_node->get_name());
        new_node->set_parent(parent_node);

        for (int i = 0; i < curr_node->num_files(); i++)
        {
            new_node->add_file(curr_node->get_file(i));
        }

        // recurse and coy rest of tree
        for (int i = 0; i < curr_node->num_subdirectories(); i++)
        {
            new_node->add_subdirectory(pre_order_copy(curr_node->get_subdirectory(i), new_node));
        }

        // return new_node (copy of curr_node)
        return new_node;
    }
};
