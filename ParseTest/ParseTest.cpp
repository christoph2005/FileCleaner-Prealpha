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
					MSXML::IXMLDOMNodePtr aTask = tasks->Getitem(i);

					// Print a separating line above the data for readability:
					printf("\n\n================== Task Item #%i ==============: \n\n", i);

					// Query and print the values of all the known subtags to the current "aTask" object (using XPATH and their known tagnames)
					const char* nodeName = "TaskName";
					_bstr_t nodeValue = aTask->selectSingleNode(nodeName)->Gettext();
					printf("%s: %S\n", nodeName, nodeValue.GetBSTR());

					nodeName = "TaskScope";
					nodeValue = aTask->selectSingleNode(nodeName)->Gettext();
					printf("%s: %S\n", nodeName, nodeValue.GetBSTR());

					nodeName = "ExpirationDirectory";
					nodeValue = aTask->selectSingleNode(nodeName)->Gettext();
					printf("%s: %S\n", nodeName, nodeValue.GetBSTR());

					nodeName = "ExpirationType";
					nodeValue = aTask->selectSingleNode(nodeName)->Gettext();
					printf("%s: %S\n", nodeName, nodeValue.GetBSTR());

					nodeName = "ExpirationAge";
					nodeValue = aTask->selectSingleNode(nodeName)->Gettext();
					printf("%s: %S\n", nodeName, nodeValue.GetBSTR());

					nodeName = "ExpirationFinal";
					nodeValue = aTask->selectSingleNode(nodeName)->Gettext();
					printf("%s: %S\n", nodeName, nodeValue.GetBSTR());


				}

				// The stuff below is the same as from the original sample program.
				printf("\n\nConfig Value is %u \n", tasks->Getlength());

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