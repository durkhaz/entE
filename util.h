#pragma once

void push_list(std::string &element, int &index, std::vector<Entity>& list);
void push_list(std::string &element, std::vector<std::string>& list);
bool contains(std::string& str, const std::string& str1);
std::vector<std::string> get_file_list(std::string DATA_DIR);
bool is_number(const std::string& s);
unsigned int in_list(std::vector<Entity>& list, std::string& s);
unsigned int in_list(std::vector<std::string>& list, std::string& s);
void scoop_fgd(std::ifstream& inf, std::vector<std::string>& keyvalue_list, std::vector<std::string>& input_list);
std::vector<std::string> fetch_keyvalue(std::string& s);
std::vector<std::string> fetch_output(std::string& s,const std::string& c);
void split_output(std::vector<std::string>& list);
std::string makestring(char* chars, unsigned int value, unsigned int& size);

class fcstream
{
public:
	fcstream(const char* fileName);
	~fcstream();
	std::ofstream m_fileStream;
};

template <typename T> fcstream& operator<< (fcstream& stream, T val)
{
	stream.m_fileStream << val;
	std::cout << val;
	return stream;
};