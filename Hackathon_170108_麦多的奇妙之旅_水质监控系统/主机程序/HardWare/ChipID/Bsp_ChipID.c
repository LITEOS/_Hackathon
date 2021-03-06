#include "common.h"

long ChipID = 0;          //芯片ID，long型，下一行的是字符型
char ChipID_String[25];   //24个字节ID，最后一个字节是结束符


/*
 * 函数名：GetChipID
 * 描述  ：获取芯片ID
 * 输入  ：无
 * 返回  ：无
 */
void GetChipID (void)
{
  uint8_t i = 0, k = 0;
  u32 ChipUniqueID[3] = {0};
  
  ChipUniqueID[2] = *(__IO u32*)(0X1FFFF7E8);       //读取ID
  ChipUniqueID[1] = *(__IO u32 *)(0X1FFFF7EC);
  ChipUniqueID[0] = *(__IO u32 *)(0X1FFFF7F0);
  ChipID = ChipUniqueID[0];

  /* 将long型转换为字符型 */
  for (i = 0; i < 3; i++)
  {
    for (k = 0; k < 8; k++)
    {
      ChipID_String[i * 8 + k] = ((ChipUniqueID[i] << k * 4) >> 28);
      
      if (ChipID_String[i * 8 + k] <= 9)
        ChipID_String[i * 8 + k] += 0x30;
      else
      {
        switch(ChipID_String[i * 8 + k] - 9)
        {
          case 1:
            ChipID_String[i * 8 + k] = 'A';
            break;
          case 2:
            ChipID_String[i * 8 + k] = 'B';
            break;
          case 3:
            ChipID_String[i * 8 + k] = 'C';
            break;
          case 4:
            ChipID_String[i * 8 + k] = 'D';
            break;
          case 5:
            ChipID_String[i * 8 + k] = 'E';
            break;
          case 6:
            ChipID_String[i * 8 + k] = 'F';
            break;
          default:
            break;         
        }
      }
    }
  }
  
  ChipID_String[24] = '\0';   //给数组手动添加结束符
}

/*
 * 函数名：Chip2String
 * 描述  ：将从机的ID转化为字符串形�
 * 输入  ：Num：long型ID
 *         String：字符型ID
 * 返回  ：无
 */
void Chip2String (uint32_t Num, char* String)
{
  uint8_t k;
  /* convert the num to string */

  for (k = 0; k < 8; k++)
  {
    *String = ((Num << k * 4) >> 28);
    
    if (*String <= 9)
      *String += 0x30;
    else
    {
      switch(*String - 9)
      {
        case 1:
          *String = 'A';
          break;
        case 2:
          *String = 'B';
          break;
        case 3:
          *String = 'C';
          break;
        case 4:
          *String = 'D';
          break;
        case 5:
          *String = 'E';
          break;
        case 6:
          *String = 'F';
          break;
        default:
          break;         
      }
    }
    String++;
  }
  *String = '\0';
}
