#include "stdafx.h"
#include "util.h"
#include "fgd_identifiers.h"

using namespace std;

int is_in_wc(ifstream& iwc)
{
	iwc.seekg(0, iwc.end);
	unsigned int length = static_cast<int>(iwc.tellg());
	iwc.seekg(0, iwc.beg);
	char *buffer = new char[length];
	iwc.read(buffer, length);

	string extract;
	for (unsigned int i = 0; i < length; i++)
	{
		int n = static_cast<int>(buffer[i]);
		
		if ((n >= -1) && (n <= 255))
		{
			if (!iscntrl(buffer[i]) && extract.empty())
			{
				extract += buffer[i];
			}
			else if (!iscntrl(buffer[i]) && !extract.empty())
			{
				extract += buffer[i];
			}
			else if (iscntrl(buffer[i]) && !extract.empty())
			{

				if (extract == wc_args[0])
				{
					delete[] buffer;
					return 0;
				}
				extract.clear();
			}
		}
	}
	int n = static_cast<int>(buffer[35]);


	delete[] buffer;
	return n;
}

bool put_in_wc(ofstream& owc, char* ente)
{
	string buffer;
	buffer.reserve(11388);
	char null(0);
	char one(1);
	char num(static_cast<char>((wc_args.size() - 1) / 2));

	string s = ente;
	wc_args[1] = s;

	int size = 0;
	int length = wc_args[0].length();
	buffer.replace(size, length, wc_args[0]);
	size += length;
	buffer.replace(size, 128 - length, 128 - length, null);
	size += (128 - length);
	buffer.replace(size, 1, { num });
	size++;
	buffer.replace(size, 3, 3, null);
	size += 3;

	for (unsigned int i = 1; i < wc_args.size(); i++)
	{
		if ((i % 2) == 1)
		{
			buffer.replace(size, 1, { one });
			size++;
			buffer.replace(size, 3, 3, null);
			size += 3;
			if (iscntrl(wc_args[i][0])) {buffer.replace(size, 2, wc_args[i]);}
			else { buffer.replace(size, 2, 2, null); }
			size += 2;
			buffer.replace(size, 2, 2, null);
			size += 2;
			length = wc_args[i].length();
			buffer.replace(size, length, wc_args[i]);
			size += length;
			buffer.replace(size, 260 - length, 260 - length, null);
			size += (260 - length);
		}
		else
		{
			length = wc_args[i].length();
			buffer.replace(size, length, wc_args[i]);
			size += length;
			buffer.replace(size, 528 - length, 528 - length, null);
			size += (528 - length);
			buffer.replace(size, 1, { one });
			size++;
			buffer.replace(size, 7, 7, null);
			size += 7;
		}
	}
	owc.write(buffer.c_str(), (buffer.size()));

	owc.close();
	return true;
}

bool process_wc(string& file, char* ente)
{
	ifstream iwc(file, ifstream::binary);

	if (!iwc.is_open())
	{
		return false;
	}
	int val = is_in_wc(iwc);
	if (val == 0)
	{
		return false;
	}

	else
	{
		ofstream owc(file,(ofstream::binary | ofstream::out | ofstream::in));

		if (!owc.is_open())
		{
			return false;
		}

		char cd(val + 1);
		char c[] = {cd};
		owc.seekp(ios_base::beg + 35);
		owc.write(c, 1);

		if (owc.bad() || owc.fail())
		{

			owc.close();
			return false;
		}

		owc.close();
		owc.open(file, (ofstream::binary | ofstream::app));
		owc.seekp(ios_base::end);
		
		return put_in_wc(owc, ente);
	}
}