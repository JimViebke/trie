
#include <iostream>
#include <string>
#include <fstream>

#include "trie.hpp"

void small_test()
{
	trie::trie<char, 256> trie;

	trie.insert(std::string("for"));
	trie.insert(std::string("forms"));
	trie.insert(std::string("fort"));

	std::cout << "should be yes:" << std::endl;
	std::cout << (trie.contains(std::string("f")) ? "yes" : "no") << std::endl;
	std::cout << (trie.contains(std::string("fo")) ? "yes" : "no") << std::endl;
	std::cout << (trie.contains(std::string("for")) ? "yes" : "no") << std::endl;
	std::cout << (trie.contains(std::string("form")) ? "yes" : "no") << std::endl;
	std::cout << (trie.contains(std::string("forms")) ? "yes" : "no") << std::endl;

	std::cout << "should be no:" << std::endl;
	std::cout << (trie.contains(std::string("z")) ? "yes" : "no") << std::endl;
	std::cout << (trie.contains(std::string("fe")) ? "yes" : "no") << std::endl;
	std::cout << (trie.contains(std::string("foo")) ? "yes" : "no") << std::endl;
	std::cout << (trie.contains(std::string("fork")) ? "yes" : "no") << std::endl;
}

void find_missing_words()
{
	trie::trie<char, 256> trie;

	{
		std::ifstream missing_words("missing_words.txt");
		if (!missing_words) { std::cout << "Run this from the .exe\n"; return; }
		std::cout << "Building trie... ";
		std::string word;
		while (missing_words >> word) trie.insert(word);
		std::cout << "done.\n";
	}

	{
		std::ifstream words("words.txt");
		std::string word;
		while (words >> word)
		{
			if (!trie.contains(word))
			{
				std::cout << "missing_words.txt does not contain " << word << ".\n";
			}
		}
	}
}

int main()
{
	small_test();
	std::cin.ignore();
}
