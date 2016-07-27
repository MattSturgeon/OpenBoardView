#include "platform.h"
#include "BoardView.h"

#include <assert.h>
#include <nowide/fstream.hpp>
#include <string>
#include <vector>

char *file_as_buffer(size_t *buffer_size, const char *utf8_filename) {
	return file_as_buffer(buffer_size, std::string(utf8_filename));
}
char *file_as_buffer(size_t *buffer_size, const std::string &utf8_filename) {
	nowide::ifstream file;
	file.open(utf8_filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		std::string error = "Error opening \"" + utf8_filename + "\": " + strerror(errno);
		app.ShowError(error);
		*buffer_size = 0;
		return nullptr;
	}

	std::streampos sz = file.tellg();
	*buffer_size = sz;
	char *buf = (char *)malloc(sz);
	file.seekg(0, std::ios::beg);
	file.read(buf, sz);
	assert(file.gcount() == sz);
	file.close();

	return buf;
}

std::vector<std::string> buffer_to_lines(char *buffer, size_t buffer_size) {
	std::vector<std::string> lines;
	bool crlf = false;
	
	for (size_t i = 0, j = 0; i < buffer_size; i++) {
		// Seek ahead to work out the line length
		for (j = i; j < buffer_size; j++) {
			// LF
			if (buffer[j] == '\n') {
				crlf = false;
				break;
			}
			// CRLF
			else if (buffer[j] == '\r' && buffer[j+1] == '\n') {
				crlf = true;
				break;
			}
			// null
			else if (buffer[j] == '\0') {
				crlf = false;
				break;
			}
		}
		std::string line((char *)&buffer[i], j - i);
		
		lines.push_back(line);
		
		if (crlf) i = j + 1;
		else i = j;
	}

	return lines;
}

bool file_write_lines(std::vector<std::string> lines, const char *utf8_filename) {
	return file_write_lines(lines, std::string(utf8_filename));
}
bool file_write_lines(std::vector<std::string> lines, const std::string &utf8_filename) {
	return file_write_lines(lines, utf8_filename, false);
}
bool file_write_lines(std::vector<std::string> lines, const char *utf8_filename, bool append) {
	return file_write_lines(lines, std::string(utf8_filename, append));
}
bool file_write_lines(std::vector<std::string> lines, const std::string &utf8_filename, bool append) {
	nowide::ofstream file;

	if (append)
		file.open(utf8_filename, std::ios::app);
	else
		file.open(utf8_filename, std::ios::trunc);

	if (!file.is_open()) {
		std::string error = "Error opening \"" + utf8_filename + "\": " + strerror(errno);
		app.ShowError(error);
		return false;
	}

	for (auto &line : lines)
		file << line << std::endl;

	return true;
}
