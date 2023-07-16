/*
 * Filename: DirNode.cpp
 * Contains: Implementation of the DirNode class
 *           Each DirNode is a folder (and contains info of files
 *           inside that directory).
 *
 * Kennedy Smith
 * Spring 2023
 *
 */

#include "DirNode.h"

#include <filesystem>
#include <string>
#include <exception>

namespace fs = std::filesystem;

DirNode::DirNode() : directories(),
                     filenames(), name(), parent(nullptr){};

DirNode::DirNode(std::string new_name) : directories(), filenames(), name(fs::path(new_name).filename()), parent(nullptr)
{
    if (fs::is_regular_file(new_name))
    {
        throw new_name + " is not a directory.";
    }
    for (const auto &entry : fs::directory_iterator(new_name))
    {
        // std::cerr << entry.path() << std::endl;

        if (entry.is_directory())
        {
            DirNode *sub = new DirNode(entry.path());
            this->add_subdirectory(sub);
        }
        else
        {
            this->add_file(entry.path().filename());
        }
    }
}

DirNode::DirNode(const DirNode &other) : directories(other.directories), filenames(other.filenames), name(other.name), parent(other.parent){};

DirNode &DirNode::operator=(const DirNode &other)
{
    if (&other == this)
    {
        return *this;
    }

    this->directories = other.directories;
    this->filenames = other.filenames;
    this->name = other.name;
    this->parent = other.parent;

    return *this;
}

void DirNode::add_file(std::string new_name)
{
    if (fs::is_directory(fs::path(new_name)))
    {
        throw new_name + " is a directory.";
    }
    this->filenames.push_back(new_name);
}

void DirNode::add_subdirectory(DirNode *newDir)
{
    newDir->set_parent(this);
    this->directories.push_back(newDir);
}

bool DirNode::has_subdirectory() const
{
    return this->num_subdirectories() > 0;
}

bool DirNode::has_files() const
{
    return this->num_files() > 0;
}

bool DirNode::is_empty() const
{
    return !(this->has_subdirectory() || this->has_files());
}

int DirNode::num_subdirectories() const
{
    return this->directories.size();
}

int DirNode::num_files() const
{
    return this->filenames.size();
}

void DirNode::set_name(std::string new_name)
{
    this->name = new_name;
}

std::string DirNode::get_name() const
{
    return this->name;
}

fs::path DirNode::get_path() const
{
    if (this->parent != nullptr)
    {
        return this->parent->get_path() / this->name;
    }
    else
    {
        return this->name;
    }
}

DirNode *DirNode::get_subdirectory(int n) const
{
    return this->directories[n];
}

std::string DirNode::get_file(int n) const
{
    return this->filenames[n];
}

DirNode *DirNode::get_parent() const
{
    return this->parent;
}

void DirNode::set_parent(DirNode *new_parent)
{
    this->parent = new_parent;
}
