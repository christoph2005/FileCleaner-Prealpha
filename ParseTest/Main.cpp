#include <stdio.h> //- This is needed for the printf statements
#include "ReadTaskDescriptionsFromXML.h"
#include "ScanDirectoryForFilesTest.h"


int main(int argc, char* argv[]) {

	printf(">>>>>>>>>>>>>>>>>>>> Reading the XML File <<<<<<<<<<<<<<<<<<<<\n\n");
	new ReadTaskDescriptionsFromXML();
	printf("\n>>>>>>>>>>>>>>>>>>>> Reading the Done Reading XML File <<<<<<<<<<<<<<<<<<<<\n");


	printf(">>>>>>>>>>>>>>>>>>>> Scanning Directory for Files <<<<<<<<<<<<<<<<<<<<\n\n");
	new ScanDirectoryForFilesTest("C:\\Users\\chris\\Documents");
	printf("\n>>>>>>>>>>>>>>>>>>>> Done Scanning Directory for Files <<<<<<<<<<<<<<<<<<<<\n");

	return 0;
}