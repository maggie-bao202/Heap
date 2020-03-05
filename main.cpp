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

void swap (int &a, int &b);

int main(){
  char* keyword = new char[10];
  char* input = new char[200];
  bool loop = true;
  while (loop == true){
    cout << "Type CONSOLE for console input, and FILE to read in a file." << endl;
    cin.getline(keyword, 10, '\n');
    if (strcmp(keyword, "CONSOLE") == 0){
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
  cout << "Integer Array:" << endl;
  for (int i = 0; i < (size); i++){
    cout << numberInput[i] << ",";
  }
  cout << endl;
  cout << "Building Heap:" << endl;
  buildHeap(numberInput, size);
  cout << "Output:" << endl;
  for (int i = 0; i < size; i++){
    cout << numberInput[i] << ",";
  }
  cout << "Heap Visualizer: " << endl;
  int subtract = 1;
  for (int i = 0; i < size; i++){
    cout << endl;
    cout << "Node: " << numberInput[i] << endl;
    if (i != 0){
      if (i%2 ==0){
	subtract++;
      }
      cout << "Parent: " << numberInput[i-subtract] << endl;
    }
    if (numberInput[2*i+1] != 0){
      cout << "Left Child: " << numberInput[2*i+1] << endl;
    }
    if (numberInput[2*i+2] != 0){
      cout << "Right Child: " << numberInput[2*i+2] << endl;
    }
  }
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

void heapify(int* &arr, int size, int index){//check to see if parents are greater than their children. If not, swap them.
  int largest = index; //Would want to make root the largest
  int leftChild = 2 * index + 1;
  int rightChild = 2 * index + 2;

  if (leftChild < size && arr[largest] < arr[leftChild]){//if root is smaller than it's left child
    largest = leftChild;
  }
  if (rightChild < size && arr[largest] < arr[rightChild]){//same for right child
    largest = rightChild;
  }
  if (largest != index){//if the root was changed
    swap(arr[index], arr[largest]);//swap the value of the root with the current value
    heapify (arr, size, largest); //go through every parent-child relationship
  }
}

void buildHeap(int* &arr, int size){ //build max heap, passing in the integerArray
  int startIndex = (size/2)-1;//index of last node with children
  for (int i = startIndex; i >= 0; i--){//starting from the last node with children, heapify in reverse
    heapify(arr, size, i);//check to see if values are in correct place
  }
}

void swap (int &a, int &b){//swaps a and b
  int temp = a;
  a = b;
  b = temp;
}
