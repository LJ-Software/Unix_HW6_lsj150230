/*
 * Printing binary file contents of CDK Matrix
 *
 * File:   main.cc
 * Author: Logan Jones
 * Email:  lsj150230@utdallas.edu
 */

#include <iostream>
#include "cdk.h"
#include "program6.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <stdlib.h>
#include <stdint.h>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

ifstream binInFile;

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /* open file reader */
  binInFile.open("cs3377.bin", ios::in | ios::binary);


  /*
   * Display first row header info
   */
  BinaryFileHeader *bFileHeader = new BinaryFileHeader();
  binInFile.read((char *) bFileHeader, sizeof(BinaryFileHeader));
  
  /* Initialize stringstream and buffer */
  stringstream stringStream;
  char buffer [50];

  /* Magic Number */
  sprintf(buffer, "Magic: 0x%X",bFileHeader->magicNumber);
  stringStream << buffer;
  setCDKMatrixCell(myMatrix, 1, 1, stringStream.str().c_str());
  memset(buffer, 0, sizeof(buffer));
  stringStream.str("");

  /* Version number */
  sprintf(buffer, "Version: %u", bFileHeader->versionNumber);
  stringStream << buffer;
  setCDKMatrixCell(myMatrix, 1, 2, stringStream.str().c_str());
  memset(buffer, 0, sizeof(buffer));
  stringStream.str("");

  /* Number of records */
  sprintf(buffer, "%lu", bFileHeader->numRecords);
  stringStream << "NumRecords: " << buffer;
  int numRecords = atoi(buffer);
  setCDKMatrixCell(myMatrix, 1, 3, stringStream.str().c_str());
  memset(buffer, 0, sizeof(buffer));
  stringStream.str("");

  /* Loop through the records and fill in the corresponding rows */
  for(int i = 0; i < numRecords; i++){
    BinaryFileRecord *bFileRecord = new BinaryFileRecord();
    binInFile.read((char *) bFileRecord, sizeof(BinaryFileRecord));
   
    sprintf(buffer, "strlen: %u", bFileRecord->strLength);
    stringStream << buffer;
    setCDKMatrixCell(myMatrix, i+2, 1, stringStream.str().c_str());
    memset(buffer, 0, sizeof(buffer));
    stringStream.str("");

    sprintf(buffer, "%s", bFileRecord->stringBuffer);
    stringStream << buffer;
    setCDKMatrixCell(myMatrix, i+2, 2, stringStream.str().c_str());
    memset(buffer, 0, sizeof(buffer));
    stringStream.str("");
  } 

  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
