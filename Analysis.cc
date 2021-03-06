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
  // Parameters taken for all steps in the event
  vector<double> eDep;
  vector<double> energy;
  vector<string> layerpre;
  vector<string> layerpost;
  vector<double> x;
  vector<double> y;
  vector<double> z;
  vector<double> mass;

  // Parameters taken for each event for tracker 1 and 2
  vector<double> NoIncident1;
  vector<double> NoIncident2;
  vector<double> IncidentE;
  vector<double> DEP1;
  vector<double> xHit1;
  vector<double> yHit1;
  vector<double> zHit1;
  vector<double> DEP2;
  vector<double> xHit2;
  vector<double> yHit2;
  vector<double> zHit2;

  // Histograms for XY on plane 1, XY on plane 2, and E1 against E2
  TCanvas *C = new TCanvas();
  TH2D *Plane1 = new TH2D("XY_1", "XY_1", 100, 0., 0., 100, 0., 0.);
  TH2D *Plane2 = new TH2D("XY_2", "XY_2", 100, -10, 10., 100, -10, 10);
  TH2D *Energies = new TH2D("E", "E", 100, -0.1, 0.1, 100, 0., 0.);
  TH2D *Bethe1 = new TH2D("Bethe1", "Bethe1", 100, 0., 0., 100, 0., 0.);
  TH2D *Bethe2 = new TH2D("Bethe2", "Bethe2", 100, 0., 0., 100, 0., 0.);
  TH1D *Count1 = new TH1D("Count_1", "Count_1", 100, 0., 0.);
  TH1D *Count2 = new TH1D("Count_2", "Count_2", 100, 0., 0.);
  
  while (getline(infile, line))
    {
      // Read the text file, take lines as an array called values
      //cout << line << endl;
      size_t toRead = line.find(read); 
      if(toRead == 0){
	istringstream iss(line);
	vector<string> values;
	copy(istream_iterator<string>(iss),
	     istream_iterator<string>(),
	     back_inserter(values));
	if(values.size() > 3){
	  // If there's a line called end of event, we run the end event analysis
	  if(values[2] == "End"){
	    analysis = true;
	  }
	}
	if(analysis){
	  // End event analysis
	  cout << "End of event!" << endl;
	  analysis = false;
	  double Counter1 = 0;
	  double Counter2 = 0;
	  double IncidentE1 = 0;
	  double IncidentE2 = 0;
	  double Deposited1 = 0;
	  double Deposited2 = 0;
	  double X1, Y1, Z1 = 0;
	  double X2, Y2, Z2 = 0;
	  // Check for layer 1 or layer 2, make weighted mean of XYZ, and total energy deposition
	  for(int i = 0; i < eDep.size(); i++){
	    if(strcmp(layerpost[i].c_str(), "Tracker1") == 0){
	      X1+= x[i]*eDep[i];
	      Y1 += y[i]*eDep[i];
	      Z1 += z[i]*eDep[i];
	      Deposited1 += eDep[i];
	      if(strcmp(layerpre[i].c_str(), layerpost[i].c_str()) != 0){
		cout << layerpre[i] << " " << layerpost[i] << endl;
		Counter1 += 1;
		IncidentE1 += energy[i];
	      }
	    }
	    if(strcmp(layerpost[i].c_str(), "Tracker2") == 0){
	      X2+= x[i]*eDep[i];
	      Y2 += y[i]*eDep[i];
	      Z2 += z[i]*eDep[i];
	      Deposited2 += eDep[i];
	      if(strcmp(layerpre[i].c_str(), layerpost[i].c_str()) != 0){
		cout << layerpre[i] << " " << layerpost[i] << endl;
		Counter2 += 1;
		IncidentE2 += energy[i];
	      }
	    }
	  }
	  // Weight them means
	  if(Deposited1 != 0){
	  X1 /= Deposited1;
	  Y1 /= Deposited1;
	  Z1 /= Deposited1;
	  }
	  xHit1.push_back(X1);
	  yHit1.push_back(Y1);
	  zHit1.push_back(Z1);
	  DEP1.push_back(Deposited1);
	  // XY plane 1
	  Plane1->Fill(X1, Y1);

	  // Weight them means again
	  if(Deposited2 != 0){
	  X2 /= Deposited2;
	  Y2 /= Deposited2;
	  Z2 /= Deposited2;
	  }
	  xHit2.push_back(X2);
	  yHit2.push_back(Y2);
	  zHit2.push_back(Z2);
	  DEP2.push_back(Deposited2);
	  // XY plane 2
	  Plane2->Fill(X2, Y2);

	  // E1 E2 - the important one!!!! Let's see if there's a pattern!!!
	  Energies->Fill(Deposited1, Deposited2);

	  Count1->Fill(Counter1);
	  Count2->Fill(Counter2);

	  Bethe1->Fill(IncidentE1, Deposited1);
	  //Bethe2->Fill(IncidentE2, Deposited2);
	  Bethe2->Fill(energy[0], Deposited2);

	  cout << X1 << " " << Y1 << " " << Deposited1 << " " << Counter1 << endl;
	  cout << X2 << " " << Y2 << " " << Deposited2 << " " << Counter2 << endl;
	  
	  eDep.clear();
	  energy.clear();
	  layerpre.clear();
	  layerpost.clear();
	  x.clear();
	  y.clear();
	  z.clear();
	  mass.clear();
	}
	else{
	  if(values.size() > 10){
	    // For lines that aren't comments or the end of an event, put values into vectors
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
	    layerpre.push_back(values[11]);
	    layerpost.push_back(values[12]);
	  }
	}
      }
    }
  Plane1->Draw();
  C->SaveAs("./XY1.png");
  Plane2->Draw();
  C->SaveAs("./XY2.png");
  Energies->Draw();
  C->SaveAs("./E1E2.png");
  Count1->Draw();
  C->SaveAs("./Count1.png");
  Count2->Draw();
  C->SaveAs("./Count2.png");
  Bethe1->Draw();
  C->SaveAs("./Bethe1.png");
  Bethe2->Draw();
  C->SaveAs("./Bethe2.png");
}
