  #include<stdio.h>
  #include<stdlib.h>
  #include<fstream>
  #include<iostream>
  #include<string>
  #include<vector>
  #include <iomanip>
  #include <stdint.h>
  #include<math.h>
  #include <fstream>
  #include <sstream>
#include <bitset>

using namespace std;
struct vtr{
   uint8_t v[16];
};
typedef struct vtr vetor;
/*    #define C  P[0]; // carry flag, underflow or overflow
    #define Z  P[1]; // zero  flag, result of any operation is zero
    #define I  P[2]; // interrupt disable flag, serve to mask any interruption, it's set by SEI instruction, and clear by CLI instruction
    #define D  P[3]; // decimal mode flag, switch to BCD, and BCD data will be ignorated
    #define B  P[4]; // break flag, break instruction has been executed
    #define V  P[6]; // the overflow flag, set by result of complement of two are invalid
    #define N  P[7]; // negative flag, represents the sign of that byte
     // bit 5 of P has unused
     */
/*
  The CPU has three components
  1 - the ROM(cartridge)
  2 - the CPU RAM ()
  3 - the IO registers()
  4 - the PPU control the devices
*/
 void memory_map(*uint16_t addr/*remaining memory*/){
   if((*addr) > 0x0 | (*addr)<=0x00FF){ //zero page
              
   }if((*addr) > 0x01FF | (*addr)<=0x01FF){
              
   }

 }
int main(int argc, char* argv[])
{
    //vector<vetor> MEM[16];
    uint16_t PC; // the program counter, your responsability is keep the flow control
    uint8_t SP; // the stack pointer, keep pointer to the stack execution
    uint8_t A; // the acumulator registrer, store results of arithmetic and logic operations
    uint8_t X,Y; // index of register; 1 byte for each one  (op op | xx xx | yy yy)
    uint8_t P; // processor status last operation, flag of 1 bit
    uint8_t opcode; // the first byte is the opcode
    uint8_t bin;
    uint16_t map_mem[65536]; // map memory address
    bitset<8> PRG_size_ROM,CHR_size_ROM,CHR_size_RAM,Flag_six,Flag_seven,Flag_nine,Flag_ten; // 16kb units,8kb units, if zero uses CHR RAM of 8 kb units.
    ifstream rom;
    int i,j=0,tam;
     int c = 0;
    rom.open("nestest.nes", ios::binary | ios::in);
    rom.seekg(0,rom.end);
    tam = rom.tellg(); // lenght in bytes
    tam = tam/(16*(sizeof(uint8_t))); //line numbers of file
    bitset<8> MEM[tam][16] = {0};
    rom.seekg(0,rom.beg);
    if (!rom.is_open()){
          cout<<" nao foi possivel abrir o arquivo\n";
          return 0;
        }
    for(i=0;i<0x10;i++){ //get rid of header for now
        rom >>noskipws>>std::hex>>bin;
        bitset<8> a(bin);
        MEM[0][i] = a.to_ulong(); // fill the header on MEM
      }
      PRG_size_ROM = MEM[0][4]; // reference on http://wiki.nesdev.com/w/index.php/INES
      CHR_size_ROM = MEM[0][5];
      Flag_six = MEM[0][6];
      Flag_seven = MEM[0][7];
      Flag_nine = MEM[0][9];
      Flag_ten = MEM[0][10]; // 11 to 15 bytes are filled with zero
      if(CHR_size_ROM == 0){
         CHR_size_RAM = MEM[0][8];
         cout<<"entrei"<<endl;
      }
    while(!(rom.eof())){ // reading byte by byte, fill the remaining data on MEM
        for(int i = 1;i<0x10;i++){
          rom >> noskipws>> bin;
          bitset<8> a(bin);
          MEM[i][j] = a.to_ulong();
         // cout << "bin " <<hex<< MEM[i][j].to_ulong()<< endl;
        }
        j++;

    }
    rom.close();
    return 0;
}
