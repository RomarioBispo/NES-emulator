#include <iostream>
#include <fstream>
#include <vector>

#include <iomanip>
#include <bitset>

#define C  P[0]; // carry
#define Z  P[1]; // zero
#define I  P[2]; // interrupt disable
#define D  P[3]; // decimal mode, não disponível no 02C0
#define B  P[4]; // break
#define V  P[6]; // overflow
#define N  P[7]; // negative

using namespace std;

struct vtr {
	uint8_t v[16];
};

typedef struct vtr vetor;
// Registers 
uint16_t PC;
uint8_t P, SP, A, X, Y;

uint32_t count_rom_lines() {
}

int main(int argc, char* argv[]) {
	uint16_t memory_map[0xFFFF + 1]; // all memory map
	uint8_t bin;
	uint16_t linha = 0xC000;
	bitset<8> PRG_size_ROM, CHR_size_ROM, CHR_size_RAM, Flag_six, Flag_seven, Flag_nine, Flag_ten; // 16kb units,8kb units, if zero uses CHR RAM of 8 kb units.
	ifstream rom;
	int i = 1, j = 0, tam;
	rom.open("nestest.nes", ios::binary | ios::in);
	rom.seekg(0, rom.beg);
	rom.seekg(0, rom.end);
	tam = rom.tellg(); // lenght in bytes
	tam = tam / (16 * (sizeof(uint8_t))); //line numbers of file
	bitset<8> MEM[tam][16] = {0};
	rom.seekg(0, rom.beg);
	if (!rom.is_open()) {
		cout << " nao foi possivel abrir o arquivo\n";
		return 0;
	}
	//get rid of header for now
	for (i = 0; i < 0x10; i++) {
		rom >> noskipws >> std::hex >> bin;
		bitset<8> a(bin);
		// fill the header on MEM
		MEM[0][i] = a.to_ulong();
	}
	PRG_size_ROM = MEM[0][4]; // reference on http://wiki.nesdev.com/w/index.php/INES
	//cout<<"PRG size = "<<(PRG_size_ROM.to_ulong() * 16)<<"kbytes"<<endl;
	CHR_size_ROM = MEM[0][5];
	// cout<<"CRH size = "<<(PRG_size_ROM.to_ulong() * 8)<<"kbytes"<<endl;
	Flag_six = MEM[0][6];
	// cout<<"Flag six = "<<Flag_six<<endl;
	Flag_seven = MEM[0][7];
	// cout<<"Flag seven = "<<Flag_six<<endl;
	Flag_nine = MEM[0][9];
	// cout<<"Flag nine = "<<Flag_six<<endl;
	Flag_ten = MEM[0][10]; // 11 to 15 bytes are filled with zero
	// cout<<"Flag ten = "<<Flag_six<<endl;
	if (CHR_size_ROM == 0) {
		CHR_size_RAM = MEM[0][8];
		cout << "entrei" << endl;
	}
	// reading byte by byte, fill the remaining data on MEM
	while (!(rom.eof())) { 
		for (j = 0; i < 0x10; i++) {
			rom >> noskipws >> bin;
			bitset<8> a(bin);
			MEM[i][j] = a.to_ulong();
			cout << "bin " << hex << MEM[i][j].to_ulong() << endl;
			system("pause");
		}
		i++;
	}
	// copy of PRG data to unit of size 16kb to last memory map
	for (i = 1; i < (PRG_size_ROM.to_ulong() * (1024)); i++) { 
		for (j = 0; j < 0x10; j++) {
			cout << "j = " << dec << j << endl;
			memory_map[linha] = MEM[i][j].to_ulong();
			cout << "MEM = " << hex << MEM[i][j].to_ulong() << endl;
			cout << "memory_map = " << hex << memory_map[linha] << endl;
			system("pause");
			linha++;
		}
	}

	// first instruction of file (little endian)
	auto reset = (memory_map[0xFFFD] << 8) | memory_map[0xFFFC];
	cout<<"reset = "<<reset<<endl;

	rom.close();
	return 0;
}
