/**************************************************************************/
/*                                                                        */
/*   A2 tester file                                                       */
/*                                                                        */
/*   To compile: g++ a2tester.cpp timer.cpp -std=c++0x                    */
/*   You will also need:                                                  */
/*      * timer.h/timer.cpp                                               */
/*      * dictionary.txt                                                  */ 
/*                                                                        */
/*                                                                        */
/*   Reminder that if you are working in VS, you need to change the       */
/*   #define PLATFORM line in timer.h                                     */
/*                                                                        */
/*                                                                        */
/**************************************************************************/

#include "table.h"
#include "timer.h"
#include <string>
#include <iostream>
#include <cstdlib>

bool test1(std::string key[], int data[], int max, std::string& error);	
bool test2(std::string key[], int data[], int max, std::string& error);	
bool test3(std::string key[], int data[], int max, std::string& error);	
bool test4(std::string key[], int data[], int max, std::string& error);	
bool test5(std::string key[], int data[], int max, std::string& error);	
bool test6(std::string key[], int data[], int max, std::string& error);	
bool test7(std::string key[], int data[], int max, std::string& error);	
bool test8(std::string key[], int data[], int max, std::string& error);	
bool test9(std::string key[], int data[], int max, std::string& error);	
bool test10(std::string key[], int data[], int max, std::string& error);	
bool test11(std::string key[], int data[], int max, std::string& error);	

const int numTests=11;
const int maxRecords=2000000;

typedef bool (*TestPtr)(std::string [], int [], int , std::string& );
void createData(std::string keys[],int data[],int max);
int main(void){
	TestPtr runTest[numTests]={test1, test2, test3, test4, test5, 
		                       test6, test7, test8, test9, test10,
		                   	   test11};
	std::string msg;
	bool result=true;
	int numPassed=0;

    std::string* keys = new std::string[maxRecords];        //list of test cases. 
    int* data=new int[maxRecords];

    Timer t;
    double times[numTests];
    createData(keys,data,maxRecords);
	for(int i=0;result && i<numTests;i++){
		t.reset();
		t.start();
		result = runTest[i](keys,data,maxRecords,msg);
		t.stop();
		times[i]=t.currtime();
		if(!result){
			std::cout << msg << std::endl;
		}
		else{
			numPassed++;
			std::cout << "Test " << i+1 << " passed!" << std::endl;
		}
	}
	if(numPassed == numTests){
		std::cout << std::endl;
		std::cout << "  Test Number  |    Time     " << std::endl;
		std::cout << "---------------|-------------" << std::endl;

		for(int i=0;i<numTests;i++){
			std::cout << "   Test ";
			std::cout.width(2);
			std::cout << i+1;
			std::cout << "     |  " << times[i] << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Congratulations! You have passed testing for A2 part 3" << std::endl;
	}
	else{
		std::cout << std::endl;
		std::cout << "Looks like you still have some work left to do" << std::endl;
	}
}
/* test1: Initialization, numRecords(),  isEmpty()
*/
bool test1(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table1(1000,0.65);
	ChainingTable<int> table2(10000,1.0);
	ChainingTable<int> table3(20000,2.0);
	bool isGood=true;
	if(table1.numRecords()!=0 || table2.numRecords()!=0 || table3.numRecords() != 0){
		isGood=false;
		error="Error 1a: numRecords() should return 0 when table is empty";
	}
	else if(!table1.isEmpty() || !table2.isEmpty() || !table3.isEmpty()){
		isGood=false;
		error="Error 1b: isEmpty() should return true when table is empty";
	}
	else if(table1.capacity()!=1000){
		isGood=false;
		error="Error 1c: capacity() should return ";
		error+= std::to_string(1000);
		error+=" records, your numRecords() returned: ";
		error+=std::to_string(table1.capacity());				
	}
	else if(table2.capacity()!=10000){
		isGood=false;
		error="Error 1d: capacity() should return ";
		error+= std::to_string(10000);
		error+=" records, your numRecords() returned: ";
		error+=std::to_string(table2.capacity());				

	}
	else if(table3.capacity()!=20000){
		isGood=false;
		error="Error 1e: capacity() should return ";
		error+= std::to_string(20000);
		error+=" records, your numRecords() returned: ";
		error+=std::to_string(table3.capacity());				
	}

	return isGood;
}

/*test2: use update() with new records.  The number of slots available should not
  change.
*/
bool test2(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table1(1000,0.65);
	ChainingTable<int> table2(10000,1.0);
	ChainingTable<int> table3(20000,2.0);

	bool isGood=true;
	int i=0;
	int count=0;
	while(isGood && count<650){
		table1.update(keys[i],data[i]);
		if(table1.isEmpty()){
			isGood=false;
			error="Error 2a: table is not empty, isEmpty() should return false, your isEmpty() returns true";
		}
		if(isGood && table1.numRecords()!=count+1){
			isGood=false;
			error="Error 2b: table should have ";
			error+= std::to_string(count+1);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table1.numRecords());				
		}
		if(isGood && table1.capacity()!= 1000){
			isGood=false;
			error="Error 2c: table capacity should be 1000";
		}
		i++;
		count++;
	}


	count=0;
	while(isGood && count<10000){
		table2.update(keys[i],data[i]);

		if(table2.isEmpty()){
			isGood=false;
			error="Error 2d: table is not empty, isEmpty() should return false, your isEmpty() returns true";
		}
		if(isGood && table2.numRecords()!=count+1){
			isGood=false;
			error="Error 2e: table should have ";
			error+= std::to_string(count+1);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table2.numRecords());				
		}		
		if(isGood && table2.capacity()!= 10000){
			isGood=false;
			error="Error 2f: table capacity should be 10000";
		}
	
		i++;
		count++;
	}


	count=0;
	while(isGood && count<40000){
		table3.update(keys[i],data[i]);
		if(table3.isEmpty()){
			isGood=false;
			error="Error 2g: table is not empty, isEmpty() should return false, your isEmpty() returns true";
		}
		if(isGood && table3.numRecords()!=count+1){
			isGood=false;
			error="Error 2h: table should have ";
			error+= std::to_string(count+1);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table3.numRecords());				
		}		
		if(isGood && table3.capacity()!= 20000){
			isGood=false;
			error="Error 2i: table capacity should be 20000";
		}

		i++;
		count++;
	}

	return isGood;

}

/*test3: use update() with new records, number of slots should not change,
check that find works.
*/
bool test3(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table1(1000,0.65);
	ChainingTable<int> table2(10000,1.0);
	ChainingTable<int> table3(20000,2.0);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<650){
		table1.update(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.update(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<40000){
		table3.update(keys[i],data[i]);
		i++;
		count++;
	}

	i=0;
	count=0;
	while(isGood && count<650){
		int value;
		isGood=table1.find(keys[i],value);
		if(!isGood){
			error="Error 3a: find returned false for a record that should exist in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 3b: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		int value;
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 3c: find returned false for a record that should exist in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;								
				error="Error 3d: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<40000){
		int value;
		isGood=table3.find(keys[i],value);
		if(!isGood){
			error="Error 3e: find returned false for a record that should exist in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 3f: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}


	return isGood;
}

/*test 4: modify records, ensure numRecords() is returning the correct value.
  number of slots should not incrase during this process
*/
bool test4(std::string keys[], int data[], int max, std::string& error){

	ChainingTable<int> table1(1000,0.65);
	ChainingTable<int> table2(10000,1.0);
	ChainingTable<int> table3(20000,2.0);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<650){
		table1.update(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.update(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<40000){
		table3.update(keys[i],data[i]);
		i++;
		count++;
	}

	i=0;
	count=0;
	while(isGood && count<650){
		if(count%2){
			table1.update(keys[i],data[i]+1);
		}

		if(table1.numRecords()!=650){
			isGood=false;
			error="Error 4a: table should have ";
			error+= std::to_string(650);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table1.numRecords());				
		}
		if(isGood && table1.capacity()!= 1000){
			isGood=false;
			error="Error 4b: table capacity should be 1000";
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		if(count%2){
			table2.update(keys[i],data[i]+2);
		}
		if(table2.numRecords()!=10000){
			isGood=false;
			error="Error 4c: table should have ";
			error+= std::to_string(10000);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table2.numRecords());				
		}		
		if(isGood && table2.capacity()!= 10000){
			isGood=false;
			error="Error 4d: table capacity should be 10000";
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<40000){
		if(count%2){
			table3.update(keys[i],data[i]+3);
		}
		if(table3.numRecords()!=40000){
			isGood=false;
			error="Error 4e: table should have ";
			error+= std::to_string(40000);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table3.numRecords());				
		}		
		if(isGood && table3.capacity()!= 20000){
			isGood=false;
			error="Error 4f: table capacity should be 20000";
		}
		i++;
		count++;
	}
	return isGood;
}
/*test 5: Modify records and test find, ensure that find returns true 
for all records and that the values are updated
*/

bool test5(std::string keys[], int data[], int max, std::string& error){

	ChainingTable<int> table1(1000,0.65);
	ChainingTable<int> table2(10000,1.0);
	ChainingTable<int> table3(20000,2.0);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<650){
		table1.update(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.update(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<40000){
		table3.update(keys[i],data[i]);
		i++;
		count++;
	}

	i=0;
	count=0;
	while(count<650){
		if(count%2){
			table1.update(keys[i],data[i]+1);
		}
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		if(count%2){
			table2.update(keys[i],data[i]+2);
		}
		i++;
		count++;
	}
	count=0;
	while(count<40000){
		if(count%2){
			table3.update(keys[i],data[i]+3);
		}
		i++;
		count++;
	}


	i=0;
	count=0;
	int value;
	int correct;

	while(isGood && count<650){
		isGood=table1.find(keys[i],value);
		if(!isGood){
			error="Error 5a: find returned false for a record that should exist in the table";
		}
		else{
			correct=data[i]+(count%2);
			if(value!=correct){
				isGood=false;				
				error="Error 5b: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(correct);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 5c: find returned false for a record that should exist in the table";
		}
		else{
			correct=data[i]+(count%2)*2;

			if(value!=correct){

				isGood=false;								
				error="Error 5d: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(correct);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<40000){
		int value;
		isGood=table3.find(keys[i],value);
		if(!isGood){
			error="Error 5e: find returned false for a record that should exist in the table";
		}
		else{
			correct=data[i]+(count%2)*3;
			if(value!=correct){
				isGood=false;				
				error="Error 5f: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(correct);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	return isGood;

}

/*Test 6: add enough records that will force a resize, ensure all records can be found
*/
bool test6(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table1(1000,0.65);
	ChainingTable<int> table2(10000,1.0);
	ChainingTable<int> table3(20000,2.0);
	int value;
	int i;
	int count;
	bool isGood=true;
	double loadFactor=0.65;
	int correctCap=1000;

	for(i=0, count=0;isGood && count<65000;count++, i++){
		table1.update(keys[i],data[i]);

		if(table1.isEmpty()){
			isGood=false;
			error="Error 6a: table is not empty, isEmpty() should return false, your isEmpty() returns true";
		}
		if(isGood && table1.numRecords()!=count+1){
			isGood=false;
			error="Error 6b: table should have ";
			error+= std::to_string(count+1);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table1.numRecords());				
		}
		if(isGood && table1.capacity() != correctCap){
			isGood=false;
			error="Error 6c: table should have capacity of";
			error+= std::to_string(correctCap);
			error+=".  your capacity() returned: ";
			error+=std::to_string(table1.capacity());				
		}
		isGood=table1.find(keys[i],value);
		if(!isGood){
			isGood=false;
			error = "Error 6d: couldn't find a value that was just added: ";
			error+= keys[i];
		}

		if((double)table1.numRecords()/correctCap == loadFactor){
			correctCap=correctCap*2;
		}

	}
	loadFactor = 1.0;
	correctCap=10000;
	for(count=0; isGood&&  count<100000; count++,i++){
		table2.update(keys[i],data[i]);
		if(table2.isEmpty()){
			isGood=false;
			error="Error 6e: table is not empty, isEmpty() should return false, your isEmpty() returns true";
		}
		if(isGood && table2.numRecords()!=count+1){
			isGood=false;
			error="Error 6f: table should have ";
			error+= std::to_string(count+1);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table2.numRecords());				
		}
		if(isGood && table2.capacity() != correctCap){
			isGood=false;
			error="Error 6g: table should have capacity of";
			error+= std::to_string(correctCap);
			error+=".  your capacity() returned: ";
			error+=std::to_string(table2.capacity());				
		}
		isGood=table2.find(keys[i],value);
		if(!isGood){
			isGood=false;
			error = "Error 6h: couldn't find a value that was just added: ";
			error+= keys[i];
		}
		if((double)table2.numRecords()/correctCap == loadFactor){
			correctCap=correctCap*2;
		}
	}

	i=0;
	loadFactor=2.0;
	correctCap=20000;
	for(count=0; isGood && count<200000; count++,i++){
		table3.update(keys[i],data[i]);
		if(table3.isEmpty()){
			isGood=false;
			error="Error 6i: table is not empty, isEmpty() should return false, your isEmpty() returns true";
		}
		if(isGood && table3.numRecords()!=count+1){
			isGood=false;
			error="Error 6j: table should have ";
			error+= std::to_string(count+1);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table3.numRecords());				
		}
		if(isGood && table3.capacity() != correctCap){
			isGood=false;
			error="Error 6k: table should have capacity of";
			error+= std::to_string(correctCap);
			error+=".  your capacity() returned: ";
			error+=std::to_string(table3.capacity());				
		}
		isGood=table3.find(keys[i],value);
		if(!isGood){
			isGood=false;
			error = "Error 6l: couldn't find a value that was just added: ";
			error+= keys[i];
		}
		if((double)table3.numRecords()/correctCap == loadFactor){
			correctCap=correctCap*2;
		}


	}



	i=0;
	count=0;
	while(isGood && count<65000){
		isGood=table1.find(keys[i],value);
		if(!isGood){
			error="Error 6m: find returned false for a record that should exist in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 6n: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;

	}
	count=0;
	while(isGood && count<100000){
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 6o: find returned false for a record that should exist in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;								
				error="Error 6p: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	i=0;
	count=0;
	while(isGood && count<200000){
		int value;
		isGood=table3.find(keys[i],value);
		if(!isGood){
			error="Error 6q: find returned false for a record that should exist in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 6r: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	return isGood;

}


/*Test 7: Test remove()*/
bool test7(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table(500000,0.70);
	bool isGood=true;

	for(int i=0;i<350000;i++){
		table.update(keys[i],data[i]);
	}
	for(int i=0;isGood && i<350000;i+=2){
		isGood=table.remove(keys[i]);
		if(!isGood){
			error="Error 7a: remove() should have returned true, function returned falsed";
		}
		if(table.capacity() != 500000){
			error="Error 7b: capacity() should return 500000, it returned: ";
			error+=std::to_string(table.capacity());
		}
	}

	int value;
	int result;
	for(int i=0;isGood && i<350000;i++){
		result=table.find(keys[i],value);
		if(i%2){
			if(!result){
				isGood=false;
				error="Error 7c: key (";
				error+=keys[i];
				error+=") that was not removed find() is returning false";
			}
			else{
				if(value != data[i]){
					isGood=false;
					error="Error 7d: value passed back from find is not correct after a remove operation";
				}
			}
		}
		else {
			if(result){
				isGood=false;
				error="Error 7e: key (";
				error+=keys[i];
				error+=") was removed but find() is returning true";			
			}
		}
	}
	return isGood;
}




/*Test 8: Test Copy Constructor, ensure that copy is same as original*/
bool test8(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table1(1000,0.65);
	ChainingTable<int> table2(10000,1.0);
	ChainingTable<int> table3(20000,2.0);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<650){
		table1.update(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.update(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<40000){
		table3.update(keys[i],data[i]);
		i++;
		count++;
	}

	ChainingTable<int> table1copy=table1;
	ChainingTable<int> table2copy=table2;
	ChainingTable<int> table3copy=table3;

	if(isGood && table1copy.numRecords() != table1.numRecords()){
		error="Error 8a: number of records was not correct.\n Correct number of records: ";
		error+=std::to_string(table1.numRecords());
		error+="\nYour function returns: ";
		error+=std::to_string(table1copy.numRecords());
		isGood=false;
	}
	if(isGood && table2copy.numRecords() != table2.numRecords()){
		error="Error 8b: number of records was not correct.\n Correct number of records: ";
		error+=std::to_string(table2.numRecords());
		error+="\nYour function returns: ";
		error+=std::to_string(table2copy.numRecords());
		isGood=false;

	}
	if(isGood && table3copy.numRecords() != table3.numRecords() ){
		error="Error 8c: number of records was not correct.\n Correct number of records: ";
		error+=std::to_string(table3.numRecords());
		error+="\nYour function returns: ";
		error+=std::to_string(table3copy.numRecords());
		isGood=false;
	}

	if(isGood && table1copy.capacity() != table1.capacity()){
		error="Error 8d: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(table1.capacity());
		error+="\nYour function returns: ";
		error+=std::to_string(table1copy.capacity());
		isGood=false;
	}
	if(isGood && table2copy.capacity() != table2.capacity()){
		error="Error 8e: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(table2.capacity());
		error+="\nYour function returns: ";
		error+=std::to_string(table2copy.capacity());
		isGood=false;

	}
	if(isGood && table3copy.capacity() != table3.capacity()){
		error="Error 8f: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(table3.capacity());
		error+="\nYour function returns: ";
		error+=std::to_string(table3copy.capacity());
		isGood=false;
	}


    //alter original record's data
	while(count<650){
		table1.update(keys[i],data[i]+1);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.update(keys[i],data[i]+1);
		i++;
		count++;
	}
	count=0;
	while(count<40000){
		table3.update(keys[i],data[i]+1);
		i++;
		count++;
	}

	i=0;
	count=0;
	while(isGood && count<650){
		int value;
		isGood=table1copy.find(keys[i],value);
		if(!isGood){
			error="Error 8g: find returned false for a record that should exist in the table created with copy constructor";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 8h: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		int value;
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 8i: find returned false for a record that should exist in the table created with copy constructor";
		}
		else{
			if(value!=data[i]){
				isGood=false;								
				error="Error 8j: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<40000){
		int value;
		isGood=table3.find(keys[i],value);
		if(!isGood){
			error="Error 8k: find returned false for a record that should exist in the table created with copy constructor";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 8l: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";
			}
		}
		i++;
		count++;
	}


	return isGood;



}

/*Test 9: Check that deep copy was created with assignment operator*/
bool test9(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table1(1000,0.65);
	ChainingTable<int> table2(10000,1.0);
	ChainingTable<int> table3(200000,2.0);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<650){
		table1.update(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.update(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<1000000){
		table3.update(keys[i],data[i]);
		i++;
		count++;
	}

	//duplicate table1
	table2=table1;

	count=0;
	while(count<650){
		table1.update(keys[i],data[i]+2);
		i++;
		count++;
	}

	count=0;
	i=0;
	if(table2.numRecords() != 650){
		error="Error 9a: number of records was not correct.\n Correct number of records: 650";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	} 
	if(isGood && table2.capacity() != 1000){
		error="Error 9b: copy's capacity was not correct.\n Correct capacity: 1000 ";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	while(isGood && count<650){
		int value;
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 9c: find returned false for a record that should be in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 9d: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find() passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}
	int correctCap=1000;
	table2.update(keys[i],data[i]);
	correctCap*=2;
	if(isGood && table2.capacity() != correctCap){
		error="Error 9e: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	if(isGood && table2.numRecords() != 651){
		error="Error 9f: number of records was not correct.\n Correct number of records: 651";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	}

	table2=table3;
	correctCap = table3.capacity();
	if(table2.numRecords() != 1000000){
		error="Error 9g: number of records was not correct.\n Correct number of records: 650";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	} 
	if(isGood && table2.capacity() != correctCap){
		error="Error 9h: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}

	i=10650;
	count=0;
	while(count<1000000){
		table2.update(keys[i],data[i]+2);
		i++;
		count++;
	}

	count=0;
	i=10650;
	while(isGood && count<1000000){
		int value;
		isGood=table3.find(keys[i],value);
		if(!isGood){
			error="Error 9i: find returned false for a record that should be in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 9j: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find() passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}


	return isGood;
}


/*Test 10: Test move constructor*/
bool test10(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table(10000,0.65);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<6500){
		table.update(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;

	int correctCap=table.capacity();

	ChainingTable<int> moved1=std::move(table);
	if(isGood && moved1.capacity() != correctCap){
		error="Error 10a: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(moved1.capacity());
		isGood=false;
	}
	if(isGood && moved1.numRecords() != 6500){
		error="Error 10b: number of records was not correct.\n Correct number of records: 6500";
		error+="\nYour function returns: ";
		error+=std::to_string(moved1.numRecords());
		isGood=false;
	}
	i=0;
	count=0;
	while(isGood && count<6500){
		int value;
		isGood=moved1.find(keys[i],value);
		if(!isGood){
			error="Error 10c: find returned false for a record that should exist in the table created with copy constructor";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 10d: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";
			}
		}
		i++;
		count++;
	}
	moved1.update(keys[i],data[i]);
	correctCap*=2;
	if(isGood && moved1.capacity() != correctCap){
		error="Error 10e: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(moved1.capacity());
		isGood=false;
	}
	if(isGood && moved1.numRecords() != 6501){
		error="Error 10f: number of records was not correct.\n Correct number of records: 6501";
		error+="\nYour function returns: ";
		error+=std::to_string(moved1.numRecords());
		isGood=false;
	}
	return isGood;


}
/*Test 11: move assignment*/
bool test11(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table1(1000,0.65);
	ChainingTable<int> table2(10000,0.70);
	ChainingTable<int> table3(100000,0.60);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<650){
		table1.update(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<7000){
		table2.update(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<60000){
		table3.update(keys[i],data[i]);
		i++;
		count++;
	}

	//duplicate table2
	table2=std::move(table1);
	int correctCap=1000;

	if(isGood && table2.capacity() != correctCap){
		error="Error 11a: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	if(isGood && table2.numRecords() != 650){
		error="Error 11b: number of records was not correct.\n Correct number of records: 650";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	}

	count=0;
	i=0;
	while(isGood && count<650){
		int value;
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 11c: find returned false for a record that should be in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 11d: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find() passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}

	table2.update(keys[i],data[i]);
	correctCap*=2;
	if(isGood && table2.capacity() != correctCap){
		error="Error 11e: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	if(isGood && table2.numRecords() != 651){
		error="Error 11f: number of records was not correct.\n Correct number of records: 651";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	}
    
    correctCap=100000;
	table2=std::move(table3);

	if(isGood && table2.capacity() != correctCap){
		error="Error 11g: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	if(isGood && table2.numRecords() != 60000){
		error="Error 11h: number of records was not correct.\n Correct number of records: 60000";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	}


	i=7650;
	count=0;
	while(isGood && count<60000){
		int value;
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 11i: find returned false for a record that should be in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 11j: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find() passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}


	table2.update(keys[i],data[i]);
	correctCap*=2;
	if(isGood && table2.capacity() != correctCap){
		error="Error 11k: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	if(isGood && table2.numRecords() != 60001){
		error="Error 11l: number of records was not correct.\n Correct number of records: 60001";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	}
	return isGood;
}


void createData(std::string keys[],int data[],int max){
	FILE* fp=fopen("dictionary.txt","r");
	if(!fp){
		std::cout << "You need dictionary.txt in your current directory" << std::endl;
		exit(0);
	}
	int i=0;
	std::string front="A_";
	char curr[50];
	while(fscanf(fp,"%s\n",curr)==1){
		keys[i]=curr;
		data[i]=rand()%100;
		i++;                      
	}
	int numWords=i;
	int j=0;
	while(i<max){
		keys[i]=front+keys[j];
		data[i]=rand()%100;
		i++;
		j++;
		if(j==numWords){
			front[0]+=1;
			j=0;
		}
	}
}

