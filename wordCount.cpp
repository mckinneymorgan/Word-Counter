// Original author: Morgan McKinney 4/2020

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Hash Table Entry Structure
struct hashTableEntry {
	int count;
	string word;
	char key;
};

// Hash Function
// (Referenced pages.cs.wisc.edu/~siff/CS367/Notes/hash.html)
// (Referenced programiz.com/cpp-programming/examples/ASCII-value-character)
int hashFunction(string s, int tableSize) {
	int hashValue = 0;
	// Find sum of ASCII values for each character in s
	for (size_t i = 0; i < s.length(); i++) {
		hashValue += int(s[i]);
	}
	hashValue = hashValue * 255 % tableSize;
	return hashValue;
} // hash()

// Insert Into Hash Table (External Chaining)
// (Referenced hackerearth.com/fr/practice/data-structures/hash-tables/basics-of-hash-tables/tutorial/)
void insert(string s, int tableSize, vector<hashTableEntry>* table) {
	// Find index to insert on
	int index = hashFunction(s, tableSize);
	// Initialize data to be inserted
	hashTableEntry data;
	data.word = s;
	data.key = s[0];
	data.count = 1;
	// Push data to front of vector
	table[index].push_back(data);
} // insert()

// Search Hash Table (External Chaining)
// (Referenced hackerearth.com/fr/practice/data-structures/hash-tables/basics-of-hash-tables/tutorial/)
int search(string s, int tableSize, vector<hashTableEntry>* table) {
	int foundIndex = -1; // Index not found by default
	int index = hashFunction(s, tableSize);
	// Search for calculated index
	for (size_t i = 0; i < table[index].size(); i++) {
		if (table[index][i].word == s) { // String is found
			foundIndex = i; // Update found index
			return foundIndex;
		}
	}
	return foundIndex;
} // search()

// Addd to Word Occurence Count
void addCount(string s, int tableSize, vector<hashTableEntry>* table, int i) {
	int bucketIndex = hashFunction(s, tableSize);
	table[bucketIndex][i].count++;
} // addCount()

// Swap Two Characters
// (Referenced geeksforgeeks.org/sort-the-character-array-based-on-ascii-n/)
void swap(char* x, char* y) {
	char z = *x;
	*x = *y;
	*y = z;
}

// Partition Array
// (Referenced geeksforgeeks.org/sort-the-character-array-based-on-ascii-n/)
int partition(hashTableEntry arr[], int low, int high, int mod) {
	char pivotKey = arr[high].key;
	int i = (low - 1);
	int pivot = pivotKey % mod;
	for (int j = low; j <= high - 1; j++) {
		// Compare ASCII values
		int k = arr[j].key % mod;
		if (k <= pivot) {
			i++;
			swap(&arr[i].key, &arr[j].key);
		}
	}
	swap(&arr[i + 1].key, &arr[high].key);
	int returnValue = i + 1;
	return returnValue;
}

// Quicksort
// (Referenced class notes on Quicksort)
// (Referenced geeksforgeeks.org/sort-the-character-array-based-on-ascii-n/)
void quickSort(hashTableEntry arr[], int low, int high, int mod) {
	if (low < high) {
		int partitionIndex = partition(arr, low, high, mod);
		// Sort elements before and after partition
		quickSort(arr, low, partitionIndex - 1, mod);
		quickSort(arr, partitionIndex + 1, high, mod);
	}
}

int main() {
	// Read input
	string w;
	vector<string> allWords;
	while(cin >> w) {
		allWords.push_back(w);
	}	
	int wordCount = allWords.size(); // Store total number of words
	int uniqueWordCount = 0;
	// Create hash table
	// (Referenced geeksforgeeks.org/array-of-vectors-in-c-stl/)
	vector<hashTableEntry> hashTable[wordCount];
	// Transfer words from vector to hash table
	for (auto i = allWords.begin(); i != allWords.end(); i++) {
		// Has the word been added yet?
		int wordIndex = search(*i, wordCount, hashTable);
		if (wordIndex == -1) { // Word is unique
			insert(*i, wordCount, hashTable);
			uniqueWordCount++;
		}
		else { // Word has already been added
			addCount(*i, wordCount, hashTable, wordIndex);
		}
	}
	// Transfer hash table contents to an array
	hashTableEntry sortedArray[uniqueWordCount];
	int index = 0;
	for (int i = 0; i < wordCount; i++) {
		for (size_t j = 0; j < hashTable[i].size(); j++) {
			sortedArray[index] = hashTable[i][j];
			index++;
		}
	}
	// Sort array
	// (Referenced geeksforgeeks.org/sort-the-character-array-based-on-ascii-n/)
	int mod = 3;
	quickSort(sortedArray, 0, uniqueWordCount - 1, mod);
	// Print output
	for (int i = 0; i < uniqueWordCount; i++) {
		cout << sortedArray[i].word << " ";
		cout << sortedArray[i].count << endl;
	}
	return 0;
}
