// Opening an XML File and reading values for --- Expiration Tasks Project ---

#include <stdio.h> 
#include <tchar.h>
#include <windows.h>
#import <msxml6.dll> rename_namespace(_T("MSXML"))

#include <conio.h>

int main(int argc, char* argv[]) {
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr)) {
		try {
			MSXML::IXMLDOMDocument2Ptr xmlDoc;
			hr = xmlDoc.CreateInstance(__uuidof(MSXML::DOMDocument60),
				NULL, CLSCTX_INPROC_SERVER);
			// TODO: if (FAILED(hr))...

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
					MSXML::IXMLDOMNodePtr ATask = tasks->Getitem(i);
					// Print a separating line above the data for readability:
					printf("================== Task Item #%i ==============: \n\n", i);


					/* 
					* In the following loop, "task_child_ptr" "points at" all of the child nodes belonging to the "ATask" XML Dom Node.
					* In the "loop body" the "Name" and "Value" of the "subtags" to this particular task are displayed.
					* The "current xml subtag" to the Task is represented by the "task_child_ptr" "IXMLDOMNodePtr" object:
					*     Every time the loop iterates, the "task_child_ptr" "points at" the "next subtag"
					*     
					* Lamens: This prints the data held in each Task
					*/

					// First "task_child_ptr" "points at" the "first child" of the Task
					MSXML::IXMLDOMNodePtr task_child_ptr = ATask->GetfirstChild();
					// It continues to point at each "next sibling" until it has pointed at every child once:
					while (task_child_ptr != nullptr) {

						// Once it finds a "child" it checks the name to see if it's a "comment"-type xml node (In the future the read query might be changed to ignore comments)
						BSTR baseName = NULL;
						// This function, "get_nodeName", will copy the BSTR-string-typed data into the memory location that you tell it to.
						// In this case, we give it the memory address for our BSTR "baseName" variable.
						task_child_ptr->get_nodeName(&baseName);

						// Here we're checking to make sure we aren't looking at a "comment" in the XML, because we don't really want to process those.
						// This is a complicated comparison in that "baseName" is BSTR-typed, and "#comment" is a "literal-string" type, there is no way to "compare" these specific types.
						// The solution I found was to convert both the "baseName"-variable and the "#comment"-literal strings to the "_bstr_t" string class which has an "overloaded equality operator ( == ) "
						// If the _bstr_t versions of the strings match, the original strings are a match
						if (_bstr_t(baseName) != _bstr_t("#comment")) {
							//If it's not a #comment, then go ahead and print the name of the xml-node
							printf("\t\tChild Node Name: %S \n", baseName);

							// Also, get the text between that xml node and print it.
							BSTR nodeValue = NULL;
							task_child_ptr->get_text(&nodeValue);
							printf("\t\tChild Node Value: %S\n\n", nodeValue);
						}

						// This line just tells the "task_child_ptr" to point to the "next child".
						// If there are no more children, it will point to a NULL, and the loop will end.
						task_child_ptr = task_child_ptr->GetnextSibling();
					}



				}

				// The stuff below is the same as from the original sample program.
				printf("Config Value is %u \n", tasks->Getlength());

				MSXML::IXMLDOMNodePtr node;
				node = xmlDoc->createNode(MSXML::NODE_ELEMENT, _T("Engine"), _T(""));
				node->text = _T("Engine 1.0");
				xmlDoc->documentElement->appendChild(node);
				hr = xmlDoc->save(_T("output.xml"));
				if (SUCCEEDED(hr))
					printf("output.xml successfully saved\n");
			}
		}
		catch (_com_error & e) {
			printf("ERROR: %ws\n", e.ErrorMessage());
		}
		CoUninitialize();
	}

	_getch();
	return 0;
}