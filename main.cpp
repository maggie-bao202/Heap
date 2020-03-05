#include "Node.h"
#include <cstring>
#include <fstream>
#include <math.h>
#include <iostream>

using namespace std;

void charToIntegerArray(char* carray, int* &iarray, int &a);

int pow(int a, int b);

void heapify(int* &arr, int size, int index);

void buildHeap(int* &arr, int size);

void printHeap(int* &arr, int size);

int main(){
  char* keyword = new char[10];
  char* input = new char[200];
  bool loop = true;
  while (loop == true){
    cout << "Type MANUAL for console input, and FILE to read in a file." << endl;
    cin.getline(keyword, 10, '\n');
    if (strcmp(keyword, "MANUAL") == 0){
      cin.getline(input, 200, '\n');
      loop = false;
    }
    else if (strcmp(keyword, "FILE") == 0){
      cout << "Enter file name: " << endl;
      char* name = new char[40];
      cin.getline(name, 40, '\n');
      ifstream fileStream (name);
      if (fileStream.is_open()){
	fileStream.getline(input, 200);
      }
      else{
	cout << "Invalid file name." << endl;
	return 0;
      }
      fileStream.close();
      loop = false;
    }
    else{
      cout << "Invalid keyword. All words are case sensitive." << endl;
    }
  }
  int* numberInput = new int[101];
  int size = 0;
  charToIntegerArray(input, numberInput, size);
  /*for (int i = 0; i < (size); i++){
    cout << numberInput[i] << ",";
    }*/
  buildHeap(numberInput, size);
  printHeap(numberInput, size);
  return 0;
}

void charToIntegerArray(char* carray, int* &iarray, int &a){
  int counter = 0;
  int place = 0;
  for (int i = 0; i < strlen(carray); i++){
    if (carray[i] >= '0' && carray[i] <= '9'){
      if (place != 2){
	counter = (counter * pow(10, place)) + (carray[i] - '0');
	place++;
      }
      else{
	counter = (counter * pow(10, place-1)) + (carray[i] - '0');
      }
      if (i == strlen(carray)-1){
	iarray[a++] = counter;
      }
    }
    else if (carray[i] == ' '){
      iarray[a++] = counter;
      counter = 0;
      place = 0;
    }
  }
}

int pow(int a, int b){
  int x = 1;
  for (int i = 1; i <= b; i++){
    x *= a;
  }
  return x;
}

void heapify(int* &arr, int size, int index){
  int largest = index;
  int leftChild = 2 * index + 1;
  int rightChild = 2 * index + 2;

  if (leftChild < size && arr[largest] < arr[leftChild]){
    largest = leftChild;
  }
  if (rightChild < size && arr[largest] < arr[rightChild]){
    largest = rightChild;
  }
  if (largest != index){
    swap(arr[index], arr[largest]);
    heapify (arr, size, largest);
  }
}

void buildHeap(int* &arr, int size){
  int startIndex = (size/2)-1;
  for (int i = startIndex; i >= 0; i--){
    heapify(arr, size, i);
  }
}

void printHeap(int* &arr, int size){
  cout << "Array representation of Heap:\n";
  for (int i = 0; i < size; i++){
    cout << arr[i] << " ";
    cout << '\n';
  }
}
