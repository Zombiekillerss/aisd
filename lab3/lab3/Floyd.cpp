#include "Floyd.h"

Floyd::Floyd()
{
	matrix = nullptr;
}

Floyd::~Floyd()
{
	for (size_t i = 0; i < size; i++)
	{
		delete matrix[i];
	}
	size = 0;
	if (matrix)
		delete matrix;
	matrix = nullptr;
}

string Floyd::cheapway(string start, string end, string pathtofile)
{
	writefromfile(pathtofile);
	int colstart = 0, colend = 0;
	colstart = namecol.find(start);
	colend = namecol.find(end);
	if (colstart == -1 || colend == -1)
		throw invalid_argument("lol");
	string result = "";
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (j == i)
				continue;
			for (int k = 0; k < size; k++)
			{
				if (k == i || j == k || matrix[i][k].isinf || matrix[j][i].isinf)
					continue;
				if (matrix[i][k].value + matrix[j][i].value < matrix[j][k].value || matrix[j][k].isinf)
				{
					matrix[j][k].isinf = false;
					matrix[j][k].value = matrix[i][k].value + matrix[j][i].value;
					matrix[j][k].intermediate = matrix[j][i].intermediate;
					if (matrix[j][k].intermediate == -1)
						matrix[j][k].intermediate = i;
				}
			}
		}
	}
	result += start + "->";
	while (matrix[colstart][colend].intermediate != -1)
	{
		colstart = matrix[colstart][colend].intermediate;
		result += namecol.get_elem(colstart) + "->";
	}
	result += end;
	return result;
}

void Floyd::print_matrix()
{
	cout << endl << "Modified matrix" << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << matrix[i][j].value << " ";
		}
		cout << endl;
	}
}

void Floyd::writefromfile(string pathtofile)
{
	ifstream file;
	//Here (...);(...);...;... there may be spaces, in other places they should not be!
	file.open(pathtofile);
	string newstr;
	string newoldstr = "";
	int row = 0, col = 0;
	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> newstr;
			newoldstr += newstr;
			if (countstr(newoldstr, ';') != 3)
			{
				newoldstr += ' ';
				continue;
			}
			if (!namecol.contains(newoldstr.substr(0, newoldstr.find(';'))))
				namecol.push_back(newoldstr.substr(0, newoldstr.find(';')));
			if (!namecol.contains(newoldstr.substr(newoldstr.find(';') + 1, newoldstr.find(';', newoldstr.find(';')))))
				namecol.push_back(newoldstr.substr(newoldstr.find(';') + 1, newoldstr.find(';', newoldstr.find(';'))));
			newoldstr = "";
		}
		file.close();
	}
	size = namecol.get_size();
	if (size > 0)
	{
		matrix = new Elem * [size];
		for (int i = 0; i < size; i++)
		{
			matrix[i] = new Elem[size];
			for (int j = 0; j < size; j++)
			{
				matrix[i][j].intermediate = -1;
			}
		}
		file.open(pathtofile);
		string sum;
		if (file.is_open())
		{
			while (!file.eof())
			{
				file >> newstr;
				newoldstr += newstr;
				if (countstr(newoldstr, ';') != 3)
				{
					newoldstr += ' ';
					continue;
				}
				row = namecol.find(newoldstr.substr(0, newoldstr.find(';')));
				col = namecol.find(newoldstr.substr(newoldstr.find(';') + 1, newoldstr.find(';', newoldstr.find(';'))));
				if (row != -1 && col != -1)
				{
					sum = newoldstr.substr(newoldstr.find(';', newoldstr.find(';') + 1) + 1,
						newoldstr.rfind(';') - newoldstr.find(';', newoldstr.find(';') + 1) - 1);
					if (sum == "N/A")
						matrix[row][col].isinf = true;
					else matrix[row][col].value = atoi(sum.c_str());
					sum = newoldstr.substr(newoldstr.rfind(';') + 1);
					if (sum == "N/A")
						matrix[col][row].isinf = true;
					else matrix[col][row].value = atoi(sum.c_str());
				}
				newoldstr = "";
			}
			cout << "Adjacency matrix" << endl;
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (!matrix[i][j].value)
						cout << "0 ";
					else cout << "1 ";
				}
				cout << endl;
			}
			file.close();
		}
	}
	else throw invalid_argument("You entered the data incorrectly or the file was not found!!");
}

size_t Floyd::countstr(string str, char ch)
{
	size_t counts = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ch)
			counts++;
	}
	return counts;
}
