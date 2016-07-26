#pragma once

#include <string>
#include <vector>

struct History {
	std::vector<std::string> history;       // Array of files in the history
	std::string fname;                      // File name where histories are stored
	static const size_t max_len = 5;        // How many entries in the history array
	static const size_t max_print_len = 30; // Maximum number of chars to print in the menu
	

	// Change the filename used by load()
	void set_filename(const char *);
	void set_filename(const std::string &);

	// Load the history from a file
	// passing in a string will call set_filename()
	bool load(const char *);
	bool load(const std::string &);
	bool load();

	// Add a filename to the history and save to fname
	bool add(const char *);
	bool add(const std::string &);

	// Ensure string is shorter than max_print_len
	static std::string trim(const char *str) {
		return trim(std::string(str));
	}
	static std::string trim(const std::string &str) {
		if (str.length() < max_print_len)
			return str;

		// Trim string to max_print_len, replacing the first 3 chars with "..."
		std::string trimed = "..." + str.substr(3 + (str.length() - max_print_len));

		return trimed;
	}
};
