/**
 * Index.h
 *
 *      Interface for the Index class, a class that builds an queryable index
 *      of all text files below provided directory
 *
 * Kennedy Smith
 *
 */
#pragma once

#include <iostream>
#include <vector>

#include "DirNode.h"
#include "Entry.h"
#include "FSTree.h"
#include "Hashtable.h"

class Index
{

private:
    Hashtable<std::vector<Entry>> entries;
    std::vector<std::string> files;

    /**
     * @brief Converts a string to lowercase
     *
     * @param s        String to lower
     * @return string  Lowercase version of string
     */
    std::string &lower(std::string &s) const;

    /**
     * @brief Iterates through directory tree, and parses any files found
     *
     * @param node Root of FSTree to search
     */
    void build_index(DirNode *node);

    /**
     * @brief Checks whether another identical word on the same line was already
     *        added to the Index
     *
     * @param e      Vector of Entrys for a given key
     * @param to_add  Potential entry to add to e
     * @return       Returns true if to_add is not an empty string and hasn't
     *                            already been added to index
     *                       false otherwise
     */
    bool should_add(const std::vector<Entry> &e, const Entry &to_add) const;

    /**
     * @brief Prints out formatted output to request ostream
     *
     * @param e   Entry to print
     * @param out Stream to print to
     */
    void report_match(const Entry &e, std::ostream &out) const;

    /**
     * @brief Parses all words from the file named filename and inserts into this Index
     *
     * @param filename
     */
    void parse_file(const std::string &filename);

public:
    /**
     * @brief Removes leading and trailing non-alphanumeric characters from string
     *
     * @param s       String to clean
     * @return string Cleaned version of string
     */
    std::string &clean_string(std::string &s) const;

    /**
     * @brief         Performs a query for word on this index
     *
     * @param word string   The string to query
     * @param out     ostream& The output stream to use to print out matches
     */
    void query(const std::string &word, std::ostream &out) const;

    /**
     * @brief       Creates an Index of the file system starting with directory named root.
     *
     * @param root       Name of directory to search from for index building.
     */
    void init(std::string root);

    /**
     * @brief       Creates a new Index of this file system starting with directory named root.
     *
     * @param root       Name of directory to search from for index building.
     */
    Index(std::string root);

    /**
     * @brief       Creates a new, empty index.
     */
    Index() {}
};
