#if _DEBUG
	#include "../memory/memoryWork.h"
#else
	#include "../memory/events/new_event.h"
#endif
#include "encryption.h"
#include <iostream>
#include <fstream>
#include "../memory/helper_functions.h"
#include "dm_assert.h"

sumFileS sumFile;

namespace encryption
{
	static string f(string s, size_t key)
	{
		string ciphertext = "";

		int len = s.length();
		for (int i = 0; i < len; i++)
		{
			s[i] = s[i] ^ static_cast<char>(key);
			ciphertext += s[i];
		}

		return ciphertext;
	}

	void encryptionString(string targetFile, string newFile, size_t key)
	{
		string ciphertext = "";
		ifstream file(targetFile);
		string s;
		while (getline(file, s))
		{
			ciphertext += f(s, key) + "\n";
		}

		file.close();

		ofstream out;
		out.open(newFile, ios::out);
		if (out.is_open())
		{
			out << ciphertext << endl;
		}
		out.close();
	}
	/////////////////////////////////////////////////////////////////////////////////
	static size_t getKey(size_t key[], size_t size, size_t& i)
	{
		if (i > size)
			i = 0;

		if (key[i] == 0)
			return key[size];

		size_t v = key[i];

	//	log_always("getKey(size: " + to_string(size) + ", i: " + to_string(i) + ", v: " + to_string(v) + ")");

		return v;
	}

	void encryptionBin(string targetFile, string newFile, size_t key[], size_t size)
	{
		ofstream nFile;
		nFile.open(newFile, ios::binary | ofstream::out);

		ifstream file(targetFile, ios::binary);
		char byte;
		size_t i = 0;
		while (file.read(&byte, sizeof(byte)))
		{
			char b_k = byte ^ static_cast<char>(getKey(key, size, i));
			nFile.write(reinterpret_cast<char*>(&b_k), sizeof(char));
			i++;
		}
		file.close();

		nFile.close();
	}
	/////////////////////////////////////////////////////////////////////////////////
	static char getKey(string key, size_t& i, size_t size)
	{
		if (i >= size)
			i = 0;

	//	if (!key[i])
	//		return key[0];

		char v = key[i];

	//	log_always("getKey(size: " + to_string(size) + ", i: " + to_string(i) + ", v: " + to_string(v) + ")");

		return v;
	}

	void encryptionBin(string targetFile, string newFile, string key)
	{
		size_t size = key.length();

		ofstream nFile;
		nFile.open(newFile, ios::binary | ofstream::out);

		ifstream file(targetFile, ios::binary);
		char byte;
		size_t i = 0;
		while (file.read(&byte, sizeof(byte)))
		{
			char b_k = byte ^ getKey(key, i, size);
			nFile.write(reinterpret_cast<char*>(&b_k), sizeof(char));
			i++;
		}
		file.close();

		nFile.close();
	}

	void encryptionBin(string targetFile, string newFile, string key, size_t byteNum)
	{
		size_t size = key.length();

		ofstream nFile;
		nFile.open(newFile, ios::binary | ofstream::out);

		ifstream file(targetFile, ios::binary);
		char byte;
		size_t i = 0;
		size_t _byteNum = 0;
		while (file.read(&byte, sizeof(byte)))
		{
			if (_byteNum <= byteNum)
			{
				char b_k = byte ^ getKey(key, i, size);
				nFile.write(reinterpret_cast<char*>(&b_k), sizeof(char));
			}
			else
			{
				nFile.write(reinterpret_cast<char*>(&byte), sizeof(char));
			}
			i++;
			_byteNum++;
		}
		file.close();

		nFile.close();
	}
	/////////////////////////////////////////////////////////////////////////////////
	uint32_t checksum(std::ifstream& file)
	{
		uint32_t sum = 0;

		uint32_t word = 0;
		while (file.read(reinterpret_cast<char*>(&word), sizeof(word))) {
			sum += word;
			word = 0;
		}

		sum += word;

		return sum;
	}

	void getFilesSum()
	{
		string fileName = "";
		const char* mod = helper_functions::getModPatchName();
		if (mod && mod[0] && strcmp(mod, ".") != 0)
		{
			fileName += string(mod) + "\\";
		}

		for (int f = 0; f < sumFile.fileNum; f++)
		{
			string fName = fileName + "data\\" + sumFile.files[f];

			if (!fileExists(fName))
			{
				fName = "data\\" + sumFile.files[f];
			}

			struct stat fileStat;
			if (stat(fName.c_str(), &fileStat) == 0)
			{
				ifstream file(fName);
				sumFile.sum[f]      = checksum(file);
				sumFile.fileStat[f] = fileStat;
				file.close();
			}
			else
			{
				sumFile.sum[f] = 0;
			}

			sumFile.sumAll += sumFile.sum[f];

		#if _DEBUG
			LOG_ALWAYS(RELEASE, "getFilesSum(f: " + to_string(f) + ", sumFile.sum[f]: " + to_string(sumFile.sum[f]) + ", sumFile.files[f]: " + sumFile.files[f] + ", fName: " + fName + ", sumFile.sumAll: " + to_string(sumFile.sumAll) + ")");
		#endif
		}
	}

	void updateAllSum()
	{
		sumFile.sumAll = 0;

		for (size_t f = 0; f < sumFile.show_me.size(); f++)
		{
			string fileName = sumFile.show_me[f];
			ifstream file(fileName);

			uint32_t sum = encryption::checksum(file);
			sumFile.show_me_sum[f] = sum;
			sumFile.sumAll += sum;

		#if _DEBUG
			LOG_ALWAYS(RELEASE, "getFilesSum(f: " + to_string(f) + ", sum: " + to_string(sum) + ", fileName: " + fileName + ", sumFile.sumAll: " + to_string(sumFile.sumAll) + ")");
		#endif
		}

		getFilesSum();
	}




	/////////////////////////////////////////////////////////////////////////////////
}




















