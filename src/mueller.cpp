#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <algorithm>

std::string get_indent(int indent) {
  std::stringstream str;
  for (int i = 0; i < indent; i++) {
    str << " ";
  }
  return str.str();
}

std::string read_file(const std::string &file) {
  std::ifstream ifs(file);
  return std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
}

std::string get_filename(const std::string &file) {
  for (int i = file.length(); i >= 0; i--) {
    if (file[i]=='.') {
      return file.substr(0, i);
    }
  }
  return "";
}

std::string exec(const char *cmd) {
  std::array<char, 128> buffer{};
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get())!=nullptr) {
    result += buffer.data();
  }
  return result;
}

int main(int argc, char **argv) {
  std::string input = read_file(argv[1]);
  std::string filename = get_filename(argv[1]);
  int indent = 4;
  std::stringstream program;
  program << "int main() {\n";
  program << get_indent(indent) + "char array[30000] = {0};\n";
  program << get_indent(indent) + "char *ptr=array;\n";
  for (char c : input) {
    program << get_indent(indent);
    switch (c) {
      case '>': program << "++ptr;\n";
        break;
      case '<': program << "--ptr;\n";
        break;
      case '+': program << "++*ptr;\n";
        break;
      case '-': program << "--*ptr;\n";
        break;
      case '.': program << "putchar(*ptr);\n";
        break;
      case ',': program << "*ptr=getchar();\n";
        break;
      case '[': program << "while (*ptr) {\n";
        indent += 4;
        break;
      case ']': program << "}\n";
        indent -= 4;
        break;
      default: program << "";
        break;
    }
  }
  program << get_indent(indent) + "putchar(10);\n";
  program << "}";
  std::cout << program.str() << std::endl;
  std::ofstream out("prog.c");
  out << program.str();
  out.close();
  std::string cmd = "clang -O3 prog.c -o " + filename;
  exec(cmd.c_str());
  exec("rm prog.c");
}