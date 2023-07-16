/*
 * Filename: DirNode.h
 * Contains: Interface of the DirNode class
 *           Each DirNode is a folder (and contains info of files
 *           inside that directory).
 *
 * Kennedy Smith
 */

#pragma once

#include <vector>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;

// This are the nodes that make up our n-ary file tree
class DirNode
{

public:
    // Default constructor. Creates empty dirNode.
    DirNode();

    // Constructor: given the path to explore fully explores that path
    DirNode(std::string new_name);

    // Copy Constructor
    DirNode(const DirNode &other);

    // assignment overload. Will seg fault if copied onto itself.
    DirNode &operator=(const DirNode &other);

    // Adds a file with the name "new_name" to the current node
    void add_file(std::string new_name);

    // adds a sub directory (newDir) to the current node
    void add_subdirectory(DirNode *newDir);

    // returns true if there are sub directories in the current node
    bool has_subdirectory() const;

    // returns true if there are files in the current node
    bool has_files() const;

    // returns true if there are no files or sub directories
    bool is_empty() const;

    // returns the number of sub directories
    int num_subdirectories() const;

    // returns the number of files in the current node
    int num_files() const;

    // sets the name of the current node
    void set_name(std::string new_name);

    // returns the name of the current directory
    std::string get_name() const;

    // returns the path to this directory relative to the root of the tree
    fs::path get_path() const;

    // returns the nth subdirectory
    DirNode *get_subdirectory(int n) const;

    // returns nth file name
    std::string get_file(int n) const;

    // get parent directory node
    DirNode *get_parent() const;

    // set parent directory node
    void set_parent(DirNode *new_parent);

private:
    // list of all of the sub directories in the
    // current directories
    std::vector<DirNode *> directories;

    // list of all the filenames in the current directory
    std::vector<std::string> filenames;

    // current directory name
    std::string name;

    // pointer to parent directory
    DirNode *parent;
};
