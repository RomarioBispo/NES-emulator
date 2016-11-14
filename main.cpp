
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
int main(int argc, char* argv[])
{
    vector<uint32_t> MEM[8]; // main memory defined by 24 bits
    uint16_t PC; // the program counter, your responsability is keep the flow control
    uint8_t SP; // the stack pointer, keep pointer to the stack execution
    uint8_t A; // the acumulator registrer, store results of arithmetic and logic operations
    uint8_t X,Y; // index of register; 1 byte for each one  (op op | xx xx | yy yy)
    uint8_t P; // processor status last operation, flag of 1 bit
    uint8_t opcode; // the first byte is the opcode
    uint8_t bin;
    ifstream rom;
    rom.open("nestest.nes", ios::binary | ios::in);
    if (!rom.is_open()){
          cout<<" nao foi possivel abrir o arquivo\n";
          return 0;
        }

    for(int i=0;i<0x10;i++) //get rid of header for now
    rom >>noskipws>> bin;
    while(!(rom.eof())) // reading byte by byte
    {
        rom >> noskipws>> bin;
        bitset<8> a(bin);
        cout << "bin " <<hex<< a.to_ulong() << endl;
        system("pause");

    }
    rom.close();
    return 0;
}
