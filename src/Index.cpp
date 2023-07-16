/**
 * Index.cpp
 *
 *      Implementation for the Index class, a class that builds an queryable
 *      index of all text files below provided directory
 *
 * Kennedy Smith
 *
 */
#include "Index.h"
#include <filesystem>
#include <algorithm>
#include <sstream> // Added this header for std::stringstream
#include <fstream>
#include "DirNode.h"
#include "FSTree.h"

using std::string;
namespace fs = std::filesystem;

string &Index::clean_string(string &s) const
{
    size_t start = 0, end = 0;

    // Find the first alphanumeric from the back
    for (size_t i = s.size(); 0 < i; i--)
    {
        if (::isalnum(s[i - 1]))
        {
            end = i;
            break;
        }
    }

    for (size_t i = 0; i < end; i++)
    {
        // Find first alnum from front
        if (start == 0)
        {
            if (::isalnum(s[i]))
            {
                // If first character is isalnum nothing to be
                // done
                if (i == 0)
                {
                    break;
                }
                start = i;
            }
        }
        s[i - start] = s[i];
    }
    s.resize(end - start);
    return s;
}

Index::Index(string root)
{
    init(root);
}

void Index::init(string root)
{
    build_index(FSTree(root).get_root());
}

void Index::query(const string &word, std::ostream &out) const
{
    try
    {
        string key = word, clean_word = word;
        clean_string(clean_word);

        bool reported_match = false;
        for (const Entry &e : entries.at(key))
        {
            if (e.word == clean_word)
            {
                report_match(e, out);
                reported_match = true;
            }
        }
        if (!reported_match)
        {
            out << "query not found" << std::endl;
        }
    }
    catch (std::exception &e)
    {
        out << "query not found" << std::endl;
    }
}

void Index::parse_file(const string &filename)
{
    std::ifstream infile(filename);
    std::string line, word;
    std::streampos position;      // This a way of remembering positions in a file
    unsigned lineno = 0;          // Current line number
    size_t fileno = files.size(); // Current file index in files array

    if (!infile)
    {
        throw std::runtime_error("Could not open " + filename);
    }
    // Save position of infile (to remember where current line starts),
    // then gets the line
    // Uses comma operator : https://en.wikipedia.org/wiki/Comma_operator
    while (position = infile.tellg(), getline(infile, line))
    {
        std::stringstream ss(line);
        lineno++;

        // Get each word in line
        while (ss >> word)
        {
            clean_string(word);

            // Store cleaned word in the entry
            Entry to_add{word, lineno, position, fileno};

            // Get the vector of entries from hashtable
            // A new one is created if one didn't already exist
            std::vector<Entry> &entryList = entries[word];

            if (should_add(entryList, to_add))
            {
                entryList.push_back(to_add);
            }
        }
    }

    files.push_back(filename);
}

bool Index::should_add(const std::vector<Entry> &e, const Entry &to_add) const
{
    if (to_add.word == "")
    {
        return false;
    }

    for (size_t i = 0; i < e.size(); i++)
    {
        // stop if current entry is not on same line or in same file
        if (to_add.lineno != e[i].lineno || to_add.fileno != e[i].fileno)
        {
            return true;
        }
        else if (e[i].word == to_add.word)
        {
            return false;
        }
    }
    return true;
}

string &Index::lower(string &s) const
{
    // <algorithm> std::transform
    // Iterates through string and transforms string to lowercase
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

void Index::build_index(DirNode *node)
{
    // Iterate through all files in this directory and parse them
    for (int i = 0; i < node->num_files(); i++)
    {
        std::string filename = node->get_path().string() + "/" + node->get_file(i);
        parse_file(filename);
    }

    // Recursively call build_index on all subdirectories
    for (int i = 0; i < node->num_subdirectories(); i++)
    {
        build_index(node->get_subdirectory(i));
    }
}

void Index::report_match(const Entry &e, std::ostream &out) const
{
    std::ifstream infile(files[e.fileno]);
    string line;

    if (!infile)
    {
        throw std::runtime_error("Could not open " + files[e.fileno]);
    }

    // Read correspond  g line from file
    infile.seekg(e.sentence);
    getline(infile, line);

    out << files[e.fileno] << ":" << e.lineno << ":" << line << std::endl;
}
