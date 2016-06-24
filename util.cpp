#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include "util.h"

using namespace std;


fcstream::fcstream(const char* fileName)
{
	m_fileStream.open(fileName, ofstream::app);
}

fcstream::~fcstream()
{
	m_fileStream.flush();
	m_fileStream.close();
}



void push_list(string &element, int &index, vector<Entity>& list)
{
	bool duplicate = false;
	for (int i = 0; i < index; i++) //checking if element already exists in the list
	{
		if (list[i].oldname == element)
		{
			duplicate = true;
			break;
		}
	}
	if (!duplicate)
	{
		list.push_back(Entity());
		list[index] = { element };
		index++;
	}
}

void push_list(string &element, vector<string>& list)
{
	bool duplicate = false;
	for (size_t i = 0; i < list.size(); i++) //checking if element already exists in the list
	{
		if (list[i] == element)
		{
			duplicate = true;
			break;
		}
	}
	if (!duplicate)
	{
		string s;
		list.push_back(s);
		//printf("%s\n", element.c_str());
		list[(list.size() - 1)] = { element };
	}
}

bool contains(string& str, const string& str1)
{
	string::size_type found = str.find(str1);
	return (found != string::npos);
}

vector<string> get_file_list(string DATA_DIR)
{
	HANDLE hFind;
	WIN32_FIND_DATAA data;
	vector<string> files;

	hFind = FindFirstFileA(DATA_DIR.c_str(), &data);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			files.push_back(data.cFileName);
			//printf("%s\n", data.cFileName);
		} while (FindNextFileA(hFind, &data));
		FindClose(hFind);
	}
	return files;
}

string fetch_property(const string& str)
{
	size_t max = (str.find_first_of("(") - 1);
	string result;
	for (int i = max; i > -1; i--)
	{
		if (isblank(str[i]) || (i == 0) )
		{
			result = str.substr((i+1), (max - i));
			break;
		}
	}
	return result;
}

string fetch_defaultv(const string& str)
{
	size_t n = (str.find_first_of(":")) + 1;
	string s = str.substr(n, (str.length() - n));

	size_t m = s.find_first_of(":");
	if (m == string::npos)
	{
		s.clear();
		return s;
	}
	n += m;
	s = str.substr(n, (str.length() - n));
	s.clear();

	for (size_t i = (n + 1); i < str.length(); i++)
	{
		if (str[i] == ':')
		{
			break;
		}
		else if (!isblank(str[i]) && (str[i] != '"'))
		{
			s += str[i];
		}
	}
	return s;
}

bool is_number(const string& s)
{
	return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !(isdigit(c) | (c == '-') | (c == '.')); }) == s.end();
}

bool has_number(const string& s)
{
	return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return isdigit(c); }) != s.end();
}

unsigned int in_list(vector<Entity>& list, string& s)
{
	for (unsigned int i = 0; i < size(list); i++)
	{
		if (list[i].oldname == s)
		{
			return i;
		}
	}
	return UINT_MAX;
}

unsigned int in_list(vector<string>& list, string& s)
{
	for (unsigned int i = 0; i < size(list); i++)
	{
		if (list[i] == s)
		{
			return i;
		}
	}
	return UINT_MAX;
}

void scoop_fgd(ifstream& inf, vector<string>& keyvalue_list, vector<string>& input_list)
{
	while (inf)
	{
		string s;
		string str;
		getline(inf, str);
		transform(str.begin(), str.end(), str.begin(), ::tolower);
		if (contains(str, "target_destination") || contains(str, "target_source"))
		{
			s = fetch_property(str);
		}
		/*
		else
		{
			if (contains(str, "string"))
			{
				if (contains(str, "target"))
				{
					if (!is_number(str))
					{
						s = fetch_property(str);
					}
				}
			}
		}
		*/
		if (!s.empty())
		{
			if (contains(str.substr(0, 8), "input "))
			{
				push_list(s, input_list);
			}
			else if (!contains(str.substr(0, 8), "output "))
			{
				string t = fetch_defaultv(str);
				
				//printf("%s\n", s.c_str());

				if (t.empty() || !is_number(t))
				{
					push_list(s, keyvalue_list);
				}
			}
		}
	}

}

vector<string> fetch_keyvalue(string& s)
{
	vector<string> keyvalues;
	size_t i = 0;
	size_t j = 0;
	while (i < s.length())
	{
		i = ((s.substr(i).find("\"")) + 1) + i;
		if (i == string::npos) { break; }
		size_t j = s.substr(i).find("\"");
		keyvalues.push_back(s.substr(i, j));

		i = i + j + 1;
	}
	return keyvalues;
}

vector<string> fetch_output(string& s, const string& c)
{
	vector<string> addoutput;
	size_t j = 0;
	size_t k = 0;

	while (1)
	{
		j = s.substr(j).find_first_of(c);
		if (j == string::npos) { addoutput.push_back(s.substr(k));  break; }
		else { j += (k + 1); }
		addoutput.push_back(s.substr(k, ((j - 1) - k)));
		k = j;
	}
	return addoutput;
}

void split_output(vector<string>& list)
{
	unsigned int length = size(list);

	for (unsigned int i = 0; i < length; i++)
	{
		size_t index = list[i].find(" ");
		if (index != string::npos)
		{
			string extract = list[i].substr((index + 1));
			list.insert((list.begin() + (i + 1)), extract);
			list[i].resize(index);
			length++;
			i++;
		}
	}
}

string makestring(char* chars, unsigned int value, unsigned int& size) //generates a unique string from an integer
{
	string result(1, chars[(value - (size * (value / size)))]); // # -> ~ 

	if (value > (size - 1))
	{
		string bstr(1, chars[(value / size) - 1]);
		result = bstr + result;
	}
	return result;
}