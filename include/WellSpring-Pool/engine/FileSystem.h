#pragma once

#include <string>
#include <unordered_set>
#include <fstream>
#include <string.h>
#include <stdint.h>

class File {
  std::ifstream _file;
  bool _is_open = false;

  static std::unordered_set<std::string> open_files;

public:
  static bool fileExists(const std::string &path);
  static void deleteFile(const std::string &path);

  File(const std::string &path);
  File();
  ~File();

  File(File &&other);
  File &operator=(File &&other);

  void open(const std::string &path);

  // Equivalent to loading an std::string with read(getSize())
  std::string allContent();
  
  size_t getSize();



  // Reads amount bytes, then sets amount to the number of bytes read.
  void *read(size_t *amount, size_t from = 0);

  // Reads an amount of bytes. buffer should be allocated with amount bytes. Returns the number of bytes read.
  size_t read(size_t amount, void *buffer, size_t from = 0);

  // Reads an amount of bytes.
  std::string read(size_t amount, size_t from = 0);

  // Reads until delim. amount is the maximum number of bytes to be read, and will be set to the number of bytes read.
  void readUntil(size_t *amount, void *buffer, char delim, size_t from = 0);

  // Reads until delim.
  std::string readUntil(char delim, size_t from = 0);

  // Returns the maximum number of bytes readUntil will read. Call this before C-like readUntil.
  size_t bytesUntil(char delim, size_t from = 0);

  // Deletes the file
  void remove();

  // Revokes access to a file
  void close();

  // Deletes all of a file's content
  void clearContent();

  // Appends more data to the end of a file
  void addContent(const std::string &content);
  void addContent(size_t amount, const void *buffer);

  // Overrites existing file data
  void writeContent(const std::string &content, size_t from);
  void writeContent(size_t amount, const void *buffer, size_t from);
};

// Tips:
// - To replace a file's content, call clearContent() and addContent() together