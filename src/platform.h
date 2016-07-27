#pragma once

#include "imgui.h"
#include "utf8.h"

// Windows .rc definitions
#include "resource.h"

#include <nowide/iostream.hpp>
#include <string>
#include <vector>

// Loads an entire file in to memory.  The returned buffer must be later freed by the caller.
char *file_as_buffer(size_t *buffer_size, const char *utf8_filename);
char *file_as_buffer(size_t *buffer_size, const std::string &utf8_filename);

// Convert a buffer into an array of strings (lines)
std::vector<std::string> buffer_to_lines(char *buffer, size_t buffer_size);

// Write each line in the array to the file
bool file_write_lines(std::vector<std::string> lines, const char *utf8_filename);
bool file_write_lines(std::vector<std::string> lines, const std::string &utf8_filename);
bool file_write_lines(std::vector<std::string> lines, const char *utf8_filename, bool append);
bool file_write_lines(std::vector<std::string> lines, const std::string &utf8_filename, bool append);

// Shows a file dialog (should hang the current thread) and returns the utf8 filename picked by the
// user or nullptr.  If non-null is returned, it must be later freed by the caller.
//
// Filetype filtering must be implemented separately in each and every one of these functions (this
// could be done in a more elegant way in the future, if the scope of the project expands to include
// lots of formats)
std::string show_file_picker();

unsigned char *LoadAsset(int *asset_size, int asset_id);
