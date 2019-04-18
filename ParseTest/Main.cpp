#include <stdio.h> //- This is needed for the printf statements
#include "ReadTaskDescriptionsFromXML.h"
#include "ScanDirectoryForFilesTest.h"
#include "ReadFileDateTimes.h"

int main(int argc, char* argv[]) {

	printf(">>>>>>>>>>>>>>>>>>>> Reading the XML File <<<<<<<<<<<<<<<<<<<<\n\n");
	new ReadTaskDescriptionsFromXML();
	printf("\n>>>>>>>>>>>>>>>>>>>> Done Reading XML File <<<<<<<<<<<<<<<<<<<<\n");


	printf(">>>>>>>>>>>>>>>>>>>> Scanning Directory for Files <<<<<<<<<<<<<<<<<<<<\n\n");
	new ScanDirectoryForFilesTest("C:\\Users\\chris\\Documents");
	printf("\n>>>>>>>>>>>>>>>>>>>> Done Scanning Directory for Files <<<<<<<<<<<<<<<<<<<<\n");


	printf(">>>>>>>>>>>>>>>>>>>> Scanning Files for Dates <<<<<<<<<<<<<<<<<<<<\n\n");
	new ReadFileDateTimes("C:\\Users\\chris\\Documents\\TempTitle.txt");
	printf("\n>>>>>>>>>>>>>>>>>>>> Done Scanning Files for Dates <<<<<<<<<<<<<<<<<<<<\n");

	return 0;
}