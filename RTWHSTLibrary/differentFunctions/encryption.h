#pragma once
#include <string>
using namespace std;

struct sumFileS
{
	int         fileNum = 10;
	uint32_t    sumAll = 0;
	uint32_t    sum[10];
	struct stat fileStat[10];
	std::string files[10]
	{
		"descr_character.txt",
		"descr_cultures.txt",
		"descr_ship.txt",
		"descr_sm_resources.txt",
		"export_descr_ancillaries.txt",
		"export_descr_character_traits.txt",
		"export_descr_buildings.txt",
		"export_descr_unit.txt",
		"export_descr_advice.txt",
		"descr_sm_factions.txt"
	};
	std::vector<std::string> show_me;
	std::vector<uint32_t> show_me_sum;

	sumFileS() :
		fileNum(10),
		sumAll(0),
		sum(),
		fileStat(),
	//	files(),
		show_me(),
		show_me_sum()
	{
	};
};
extern sumFileS sumFile;

namespace encryption
{
	void encryptionString(string targetFile, string newFile, size_t key);
	void encryptionBin(string targetFile, string newFile, size_t key[], size_t size);
	void encryptionBin(string targetFile, string newFile, string key);
	void encryptionBin(string targetFile, string newFile, string key, size_t byteNum);
	uint32_t checksum(std::ifstream& file);
	void getFilesSum();
	void updateAllSum();
}




