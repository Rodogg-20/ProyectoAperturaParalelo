#include <omp.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

long long x1=0;
long long y1=0;
long long x2=0;
long long y2=0;
int cont = 0;

void noise_detection(float** points, float epsilon, int min_samples, long long int size) {
    cout << "Step 0" << "\n"; 
    for (long long int i=0; i < size; i++) {
        points[i][2] = rand() % 2;
    }   
    //aqui entra a acomparar distancias
    for (long long int j=0; j < size; j++){
        x1 = points[j][0];
        y1 = points[j][1];
        cont=0;

        while(cont<min_samples){
            if (x1!=x2 && y1!=y2){
                    //función euclideana
                    d=sqrt(pow(x2-x1,2)+pow(y2-y1,2));
                    if (d<=epsilon)
                        cont++;
                    
            }
        }
        if (cont==min_samples){
            points[i][2]=0;       
        }
    }

    cout << "Complete" << "\n"; 
}

void load_CSV(string file_name, float** points, long long int size) {
    ifstream in(file_name);
    if (!in) {
        cerr << "Couldn't read file: " << file_name << "\n";
    }
    long long int point_number = 0; 
    while (!in.eof() && (point_number < size)) {
        char* line = new char[12];
        streamsize row_size = 12;
        in.read(line, row_size);
        string row = line;
        //cout << stof(row.substr(0, 5)) << " - " << stof(row.substr(6, 5)) << "\n";
        points[point_number][0] = stof(row.substr(0, 5));
        points[point_number][1] = stof(row.substr(6, 5));
        point_number++;
    }
}

void save_to_CSV(string file_name, float** points, long long int size) {
    fstream fout;
    fout.open(file_name, ios::out);
    for (long long int i = 0; i < size; i++) {
        fout << points[i][0] << ","
             << points[i][1] << ","
             << points[i][2] << "\n";
    }
}

int main(int argc, char** argv) {

    const float epsilon = 0.03;
    const int min_samples = 10;
    const long long int size = 4000;
    const string input_file_name = to_string(size)+"_data.csv";
    const string output_file_name = to_string(size)+"_results.csv";    
    float** points = new float*[size];

    for(long long int i = 0; i < size; i++) {
        points[i] = new float[3]{0.0, 0.0, 0.0}; 
        // index 0: position x
        // index 1: position y 
        // index 2: 0 for noise point, 1 for core point
    }

    load_CSV(input_file_name, points, size);
    
    noise_detection(points, epsilon, min_samples, size); 
        
    save_to_CSV(output_file_name, points, size);

    for(long long int i = 0; i < size; i++) {
        delete[] points[i];
    }
    delete[] points;
    return 0;
}
