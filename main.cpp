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
    vector<uint32_t> MEM; // main memory defined by 24 bits
    uint16_t PC; // the program counter, your responsability is keep the flow control
    uint8_t SP; // the stack pointer, keep pointer to the stack execution
    uint8_t A; // the acumulator registrer, store results of arithmetic and logic operations
    uint8_t X,Y; // index of register; 1 byte for each one  (op op | xx xx | yy yy)
    uint8_t P; // processor status last operation, flag of 1 bit
    uint8_t opcode; // the first byte is the opcode
    uint32_t i =0;
    streampos tam;
    char *memblock;
    //char buffer[255];
    ifstream rom;
    rom.open("legend of zelda.nes",ios::binary);
    if (!rom.is_open()){
          cout<<" nao foi possivel abrir o arquivo\n";
          return 0;
        }
    rom.seekg (0,ios::end);
    tam = rom.tellg(); // get length of file
    rom.seekg (0,ios::beg);
    cout<<"sz = "<< dec<<tam<<" bytes"<<endl;
    memblock = new char [tam]; // allocate memory
    rom.read (memblock, tam); // read all file
   // rom.getline(memblock,tam); // read line by line
   // std::stringstream iss( string( memblock ) ); // delete temporary buffer
    cout<<"mem block "<<memblock<<endl;
    delete [] memblock; // close filestream
   // cout << "WELCOME TO THE NES EMULATOR" << endl;
    rom.close();



    return 0;
}
