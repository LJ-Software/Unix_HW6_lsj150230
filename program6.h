/*Programmed by Logan Jones
 * lsj150230@utdallas.edu
 *CS 3377.002
 *
 */
#ifndef PRG6_H
#define PRG6_H

#include <stdint.h>

class BinaryFileHeader{
	public:

	uint32_t magicNumber;         /* Should be 0xFEEDFACE */
   	uint32_t versionNumber;
	uint64_t numRecords;
};

/*  
 * Records in the file have a fixed length buffer
 * that will hold a C-Style string. This is the
 * size of the fixed length buffer.
 */  
const int maxRecordStringLength = 25;

class BinaryFileRecord
{ 
 public:
   uint8_t strLength;
   char stringBuffer[maxRecordStringLength];
};  

#endif
