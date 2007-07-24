// Author: David Lawrence  June 25, 2004
//
//
// hd_ana.cc
//

#include <iostream>
using namespace std;

#include <JANA/JApplication.h>
#include <JANA/JCalibration.h>

void ParseCommandLineArguments(int &narg, char *argv[]);
void Usage(void);

unsigned int RUN_NUMBER = 100;
string NAMEPATH="";

//-----------
// main
//-----------
int main(int narg, char *argv[])
{
	// Parse the command line
	ParseCommandLineArguments(narg, argv);

	// Instantiate a JApplication object and use it to get a JCalibration object
	JApplication *app = new JApplication(narg, argv);
	JCalibration *jcalib = app->GetJCalibration(RUN_NUMBER);
	
	// Get constants
	map<string, string> vals;
	jcalib->Get(NAMEPATH, vals);
	
	// Display constants
	cout<<endl<<"Values for \""<<NAMEPATH<<"\" for run "<<RUN_NUMBER<<endl;
	cout<<"--------------------"<<endl;
	map<string, string>::iterator iter;
	
	// Make one pass to find the maximum key width
	unsigned int max_key_width = 1;
	for(iter=vals.begin(); iter!=vals.end(); iter++){
		string key = iter->first;
		if(key.length()>max_key_width) max_key_width=key.length();
	}
	max_key_width++;

	for(iter=vals.begin(); iter!=vals.end(); iter++){
		string key = iter->first;
		string val = iter->second;
		cout<<iter->first<<" ";
		if(key.length()<max_key_width)
			for(unsigned int j=0; j<max_key_width-key.length(); j++)cout<<" ";
		cout<<iter->second;
		cout<<endl;
	}
	cout<<endl;
	
	delete app;

	return 0;
}

//-----------
// ParseCommandLineArguments
//-----------
void ParseCommandLineArguments(int &narg, char *argv[])
{
	if(narg==1)Usage();

	for(int i=1;i<narg;i++){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 'h':
					Usage();
					break;
				case 'R':
					if(strlen(argv[i])==2){
						RUN_NUMBER = atoi(argv[++i]);
					}else{
						RUN_NUMBER = atoi(&argv[i][2]);
					}
					break;
			}
		}else{
			NAMEPATH = argv[i];
		}
	}
}

//-----------
// Usage
//-----------
void Usage(void)
{
	cout<<"Usage:"<<endl;
	cout<<"       janacalibread [options] namepath"<<endl;
	cout<<endl;
	cout<<"Print the contents of a JANA data source (e.g. a file)"<<endl;
	cout<<"to the screen."<<endl;
	cout<<endl;
	cout<<"Options:"<<endl;
	cout<<endl;
	cout<<"   -h        Print this message"<<endl;
	cout<<"   -R run    Set run number to \"run\""<<endl;
	cout<<"   -t type   Set data type (float, int, ...)"<<endl;
	cout<<endl;

	exit(0);
}


