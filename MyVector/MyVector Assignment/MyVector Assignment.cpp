#include<string.h>//I have attempted the bonus
#include<iostream>

using namespace std;

template<class T>
class myvector{
private:
	int length, _capacity;
	T *element;
	exception out_of_range;
public:
	myvector(){ //constructor
		length = 0;
		_capacity = 20;
		element = new T[_capacity];
	}
	myvector(int new_capacity){ //another vector of the same type(as a const reference) --copy the contents of the vector
		_capacity = new_capacity;
		element = new T[_capacity];
		length = 0;
	}
	myvector & operator= (myvector const & another_vecter){ //assignment operator
		length = another_vecter.length;
		_capacity = another_vecter._capacity;
		element = new T[_capacity];
		for (int i = 0; i < length; i++) element[i] = another_vecter.element[i];
		return *this;
	}
	myvector(myvector && another_vector){ //move constructor
		length = another_vector.length;
		_capacity = another_vector._capacity;
		element = new T[_capacity];
		for (int i = 0; i < another_vector._capacity; i++)
		element[i] = another_vector.element[i];
		another_vector.length = 0;
		another_vector._capacity = 0;
	}
	myvector(myvector const & another_vecter){ // another vector of the same type (as a const reference) -- copy the contents of the vector// copy constructor
		length = another_vecter.length;
		_capacity = another_vecter._capacity;
		element = new T[_capacity];
		for (int i = 0; i < length; i++) element[i] = another_vecter.element[i];
	}
	myvector(T *arr, int arrlength){ //an array of the same type and the integer array length -- copy contents of array into the vector
		length = arrlength;
		_capacity = length * 2 + 1;
		element = new T[_capacity];
		for (int i = 0; i<length; i++)
			element[i] = arr[i];
	}
	myvector operator+ (myvector const & another_vector){ //assignment operator
		myvector<T> temp;
		temp.reserve(_capacity + another_vector._capacity);
		for (int i = 0; i < length; i++) temp.push_back(element[i]);
		for (int i = 0; i < another_vector.length; i++) temp.push_back(another_vector.element[i]);
		return temp;
	}
	int size() const{ // return the current length of the vector
		return length;
	}
	int capacity() const{ // return the current _capacity of the vector
		return _capacity;
	}
	bool empty() const{ // return whether or not the vector is empty
		return (length == 0);
	}
	void resize(int newlength){ // resize the vector (change length) to the specified size, changing _capacity as needed
		if (newlength < 0) throw out_of_range;
		length = newlength;
		if (length > _capacity) reserve(2 * length + 1);
	}
	void reserve(int new_capacity){ // change the vector _capacity to the specified size, or give an error if _capacity would get smaller than length
		if (new_capacity < length) throw out_of_range;
		else {
			_capacity = new_capacity;
			T *temp = new T [_capacity];
			for (int i = 0; i < length; i++) temp[i] = element[i];
			delete[]element;
			element = temp;
		}
	}
	void assign(int position, T const & value){ // assign the second argument as the value of the vector at the position of the first argument
		if (position < 0 || position >= length) throw out_of_range;
		else element[position] = value;
	}
	void push_back(T const & value){ // increase length by 1 and add the argument as the value at the end
		if (length >= _capacity) reserve(2 * _capacity);
	    element[length++] = value;
	}
	T pop_back(){ // decrease length by 1, returning the value removed from the vector
		if (length > 0) return element[--length];
		else throw out_of_range;
	}
	void insert(int position, T const & value){ // increase length by 1, put the value specified in the second argument at index specified by first argument and shift all values to the right in the vector down by one index
		if (length >= _capacity) reserve(2 * _capacity);
		if (position < 0 || position >= length) throw out_of_range;
		else if (position < length){
			for (int i = length; i > position; i--) element[i] = element[i - 1];
			element[position] = value;
			length++;
		}
	}
	void erase(int position){ // decrease length by 1, remove the item at the specified index, and shift all other items left to eliminate the "hole"
		if (position < 0 || position >= length) throw out_of_range;
		else for (int i = position; i < length - 1; i++) element[i] = element[i + 1];
		length--;
	}
	void erase(int position1, int position2){ // same as erase(int), but removes all elements between the indexes specified by the first and second argument
		if (position1 < 0 || position2 < 0 || position1 >= length || position2 >= length || position1 > position2) throw out_of_range;
		length = length - (position2 - position1 + 1);
		for (int i = 0; i < length; i++) element[position1 + i] = element[position2 + i + 1];
	}
	void clear(){ // remove all elements from the list
		length = 0;
	}
	T & at(int index) const { //return a member of the vector at the index specified
		if (index < 0 || index >= length) throw out_of_range;
		else return element[index];
	}
	T & operator[] (int index) const { //return a member of the vector at the index specified
		if (index < 0 || index >= length) throw out_of_range;
		else return element[index];
	}
	~myvector(){ //destructor
		delete[] element;
	}
};
void main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	myvector<int> a(arr, 10);
	myvector<int> b(a);
	myvector<char*> c;
	cout << "This is a test example!" << endl;
	try
	{
		myvector<int> d;
		d = a;
		for (int i = 0; i<d.size(); i++)
			cout << d[i] << " ";
		cout << endl;
		myvector<int> e(a+b);
		for (int i = 0; i<e.size(); i++)
			cout << e[i] << " ";
		cout << endl;
		for (int i = 11; i<28; i++)
			b.push_back(i);
		cout << b[5];
		cout << endl;
		for (int i = 0; i<b.size(); i++)
			cout << b[i] << " ";
		cout << endl;
		b.insert(2, 1000);
		cout << b.capacity() << endl;
		for (int i = 0; i<b.size(); i++)
			cout << b[i] << " ";
		cout << endl;
		b.erase(2);
		for (int i = 0; i<b.size(); i++)
			cout << b[i] << " ";
		cout << endl;
		b.erase(2,5);
		for (int i = 0; i<b.size(); i++)
			cout << b[i] << " ";
		cout << endl;
		b.assign(10, 1);
		for (int i = 0; i<b.size(); i++)
			cout << b[i] << " ";
		cout << endl;
		cout << b.size();
		cout << endl;
		a.resize(15);
		while (!a.empty())
			cout << a.pop_back() << " ";
		cout << endl;
		while (!b.empty())
			cout << b.pop_back() << " ";
		cout << endl;
		b.clear();
		while (!b.empty())
			cout << b.pop_back() << " ";
		cout << endl;
		c.push_back("Why Always Me!");
		c.push_back("Because You Are Stupid!");
		for (int i = 0; i < c.size(); i++)
			cout << c[i] << endl;
		myvector<int> x;
		x.resize(2);
		x[0] = 10;
		for (int i = 0; i<x.size(); i++)
			cout << x[i] << " ";
		cout << endl;
		myvector<int> const y = x;
		for (int i = 0; i<x.size(); i++)
			cout << x[i] << " ";
		cout << endl;
		int const z = y.at(0);
		cout << z << endl;
	}
	catch (exception out_of_range)
	{
		cout << "Out of Range! End Processing!" << endl;
	}
	system("pause");
}