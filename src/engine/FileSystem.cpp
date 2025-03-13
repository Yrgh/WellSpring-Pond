#include <engine/FileSystem.h>
#include <core/error.h>

bool File::fileExists(const std::string &path) {
  if (FILE *file = fopen(path.c_str(), "r")) {
    fclose(file);
    return true;
  }
  return false;
}

void deleteFile(const std::string &path) {
  std::remove(path.c_str());
}

File::File(const std::string &path) {
  open(path);
}

File::File() : _is_open(false) {}

File::~File() {
  if (_is_open) _file.close();
}

File::File(File &&other) : _file(std::move(other._file)), _is_open(other._is_open) { other._is_open = false; }

File &File::operator=(File &&other) {
  _file = std::move(other._file);
  _is_open = other._is_open;
  other._is_open = false;
  return *this;
}

void File::open(const std::string &path) {
  if (_is_open) reportFatalError("File is open");

  if (open_files.find(path) != open_files.end()) reportFatalError("File is already open: " + path);

  if (!fileExists(path)) reportFatalError("File does not exist: " + path);

  _file.open(path, std::ios::in | std::ios::out | std::ios::binary);
  if (!_file.is_open()) reportFatalError("Failed to open file: " + path);

  open_files.insert(path);

  _is_open = true;
}

std::string File::allContent() {
  if (!_is_open) reportFatalError("File is not open");

  // TODO
}

size_t File::getSize() {
  if (!_is_open) reportFatalError("File is not open");

  _file.seekg(0, std::ios::beg);
  std::streampos beg = _file.tellg();
  _file.seekg(0, std::ios::end);
  std::streampos end = _file.tellg();
  _file.seekg(beg);

  return end - beg;
}

void *File::read(size_t *amount, size_t from) {
  if (!_is_open) reportFatalError("File is not open");

  void *buffer = malloc(*amount);
  memset(buffer, 0, *amount);
  _file.seekg(from);
  _file.read((char *) buffer, *amount);

  *amount = strlen((char *) buffer);

  return buffer;
}

size_t File::read(size_t amount, void *buffer, size_t from) {
  if (!_is_open) reportFatalError("File is not open");

  memset(buffer, 0, amount);
  _file.seekg(from);
  _file.read((char *) buffer, amount);

  return strlen((char *) buffer);
}

std::string File::read(size_t amount, size_t from) {
  if (!_is_open) reportFatalError("File is not open");

  void *data = read(&amount, from);

  return std::string((char *) data, amount);
}

void File::readUntil(size_t *amount, void *buffer, char delim, size_t from) {
  if (!_is_open) reportFatalError("File is not open");

  // TODO
}

std::string File::readUntil(char delim, size_t from) {
  if (!_is_open) reportFatalError("File is not open");

  // TODO
}

size_t File::bytesUntil(char delim, size_t from) {
  if (!_is_open) reportFatalError("File is not open");

  // TODO
}

void File::close() {
  if (!_is_open) reportFatalError("File is not open");

  _file.close();
  _is_open = false;
}

void File::clearContent() {
  if (!_is_open) reportFatalError("File is not open");

  // TODO
}

void File::addContent(const std::string &content) {
  if (!_is_open) reportFatalError("File is not open");

  // TODO
}

void File::addContent(size_t amount, const void *buffer) {
  if (!_is_open) reportFatalError("File is not open");

  // TODO
}

void File::writeContent(const std::string &content, size_t from){
  if (!_is_open) reportFatalError("File is not open");

  // TODO
}

void File::writeContent(size_t amount, const void *buffer, size_t from) {
  if (!_is_open) reportFatalError("File is not open");

  // TODO
}