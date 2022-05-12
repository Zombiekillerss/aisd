#include "Fulkerson.h"

Fulkerson::Fulkerson()
{
	matrix = nullptr;
	size = 0;
}

Fulkerson::~Fulkerson()
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

int Fulkerson::maxflow(string pathtofile)
{
	Fulkerson::~Fulkerson();
	writefromfile(pathtofile);
	int end = namecol.find("T"), start = namecol.find("S"), i = 0, minvalue = 0, sum = 0;
	elem el;
	bool isnotnul = false;
	do
	{
		isnotnul = false;
		for (int j = 0; j < size && !isnotnul; j++)
			isnotnul = matrix[start][j];
		if (isnotnul)
		{
			for (int j = 0, i = start; j < size; j++)
			{
				if (matrix[i][j] > 0)
				{
					el.index = j;
					el.value = matrix[i][j];
					place.push_back(el);
					i = j;
					j = -1;
				}
				if (i == end)
					break;
				else if (j == size - 1)
				{
					if (place.get_size() == 1)
						i = start;
					else
						i = place.get_elem(place.get_size() - 2).index;
					matrix[i][place.get_elem(place.get_size() - 1).index] = 0;
					place.clear();
					j = -1;
					if (i == start)
						break;
					i = start;
				}
			}
			if(place.get_size())
				minvalue = place.get_elem(0).value;
			for (int j = 0, i = start; j < place.get_size(); j++)
			{
				if (minvalue > place.get_elem(j).value)
					minvalue = place.get_elem(j).value;
				if (j == place.get_size() - 1)
					sum += minvalue;
			}
			for (int j = 0, i = start; j < place.get_size(); i = place.get_elem(j).index, j++)
			{
				matrix[i][place.get_elem(j).index] -= minvalue;
			}
			place.clear();
			std::cout << "Modified matrix" << endl;
			std::cout << "  ";
			for (i = 0; i < size; i++)
			{
				std::cout << namecol.get_elem(i) << " ";
			}
			std::cout << endl;
			for (i = 0; i < size; i++)
			{
				std::cout << namecol.get_elem(i) << " ";
				for (int j = 0; j < size; j++)
				{
					std::cout << matrix[i][j] << " ";
				}
				std::cout << endl;
			}
			std::cout << endl;
		}
	} while (isnotnul);
	return sum;
}

void Fulkerson::writefromfile(string pathtofile)
{
	ifstream file;
	file.open(pathtofile);
	string newstr;
	int from = -1, to = -1;
	if (file.is_open())
	{
		int i = -1;
		while (!file.eof())
		{
			file >> newstr;
			i++;
			if (!namecol.contains(newstr) && i < 2)
				namecol.push_back(newstr);
			else if (i == 2)
				i = -1;
			newstr = "";
		}
		file.close();
	}
	size = namecol.get_size();
	if (size > 0)
	{
		matrix = new int * [size];
		for (int i = 0; i < size; i++)
		{
			matrix[i] = new int[size];
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] = 0;
			}
		}
		file.open(pathtofile);
		string sum;
		if (file.is_open())
		{
			while (!file.eof())
			{
				file >> newstr;
				if (from == -1)
				{
					from = namecol.find(newstr);
					continue;
				}
				else if (to == -1)
				{
					to = namecol.find(newstr);
					continue;
				}
				matrix[from][to] = atoi(newstr.c_str());
				from = -1;
				to = -1;
			}
			std::cout << "Initial matrix" << endl;
			std::cout << "  ";
			for (int i = 0; i < size; i++)
			{
				std::cout << namecol.get_elem(i) << " ";
			}
			std::cout << endl;
			for (int i = 0; i < size; i++)
			{
				std::cout << namecol.get_elem(i) << " ";
				for (int j = 0; j < size; j++)
				{
					std::cout << matrix[i][j] << " ";
				}
				std::cout << endl;
			}
			std::cout << endl;
			file.close();
		}
	}
	else throw invalid_argument("You entered the data incorrectly or the file was not found!!");
}
