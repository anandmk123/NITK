#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Structure to represent a person with height and gender
struct Person {
    int height;  // Height of the person
    bool is_man; // True if the person is a man, false otherwise
};

// Free function to compare heights
bool cmp(const Person& a, const Person& b) {
    return a.height < b.height;
}

// Function to find the maximum number of valid pairs based on height criteria
int maxPairs(vector<Person>& men, vector<Person>& women, vector<pair<int, int>>& pairs) {
    // Sort men and women by height using the free comparator function
    sort(men.begin(), men.end(), cmp);
    sort(women.begin(), women.end(), cmp);

    int count = 0; // To keep track of the number of valid pairs
    int i = 0, j = 0; // Pointers for men and women

    // Try to form pairs using a greedy approach
    while (i < men.size() && j < women.size()) {
        if (men[i].height >= women[j].height && men[i].height <= women[j].height + 3) {
            pairs.push_back({men[i].height, women[j].height});  // Store the pair of heights
            count++;  // Valid pair found
            i++;      // Move to the next man
            j++;      // Move to the next woman
        } 
        else if (men[i].height < women[j].height) {
            i++;  // Move to the next man if he's too short
        } 
        else {
            j++;  // Move to the next woman if the man is too tall
        }
    }

    return count; // Return the total number of pairs
}

int main() {
    // Example input: lists of men and women with their heights
    vector<Person> men = {{65, true}, {70, true}, {72, true}};
    vector<Person> women = {{63, false}, {68, false}, {69, false}};
    
    vector<pair<int, int>> pairs;  // To store the valid pairs

    // Output the maximum number of valid pairs
    int max_pairs = maxPairs(men, women, pairs);

    cout << "Maximum pairs: " << max_pairs << endl;
    cout << "Pairs (Man's height, Woman's height):" << endl;
    for (const auto& p : pairs) {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }

    return 0;
}
