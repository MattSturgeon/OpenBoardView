#include "History.h"
#include "platform.h"

void History::set_filename(const char *filename) {
	set_filename(std::string(filename));
}
void History::set_filename(const std::string &filename) {
	fname = filename;
}

bool History::load(const char *filename) {
	return load(std::string(filename));
}
bool History::load(const std::string &filename) {
	set_filename(filename);
	return load();
}
bool History::load() {
	if (fname.empty())
		return false;

	size_t buffer_size;
	char *buffer = file_as_buffer(&buffer_size, fname);

	if (!buffer)
		return false;
	
	history = buffer_to_lines(buffer, buffer_size);

	return true;
}

bool History::add(const char *newfile) {
	return add(std::string(newfile));
}
bool History::add(const std::string &newfile) {
	if (fname.empty())
		return false;

	// Start a new history
	std::vector<std::string> newHist { newfile };

	// Append the old history
	for (auto &filename : history) {
		// Skip if the history is getting too big
		if (newHist.size() > max_len - 1)
			continue;
		// Skip if we are readding a filename
		// This would be caught by the find iterator, but this saves us a second loop
		if (newfile == filename)
			continue;
		// Check we don't have the same file already
		// This is more of a just-in-case, (assuming we have no bugs and no one else modifies the history file)
		std::vector<std::string>::iterator it = find (newHist.begin(), newHist.end(), filename);
		if (it != newHist.end())
			continue;

		newHist.push_back(filename);
	}

	// Save the changes to disk
	file_write_lines(newHist, fname);

	// Load the new changes
	return load();
}
