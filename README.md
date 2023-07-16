# Grop

## Description

Grop is a program that behaves similarly to the Unix `grep` program. It allows you to index files within a directory and perform fast search queries on the indexed directory. The program reads files in a directory, stores information about the files and the words they contain, and then allows you to search for specific words or phrases in the indexed files.

## Getting Started

To use Grop, you need to compile and run the program. The reference implementation is provided as `the_grop`, and your executable should be called `grop`. The `grop` program takes two command-line arguments: the input directory to index and the name of the file to which the search results should be printed.

Here is an example command to run `the_grop`:

```$ ./the_grop ~/cpsc223/psets/pset-6-grop out.txt```

If you don't specify exactly two command-line arguments (in addition to the program name), an error message will be printed, and the program will exit.

## Indexing Files

The first step of the `grop` program is to index all the files within a directory. It explores the file system, reads the files, and stores information about the files and the words they contain. The index is built so that future search queries can be answered quickly.

The program uses the `FSTree` and `DirNode` classes to represent the file system. The `FSTree` class is an n-ary tree consisting of `DirNode`s, which represent directories and files. The provided starter code for the `FSTree` and `DirNode` classes should not be modified.

## Performing Search Queries

Once the files are indexed, the `grop` program prompts the user for search queries. It prints "`Query? `" and waits for input from the user. You can enter a word or phrase to search for in the indexed files. The program will list all the lines in which the query appears, along with the file name, line number, and the full line. The search is case-sensitive, so "word" and "Word" are considered different strings.

To exit the program, you can enter "`@q`", "`@quit`", or use the `ctrl-D` keyboard shortcut. The program will print "`Goodbye! Thank you and have a nice day.`" and exit.