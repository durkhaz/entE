#include "stdafx.h"
#include "util.h"
#include "wc.h"
#include "fgd_identifiers.h"

#define ERR_BO "FAILED!\n  FATAL ERROR! Buffer overflow when waiting for \\n or eof!"
#define ERR_NF "ERROR! One argument is required!"
#define ERR_WF "ERROR! File is not a vmf!"
#define ERR_CO "FAILED!\nERROR! Could not open "
#define MSG_WA "entE-Command Sequence was successfully added to CmdSeq.wc!\n"
#define MSG_WF "entE-Command Sequence could not be written because it either already exists or there has been an error.\n"

using namespace std;

int main(int argc, char* argv[])
{
	string fcur;
	if (argc == 1)
	{
		fcur.assign(argv[0]);
	}
	else
	{
		fcur.assign(argv[1]);
	}
	string logf = fcur;
	logf.replace(logf.find_first_of("."), logf.length(), ".log");
	fcstream *log = new fcstream(logf.c_str());

	//check if argument was passed in
	if (argc == 1) 
	{ 
		//if no argument, it checks for CmdSeq.wc
		vector<string> files = get_file_list("CmdSeq.wc");
		if (!files.empty())
		{
			if (process_wc(files[0], argv[0]))
			{
				*log << MSG_WA;
				exit(0);
			}
			else
			{
				*log << MSG_WF;
				exit(1);
			}
		}
		else
		{
			*log << ERR_NF;
			exit(1);
		}
	} 

	//check if file has vmf extension
	if (fcur.substr(((fcur.find_first_of(".")) + 1)) != "vmf") 
	{ 
		*log << ERR_WF;
		exit(1);
	} 

	cout << "\n\n\n";

	vector<string> files = get_file_list("*.fgd");
	if (!files.empty())
	{
		*log << files.size() << " fgd's found in directory!\nUpdating identifiers... ";
		int penis = keyvalue_list.size();
		int size = (keyvalue_list.size() + input_list.size());
		for (unsigned int i = 0; i < files.size(); i++)
		{
			ifstream inf(files[i]);
			scoop_fgd(inf, keyvalue_list, input_list);
			while (inf) {};
		}
		*log << "DONE!   " << ((keyvalue_list.size() + input_list.size()) - size) << " new identifiers added.\n";

		for (unsigned int i = penis; i < keyvalue_list.size(); i++)
		{
			*log << keyvalue_list[i] << "\n";
		}
		
		/*
		ofstream extract("fgd_extract.dat");
		extract << keyvalue_list.size() << " Unique keyvalues found:\n\n";
		for (size_t i = 0; i < keyvalue_list.size(); i++)
		{
			extract << "\"" + keyvalue_list[i] + "\",\n";
		}
		extract << "\n\n\n\n" << input_list.size() << " Unique inputs found:\n\n";

		for (size_t i = 0; i < input_list.size(); i++)
		{
			extract << "\"" + input_list[i] + "\",\n";
		}
		extract.flush();
		extract.close();
		*/
	}
	else
	{
		*log << "No fgd files found in directory. Running using default identifiers!\n";
	}


	int ent_number = 0;
	int wc_number = 0;
	int blk_number = 0;
	vector<Entity> ent_list;
	vector<Entity> wc_list;
	vector<Entity> blk_list;

	*log << "Generating base-64 numeral system...";
	char chars[63]; // list of chars relevant for targetnames
	unsigned int chars_listed = 0;
	for (int i = 35; i < 127; i++) 
	{
		if ((i != 42) && (i != 44) && (i != 58) && ((i < 65) || (i > 90)))  //no * , or :
		{
			char ctemp(i);
			chars[chars_listed] = ctemp;
			chars_listed++;
		}
	}

	*log << "DONE!\nOpening vmf...";
	ifstream inf(fcur); //opens vmf
	if (!inf.is_open())
	{
		*log << ERR_CO << fcur;
		exit(1);
	}

	unsigned int block = 0;
	while (inf && (block < 4)) //skip past worldspawn block
	{
		char n;
		inf.ignore(numeric_limits<streamsize>::max(), '{');
		unsigned int depth = 1;
		while ((depth > 0) && (inf))
		{
			inf >> n;
			if (n == '{') { depth++; }
			else if (n == '}') { depth--; }
		}
		block++;
	}
	streampos start = inf.tellg(); //keep position for later

	*log << "DONE!\nFetching targetnames and wildcards...";

	while (inf)
	{
		string strInput;
		getline(inf, strInput);
		if (inf.fail() && !inf.eof())
		{
			inf.clear();
			*log << ERR_BO << " Position: " << inf.tellg();
			delete log;
			exit(EXIT_FAILURE);
		}

		if (strInput.size() > 8)
		{
			if (strInput.substr(2, 10) == "targetname") //find all targetnames
			{
				string ent = strInput.substr(15);
				ent.pop_back();
				if (is_number(ent))
				{
					push_list(ent, blk_number, blk_list);
				}
				else
				{
					push_list(ent, ent_number, ent_list);
				}
			}


			size_t match = strInput.find("*"); //find all wildcards
			if (match != string::npos)
			{
				size_t smatch = strInput.find_last_of(" \"", match);
				string wc_buffer = strInput.substr((smatch + 1), ((match - smatch)) - 1);
				if (!is_number(wc_buffer))
				{
					push_list(wc_buffer, wc_number, wc_list);
				}
			}
		}
	}

	sort(wc_list.begin(), wc_list.begin() + wc_number);
	*log << "DONE!\nProcessing wildcards and affected targetnames...";
	for (int i = 0; i < wc_number; i++) // targetnames referenced by wildcards get special treatment and get moved to the back of the list
	{
		vector<int> erase_list;
		unsigned int matches = 0;
		for (int j = 0; j < ent_number; j++)
		{
			if (ent_list[j].oldname.substr(0, wc_list[i].oldname.length()) == wc_list[i].oldname)
			{
				
				string bstr(makestring(chars, ((((chars_listed * chars_listed) + chars_listed) - 1) - i), chars_listed));
				if (!ent_list[j].newname.empty())
				{
					bstr = (ent_list[j].newname.substr(0, ent_list[j].newname.length() - 1))+bstr;
				}
				wc_list[i].newname = (bstr + "*");
				ent_list.push_back(ent_list[j]);
				if (ent_list[j].oldname != wc_list[i].oldname)
				{
					bstr = bstr + makestring(chars, matches, chars_listed);
				}
				ent_list[(ent_list.size() - 1)] = { ent_list[j].oldname, bstr };
				erase_list.push_back(j);
				matches++;
			}
		}
		for (size_t j = 0; j < erase_list.size(); j++)
		{
			ent_list.erase(ent_list.begin() + (erase_list[j] - j)); // SLOW AF
		}
	}
	*log << "DONE!\nProcessing remaining targetnames...";
	unsigned int offset = 0;
	for (int i = 0; i < ent_number; i++)
	{
		if (ent_list[i].newname.empty())
		{
			for (int j = 0; j < UINT_MAX; j++)
			{
				unsigned int k = in_list(blk_list, makestring(chars, (i + offset), chars_listed));
				if (k != UINT_MAX)
				{
					offset++;
				}
				else
				{
					break;
				}
			}
			ent_list[i].newname = makestring(chars, (i + offset), chars_listed);
		}
	}

	for (int i = 0; i < wc_number; i++) //move over all non empty wildcards (all that aren't class name references)
	{
		if (!wc_list[i].newname.empty())
		{
			ent_list.push_back(wc_list[i]);
			ent_list[ent_list.size() - 1].oldname += "*";
		}
	}

	*log << "DONE!\nPreparing new vmf...";
	inf.clear();
	inf.seekg(0, ios_base::beg); // move pointer back to start
	
	ofstream outf(fcur.insert((fcur.find_first_of(".")), "_new")); //creates new vmf
	
	while (inf && (inf.tellg() < start))
	{
		string strInput;
		getline(inf, strInput);
		outf << strInput << '\n';
	}

	if (inf.fail() && !inf.eof())
	{
		inf.clear();
		*log << ERR_BO << " Position: " << inf.tellg();
		delete log;
		exit(EXIT_FAILURE);
	}

	*log << "DONE!\nReplacing targetnames...";

	int o_chars = 0;
	int n_chars = 0;

	while (inf)
	{
		string line;
		getline(inf, line);
	
		if (inf.fail() && !inf.eof())
		{
			inf.clear();
			*log << ERR_BO << " Position: " << inf.tellg();
			delete log;
			exit(EXIT_FAILURE);
		}
		if (line.size() > 1)
		{
			if (line[1] == '"') //keyvalue block
			{
				vector<string> muell = fetch_keyvalue(line);
				string key = muell[0];
				string value = muell[1];
				vector<string>().swap(muell);
				//outf << key + "  " + value + "\n";

				if (!value.empty())
				{
					unsigned int i = in_list(ent_list, value);
					if (i != UINT_MAX)
					{
						transform(key.begin(), key.end(), key.begin(), ::tolower);
						unsigned int j = in_list(keyvalue_list, key);
						if (j != UINT_MAX)
						{
							line.replace((line.length() - value.length() - 1), value.length(), ent_list[i].newname);
							o_chars += ent_list[i].oldname.length(); n_chars += ent_list[i].newname.length();
						}
						else
						{
							*log << "\nUnknown key " + key + " for targetname " + value + " found! Skipping ambigious match!\n";
						}
					}
				}
				outf << line << '\n';
			}

			else if (line[2] == '"') //output block
			{
				vector<string> muell = fetch_keyvalue(line);
				unsigned int offset = muell[0].length() + 6;
				vector<string> output = fetch_output(muell[1],",");
				vector<string>().swap(muell);

				if (output.size() > 1)
				{
					if (!output[2].empty())
					{
						transform(output[1].begin(), output[1].end(), output[1].begin(), ::tolower);
						//keyvalue output
						if (output[1] != "addoutput")
						{
							unsigned int j = in_list(ent_list, output[2]);
							if (j != UINT_MAX)
							{
								unsigned int k = in_list(input_list, output[1]);
								if (k != UINT_MAX)
								{
									line.replace((offset + output[0].length() + output[1].length() + 2), output[2].length(), ent_list[j].newname);
									o_chars += ent_list[j].oldname.length(); n_chars += ent_list[j].newname.length();
								}
								else
								{
									*log << "\nUnknown Input " + output[1] + " for targetname " + output[2] + " found! Skipping ambigious match!\n";
								}
							}
						}
						else
						{
							vector<string> addoutput = fetch_output(output[2], ":");
							split_output(addoutput);


							if (addoutput.size() > 2)
							{
								if (addoutput.size() > 6)
								{
									unsigned int j = in_list(ent_list, addoutput[4]);
									if (j != UINT_MAX)
									{
										transform(addoutput[3].begin(), addoutput[3].end(), addoutput[3].begin(), ::tolower);
										unsigned int k = in_list(keyvalue_list, addoutput[3]);
										if (k != UINT_MAX)
										{
											line.replace((offset + output[0].length() + output[1].length() + 2) + (addoutput[0].length() + addoutput[1].length() + +addoutput[2].length() + addoutput[3].length() + 4), addoutput[4].length(), ent_list[j].newname);
											o_chars += ent_list[j].oldname.length(); n_chars += ent_list[j].newname.length();
										}
										else
										{
											*log << "\nUnknown key " + addoutput[3] + " for targetname " + addoutput[4] + " found inside " + addoutput[2] + " statement! Skipping ambigious match!\n";
										}
									}
								}
								else
								{
									unsigned int j = in_list(ent_list, addoutput[3]);
									if (j != UINT_MAX)
									{
										transform(addoutput[2].begin(), addoutput[2].end(), addoutput[2].begin(), ::tolower);
										unsigned int k = in_list(keyvalue_list, addoutput[2]);
										if (k != UINT_MAX)
										{
											line.replace((offset + output[0].length() + output[1].length() + 2) + (addoutput[0].length() + addoutput[1].length() + addoutput[2].length() + 3), addoutput[3].length(), ent_list[j].newname);
											o_chars += ent_list[j].oldname.length(); n_chars += ent_list[j].newname.length();
										}
										else
										{
											*log << "\nUnknown key " + addoutput[2] + " for targetname " + addoutput[3] + " found! Skipping ambigious match!\n";
										}
									}
								}
								unsigned int j = in_list(ent_list, addoutput[1]);
								if (j != UINT_MAX)
								{
									line.replace((offset + output[0].length() + output[1].length() + 2) + (addoutput[0].length() + 1), addoutput[1].length(), ent_list[j].newname);
									o_chars += ent_list[j].oldname.length(); n_chars += ent_list[j].newname.length();
								}
							}
							else
							{
								unsigned int j = in_list(ent_list, addoutput[1]);
								if (j != UINT_MAX)
								{
									transform(addoutput[0].begin(), addoutput[0].end(), addoutput[0].begin(), ::tolower);
									unsigned int k = in_list(keyvalue_list, addoutput[0]);
									if (k != UINT_MAX)
									{
										line.replace((offset + output[0].length() + output[1].length() + 2) + (addoutput[0].length() + 1), addoutput[1].length(), ent_list[j].newname);
										o_chars += ent_list[j].oldname.length(); n_chars += ent_list[j].newname.length();
									}
									else
									{
										*log << "\nUnknown key " + addoutput[0] + " for targetname " + addoutput[1] + " found! Skipping ambigious match!\n";
									}
								}
							}

							vector<string>().swap(addoutput);
							/*

							#wddOutput
								"OnTrigger"		"!activator"				"AddOutput"	"health"					"1000"			"0"		"-1"
								"OnTrigger"		"!activator"				"AddOutput" "rendercolor"				"112 122 214"	"0"		"-1"
								"OnCase08"		"ammdis_entspawner_team1"	"AddOutput" "EntityTemplate"			"ammopt9"		"0.1"	"-1"
								"OnCase06"		"spawn3r"					"AddOutput"	"EntityTemplate"			"t_runner"		"0.1"	"-1"
								"OnHitMin"		"sc_logic3"					"Trigger"	"-1"										"0.5"	"-1"
								"OnHitMin"		"sc_deduct"					"FireUser1" "-1"										"0"		"-1"
								"case06"		"20"
								"targetname"	"obj9_z1"

								"OnUser1" "obj4_em,AddOutput,EntityTemplate obj4_templ,0,-1"

							*/
						}

					}
					unsigned int i = in_list(ent_list, output[0]);
					if (i != UINT_MAX) 
					{ 
						line.replace(offset, output[0].length(), ent_list[i].newname); 
						o_chars += ent_list[i].oldname.length(); n_chars += ent_list[i].newname.length();
					}
				}

				vector<string>().swap(output);

				outf << line << '\n';
			}
			else { outf << line << '\n'; }
		}
		else { outf << line << '\n'; }
	}
	*log << "DONE!\n\n";
	inf.close(); //close input vmf
	outf.flush();
	outf.close(); //close output vmf

	delete log;
	// debug output

	ofstream tn_list(logf, ofstream::app); //creates debug list

	float ratio = ((static_cast<float>(o_chars) - static_cast<float>(n_chars)) / o_chars) * 100;
	tn_list << "Reduced " << o_chars << " characters to " << n_chars << ". " << static_cast<int>(ratio) << "% Reduction!\n\n";
	tn_list << ent_number << " Unique entity targetnames found:" << endl << endl;

	for (int i = 0; i < ent_number; i++)
	{
		tn_list << ent_list[i].oldname + "  :  " + ent_list[i].newname << endl;
	}

	tn_list << endl << wc_number << " Unique Wildcards found:" << endl << endl;

	for (size_t i = 0; i < wc_list.size(); i++)
	{
		tn_list << wc_list[i].oldname + "  :  " + wc_list[i].newname << endl;
	}

	tn_list << endl << blk_number << " Blacklist elements:" << endl << endl;

	for (size_t i = 0; i < blk_list.size(); i++)
	{
		tn_list << blk_list[i].oldname << endl;
	}
	tn_list.flush();
	tn_list.close(); //close output vmf
	//std::cin.ignore();
	return 0;
}