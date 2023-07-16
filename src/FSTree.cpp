/*
 * Filename: DirNode.h
 * Contains: Implementation of the FSTree class
 *           This class contains an n-ary tree to represent a file system
 *
 * Kennedy Smith
 *
 */

#include "FSTree.h"

#include <filesystem>
namespace fs = std::filesystem;

FSTree::FSTree() : root(){};

FSTree::FSTree(std::string root_name)
{
    auto rel = (fs::path(root_name) / ".");
    auto root = fs::absolute(rel);
    this->root = new DirNode(root);
    this->root->set_name(rel.parent_path());
};

FSTree::FSTree(const FSTree &other) : root(other.root){};

FSTree::~FSTree()
{
    this->burn_tree();
}

FSTree &FSTree::operator=(const FSTree &other)
{
    if (this == &other)
    {
        return *this;
    }

    this->burn_tree();

    this->root = this->pre_order_copy(other.root, nullptr);

    return *this;
}

DirNode *FSTree::get_root() const
{
    return this->root;
}

bool FSTree::is_empty()
{
    return this->root->is_empty();
}

void FSTree::burn_tree()
{
    burn_tree(this->root);
}

bool FSTree::is_file(const std::string path)
{
    return fs::is_regular_file(fs::path(path));
}

bool FSTree::is_dir(const std::string path)
{
    return fs::is_directory(fs::path(path));
}

std::string FSTree::base_name(std::string const &path)
{
    return fs::path(path).filename();
}

DirNode *FSTree::buildTree(std::string root_name)
{
    return new DirNode(root_name);
}

void FSTree::burn_tree(DirNode *root)
{
    for (int i = 0; i < root->num_subdirectories(); i++)
    {
        burn_tree(root->get_subdirectory(i));
    }
    delete root;
}