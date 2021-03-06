#include "ReadTaskDescriptionsFromXML.h"
// Opening an XML File and reading values for --- Expiration Tasks Project ---
#include <stdio.h> //- This is needed for the printf statements
//#include <windows.h> //- This doesn't appear to be needed for the msxml6 library (not sure what it's for right now)
#include "Task.h"

#include <tchar.h> // - This appears to be NEEDED for the msxml6 library
#import <msxml6.dll> rename_namespace(_T("MSXML"))


ReadTaskDescriptionsFromXML::ReadTaskDescriptionsFromXML()
{
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr)) {
		try {
			MSXML::IXMLDOMDocument2Ptr xmlDoc;
			hr = xmlDoc.CreateInstance(__uuidof(MSXML::DOMDocument60),
				NULL, CLSCTX_INPROC_SERVER);
			// TODO: if (FAILED(hr))... // I wonder if we actually need to be concerned about this...

			if (xmlDoc->load(_T("ExpireTaskConfig.xml")) != VARIANT_TRUE) {
				printf("Unable to load input.xml\n");
			}
			else {
				printf("XML was successfully loaded\n");

				xmlDoc->setProperty("SelectionLanguage", "XPath");

				// For every Task (Node) print their subvalues; if it is not a comment element (Node):
				MSXML::IXMLDOMNodeListPtr tasks = xmlDoc->selectNodes("/AllTasks/Task");
				for (int i = 0; i < tasks->Getlength(); i++) {

					// ATask is the "i-th" "Node" that matched the "selectNodes" query above; numbered [0, 1, 2, 3, ..., i, ..., tasks->GetLength()]
					// Lamens: "ATask" represents one task at a time, out of all the Tasks defined in the XML, and every time the loop iterates it represents the "next task"
					MSXML::IXMLDOMNodePtr aTask = tasks->Getitem(i);

					// Print a separating line above the data for readability:
					printf("\n\n================== Task Item #%i ==============: \n\n", i);

					Task T = Task(
						aTask->selectSingleNode("TaskName")->Gettext(),
						aTask->selectSingleNode("TaskScope")->Gettext(),
						aTask->selectSingleNode("ExpirationDirectory")->Gettext(),
						aTask->selectSingleNode("ExpirationType")->Gettext(),
						aTask->selectSingleNode("ExpirationAge")->Gettext(),
						aTask->selectSingleNode("ExpirationFinal")->Gettext()
					);
					T.Execute();
				}



				/* We don't need to do any of this for our purpose...
				MSXML::IXMLDOMNodePtr node;
				node = xmlDoc->createNode(MSXML::NODE_ELEMENT, _T("Engine"), _T(""));
				node->text = _T("Engine 1.0");
				xmlDoc->documentElement->appendChild(node);
				hr = xmlDoc->save(_T("output.xml"));
				if (SUCCEEDED(hr))
					printf("output.xml successfully saved\n");
				*/
			}
		}
		catch (_com_error & e) {
			printf("ERROR: %ws\n", e.ErrorMessage());
		}
		CoUninitialize();
	}
}


ReadTaskDescriptionsFromXML::~ReadTaskDescriptionsFromXML()
{
}