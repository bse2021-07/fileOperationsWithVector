/*fileOperationsWithVector.cpp : This file contains the 'main' function. 
Program execution begins and ends there.*/


//******************
//Headers
//******************
#include <iostream>
#include <string>
#include <fstream> // to handle file operations
#include <sstream> // to handle string stream convertion
#include <vector> // to handle unlimited structure array
using namespace std; 

//***********************
//Definition of structure
//***********************

struct Marker {
    string brand;
    string color;
    double price;

    //constructor to initialize the variables of the structure
    //you can provide a default value to your variables
    Marker(string b="Warwick", string c="red", double p=2.5) {
        brand = b;
        color = c;
        price = p;
    }
};

//***********************
//Function prototypes
//***********************
vector <Marker> inputMarker(vector<Marker> &marker);//returns a Marker vector
void outputMarker(vector<Marker>& marker);//returns nothing
void writeToFile(vector<Marker>& marker);//returns nothing
vector <Marker> readFromFile();//returns a Marker vector
vector<Marker> searchAndUpdate(vector<Marker> markerFromFile);

int main()
{    
    //declaration marker to be of Marker structure type which is unlimited
    vector <Marker> marker;//data from the user
    vector <Marker> markerFromFile;//data from the file
    //when marker is passed, by default, it passes the pointer
   // inputMarker(marker);//calling a function to get input
    //outputMarker(marker);
    //writeToFile(marker);
     markerFromFile=readFromFile();
   // outputMarker(markerFromFile);
     markerFromFile=searchAndUpdate(markerFromFile);//markerFromFile vector is updated after updating the file content
    outputMarker(markerFromFile);
    return 0;
}

//***********************
//Definition of functions
//***********************

//inputMarker to take user input
vector <Marker> inputMarker(vector<Marker>& parker) {
    cout << "\nFrom inputMarker Function";
    cout << "\n***************************";
    Marker m;//we receive one marker data at any given time
    char answer = 'y';
    while (tolower(answer) == 'y') {
        cout << "\nPlease enter the brand of the marker: ";
        getline(cin,m.brand);
        cout << "\nPlease enter the color of the marker: ";
        getline(cin,m.color);
        cout << "\nPlease enter the price of the marker: ";
        cin >> m.price;
        parker.push_back(m);
        
        cout << "\nDo you wish to continue inputting data?";
        cin >> answer;
    }

    return (parker);
}

//outputMarker to produce the output on the console
void outputMarker(vector<Marker>& marker) {
    cout << "\nFrom outputMarker Function";
    cout << "\n***************************";
    int i;
    for (i = 0; i < marker.size(); i++) {
        cout << "\nThe brand of the marker is: " << marker[i].brand;
        cout << "\nThe color of the marker is: " << marker[i].color;
        cout << "\nThe price of the marker is: " << marker[i].price;
    }
}

//writeToFile function facilitates the storing of marker details
void writeToFile(vector<Marker>& marker) {
    cout << "\nWriting to file ";
    cout << "\n***************************";
    int i;
    fstream myFile("markerFile.csv", ios::app);
    for (i = 0; i < marker.size(); i++) {
        myFile << marker[i].brand << "," << marker[i].color <<","<< marker[i].price << endl;
    }
    myFile.close();    
   
}

//readFromFile function to read data from the markerFile.csv
vector <Marker> readFromFile() {
    cout << "\nFrom readFile Function";
    cout << "\n***************************\n";
    fstream myFile("markerFile.csv", ios::in) ;
    vector<Marker> tempMarker;

    Marker m;
    string line;
    while (getline(myFile, line)) {
        cout << line<<endl;
        istringstream linestream(line);//to split the row into columns/properties
        string item;
        //until the appearance of comma, everything is stored in item
        getline(linestream, item, ',');
        m.brand = item;

        getline(linestream, item, ',');
        m.color = item;

        getline(linestream, item, ',');
        stringstream ss(item);//converting string into double
        ss >> m.price;//the converted double value will be given to m.price

        tempMarker.push_back(m);

    }


    myFile.close();

    return(tempMarker);
}

//searchAndUpdate function to search for a record and update 
vector<Marker> searchAndUpdate(vector<Marker> markerFromFile) {
   
   
    fstream myFile("markerFile.csv", ios::out);
   // cout << "\nsize=" << markerFromFile.size();
    cout << "\nsearching ....";
    
    
    //if you want to update a data, get the details from the user. Assume you are chaning the price for Bic
    string searchBrand;
    cout << "\nEnter the brand you want to search:";
    getline(cin, searchBrand);//these are searched and found from the if condition.
   
    double newPrice;
    cout << "\nEnter the new price of the brand: ";
    cin >> newPrice;
     
    int i;
    for (i = 0; i < markerFromFile.size(); i++) {
       // cout << "\nlooping through";
        if (markerFromFile[i].brand == searchBrand) {
            //if matching branch is found, it displays on the console. 
            cout << markerFromFile[i].brand << "\t" << markerFromFile[i].color << "\t" << markerFromFile[i].price << endl;
            
            markerFromFile[i].price=newPrice;
        }
        //overwriting the file with new set of data
        myFile << markerFromFile[i].brand << "," << markerFromFile[i].color << "," << markerFromFile[i].price << endl;
    }
    myFile.close();
    //always after updating the file, remember to read and store it again 
    markerFromFile = readFromFile();
    return (markerFromFile);
}