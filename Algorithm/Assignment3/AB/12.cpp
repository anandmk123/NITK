#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minGuards(vector<double>& paintings) {
    sort(paintings.begin(), paintings.end()); // Step 1: Sort the positions
    int guards = 0;
    int i = 0;
    int n = paintings.size();
    
    vector<vector<double>> guardCoverage; // To track only the covered paintings for each guard

    while (i < n) {
        guards++; // Place a new guard
        
        vector<double> coveredPaintings; // Store the paintings covered by this guard
        
        // Place guard at rightmost position within 1 unit of paintings[i]
        double guardPosition = paintings[i] + 1;
        
        // Move to the rightmost painting covered by this guard
        while (i < n && paintings[i] <= guardPosition + 1) {
            coveredPaintings.push_back(paintings[i]);
            i++;
        }
        
        // Store covered paintings for this guard
        guardCoverage.push_back(coveredPaintings);
    }
    
    // Print which guard covers which paintings
    for (int j = 0; j < guardCoverage.size(); j++) {
        cout << "Guard " << j + 1 << " covers paintings: ";
        for (int k = 0; k < guardCoverage[j].size(); k++) {
            cout << guardCoverage[j][k] << " ";
        }
        cout << endl;
    }
    
    return guards;
}

int main() {
    vector<double> paintings = {1.0, 2.0, 2.9, 4.0, 6.0, 6.5, 9.0};
    int ming = minGuards(paintings);
    cout << "Minimum number of guards needed: " << ming << endl;
    return 0;
}
