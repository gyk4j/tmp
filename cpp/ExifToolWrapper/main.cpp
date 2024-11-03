#include <iostream>

#include "ExifToolWrapper.h"

using namespace std;

int main(int argc, char *argv[])
{
	bool bHasExiftool = false;
	
	bHasExiftool = ExifToolWrapper::check_tool_exists();
	
	string exists = (bHasExiftool) ? "yes" : "no";
	
	cout << "exiftool: " << exists << endl;
	
	if(argc > 0){
		ExifToolWrapper exiftool;		
		exiftool.run(argv[1]);
		
		bool bHasExifData = exiftool.has_exif_data();
		cout << "Has EXIF data: " << bHasExifData << endl;
		
		if (bHasExifData) {
		ExifTagItem* tag = exiftool.find("Date/Time Original");
		
			if (tag != NULL){
				cout 
					<< "Group: " << tag->group << endl
					<< "Name : " << tag->name  << endl
					<< "Value: " << tag->value << endl;
			} else {
				cout << "Date/Time Original tag not found." << endl;
			}
		}
	} else {
		cout << "No input file specified." << endl;
	}
	
	return 0;
}
