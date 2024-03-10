#include <list>

#include "FS.h"

using namespace std;

list<string> list_dir(File root) {
  list<string> files = list<string>();
  File file = root.openNextFile();
  while (file) {
    if (!file.isDirectory())
      files.push_back(file.name());
    else
      files.push_back((string)file.name() +
                      "/");  // A folder is indicated by a final slash. Cast
                             // char* to string to use +
    file = root.openNextFile();
  }

  return files;
}

list<string> list_fs(File root) {
  list<string> files = list<string>();
  File file = root.openNextFile();
  while (file) {
    if (!file.isDirectory())
      files.push_back(file.path());
    else
      files.splice(files.end(), list_dir(file));
    file = root.openNextFile();
  }

  return files;
}