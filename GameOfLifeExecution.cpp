#include "GameOfLifeExecution.h"

/*
---------------Game of Life Code---------------
 The cells are updated byte by byte. The previous and current
 bytes are kept track of to save on space. 
 
 */

void stepOfLife(byte * cell_Array) {
  int k, kminor;
  byte mask, val, left, right, pc, j;
  byte prevLineConfig[LCD_Y / 8];
  byte updateLineConfig[LCD_Y / 8];
  byte sumTotal[8];
  int i;
  for (i = 0; i < LCD_Y / 8; i++)
    prevLineConfig[i] = 0;

  for (i = 0; i < LCD_X; i++) {
    kminor = -1;

    for (j = 0; j < LCD_Y / 8; j++) {
      updateLineConfig[j] = cell_Array[i + j * LCD_X];
    }

    for (k = 0; k < LCD_X * LCD_Y / 8; k += LCD_X) {

      kminor++;

      mask = 0x01;
      val = cell_Array[i + k];
      left = 0;
      right = 0;

      left = prevLineConfig[kminor];

      if (i != (LCD_X - 1))
        right = cell_Array[i + k + 1];
      else
        right = 0;

      for (j = 0; j < 8; j++)
        sumTotal[j] = 0;

      if (k != 0) {
        if ((cell_Array[i + k - 84] & 0x80) == 0x80)
          sumTotal[0]++;
        if (i != (LCD_X - 1))
          if ((cell_Array[i + k - 83] & 0x80) == 0x80)
            sumTotal[0]++;

        if ((prevLineConfig[kminor - 1] & 0x80) == 0x80)
          sumTotal[0]++;
      }

      if (kminor != (LCD_Y / 8 - 1)) {
        if ((cell_Array[i + k + 84] & 0x01) == 0x01)
          sumTotal[7]++;
        if (i != (LCD_X - 1))
          if ((cell_Array[i + k + 85] & 0x01) == 0x01)
            sumTotal[7]++;

        if ((prevLineConfig[kminor + 1] & 0x01) == 0x01)
          sumTotal[7]++;
      }

      for (j = 0; j < 8; j++) {
        pc = 0;
        if ((left & mask) == mask)
          pc++;
        if ((right & mask) == mask)
          pc++;
        sumTotal[j] += pc;
        if (j > 0)
          sumTotal[j - 1] += pc;
        if (j < 7)
          sumTotal[j + 1] += pc;

        if ((val & mask) == mask) {
          if (j > 0)
            sumTotal[j - 1]++;
          if (j < 7)
            sumTotal[j + 1]++;
        }

        mask = mask << 1;
      }

      mask = 0x01;
      for (j = 0; j < 8; j++) {

        if (sumTotal[j] == 3)
          updateLineConfig[kminor] |= mask;

        else if (sumTotal[j] == 2)
          updateLineConfig[kminor] = updateLineConfig[kminor];

        else
          updateLineConfig[kminor] &= (~mask);

        mask = mask << 1;

      }
    }

    for (j = 0; j < LCD_Y / 8; j++) {
      prevLineConfig[j] = cell_Array[i + j * LCD_X];
      cell_Array[i + j * LCD_X] = updateLineConfig[j];
    }

  }
}


