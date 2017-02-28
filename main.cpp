  #include<stdio.h>
  #include<stdlib.h>
  #include<fstream>
  #include<iostream>
  #include<vector>
  #include <bitset>
  #include <iomanip>


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
void rom_size(int *tam,ifstream *rom){ // get the line numbers of file
    (*rom).seekg(0,(*rom).end);
    *tam = (*rom).tellg();
    *tam = *tam/(16*(sizeof(uint8_t)));
    (*rom).seekg(0,(*rom).beg);

}
#include<stdio.h>
  #include<stdlib.h>
  #include<fstream>
  #include<iostream>
  #include<vector>
  #include <bitset>
  #include <iomanip>

using namespace std;
/*
 This modifications are to simplify the implementations of instructions set
  ADDRESSING MODES CODIFICATIONS
  0 - IMMEDIATE
  1 - ZERO PAGE
  2 - ZERO PAGE,X
  3 - ABSOLUTE
  4 - ABSOLUTE,X
  5 - ABSOLUTE,Y
  6 - INDIRECT,X
  7 - INDIRECT,Y
*/
void adc_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){  // perform the operation between acummulator with immediate value
   (*PC)++;
   switch(type){
       case 0:
           for(int i = 0;i<2;i++){ // two cycles for this operation
             *A = (*A) + (memory_map[(*PC)]);
             if (*A > 0xFF){ // carry
                 *P = *P | 0x01;
             }
             else{
                *P = *P & 0xFE;
             }
           }
              break;
       case 1:
           for(int i = 0;i<3;i++){ // three cycles for this operation
             *A = (*A) + (memory_map[(*PC)]);
             if (*A > 0xFF){ // carry
                 *P = *P | 0x01;
             }
             else{
                *P = *P & 0xFE;
             }
           }
              break;
       case 2:
             for(int i = 0;i<4;i++){ // four cycles for this operation
             *A = (*A) + (memory_map[(*PC) + (*X)]);
             if (*A > 0xFF){ // carry
                 *P = *P | 0x01;
             }
             else{
                *P = *P & 0xFE;
             }
           }
              break;
       case 3:
        uint8_t b1,b2;
             uint16_t b3;
             b1 = memory_map[(*PC)];
             (*PC)++;
             b2 = memory_map[(*PC)];
             b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
             *A = (*A) + (memory_map[(b1)]);
        for(int i = 0;i<4;i++){ // four cycles for this operation
             if (*A > 0xFF){ // carry
                 *P = *P | 0x01;
             }
             else{
                *P = *P & 0xFE;
             }
           }
              break;
       case 4:
            for(int i = 0;i<4;i++){ // four cycles for this operation + 1 if page crossed
             uint8_t b1,b2;
             uint16_t b3;
             b1 = memory_map[(*PC)];
             (*PC)++;
             b2 = memory_map[(*PC)];
             b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
             *A = (*A) + (memory_map[(b1)+(*X)]);
             if (*A > 0xFF){ // carry
                 *P = *P | 0x01;
             }
             else{
                *P = *P & 0xFE;
             }
           }
              break;
       case 5:
        for(int i = 0;i<5;i++){ // four cycles for this operation + 1 if page crossed
             uint8_t b1,b2;
             uint16_t b3;
             b1 = memory_map[(*PC)];
             (*PC)++;
             b2 = memory_map[(*PC)];
             b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
             *A = (*A) + (memory_map[(b1)+(*Y)]);
             if (*A > 0xFF){ // carry
                 *P = *P | 0x01;
             }
             else{
                *P = *P & 0xFE;
             }
           }
              break;
       case 6:
           for(int i = 0;i<6;i++){ // six cycles for this operation
             uint8_t b1,b2;
             uint16_t b3;
             *A = (*A) + (memory_map[(*PC)+(*X)]);
             if (*A > 0xFF){ // carry
                 *P = *P | 0x01;
             }
             else{
                *P = *P & 0xFE;
             }
           }
              break;
       case 7:
        for(int i = 0;i<5;i++){ // six cycles for this operation + 1 if page crossed
             uint8_t b1,b2;
             uint16_t b3;
             *A = (*A) + (memory_map[(*PC)+(*Y)]);
             if (*A > 0xFF){ // carry
                 *P = *P | 0x01;
             }
             else{
                *P = *P & 0xFE;
             }
           }
              break;
   }


}
void and_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){  // perform the operation between acummulator with immediate value
   (*PC)++;
   switch(type){
       case 0:
           for(int i = 0;i<2;i++){ // two cycles for this operation
             *A = (*A) & (memory_map[(*PC)]);
             if (*A <= 0x00){ // zero
                    if(*A == 0x00){
                      *P = *P | 0x02;
                    } else if(*A < 0x00){ //negative flag
                         *P = *P | 0x80;

                    }
             }
             else{
                *P = *P & 0x7D;

             }
           }
              break;
       case 1:
           for(int i = 0;i<3;i++){ // three cycles for this operation
             *A = (*A) & (memory_map[(*PC)]);
                 if (*A <= 0x00){ // zero
                    if(*A == 0x00){
                      *P = *P | 0x02;
                    } else if(*A < 0x00){ //negative flag
                         *P = *P | 0x80;

                    }
             }
             else{
                *P = *P & 0x7D;

             }
           }
              break;
       case 2:
             for(int i = 0;i<4;i++){ // four cycles for this operation
             *A = (*A) & (memory_map[(*PC) + (*X)]);
                 if (*A <= 0x00){ // zero
                    if(*A == 0x00){
                      *P = *P | 0x02;
                    } else if(*A < 0x00){ //negative flag
                         *P = *P | 0x80;

                    }
             }
             else{
                *P = *P & 0x7D;

             }
           }
              break;
       case 3:
        for(int i = 0;i<4;i++){ // four cycles for this operation
             uint8_t b1,b2;
             uint16_t b3;
             b1 = memory_map[(*PC)];
             (*PC)++;
             b2 = memory_map[(*PC)];
             b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
             *A = (*A) & (memory_map[(b1)]);
                   if (*A <= 0x00){ // zero
                    if(*A == 0x00){
                      *P = *P | 0x02;
                    } else if(*A < 0x00){ //negative flag
                         *P = *P | 0x80;

                    }
             }
             else{
                *P = *P & 0x7D;

             }
           }
              break;
       case 4:
            for(int i = 0;i<4;i++){ // four cycles for this operation + 1 if page crossed
             uint8_t b1,b2;
             uint16_t b3;
             b1 = memory_map[(*PC)];
             (*PC)++;
             b2 = memory_map[(*PC)];
             b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
             *A = (*A) & (memory_map[(b1)+(*X)]);
                  if (*A <= 0x00){ // zero
                    if(*A == 0x00){
                      *P = *P | 0x02;
                    } else if(*A < 0x00){ //negative flag
                         *P = *P | 0x80;

                    }
             }
             else{
                *P = *P & 0x7D;

             }
           }
              break;
       case 5:
        for(int i = 0;i<5;i++){ // four cycles for this operation + 1 if page crossed
             uint8_t b1,b2;
             uint16_t b3;
             b1 = memory_map[(*PC)];
             (*PC)++;
             b2 = memory_map[(*PC)];
             b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
             *A = (*A) & (memory_map[(b1)+(*Y)]);
                  if (*A <= 0x00){ // zero
                    if(*A == 0x00){
                      *P = *P | 0x02;
                    } else if(*A < 0x00){ //negative flag
                         *P = *P | 0x80;

                    }
             }
             else{
                *P = *P & 0x7D;

             }
           }
              break;
       case 6:
           for(int i = 0;i<6;i++){ // six cycles for this operation
             uint8_t b1,b2;
             uint16_t b3;
             *A = (*A) & (memory_map[(*PC)+(*X)]);
                  if (*A <= 0x00){ // zero
                    if(*A == 0x00){
                      *P = *P | 0x02;
                    } else if(*A < 0x00){ //negative flag
                         *P = *P | 0x80;

                    }
             }
             else{
                *P = *P & 0x7D;

             }
           }
              break;
       case 7:
        for(int i = 0;i<5;i++){ // six cycles for this operation + 1 if page crossed
             uint8_t b1,b2;
             uint16_t b3;
             *A = (*A) & (memory_map[(*PC)+(*Y)]);
                   if (*A <= 0x00){ // zero
                    if(*A == 0x00){
                      *P = *P | 0x02;
                    } else if(*A < 0x00){ //negative flag
                         *P = *P | 0x80;

                    }
             }
             else{
                *P = *P & 0x7D;

             }
           }
              break;
   }


}
void asl_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
    switch(type){
       case 0:
           for(int i = 0;i<2;i++){ // two cycles for this operation
             *A = (*A) << 1;
             if (*A <= 0x00){ // zero
                    if(*A == 0x00){
                      *P = *P | 0x02;
                      *P = *P & 0xFE;
                    } else if(*A < 0x00){ //negative flag
                         *P = *P | 0x80;
                         *P = *P & 0xFE;

                    }
                  }
              else if (*A>0xFF){ //carry
                   *P = *P | 0x01;
                   *P = *P & 0x7D;
              }

       }
       break;
       case 1:
             for(int i = 0;i<5;i++){ // three cycles for this operation
             *A = (memory_map[(*PC)]) << 1;
                 if (*A <= 0x00){ // zero
                    if(*A == 0x00){
                      *P = *P | 0x02;
                      *P = *P & 0xFE;
                    } else if(*A < 0x00){ //negative flag
                         *P = *P | 0x80;
                         *P = *P & 0xFE;

                    }
                  }
              else if (*A>0xFF){ //carry
                   *P = *P | 0x01;
                   *P = *P & 0x7D;
              }
           }
              break;
       case 2:
            for(int i = 0;i<6;i++){ // four cycles for this operation
             *A = (memory_map[(*PC) + (*X)]) << 1;
                if (*A <= 0x00){ // zero
                    if(*A == 0x00){
                      *P = *P | 0x02;
                      *P = *P & 0xFE;
                    } else if(*A < 0x00){ //negative flag
                         *P = *P | 0x80;
                         *P = *P & 0xFE;

                    }
                  }
              else if (*A>0xFF){ //carry
                   *P = *P | 0x01;
                   *P = *P & 0x7D;
              }
           }
              break;
       case 3:
         for(int i = 0;i<6;i++){ // four cycles for this operation
             uint8_t b1,b2;
             uint16_t b3;
             b1 = memory_map[(*PC)];
             (*PC)++;
             b2 = memory_map[(*PC)];
             b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
             *A = (memory_map[(b1)]) << 1;
                   if (*A <= 0x00){ // zero
                    if(*A == 0x00){
                      *P = *P | 0x02;
                      *P = *P & 0xFE;
                    } else if(*A < 0x00){ //negative flag
                         *P = *P | 0x80;
                         *P = *P & 0xFE;

                    }
                  }
              else if (*A>0xFF){ //carry
                   *P = *P | 0x01;
                   *P = *P & 0x7D;
              }
           }
              break;
       case 4:
         for(int i = 0;i<6;i++){ // four cycles for this operation + 1 if page crossed
             uint8_t b1,b2;
             uint16_t b3;
             b1 = memory_map[(*PC)];
             (*PC)++;
             b2 = memory_map[(*PC)];
             b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
             *A = (memory_map[(b1)+(*Y)])<<1;
                   if (*A <= 0x00){ // zero
                    if(*A == 0x00){
                      *P = *P | 0x02;
                      *P = *P & 0xFE;
                    } else if(*A < 0x00){ //negative flag
                         *P = *P | 0x80;
                         *P = *P & 0xFE;

                    }
                  }
              else if (*A>0xFF){ //carry
                   *P = *P | 0x01;
                   *P = *P & 0x7D;
              }
           }
              break;
       default:
           cout <<"erro"<<endl;
}
}
void bcc_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
  uint8_t b1,b2;
  uint16_t b3;
  b1 = memory_map[(*PC)];
  (*PC)++;
  b2 = memory_map[(*PC)];
  b3 = (b2 << 8) | b1;
  for (int i =0;i<2;i++){ //
  if ((*P & 0x01) == 0x00){
      *PC = b3;
  }else{
   (*PC)++;
  }

}
  }
void bcs_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
  uint8_t b1,b2;
  uint16_t b3;
  b1 = memory_map[(*PC)];
  (*PC)++;
  b2 = memory_map[(*PC)];
  b3 = (b2 << 8) | b1;
  for (int i =0;i<2;i++){
  if ((*P & 0x01) == 0x01){
      *PC = b3;
  }else{
   (*PC)++;
  }
}
}
void beq_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
  uint8_t b1 = memory_map[(*PC)];
  for (int i =0;i<2;i++){
  if ((*P & 0x02) == 0x02){
      *PC = b1;
  }else{
   (*PC)++;
  }
}
}
void bit_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
    *P = *P | ((memory_map[(*PC)])& 0x80)>>7; // N-> M7
    *P = *P | ((memory_map[(*PC)])& 0x40)>>6; // V-> M6
    for (int i =0;i<2;i++){
          if ((*A & memory_map[(*PC)]) == 0x00){
    *P = *P | 0x02;
  }else{
    *P = *P & 0xFD;
  }
    }
}
void bmi_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
     uint8_t b1 = memory_map[(*PC)];
     for(int i = 0;i<2;i++){
   if (((*P & 0x80)>>7) == 1){
     *PC = b1;
  }else{
   *PC++;
  }
     }
}
void bne_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
uint8_t b1 = memory_map[(*PC)];
     for(int i = 0;i<2;i++){
   if (((*P & 0x02)>>1) == 0){
     *PC = b1;
  }else{
   *PC++;
  }
     }
}
void bpl_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
  uint8_t b1 = memory_map[(*PC)];
     for(int i = 0;i<2;i++){
   if (((*P & 0x80)>>7) == 0){
     *PC = b1;
  }else{
   *PC++;
  }
     }
}
void brk_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
    for(int i =0;i<7;i++){
    if(((*P & 0x04)>>3)== 1){
    // set flag to exit processor
  }else{
   // dont exit processor
  }

    }

}
void bvc_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
  uint8_t b1 = memory_map[(*PC)];
  for(int i =0;i<2;i++){
    if(((*P & 0x40)>>6)== 0){
      *PC = b1;
  }else{
    (*PC)++;
  }
  }
}
void bvs_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
  uint8_t b1 = memory_map[(*PC)];
  for(int i =0;i<2;i++){
    if(((*P & 0x40)>>6)== 1){
      *PC = b1;
  }else{
    (*PC)++;
  }
  }
}
void clc_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
  for (int i =0;i<2;i++){
      *P = *P & 0xFE;
  }
}
void cld_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
   for (int i =0;i<2;i++){
      *P = *P & 0xF7;
  }
}
void cli_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
   for (int i =0;i<2;i++){
      *P = *P & 0xFB;
  }
}
void clv_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
   for (int i =0;i<2;i++){
      *P = *P & 0xBF;
  }
}
void cmp_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
    uint8_t b1,b2;
             uint16_t b3;
             (*PC)++;
   switch(type){
             case 0:
           for(int i = 0;i<2;i++){ // two cycles for this operation
               if(*A == memory_map[*PC]){
                  *P = *P | (0x02); //zero
                  *P = *P & (0x7F); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A < memory_map[*PC]){
                  *P = *P & 0xFD;   //zero
                  *P = *P | (0x80); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A > memory_map[*PC]){
                  *P = *P & 0xFD;   //zero
                  *P = *P & (0x7F); // negative
                  *P = *P | (0x40); // overflow
               }
            }
         break;
    case 1:
            for(int i = 0;i<3;i++){ // three cycles for this operation
               if(*A == memory_map[*PC]){
                  *P = *P | (0x02); //zero
                  *P = *P & (0x7F); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A < memory_map[*PC]){
                  *P = *P & 0xFD;   //zero
                  *P = *P | (0x80); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A > memory_map[*PC]){
                  *P = *P & 0xFD;   //zero
                  *P = *P & (0x7F); // negative
                  *P = *P | (0x40); // overflow
               }
            }
        break;
    case 2:
    for(int i = 0;i<4;i++){ // four cycles for this operation
               if(*A == memory_map[(*PC)+(*X)]){
                  *P = *P | (0x02); //zero
                  *P = *P & (0x7F); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A < memory_map[(*PC)+(*X)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P | (0x80); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A > memory_map[(*PC)+(*X)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P & (0x7F); // negative
                  *P = *P | (0x40); // overflow
               }
            }
        break;
        case 3:
             b1 = memory_map[(*PC)];
             (*PC)++;
             b2 = memory_map[(*PC)];
             b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
        for(int i = 0;i<4;i++){ // four cycles for this operation
               if(*A == memory_map[b3]){
                  *P = *P | (0x02); //zero
                  *P = *P & (0x7F); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A < memory_map[b3]){
                  *P = *P & 0xFD;   //zero
                  *P = *P | (0x80); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A > memory_map[b3]){
                  *P = *P & 0xFD;   //zero
                  *P = *P & (0x7F); // negative
                  *P = *P | (0x40); // overflow
               }
            }
         break;
         case 4:
             b1 = memory_map[(*PC)];
             (*PC)++;
             b2 = memory_map[(*PC)];
             b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
          for(int i = 0;i<4;i++){ // four cycles for this operation + 1 if page crossed
               if(*A == memory_map[b3+(*X)]){
                  *P = *P | (0x02); //zero
                  *P = *P & (0x7F); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A < memory_map[b3+(*X)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P | (0x80); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A > memory_map[b3+(*X)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P & (0x7F); // negative
                  *P = *P | (0x40); // overflow
               }
            }
            break;
        case 5:
             b1 = memory_map[(*PC)];
             (*PC)++;
             b2 = memory_map[(*PC)];
             b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
         for(int i = 0;i<4;i++){ // four cycles for this operation + 1 if page crossed
               if(*A == memory_map[b3+(*Y)]){
                  *P = *P | (0x02); //zero
                  *P = *P & (0x7F); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A < memory_map[b3+(*Y)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P | (0x80); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A > memory_map[b3+(*Y)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P & (0x7F); // negative
                  *P = *P | (0x40); // overflow
               }
            }
            break;
        case 6:
             for(int i = 0;i<6;i++){ // six cycles for this operation
               if(*A == memory_map[(*PC)+(*X)]){
                  *P = *P | (0x02); //zero
                  *P = *P & (0x7F); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A < memory_map[(*PC)+(*X)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P | (0x80); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A > memory_map[(*PC)+(*X)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P & (0x7F); // negative
                  *P = *P | (0x40); // overflow
               }
            }
            break;
         case 7:
               for(int i = 0;i<5;i++){ // five cycles for this operation + 1 if page crossed
               if(*A == memory_map[(*PC)+(*Y)]){
                  *P = *P | (0x02); //zero
                  *P = *P & (0x7F); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A < memory_map[(*PC)+(*Y)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P | (0x80); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*A > memory_map[(*PC)+(*Y)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P & (0x7F); // negative
                  *P = *P | (0x40); // overflow
               }
            }
            break;
          }
        }
void cpx_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
  switch(type){
    case 0:
       for(int i = 0;i<2;i++){ // two cycles for this operation
               if(*X == memory_map[(*PC)]){
                  *P = *P | (0x02); //zero
                  *P = *P & (0x7F); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*X < memory_map[(*PC)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P | (0x80); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*X > memory_map[(*PC)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P & (0x7F); // negative
                  *P = *P | (0x40); // overflow
               }
            }
            break;
     case 1:
  for(int i = 0;i<3;i++){ // three cycles for this operation
               if(*X == memory_map[(*PC)]){
                  *P = *P | (0x02); //zero
                  *P = *P & (0x7F); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*X < memory_map[(*PC)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P | (0x80); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*X > memory_map[(*PC)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P & (0x7F); // negative
                  *P = *P | (0x40); // overflow
               }
            }
            break;
     case 3:
             uint8_t b1,b2;
             uint16_t b3;
             b1 = memory_map[(*PC)];
             (*PC)++;
             b2 = memory_map[(*PC)];
             b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
  for(int i = 0;i<4;i++){ // four cycles for this operation
               if(*X == memory_map[b3]){
                  *P = *P | (0x02); //zero
                  *P = *P & (0x7F); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*X < memory_map[b3]){
                  *P = *P & 0xFD;   //zero
                  *P = *P | (0x80); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*X > memory_map[b3]){
                  *P = *P & 0xFD;   //zero
                  *P = *P & (0x7F); // negative
                  *P = *P | (0x40); // overflow
               }
            }
            break;

  }

}
void cpy_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
   switch(type){
    case 0:
       for(int i = 0;i<2;i++){ // two cycles for this operation
               if(*X == memory_map[(*PC)]){
                  *P = *P | (0x02); //zero
                  *P = *P & (0x7F); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*X < memory_map[(*PC)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P | (0x80); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*X > memory_map[(*PC)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P & (0x7F); // negative
                  *P = *P | (0x40); // overflow
               }
            }
            break;
     case 1:
  for(int i = 0;i<3;i++){ // three cycles for this operation
               if(*X == memory_map[(*PC)]){
                  *P = *P | (0x02); //zero
                  *P = *P & (0x7F); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*X < memory_map[(*PC)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P | (0x80); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*X > memory_map[(*PC)]){
                  *P = *P & 0xFD;   //zero
                  *P = *P & (0x7F); // negative
                  *P = *P | (0x40); // overflow
               }
            }
            break;
     case 3:
             uint8_t b1,b2;
             uint16_t b3;
             b1 = memory_map[(*PC)];
             (*PC)++;
             b2 = memory_map[(*PC)];
             b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
  for(int i = 0;i<4;i++){ // four cycles for this operation
               if(*X == memory_map[b3]){
                  *P = *P | (0x02); //zero
                  *P = *P & (0x7F); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*X < memory_map[b3]){
                  *P = *P & 0xFD;   //zero
                  *P = *P | (0x80); // negative
                  *P = *P & (0xBF); // overflow
               }else if(*X > memory_map[b3]){
                  *P = *P & 0xFD;   //zero
                  *P = *P & (0x7F); // negative
                  *P = *P | (0x40); // overflow
               }
            }
            break;

  }

}
void dec_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
    uint8_t b1,b2;
    uint16_t b3;
  switch(type){
    case 1:
      memory_map[*PC]--;
    for(int i = 0; i< 5;i++){
          if (memory_map[*PC] == 0){
                    *P = *P | 0x02;
                    *P = *P & 0x7F;
          }else if(memory_map[*PC] < 0){
                   *P = *P | 0x80;
                   *P = *P & 0xFD;
          }
         }
          break;
           case 2:
            memory_map[(*PC)+(*X)]--;
            for(int i = 0; i< 6;i++){
          if (memory_map[(*PC)+(*X)] == 0){
                    *P = *P | 0x02;
                    *P = *P & 0x7F;
          }else if(memory_map[(*PC)+(*X)] < 0){
                   *P = *P | 0x80;
                   *P = *P & 0xFD;
          }
        }
          break;
          case 3:
             b1 = memory_map[(*PC)];
             (*PC)++;
             b2 = memory_map[(*PC)];
             b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
            memory_map[b3]--;
            for(int i = 0; i< 6;i++){
          if (memory_map[b3+(*X)] == 0){
                    *P = *P | 0x02;
                    *P = *P & 0x7F;
          }else if(memory_map[b3+(*X)] < 0){
                   *P = *P | 0x80;
                   *P = *P & 0xFD;
          }
        }
          break;
          case 4:
             b1 = memory_map[(*PC)];
             (*PC)++;
             b2 = memory_map[(*PC)];
             b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
             memory_map[b3+(*X)]--;
            for(int i = 0; i< 7;i++){
          if (memory_map[b3+(*X)] == 0){
                    *P = *P | 0x02;
                    *P = *P & 0x7F;
          }else if(memory_map[b3+(*X)] < 0){
                   *P = *P | 0x80;
                   *P = *P & 0xFD;
          }
        }
          break;
          }

  }
void dex_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
  (*X)--;
  for(int i =0; i<2;i++){
    if (*X == 0){
                    *P = *P | 0x02;
                    *P = *P & 0x7F;
          }else if(*X < 0){
                   *P = *P | 0x80;
                   *P = *P & 0xFD;
          }
  }
}
void dey_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
  (*Y)--;
  for(int i =0; i<2;i++){
    if (*Y == 0){
                    *P = *P | 0x02;
                    *P = *P & 0x7F;
          }else if(*Y < 0){
                   *P = *P | 0x80;
                   *P = *P & 0xFD;
          }
  }
}
void eor_op(uint8_t *A,uint16_t *memory_map,uint16_t *PC,int type,int *P,uint8_t *X,uint8_t *Y){
       uint8_t b1,b2;
     uint16_t b3;
 switch(type){
  case 0:
   *A = (*A) ^ memory_map[*PC];
   for(int i =0;i<2;i++){
    if (*A == 0x00){
         *P = *P | 0x02;
         *P = *P & 0x7F;
   }else if(*A < 0x00){
         *P = *P | 0x80;
         *P = *P & 0x7D;
   }
   }
   break;
   case 1:
       *A = (*A) ^ memory_map[*PC];
       for(int i =0;i<3;i++){
        if (*A == 0x00){
         *P = *P | 0x02;
         *P = *P & 0x7F;
   }else if(*A < 0x00){
         *P = *P | 0x80;
         *P = *P & 0x7D;
          }
       }
   break;
   case 2:
     *A = (*A) ^ memory_map[(*PC)+(*X)];
      for(int i =0;i<4;i++){
   if (*A == 0x00){
         *P = *P | 0x02;
         *P = *P & 0x7F;
   }else if(*A < 0x00){
         *P = *P | 0x80;
         *P = *P & 0x7D;
   }
 }
   break;
      case 3:
     b1 = memory_map[(*PC)];
     (*PC)++;
     b2 = memory_map[(*PC)];
     b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
     *A = (*A) ^ memory_map[b3];
      for(int i =0;i<4;i++){
   if (*A == 0x00){
         *P = *P | 0x02;
         *P = *P & 0x7F;
   }else if(*A < 0x00){
         *P = *P | 0x80;
         *P = *P & 0x7D;
   }
 }
   break;
   case 4:
     b1 = memory_map[(*PC)+(*X)];
     (*PC)++;
     b2 = memory_map[(*PC)+(*X)];
     b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
     *A = (*A) ^ memory_map[b3];
   if (*A == 0x00){
         *P = *P | 0x02;
         *P = *P & 0x7F;
   }else if(*A < 0x00){
         *P = *P | 0x80;
         *P = *P & 0x7D;
   }
    break;
    case 5:
     b1 = memory_map[(*PC)+(*Y)];
     (*PC)++;
     b2 = memory_map[(*PC)+(*Y)];
     b3 = (b2 << 8) | b1; // 2bytes b2b1 little endian
     *A = (*A) ^ memory_map[b3];
     for(int i =0;i<4;i++){ // + 1 cycle if page boundary crossed
         if (*A == 0x00){
         *P = *P | 0x02;
         *P = *P & 0x7F;
   }else if(*A < 0x00){
         *P = *P | 0x80;
         *P = *P & 0x7D;
   }
     }
    break;
    case 6:
      *A = (*A) ^ memory_map[(*PC)+(*X)];
      for(int i =0;i<6;i++){
   if (*A == 0x00){
         *P = *P | 0x02;
         *P = *P & 0x7F;
   }else if(*A < 0x00){
         *P = *P | 0x80;
         *P = *P & 0x7D;
   }
 }
   break;
   case 7:
     *A = (*A) ^ memory_map[(*PC)+(*Y)];
      for(int i =0;i<5;i++){ // +1 if boundary crossed
   if (*A == 0x00){
         *P = *P | 0x02;
         *P = *P & 0x7F;
   }else if(*A < 0x00){
         *P = *P | 0x80;
         *P = *P & 0x7D;
   }
 }
   break;
 }
}
void inc_op(){
  
}
void rom_size(int *tam,ifstream *rom){ // get the line numbers of file
    (*rom).seekg(0,(*rom).end);
    *tam = (*rom).tellg();
    *tam = *tam/(16*(sizeof(uint8_t)));
    (*rom).seekg(0,(*rom).beg);

}
void imprime_hexa(int tamanho,uint16_t valor){
 cout<<"mem = "<<hex<<setw(tamanho)<<setfill('0')<<uppercase<<"0x"<<valor<<" "<<endl;

}
int main(int argc, char* argv[])
{
    uint8_t SP,A,X,Y,P,bin,opcode;
    uint16_t PC,memory_map[0xFFFF+1],reset,linha = 0xC000;
    bitset<8> PRG_size_ROM,CHR_size_ROM,CHR_size_RAM,Flag_six,Flag_seven,Flag_nine,Flag_ten; // 16kb units,8kb units, if zero uses CHR RAM of 8 kb units.
    ifstream rom;
    int i =1,j=0,tam;
    rom.open("nestest.nes", ios::binary | ios::in);
    rom_size(&tam,&rom);
    bitset<8> MEM[tam][16] = {0};

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
      i = 1;
    while(!(rom.eof())){ // reading byte by byte, fill the remaining data on MEM
        for(j = 0;j<0x10;j++){
          rom >> noskipws>> bin;
          bitset<8> a(bin);
          MEM[i][j] = a.to_ulong();
        }
        i++;

    }
    for(i = 1;i<(PRG_size_ROM.to_ulong() * (1024));i++){ // copy of PRG data to unit of size 16kb to last memory map
      for(j =0;j<0x10;j++){
        memory_map[linha] = MEM[i][j].to_ulong();
        linha++;
      }
      linha++;
      }
      reset = (memory_map[0xFFFD] << 8) | memory_map[0xFFFC]; // first instruction of file (little endian)
    rom.close();
    return 0;
}
