#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

void Analysis(){
  cout << "Starting Analysis" << endl;
  ifstream infile("Output.txt");
  string line;
  string read = "G4WT";
  bool analysis = false;
  vector<double> eDep;
  vector<double> energy;
  vector<string> layer;
  vector<double> x;
  vector<double> y;
  vector<double> z;
  vector<double> mass;
  vector<double> DEP;
  vector<double> xHit;
  vector<double> yHit;
  vector<double> zHit;
  TCanvas *C = new TCanvas();
  TH2D *Plane = new TH2D("XY", "XY", 100, 0., 0., 100, 0., 0.);
  
  while (getline(infile, line))
    {
      cout << line << endl;
      size_t toRead = line.find(read); 
      if(toRead == 0){
	istringstream iss(line);
	vector<string> values;
	copy(istream_iterator<string>(iss),
	     istream_iterator<string>(),
	     back_inserter(values));
	if(values.size() > 3){
	if(values[2] == "End"){
	  analysis = true;
	}
	}
	if(analysis){
	  cout << "End of event!" << endl;
	  analysis = false;
	  double Deposited = 0;
	  double X = 0;
	  double Y = 0;
	  double Z = 0;
	  for(int i = 0; i < eDep.size(); i++){
	    X+= x[i]*eDep[i];
	    Y += y[i]*eDep[i];
	    Z += z[i]*eDep[i];
	    Deposited += eDep[i];
	  }
	  X /= Deposited;
	  Y /= Deposited;
	  Z /= Deposited;
	  xHit.push_back(X);
	  yHit.push_back(Y);
	  zHit.push_back(Z);
	  DEP.push_back(Deposited);
	  Plane->Fill(X, Y);
	  eDep.clear();
	  energy.clear();
	  layer.clear();
	  x.clear();
	  y.clear();
	  z.clear();
	  mass.clear();
	}
	else{
	  if(values.size() > 10){
	    cout << values[2] << endl;
	    //cout << line << endl;
	    //cout << values[5] << endl;
	    eDep.push_back(stod(values[5]));
	    //cout << values[6] << endl;
	    energy.push_back(stod(values[6]));
	    //cout << values[7] << endl;
	    mass.push_back(stod(values[7]));
	    //cout << values[8] << endl;
	    x.push_back(stod(values[8]));
	    //cout << values[9] << endl;
	    y.push_back(stod(values[9]));
	    //cout << values[10] << endl;
	    z.push_back(stod(values[10]));
	    //cout << values[11] << endl;
	    layer.push_back(values[11]);
	  }
	}
      }
    }
Plane->Draw();
C->Show();
}
