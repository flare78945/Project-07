/*
* File: main.cpp
* Description: Write a program that reads a C++ source file and produces an index of all identifiers in the file. For each identifier, print all line numbers in which the identifier occurs.
* Author: Minhquang Phillip Tran
* Date: April 7, 2022
* Email: phillip_tran_98@yahoo.com
*/

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <utility>

int main() 
{
	std::string f_name = "source.txt"; // file to read
	std::ifstream read;
	read.open(f_name);
	
	std::set<std::pair<std::string, int>> ident_count;

	while (read.is_open())
	{
		int line = 1; // Tracks File Line
		
		int end = read.peek();

		while (end != EOF)
		{
			std::string hold;
			char c;
			
			while (end != EOF)
			{
				c = read.get();
				//std::cout << c;
				if (isalnum(c) || c == '_')
				{
					hold += c;
				}
				if (c == '\"')
				{
					read.ignore(256, '\"');
				}
				if (c == '\n' || c == '\r')
				{
					line++;
					//std::cout << line << std::endl;
				}
				if (c == ' ' || ispunct(c))
				{
					if (!hold.empty())
					{
						if (isdigit(hold.at(0)))
						{
							hold = "";
						}
						
						else
						{
							ident_count.insert(make_pair(hold, line));
							hold = "";
						}
					}
				}
				
				end = read.peek();
			}
		}
		
		read.close();
	}

	std::string temp = "";
	
	for (auto iter = ident_count.begin(); iter != ident_count.end(); iter++)
	{
		if (temp == "")
		{
			temp = iter->first;
			std::cout << iter->first << " " << iter->second;
		}
		else if (temp != iter->first)
		{
			std::cout << std::endl;
			temp = iter->first;
			std::cout << iter->first << " " << iter->second;
		}
		else
		{
			std::cout << " " << iter->second;
		}
	}
	
	std::cout << std::endl;
}
