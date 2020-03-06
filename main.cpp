#include <cstring>
#include <fstream>
#include <math.h>
#include <iostream>

using namespace std;
/*Author: Maggie Bao. Description: After taking in either file input or console input, the program converts the char* array into an int* array, then modifies it into a heap. The program then prints out the output.*/
void charToIntegerArray(char* carray, int* &iarray, int &size);
int pow(int a, int b);
void heapify(int* &arr, int size, int index);
void buildHeap(int* &arr, int size);
void swap (int &a, int &b);
void heapVisual(int* arr, int size);

int main(){
  char* keyword = new char[10];
  char* input = new char[200];
  bool loop = true;
  while (loop == true){
    cout << "Type CONSOLE for console input, and FILE to read in a file." << endl;
    cin.getline(keyword, 10, '\n');
    if (strcmp(keyword, "CONSOLE") == 0){//if entered CONSOLE, take input from manual input
      cin.getline(input, 200, '\n');
      loop = false;//continue
    }
    else if (strcmp(keyword, "FILE") == 0){//if entered FILE, (With help from Peter Jin and his code)
      cout << "Enter file name: " << endl;
      char* name = new char[40];
      cin.getline(name, 40, '\n');//name of file must include ".txt"
      ifstream fileStream (name);
      if (fileStream.is_open()){//open file
	fileStream.getline(input, 200);//read file line into input
      }
      else{//if the file name can't be found, end the program.
	cout << "Invalid file name." << endl;
	return 0;
      }
      fileStream.close();//close file
      loop = false;//continue
    }
    else{
      cout << "Invalid keyword. All words are case sensitive." << endl;//keep looping CONSOLE or FILE until valid input
    }
  }
  int* numberInput = new int[101];//heap
  int size = 0;//size of heap
  charToIntegerArray(input, numberInput, size);//return elements as integers
  /*cout << "Integer Array:" << endl;
  for (int i = 0; i < (size); i++){
    cout << numberInput[i] << ",";
  }
  cout << endl;*/
  cout << endl;
  cout << "Building Heap..." << endl;
  buildHeap(numberInput, size);//numberInput is now the heap/tree
  cout << "Finished Build." << endl << endl;
  cout << "Output:" << endl;
  for (int i = 0; i < size; i++){//print out numberInput/heap
    cout << numberInput[i] << ",";
  }
  cout << endl << endl;
  cout << "Heap Visualizer: " << endl;
  heapVisual(numberInput, size);//print information about elements of output
  rootRemove(numberInput, size);
  cout << endl;
  for (int i = 0; i < size; i++){
    cout << numberInput[i] << ",";
  }
  return 0;
}

void charToIntegerArray(char* carray, int* &iarray, int &size){//converts a char* array to an int* array
  int counter = 0;
  int place = 0;//place holds the exponent that will be multiplied by 10
  for (int i = 0; i < strlen(carray); i++){//going through each element of char array
    if (carray[i] >= '0' && carray[i] <= '9'){//if it is a number
      if (place != 2){//if the element is either in 1s or 10s place
	counter = (counter * pow(10, place)) + (carray[i] - '0');//add to runningTotal counter
	place++;
      }
      else{//if it is 100s place, (debugged)
	counter = (counter * pow(10, place-1)) + (carray[i] - '0');
      }
      if (i == strlen(carray)-1){//add last element to int array (debugged)
	iarray[size++] = counter;
      }
    }
    else if (carray[i] == ' '){//whenever there is a space, add to int array and reset
      iarray[size++] = counter;
      counter = 0;
      place = 0;
    }
  }
}

int pow(int a, int b){//pow(10, 4) = 10^4, power function
  int x = 1;
  for (int i = 1; i <= b; i++){
    x *= a;//multiply a by itself as b many times
  }
  return x;
}

//https://www.geeksforgeeks.org/building-heap-from-array/, harsh agarwal
void heapify(int* &arr, int size, int index){//check to see if parents are greater than their children. If not, swap them.
  int largest = index; //Would want to make root the largest
  int leftChild = 2 * index + 1;
  int rightChild = 2 * index + 2;

  if (leftChild < size && arr[largest] < arr[leftChild]){//if root is smaller than it's left child
    largest = leftChild;//set the root index to be the index of child
  }
  if (rightChild < size && arr[largest] < arr[rightChild]){//check for right child after left
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

void heapVisual(int* arr, int size){//Goes through each element, and prints out parent/children information 
  int subtract = 1;
  for (int i = 0; i < size; i++){
    cout << endl;
    cout << "Node: " << arr[i] << endl;
    if (i != 0){//root does not have parent
      if (i%2 ==0){//if the element index is even, subtract one more than previous to get to parent index
        subtract++;
      }
      cout << "Parent: " << arr[i-subtract] << endl;
    }
    if (i < (size/2)-1){//if nodes before the last node with children
      cout << "Left Child: " << arr[2*i+1] << endl;
      cout << "Right Child: " << arr[2*i+2] << endl;
      }
    if (i == (size/2)-1){//for the last node with children
      cout << "Left Child: " << arr[2*i+1] << endl;
      if (size%2 == 1){//if the last index is even (start from 0)
	cout << "Right Child: " << arr[2*i+2] << endl;
      }
    }
  }
}
