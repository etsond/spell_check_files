# Spell Checker
This repository contains the speller program, which is a command-line spell checker written in C. The program reads in a dictionary file and checks the spelling of words in a given text file.

## Requirements
- A C compiler, such as GCC or Clang.
- The provided Makefile requires GNU Make.
## Usage
To compile the program, navigate to the root directory of the repository and run the following command:

```ruby
make
```
> This will generate an executable file named speller.

To run the program, pass in the name of a dictionary file and a text file to check the spelling of:

```ruby 
./speller dictionaries/small texts/cat.txt
```
The program will output a list of misspelled words and statistics about the dictionary and text file.

###  Code Overview
#### Loading the Dictionary
The dictionary is loaded into a hash table using the load function, which reads in each word from the dictionary file and calculates its hash value using the djb2 hash function. The hash table is implemented as an array of linked lists to handle collisions.

```ruby
/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Read each word from dictionary and add to hash table
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Calculate hash value for word
        unsigned int hash_value = hash(word);

        // Create new node for word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false;
        }
        strcpy(new_node->word, word);

        // Add new node to hash table
        new_node->next = table[hash_value];
        table[hash_value] = new_node;

        // Update word count
        word_count++;
    }

    // Close dictionary file
    fclose(file);
    return true;
}
```
### Checking the Text
The text file is checked using the check function, which reads in each word from the text file and checks whether it is in the dictionary. The function handles case-insensitivity and ignores words containing digits or other non-alphabetic characters.

```ruby
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // Convert word to lowercase
    char lowercase_word[LENGTH + 1];
    for (int i = 0; i < strlen(word); i++)
    {
        lowercase_word[i] = tolower(word[i]);
    }
    lowercase_word[strlen(word)] = '\0';

    // Calculate hash value for lowercase word
    unsigned int hash_value = hash(lowercase_word);

    // Search linked list for word
    for (node *n = table[hash_value]; n != NULL; n = n->next)
    {
        if (strcmp(lowercase_word, n->word) == 0)
        {
            return true;
        }
    }

    return false;
}
```
### Performance
The speller program achieves high performance by using a hash table to store the dictionary words and implementing the hash table as an array of linked lists to handle collisions. The program uses the djb2 hash function, which provides a good balance between speed and collision avoidance.

The program also takes advantage of a number of optimizations, such as case-insensitive checking and ignoring words containing digits or other non

### Usage
To use this program, follow the below steps:

1. Clone the repository to your local machine or download the ZIP file and extract it.
2. Open a terminal and navigate to the speller directory.
3. Compile the program by running the command make.
4. Run the program with a dictionary and a text file to be checked as arguments. For example,
```ruby
./speller dictionaries/large texts/shakespeare.txt
```
If there are any misspelled words, they will be printed out to the terminal.
If you would like to see the program's execution time and the number of words in the text, use the flag -v. For example, 
```ruby
./speller -v dictionaries/large texts/shakespeare.txt
```
### Dictionary
By default, the program uses the dictionaries/large dictionary, which contains over 140,000 English words. However, you can specify a different dictionary file to use as the first argument when running the program. For example,

```ruby
./speller dictionaries/small texts/cat.txt.
```

### Benchmarking
The texts directory contains various text files of different sizes that can be used for benchmarking the program's performance. You can use the time command in the terminal to get the execution time of the program. For example, time 

```ruby
./speller dictionaries/large texts/shakespeare.txt.
```

### License
This program is licensed under the MIT license. 
