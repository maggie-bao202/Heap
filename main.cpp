#include <cstring>
#include <fstream>
#include <math.h>
#include <iostream>

using namespace std;
/*Author: Maggie Bao. Description: After taking in either file input or console input, the program converts the char* array into an int* array, then modifies it into a heap. The program then prints out the output.*/

void charToIntegerArray(char* carray, int* &iarray, int &size);
int pow(int a, int b);
void heapify(int* &arr, int size, int index);
void heapVisual(int* arr, int size, int, int);
void sortByRemovingRoot(int* &arr, int &size);

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
    else if (strcmp(keyword, "FILE") == 0){//if entered FILE
      char* name = new char[40];
      cout << "Enter File Name: " << endl;
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
  for (int i = (size/2)-1; i >= 0; i--){//starting from the last node with children, heapify in reverse
    heapify(numberInput, size, i);//check to see if values are in correct place
  }
  cout << "Heap: " << endl;
  for (int i = 0; i < size; i++){
    cout << numberInput[i] << ",";
  }
  cout << endl << endl;
  cout << "Heap Tree:" << endl << endl;
  heapVisual(numberInput, size, 0, 0);//print information about elements of output
  cout << endl << endl;
  cout << "Heap Sort: " << endl;
  sortByRemovingRoot(numberInput, size);
  delete[] numberInput;
  delete[] input;
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
void heapify(int* &arr, int size, int index){//check to see if parents are greater than their children. If not, swap them. Go down the tree
  int temp = index; //Would want to make root the largest
  if (index*2+1 < size && arr[temp] < arr[index*2+1]){//if left child exists within the tree and if root is smaller than it's left child
    temp = index*2+1;//go to left child index
  }
  if (index*2+2 < size && arr[temp] < arr[index*2+2]){//check for right child after left
    temp = index*2+2;
  }
  if (temp != index){//if the root was changed, swap and heapify
    int temp0 = arr[temp];
    arr[temp] = arr[index];
    arr[index] = temp0;
    heapify (arr, size, temp); //go through every parent-child relationship
  }
}

/*void heapVisual(int* arr, int size){//Goes through each element, and prints out parent/children information 
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
*/
/*
void heapVisual(int* arr, int size){//Prints tree correctly, but kinda ugly
  int place = 0;
  int counter = 1;
  for (int i = 0; i < size; i++){
    cout << arr[i] << "\t";
    if (i+1 == counter){
      cout << endl;
      place++;
      counter += pow(2, place);
    }
  }
}
*/
void heapVisual(int* arr, int size, int depth, int index) {//help from Peter Jin to print tree sideways. Depth counts tabs. Starts at first element, 0 depth. Prints in a right-left-right left zigzag pattern
  if (index*2+2 <= size){//get the rightmost index, incrementing depth each time
    heapVisual(arr, size, depth+1, index*2+2);
  }
  for (int i = 0; i < depth; i++){//prints tabs depending on depth 
    cout << "\t";
  }
  if (index != size){//fixes print as last element of tree
    cout << arr[index] << endl;
  }
  if (index == size){//substitute spaces instead of the element
    cout << "  " << endl;
  }
  if (index*2+1 <= size) {//go to left child, increment depth
    heapVisual(arr, size, depth+1, index*2+1);
  }
}

void sortByRemovingRoot(int* &arr, int &size){//removes root and heapifies, repeats
  for (int i = 0; i < size; size--){//decrease size with each iteration
    cout << arr[0] << ",";//print the root
    arr[0] = arr[size-1];//replace last element with root
    heapify(arr, size, 0);//check if new tree meets criteria. If not, swap
    arr[size-1] = 0;//set last element to "NULL"
  }
}
