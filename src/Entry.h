/**
 * Entry.h
 *
 *      A data model for Index entries
 *        Note: This was seperated from Index class to allow the seperation of
 *              Hashtable template implementation from the interface
 *
 * Kennedy Smith
 *
 */
#pragma once

/**
 * @brief An Index Entry. Stores the word verbatim, the lineno, the
 * file name, and the position of the beginning of its line in the file.
 *
 */
struct Entry
{
    std::string word;
    unsigned lineno;
    size_t fileno;
    std::streampos sentence;

    Entry(std::string newWord, unsigned newLineno, std::streampos position,
          size_t new_fileno)
        : word(newWord),
          lineno(newLineno),
          fileno(new_fileno),
          sentence(position) {}
};
