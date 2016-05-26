#include "ConfigParser.C"
#include <string>

void testRandomAccess(){
	ConfigParser conf("test.conf");
	
	cout<<"==================\n";
	cout<<"Loading Configuration for Name=80"<<endl;
	conf.loadConfig("80");
	conf.print();
	cout<<"==================\n\n";

	cout<<"Loading Configuration for Name=76"<<endl;
	conf.loadConfig("76");
	conf.print();
	cout<<"==================\n\n";

	cout<<"Loading Configuration for Name=80_vtx_mf"<<endl;
	conf.loadConfig("80_vtx_mf");
	conf.print();
	cout<<"==================\n\n";

	cout<<"Loading Configuration for Name=NONE"<<endl;
	conf.loadConfig("NONE"); //should throw error
	conf.print();
	cout<<"==================\n\n";
}

void testSeqAccess(){
	ConfigParser conf("test.conf");
	while (conf.loadNextConfig()){
		cout<<"CONFIG:"<<endl;
		conf.print();
	}
}

void testConfigReset(){
	ConfigParser conf("test.conf");
	conf.loadNextConfig();
	conf.print();
	conf.loadNextConfig();
	conf.print();
	conf.loadFirstConfig();
	conf.print();
	conf.loadNextConfig();
	conf.print();
}

int main(){
	cout<<"Random Access Testing:"<<endl;
	testRandomAccess();

	cout<<"Sequential Testing:"<<endl;
	testSeqAccess();
	
	//cout<<"Reset Testing:"<<endl;
	//testConfigReset();
}