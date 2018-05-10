#include <string>
#include <filesystem>
#include <iostream>  
#include <fstream> 
#include <Windows.h>
#include <iostream>

bool isPrime(int number) {

	if (number < 2) return false;
	if (number == 2) return true;
	if (number % 2 == 0) return false;
	for (int i = 3; (i*i) <= number; i += 2) if (number % i == 0) return false;
	return true;

}

int crypt(const std::string &filename)
{

	std::ifstream file(filename, std::ios::in | std::ios::binary);
	std::ofstream outfile(filename + "-New", std::ios::out | std::ios::binary);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	char c;
	int i = 0;
	int x, y, z = 0;
	int byte1, byte2;
	std::string ciphertext;

	while (file.get(c))
	{
		if (isPrime(i))
		{
			char key[] = ("¯¾÷ü°½ÜÁ¸ªÅê´÷¾·");
			byte2 = (int)key[x];
			x++;
		}
		else if (i % 2 == 0)
		{
			char key[] = ("¼¤µÈ£ëÆêõãåÊßÓîæ");
			byte2 = (int)key[y];
			y++;
		}
		else
		{
			char key[] = ("ñÛ¹Ð½®¤¶½ºûÊ¸ÂÎã");
			byte2 = (int)key[z];
			z++;
		}

		// clipping the key position to the length of the key
		if (x > 16) x = 0;
		if (y > 16) y = 0;
		if (z > 16) z = 0;

		byte1 = (int)c;
		unsigned char x = byte1 ^ byte2;
		ciphertext += x; // append the crypted byte to the bytecode
		i++; // to count the file size
	}
	try
	{
		outfile.write(ciphertext.c_str(), i);
	}
	catch (...)
	{
		return 3;
	}
	try
	{
		outfile.close();
		file.close();
	}
	catch (...)
	{
		return 4;
	}

	return 0;
}




int main(int argc, char**argv)
{
	char * InFile = argc > 1 ? argv[1] : "";

	if (InFile == "")
	{
		std::cout << "No File selected! See usage notes." << std::endl;
		Sleep(5000);
		exit(1);
	}
	else
	{
		std::cout << "InFile: " << InFile << std::endl;
	}

	switch (crypt(InFile))
	{
	case 0:
	{
		std::cout << "Success! Output is labeled with -New tag in the same directory as the input file." << std::endl;
		Sleep(5000);
		exit(0);
	}
	case 1:
	{
		std::cout << "Error Reading Input file!" << std::endl;
		Sleep(5000);
		exit(1);
	}
	case 2:
	{
		std::cout << "Error creating the Output file!" << std::endl;
		Sleep(5000);
		exit(2);
	}
	case 3:
	{
		std::cout << "Error Writing to the Output file!" << std::endl;
		Sleep(5000);
		exit(3);
	}
	case 4:
	{
		std::cout << "Error closing files after use! << This can be ignored usualy!" << std::endl;
		Sleep(5000);
		exit(4);
	}
	}
	Sleep(5000);
	exit(5);
}

