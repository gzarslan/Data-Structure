/**************************************************************************/
/*                                                                        */
/*   A1 part2 tester file                                                 */
/*                                                                        */
/*   To compile: g++ a1q2tester.cpp timer.cpp -std=c++0x                  */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/**************************************************************************/

#include "SortedList.h"
#include "timer.h"
#include <string>
#include <iostream>
#include <cstdlib>



bool test1(std::string& error); 
bool test2(std::string& error); 
bool test3(std::string& error); 
bool test4(std::string& error); 
bool test5(std::string& error); 
bool test6(std::string& error);
bool test7(std::string& error);
bool test8(std::string& error);
bool test9(std::string& error);
bool test10(std::string& error);
bool test11(std::string& error);
bool test12(std::string& error);
const int numTests=12;
typedef bool (*TestPtr)(std::string&);
struct Record{
    std::string word_;
    int count_;
    std::string toString() const{ 
        std::string s="{";
        s+= word_;
        s+= ",";
        s+= std::to_string(count_);
        s+= "}";
        return s;
    }
};
std::ostream& operator<<(std::ostream& os, const Record rec);
bool operator==(const Record& a,const Record& b);
bool operator!=(const Record& a,const Record& b);
bool operator <(const Record& a, const Record& b);
void swap(int& a,int& b);
template <typename T>
void mergeArray(T arr[],T tmp[],int startA,int startB,int endB);
template <typename T>
void mergeSort(T arr[],T tmp[],int start,int end);
template <typename T>
void mergeSort(T arr[],int size);
template <typename T>
void addBack(const T& data,T arr[],int sz);
template <typename T>
void removeItem(T arr[],int idx,int sz);
template <typename T>
bool checkList(const SortedList<T>& list,const T arr2[],int sz);
template <typename T>
void duplicateArray(T dest[], const T src[],int sz);
template <typename T>
void printLists(const SortedList<T>& list,const T array[],int sz);
template<typename T>
typename SortedList<T>::iterator setIterator(SortedList<T>& list, int idx);
template <typename T>
void add(const T& data,int idx, T arr[],int sz);
template <typename T>
int search(const T& data, T arr[],int sz);


int main(void){
    TestPtr runTest[numTests]={test1, test2, test3, test4, test5, 
                               test6, test7, test8, test9, test10,
                               test11,test12};
    std::string testSummary[numTests]={
                            "empty lists, size(), empty(), c/begin(), c/end()",
                            "insert(), size(), empty(), c/begin(), c/end()",
                            "increment operators pre and postfix",
                            "decrement operators pre and postfix",
                            "return values from increment operators",
                            "return values from decrement operators",
                            "search() functions",
                            "erase(iterator)",
                            "merge function",
                            "copy constructor",
                            "copy assignment operator",
                            "large data set and timing run"
                        };
    std::string msg;
    bool result=true;
    int numPassed=0;
    for(int i=0;result && i<numTests;i++){
        result = runTest[i](msg);
        if(!result){
            std::cout << "Test " << i+1 <<" - "<< testSummary[i]<< ": failed." << std::endl;
            std::cout << msg << std::endl;
        }
        else{
            numPassed++;
            std::cout << "Test " << i+1 <<" - "<< testSummary[i]<< ": passed." << std::endl;
        }
    }
    if(numPassed == numTests){
        std::cout << "Congratulations! You have passed testing for A1 part 1" << std::endl;
    }
    else{
        std::cout << "Looks like you still have some work left to do" << std::endl;
    }
}
/* test1: Create an empty list, check size(), empty(), begin(), end() 
   cbegin() and cend()
   functions.  test returns true if passed, false otherwise
*/
bool test1(std::string& error){
    SortedList<Record> theList;
    int result;
    bool rc=true;
    result=theList.size();
    if(result != 0){
        rc=false;
        error = "Error 1a: size() function returned ";
        error += std::to_string(result);
        error += " on an empty list, should return 0." ;        
    }
    if(rc && theList.empty()==false){
        rc=false;
        error = "Error 1b: empty() function returned false on empty list, should return true";
    }
    if(rc && theList.begin() != theList.end()){
        error = "Error 1c: list is empty, begin() and end() should return iterator to same node";
        rc=false;
    }
    if(rc && theList.cbegin() != theList.cend()){
        error = "Error 1d: list is cempty, cbegin() and cend() should return iterator to same node";
        rc=false;
    }
    return rc;
}

/*test2: test insertion and size(), empty(), begin() and end() are consistent*/
bool test2(std::string& error){
    Record recs[20]={
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };
    Record sortedRecs[20];
    for(int i=0;i<20;i++){
        sortedRecs[i]=recs[i];
    }
    mergeSort(sortedRecs,20);
    SortedList<Record> theList;
    SortedList<Record>::iterator result;
    bool rc=true;
    int listSize;
    for(int i=0;rc && i<20;i++){
        result=theList.insert(recs[i]);
        if(*result != recs[i]){
            rc=false;
            error = "Error 2a: return value from insert is not correct. Should return iterator to newly added node";
        }
    }
    listSize = theList.size();
    if(rc && listSize != 20){
        rc=false;
        error = "Error 2b: size() function returned ";
        error += std::to_string(listSize);
        error += ".  size() should return 20" ;        
    }
    if(rc && theList.empty() == true){
        rc=false;
        error = "Error 2c: empty() function returned true on a non-empty list";
    }
    if(rc && theList.begin() == theList.end()){
        error = "Error 2d: list is not empty, begin() and end() should return iterator to different nodes";
        rc=false;        
    }
    if(rc && theList.cbegin() == theList.cend()){
        error = "Error 2e: list is not empty, cbegin() and cend() should return iterator to different nodes";
        rc=false;        
    }

    return rc;
}

/*test3: test ++ operators ensuring list items are in correct order*/
bool test3(std::string& error){
    Record recs[20]={
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };
    Record sortedRecs[20];
    for(int i=0;i<20;i++){
        sortedRecs[i]=recs[i];
    }
    mergeSort(sortedRecs,20);
    SortedList<Record> theList;
    SortedList<Record>::iterator result;
    bool rc=true;
    int listSize;
    for(int i=0;rc && i<20;i++){
        result=theList.insert(recs[i]);
        if(*result != recs[i]){
            rc=false;
            error = "Error 3a: return value from insert is not correct. Should return iterator to newly added node";
        }
    }
    SortedList<Record>::iterator it= theList.begin();
    for(int i=0;rc && i<20;i++){
        if(*it != sortedRecs[i]){
            error = "Error 3b: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator++(int)";
            rc=false;
        }
        it++;
    }

    SortedList<Record>::const_iterator it2= theList.cbegin();
    for(int i=0;rc && i<20;i++){
        if(*it2 != sortedRecs[i]){
            error = "Error 3c: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it2).toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably in either insert() or const_iterator::operator++(int)";
            rc=false;
        }
        it2++;
    }

    it= theList.begin();
    for(int i=0;rc && i<20;i++){
        if(*it != sortedRecs[i]){
            error = "Error 3d: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator++()";
            rc=false;
        }
        ++it;
    }

    it2= theList.cbegin();
    for(int i=0;rc && i<20;i++){
        if(*it2 != sortedRecs[i]){
            error = "Error 3e: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it2).toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably in either insert() or const_iterator::operator++(int)";
            rc=false;
        }
        ++it2;
    }

    return rc;
}

/*test 4: test decrement (--) operators*/
bool test4(std::string& error){
    Record recs[20]={
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };
    Record sortedRecs[20];
    for(int i=0;i<20;i++){
        sortedRecs[i]=recs[i];
    }
    mergeSort(sortedRecs,20);
    SortedList<Record> theList;
    SortedList<Record>::iterator result;
    bool rc=true;
    int listSize;
    for(int i=0;rc && i<20;i++){
        result=theList.insert(recs[i]);
        if(*result != recs[i]){
            rc=false;
            error = "Error 4a: return value from insert is not correct. Should return iterator to newly added node";
        }
    }
    SortedList<Record>::iterator it = theList.end();
    for(int i=19;rc && i>=0;i--){
        it--;
        if(*it != sortedRecs[i]){
            error = "Error 4b: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator++(int)";
            rc=false;
        }
    }

    SortedList<Record>::const_iterator it2 = theList.cend();
    for(int i=19;rc && i>=0;i--){
        it2--;
        if(*it2 != sortedRecs[i]){
            error = "Error 4c: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it2).toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably in either insert() or const_iterator::operator++(int)";
            rc=false;
        }

    }

    it = theList.end();
    for(int i=19;rc && i>=0;i--){
        --it;
        if(*it != sortedRecs[i]){
            error = "Error 4d: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator++()";
            rc=false;
        }

    }

    it2 = theList.cend();
    for(int i=19;rc && i>=0;i--){
        --it2;
        if(*it2 != sortedRecs[i]){
            error = "Error 4e: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it2).toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably in either insert() or const_iterator::operator++(int)";
            rc=false;
        }

    }

    return rc;

}


/*test 5: Test return values of increment operators*/
bool test5(std::string& error){
    Record recs[20]={
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };
    Record sortedRecs[20];
    for(int i=0;i<20;i++){
        sortedRecs[i]=recs[i];
    }
    mergeSort(sortedRecs,20);
    SortedList<Record> theList;
    SortedList<Record>::iterator result;
    bool rc=true;
    int listSize;
    for(int i=0;rc && i<20;i++){
        result=theList.insert(recs[i]);
    }
    Record rec;
    SortedList<Record>::iterator it= theList.begin();
    for(int i=0;rc && i<20;i++){
        if((rec = *(it++)) != sortedRecs[i]){
            error = "Error 5a: data in node at referred to by *(it++) is not correct\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (rec).toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably return of postfix iterator";
            rc=false;
        }
    }
    SortedList<Record>::const_iterator it2= theList.cbegin();
    for(int i=0;rc && i<20;i++){
        if((rec = *(it2++)) != sortedRecs[i]){
            error = "Error 5b: data in node at referred to by *(it++) is not correct\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (rec).toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably return of postfix const_iterator";
            rc=false;
        }
    }

    it = theList.begin();

    for(int i=0;rc && i<20;i++){
        if(std::addressof(++it) != std::addressof(it)){
            error = "Error 5c: return value from prefix should be reference to iterator\n ";
            rc=false;

        }
    }
    it2= theList.cbegin();
    for(int i=0;rc && i<20;i++){
        if(std::addressof(++it2) != std::addressof(it2)){
            error = "Error 5d: return value from prefix should be reference to iterator\n ";
            rc=false;

        }
    }

    it = theList.begin();

    for(int i=0;rc && i<20;i++){
        if(i<19 && (rec = *(++it)) != sortedRecs[i+1] ){
            error = "Error 5e: data in node at referred to by *(++it) is not correct\n  Data at node # ";
            error += std::to_string(i+2);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably return of prefix iterator";
            rc=false;
  
        }
    }
    it2= theList.cbegin();
    for(int i=0;rc && i<20;i++){
        if(i<19 && (rec = *(++it2)) != sortedRecs[i+1] ){
            error = "Error 5f: data in node at referred to by *(++it) is not correct\n  Data at node # ";
            error += std::to_string(i+2);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably return of prefix const_iterator";
            rc=false;

        }
    }

    return rc;
}

/*Test 6: Test return values of decrement operators*/
bool test6(std::string& error){
    Record recs[20]={
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };
    Record sortedRecs[20];
    for(int i=0;i<20;i++){
        sortedRecs[i]=recs[i];
    }
    mergeSort(sortedRecs,20);
    SortedList<Record> theList;
    SortedList<Record>::iterator result;
    bool rc=true;
    int listSize;
    for(int i=0;rc && i<20;i++){
        result=theList.insert(recs[i]);
    }
    SortedList<Record>::iterator it= theList.end();
    it--;
    Record rec;
    for(int i=19;rc && i>0;i--){
        if((rec = *(it--)) != sortedRecs[i]){
            error = "Error 6a: data in node at referred to by *(it--) is not correct\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably return of postfix iterator";
            rc=false;
        }
    }
    SortedList<Record>::const_iterator it2= theList.cend();
    it2--;
    for(int i=19;rc && i>0;i--){
        if((rec = *(it2--)) != sortedRecs[i]){
            error = "Error 6b: data in node at referred to by *(it--) is not correct\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably return of postfix const_iterator";
            rc=false;
        }
    }

    it = theList.end();

    for(int i=19;rc && i>0;i--){
        if(std::addressof(--it) != std::addressof(it)){
            error = "Error 6c: return value from prefix should be reference to iterator\n ";
            rc=false;

        }
    }
    it2= theList.cend();
    for(int i=19;rc && i>0;i--){
        if(std::addressof(--it2) != std::addressof(it2)){
            error = "Error 6d: return value from prefix should be reference to iterator\n ";
            rc=false;

        }
    }

    it = theList.end();

    for(int i=19;rc && i>0;i--){
        if((rec = *(--it)) != sortedRecs[i] ){
            error = "Error 6e: data in node at referred to by *(++it) is not correct\n  Data at node # ";
            error += std::to_string(i+2);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably return of prefix iterator";
            rc=false;
  
        }
    }
    it2= theList.cend();
    for(int i=19;rc && i>=0;i--){
        if((rec = *(--it2)) != sortedRecs[i] ){
            error = "Error 6f: data in node at referred to by *(++it) is not correct\n  Data at node # ";
            error += std::to_string(i+2);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += sortedRecs[i].toString();
            error += "\nbug probably return of prefix iterator";
            rc=false;

        }
    }

    return rc;

}

/*Test 7: Test search()*/
bool test7(std::string& error){
    Record recs[20]={
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };
    Record sortedRecs[20];
    for(int i=0;i<20;i++){
        sortedRecs[i]=recs[i];
    }
    mergeSort(sortedRecs,15);
    SortedList<Record> theList;
    SortedList<Record>::iterator result;
    const SortedList<Record>* listPtr;
    listPtr=&theList;
    bool rc=true;
    int listSize;
    for(int i=0;rc && i<15;i++){
        result=theList.insert(recs[i]);
    }
    SortedList<Record>::const_iterator const_result;
    for(int i=0;rc && i<15;i++){
        const_result=listPtr->search(recs[i]);
        if(const_result == listPtr->cend()){
            rc=false;
            error = "Error 7a: item that should have been in the linked list was not found\n";
            error += "item being searched for: ";
            error += recs[i].toString();
        }
        else if(*const_result != recs[i]){
            rc=false;
            error = "Error 7b: item found was not the one being searched for\n";
            error += "item found: ";
            error += (*const_result).toString();
            error += "item being searched for: ";
            error += recs[i].toString();
        }

    }
    for(int i=15;i<20;i++){
        const_result=listPtr->search(recs[i]);
        if(const_result != listPtr->cend()){
            rc=false;
            error = "Error 7c: searching for an item that should not be in the list resulted in something that isn't cend() \n";
            error += "item being searched for: ";
            error += recs[i].toString();
        }        
    }

    for(int i=0;rc && i<15;i++){
        result=theList.search(recs[i]);
        if(result == theList.end()){
            rc=false;
            error = "Error 7d: item that should have been in the linked list was not found\n";
            error += "item being searched for: ";
            error += recs[i].toString();
        }
        else if(*result != recs[i]){
            rc=false;
            error = "Error 7e: item found was not the one being searched for\n";
            error += "item found: ";
            error += (*result).toString();
            error += "item being searched for: ";
            error += recs[i].toString();
        }

    }
    for(int i=15;i<20;i++){
        result=theList.search(recs[i]);
        if(result != theList.end()){
            rc=false;
            error = "Error 7f: searching for an item that should not be in the list resulted in something that isn't cend() \n";
            error += "item being searched for: ";
            error += recs[i].toString();
        }        
    }

    return rc;
}


/*Test 8: test erase(it)*/
bool test8(std::string& error){
    Record recs[20]={
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };
    Record sortedRecs[20];
    for(int i=0;i<20;i++){
        sortedRecs[i]=recs[i];
    }
    mergeSort(sortedRecs,20);
    SortedList<Record> theList;
    SortedList<Record>::iterator result;
    bool rc=true;

    for(int i=0;i<20;i++){
        result=theList.insert(recs[i]);
    }
    for(int i=19; i>= 17;i-- ){
        result=theList.search(sortedRecs[i]);
        result=theList.erase(result);
        if(result!=theList.end()){
            rc=false;
            error = "Error 8a: when last item in list is erased, return value should be end()";
        }
        else{
            if(theList.search(sortedRecs[i]) != theList.end()){
                rc=false;
                error = "Error 8b: when last item in list is erased, item should not be found in list";
            }
            else if(theList.size() != i){
                rc=false;
                error = "Error 8c: size() is not correct after erase(it) of last node\n your function returned: ";
                error += std::to_string(theList.size());
                error += ".  It should return: ";
                error += std::to_string(i);


            }
        }
    }
    SortedList<Record>::const_iterator it=theList.cbegin();
    for(int i=0;rc && i<17;i++){
        if(*it !=sortedRecs[i]){
            rc=false;
            error = "Error 8d: a record that was not erased is no longer in list";
        }
        it++;
    }
    if(rc && it!=theList.cend()){
        rc=false;
        error = "Error 8e: the list has more records than expected after erasing from end of list";
    }
    for(int i=0;rc && i< 3 ;i++ ){
        result=theList.search(sortedRecs[0]);
        result=theList.erase(result);
        if(result != theList.begin()){
            rc=false;
            error = "Error 8d: when first item in list is erased, return value should be begin()";
        }
        else{
            if(theList.search(sortedRecs[0]) != theList.end()){
                rc=false;
                error = "Error 8e: when first item in list is erased, item should not be found in list";
            }
            else if(theList.size() != 16-i){
                rc=false;
                error = "Error 8f: size() is not correct after erase(it) of first node\n Your function returned: ";
                error += std::to_string(theList.size());
                error += ".  It should return:";
                error += std::to_string(16-i);

            }
        }
        removeItem(sortedRecs,0,17-i);
    }

    it=theList.cbegin();
    for(int i=0;rc && i<14;i++){
        if(*it !=sortedRecs[i]){
            rc=false;
            error = "Error 8g: a record that was not erased is no longer in list";
        }
        it++;
    }
    if(rc && it!=theList.cend()){
        rc=false;
        error = "Error 8h: the list has more records than expected after erasing from end of list";
    }

    int listSize=14;
    SortedList<Record>::iterator next;
    for(int i=1; i< listSize ;i++ ){
        next=theList.search(sortedRecs[i]);
        result=theList.erase(next++);
        if(result != next){
            rc=false;
            error = "Error 8i: when erasing a node, return value is not the next node in list";
        }
        else{
            if(theList.search(sortedRecs[i]) != theList.end()){
                rc=false;
                error = "Error 8j: when a node in list is erased, item should not be found in list";
            }
            else if(theList.size() != listSize-1){
                rc=false;
                error = "Error 8k: size() is not correct after erase(it) of first node\n Your function returned: ";
                error += std::to_string(theList.size());
                error += ".  It should return:";
                error += std::to_string(16-i);

            }
        }
        removeItem(sortedRecs,i,listSize);
        listSize--;
    }
    it=theList.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=sortedRecs[i]){
            rc=false;
            error = "Error 8l: a record that was not erased is no longer in list";
        }
        it++;
    }
    if(rc && it!=theList.cend()){
        rc=false;
        error = "Error 8m: the list has more records than expected after erasing from end of list";
    }


    return rc;
}

/*Test 9: test merge()*/
bool test9(std::string& error){  //Calvin and brown dog fox jumped lazy over quick tea
    Record recs[20]={   //Hobbes captain carrot coffee lavender lilac lily night the watch
        {"tea",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"the",20}
    };
    Record sortedRecs[20];
    for(int i=0;i<20;i++){
        sortedRecs[i]=recs[i];
    }
    mergeSort(sortedRecs,20);
    SortedList<Record> list1;
    SortedList<Record> list2;
    bool rc=true;
    Record* locations[40];
    SortedList<Record>::iterator it,it2;
    SortedList<Record>::iterator result;

    for(int i=0;i<20;i++){
        result=list1.insert(recs[i]);
    }
 
    list1.merge(list2);
    if(list1.size()!=20 || list2.size() != 0 || !list2.empty() || list1.empty()){
        rc=false;
        error = "Error 9a: merging an empty list into a non-empty list resulted in at least one list\n";
        error += "being the wrong size or list2 being not empty or list1 being empty()";        
    }
    if(rc){
        it=list1.begin();
        for(int i=0;it!=list1.end();it++, i++){
            locations[i]=&(*it);
        }
        list2.merge(list1);
        if(list1.size()!=0 || list2.size() !=20 || list2.empty() || !list1.empty()){
            rc=false;
            error = "Error 9b: merging an non-empty list into a empty list resulted in at least one list\n";
            error += "being the wrong size or list1 being not empty or list2 being empty()";        
    
        }
        it=list2.begin();
        for(int i=0;rc && it!=list2.end();it++, i++){
            if(locations[i] != &(*it)){
                rc=false;
                error = "Error 9c: merged items were not suppose to be duplicates of what was merged\n";
                error += "orginal nodes were suppose to be relinked to form merged list.";
            }
        }
        it=list2.begin();
        for(int i=0;rc && it!=list2.end();it++, i++){
            if(*it != sortedRecs[i]){
                rc=false;
                error = "Error 9d: merged list is not sorted";
            }
        }
    }
    if(rc){
        SortedList<Record> list3;
        SortedList<Record> list4;
        for(int i=0;i<10;i++){
            list3.insert(recs[i]);
            list4.insert(recs[i+10]);
        }
        it=list3.begin();
        for(int i=0;it!=list3.end();it++, i++){
            locations[i]=&(*it);
        }
        it=list4.begin();
        for(int i=10;it!=list4.end();it++, i++){
            locations[i]=&(*it);
        }
        list3.merge(list4);
        if(list3.size()!=20 || list4.size() !=0 || list3.empty() || !list4.empty()){
            rc=false;
            error = "Error 9e: merging two list resulted in at least one list\n";
            error += "being the wrong size or not returning properly for  empty()";        
    
        }
        it=list3.begin();
        for(int i=0;rc && it!=list3.end();it++, i++){
            if(search(&(*it),locations,20) == -1){
                rc=false;
                error = "Error 9f: merged items were not suppose to be duplicates of what was merged\n";
                error += "original nodes were suppose to be relinked to form merged list.";
            }
        }
        if(rc && !checkList(list3,sortedRecs,20)){
            rc=false;
            error = "Error 9g: merged list is not correctly ordered";
        }
    }
    if(rc){
        SortedList<Record> list5;
        SortedList<Record> list6;
        for(int i=0;i<10;i++){
            list5.insert(recs[i]);
            list6.insert(recs[i+10]);
        }
        it=list5.begin();
        for(int i=0;it!=list5.end();it++, i++){
            locations[i]=&(*it);
        }
        it=list6.begin();
        for(int i=10;it!=list6.end();it++, i++){
            locations[i]=&(*it);
        }
        list6.merge(list5);
        if(list6.size()!=20 || list5.size() !=0 || list6.empty() || !list5.empty()){
            rc=false;
            error = "Error 9h: merging two list resulted in at least one list\n";
            error += "being the wrong size or not returning properly for  empty()";        
    
        }
        it=list6.begin();
        for(int i=0;rc && it!=list6.end();it++, i++){
            if(search(&(*it),locations,20) == -1){
                rc=false;
                error = "Error 9i: merged items were not suppose to be duplicates of what was merged\n";
                error += "original nodes were suppose to be relinked to form merged list.";
            }
        }
        if(rc && !checkList(list6,sortedRecs,20)){
            rc=false;
            error = "Error 9j: merged list is not correctly ordered";
        }
    }
    if(rc){
        SortedList<Record> list7;
        SortedList<Record> list8;
        for(int i=0;i<20;i++){
            list7.insert(recs[i]);
            list8.insert(recs[i]);
        }
        it=list7.begin();
        it2=list8.begin();
        for(int i=0;it!=list7.end();it++, i++, it2++){
            locations[i*2]=&(*it);
            locations[i*2+1]=&(*it2);

        }
        list7.merge(list8);
        if(list7.size()!=40 || list8.size() !=0 || list7.empty() || !list8.empty()){
            rc=false;
            error = "Error 9k: merging two list resulted in at least one list\n";
            error += "being the wrong size or not returning properly for  empty()";        
    
        }
        it=list7.begin();
        for(int i=0;rc && it!=list7.end();it++, i++){
            if(&(*it)!=locations[i]){
                rc=false;
                error = "Error 9l: when items of the two lists contains an item of equal value";
                error += "the item in current list goes before item in other";
            }
        }
        it=list7.begin();
        for(int i=0;rc && it!=list7.end();it++, i++){
            if((*it)!=sortedRecs[i/2]){
                rc=false;
                error = "Error 9m: after merging two lists with duplicates the ordering is not correct";
            }
        }


    }
    return rc;

}


/*Test 10: Test copy constructor Operator*/
bool test10(std::string& error){
    Record recs[20]={
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };
    Record sortedRecs[20];
    for(int i=0;i<20;i++){
        sortedRecs[i]=recs[i];
    }
    mergeSort(sortedRecs,20);
    SortedList<Record> theList;
    SortedList<Record>::iterator origIt;
    SortedList<Record>::iterator copyIt;
    bool rc=true;

    for(int i=0;i<20;i++){
        theList.insert(recs[i]);
    }

    SortedList<Record> copy=theList;

    if(copy.size() != theList.size()){
        rc=false;
        error = "Error 10a: list created with copy constructor does not properly copy the size";
    }
    if(rc && copy.empty()){
        rc=false;
        error = "Error 10b: list created with copy constructor is empty()";
    }
    origIt=theList.begin();
    copyIt=copy.begin();
    while(rc && origIt!=theList.end()){
        if(copyIt == copy.end()){
            rc=false;
            error = "Error 10c: duplicate list has less nodes than original";            
        }
        if(rc && *origIt != *copyIt){
            rc=false;
            error = "Error 10d: duplicate list does not have same data as original";            
        }
        if(rc && std::addressof(*origIt) == std::addressof(*copyIt)){
            rc=false;
            error = "Error 10e: deep copy does not appear to have been made";            
        }
        origIt++;
        copyIt++;
    }
    if(rc && copyIt!=copy.end()){
        rc=false;
        error = "Error 10f: duplicate list appears to have more nodes than original";            
    }

    return rc;
}
/*Test 11: Test copy assignment Operator*/
bool test11(std::string& error){
    Record recs[20]={
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };
    Record sortedRecs[20];
    Record sortedRecs2[20];
    Record sortedRecs3[20];

    for(int i=0;i<10;i++){
        sortedRecs[i]=recs[i];
        sortedRecs2[i]=recs[i];
    }
    for(int i=10;i<20;i++){
        sortedRecs[i]=recs[i];
        sortedRecs3[i-10]=recs[i];
    }
    mergeSort(sortedRecs,20);
    SortedList<Record> theList;
    SortedList<Record>::iterator origIt;
    SortedList<Record>::iterator copyIt;
    SortedList<Record> copy1;
    SortedList<Record> copy2;
    bool rc=true;

    for(int i=0;i<20;i++){
        theList.insert(recs[i]);
        copy1.insert(recs[i]);
    }
    for(int i=10;i<20;i++){
        copy2.insert(recs[i]);
    }

    copy1=copy2;

    if(copy1.size() != copy2.size()){
        rc=false;
        error = "Error 11a: list assigned to by copy assignment does not properly copy the size";
    }
    if(rc && copy1.empty()){
        rc=false;
        error = "Error 11b: list assigned to by copy assignment is empty()";
    }
    origIt=copy2.begin();
    copyIt=copy1.begin();
    while(rc && origIt!=copy2.end()){
        if(copyIt == copy1.end()){
            rc=false;
            error = "Error 11c: duplicate list has less nodes than original";            
        }
        if(rc && *origIt != *copyIt){
            rc=false;
            error = "Error 11d: duplicate list does not have same data as original";            
        }
        if(rc && &(*origIt) == &(*copyIt)){
            rc=false;
            error = "Error 11e: deep copy does not appear to have been made";            
        }
        origIt++;
        copyIt++;
    }
    if(rc && copyIt!=copy1.end()){
        rc=false;
        error = "Error 11f: duplicate list appears to have more nodes than original";            
    }

    copy1 = copy2 = theList;

    if(copy1.size() != copy2.size() || copy1.size() !=theList.size()){
        rc=false;
        error = "Error 11g: list assigned to by copy assignment does not properly copy the size";
    }
    if(rc && (copy1.empty() || copy2.empty())){
        rc=false;
        error = "Error 11h: list assigned to by copy assignment is empty()";
    }
    origIt=theList.begin();
    copyIt=copy1.begin();
    while(rc && origIt!=theList.end()){
        if(copyIt == copy1.end()){
            rc=false;
            error = "Error 11i: duplicate list has less nodes than original";            
        }
        if(rc && *origIt != *copyIt){
            rc=false;
            error = "Error 11j: duplicate list does not have same data as original";            
        }
        if(rc && &(*origIt) == &(*copyIt)){
            rc=false;
            error = "Error 11k: deep copy does not appear to have been made";            
        }
        origIt++;
        copyIt++;
    }
    if(rc && copyIt!=copy1.end()){
        rc=false;
        error = "Error 11l: duplicate list appears to have more nodes than original";            
    }
    origIt=theList.begin();
    copyIt=copy2.begin();
    while(rc && origIt!=theList.end()){
        if(copyIt == copy2.end()){
            rc=false;
            error = "Error 11m: duplicate list has less nodes than original";            
        }
        if(rc && *origIt != *copyIt){
            rc=false;
            error = "Error 11n: duplicate list does not have same data as original";            
        }
        if(rc && &(*origIt) == &(*copyIt)){
            rc=false;
            error = "Error 11o: deep copy does not appear to have been made";            
        }
        origIt++;
        copyIt++;
    }
    if(rc && copyIt!=copy2.end()){
        rc=false;
        error = "Error 11p: duplicate list appears to have more nodes than original";            
    }

    return rc;   
}

/*Test 12: Timing runs*/
bool test12(std::string& error){
    int listSize=20000;
    Timer t;
    bool rc=true;
    int* array=new int[listSize];
    for(int i=0;i<listSize;i++){
        array[i]=i+1;
    }

    for(int i=0;i<listSize;i++){
        int pick = rand()%(listSize-i);
        swap(array[pick],array[listSize-i-1]);
    }   

    SortedList<int> theList;
    SortedList<int> copy2;
    for(int i=0;i<listSize;i++){
        t.start();
        theList.insert(array[i]);
        t.stop();
        copy2.insert(array[i]);
        array[i]=i+1;
    }

    std::cout << listSize << " insert(): " << t.currtime() << std::endl;
    SortedList<int>::const_iterator it;
    it=theList.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=array[i]){
            rc=false;
            error = "12a: insertion error on large data set\n";
            error += "Your record: ";
            error += std::to_string(*it);
            error += "correct data ";
            error += std::to_string(array[i]);

        }
        it++;
    }
    t.reset();
    t.start();
    SortedList<int> copy1 = theList;
    t.stop();
    std::cout << "copy constructor on list with " << listSize << " nodes: " << t.currtime() << std::endl;
    it = theList.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=array[i]){
            rc=false;
            error = "12b: copy constructor error on large data set\n";
            error += "Your record: ";
            error += std::to_string(*it);
            error += "correct data ";
            error += std::to_string(array[i]);
        }
        it++;
    }
    t.reset();
    t.start();
    copy2 = theList;
    t.stop();
    std::cout << "assignment operator on list with " << listSize << " nodes: " << t.currtime() << std::endl;
    it = theList.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=array[i]){
            rc=false;
            error = "12c: assignment operator error on large data set\n";
            error += "Your record: ";
            error += std::to_string(*it);
            error += "correct data ";
            error += std::to_string(array[i]);
        }
        it++;
    }
    t.reset();
    t.start();
    SortedList<int> copy3=std::move(theList);
    t.stop();
    std::cout << "move constructor on list with " << listSize << " nodes: " << t.currtime() << std::endl;
    it = copy3.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=array[i]){
            rc=false;
            error = "12d: move constructor error on large data set\n";
            error += "Your record: ";
            error += std::to_string(*it);
            error += "correct data ";
            error += std::to_string(array[i]);
        }
        it++;
    }
    t.reset();
    t.start();
    copy2=std::move(copy3);
    copy1=std::move(copy2);
    t.stop();
    std::cout << "move assignment on list with " << listSize << " nodes: " << t.currtime() << std::endl;
    it = copy1.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=array[i]){
            rc=false;
            error = "12e: move assignment error on large data set\n";
            error += "Your record: ";
            error += std::to_string(*it);
            error += "correct data ";
            error += std::to_string(array[i]);
        }
        it++;
    }


    delete [] array;
    return rc;
}

void swap(int& a,  int& b){
    int tmp=a;
    a=b;
    b=tmp;
}
std::ostream& operator<<(std::ostream& os, const Record rec){
    os << rec.word_;
    return os;
}
bool operator==(const Record& a,const Record& b){
    bool rc=false;
    if(a.word_==b.word_ && a.count_==b.count_){
        rc=true;
    }
    return rc;
}
bool operator!=(const Record& a,const Record& b){
    return !(a==b);
}
bool operator <(const Record& a, const Record& b){
    bool rc=false;
    if(a.word_< b.word_){
        rc=true;
    }
    return rc;
}

template <typename T>
void mergeSort(T arr[],T tmp[],int start,int end){
  //if the array is more than one element big
    if(start<end){
        int mid=(start+end)/2;
        mergeSort(arr,tmp,start,mid);
        mergeSort(arr,tmp,mid+1,end);
        mergeArray(arr,tmp,start,mid+1,end);
    }
}
/*function merges the two halfs of a sorted array together.
  The arrays are defined from arr[startA]to arr[startB-1] and arr[startB]
to arr[endB]*/

template <typename T>
void mergeArray(T arr[],T tmp[],int startA,int startB,int endB){
    int aptr=startA;
    int bptr=startB;
    int idx=startA;
    while(aptr < startB && bptr < endB+1){
        if(arr[aptr] < arr[bptr]){
            tmp[idx++]=arr[aptr];
            aptr++;
        }
        else{
            tmp[idx++]=arr[bptr];
            bptr++;
        }
    }
//merge function only does one of the two following loops
    while(aptr<startB){
        tmp[idx]=arr[aptr];
        idx++;
        aptr++;    
    }
    while(bptr < endB+1){
        tmp[idx++]=arr[bptr];
        bptr++;
    }

//copy back into arr
    for(int i=startA;i<=endB;i++){
        arr[i]=tmp[i];
    }
}

/*this is the wrapper function that "main" uses.  The world see's this and
  use this. The actual work is done by the other MergeSort() function*/
template <typename T>
void mergeSort(T arr[],int size){
    T* tmp=new T[size];
    mergeSort(arr,tmp,0,size-1);
    delete [] tmp;
}


template <typename T>
void add(const T& data,int idx, T arr[],int sz){
    for(int i=sz-1;i>=idx;i--){
        arr[i+1]=arr[i];
    }
    arr[idx]=data;
}
template <typename T>
void removeItem(T arr[],int idx,int sz){
    for(int i=idx;i<sz-1;i++){
        arr[i]=arr[i+1];
    }
}
template <typename T>
bool checkList(const SortedList<T>& list,const T array[],int sz){
    bool rc=true;
    auto it=list.cbegin();
    int i;
    for(i=0;i<sz && it!=list.cend() && rc;i++,it++){
        if(*it != array[i]){
            rc=false;
        }
    }
    if(it!=list.cend() || i < sz){
        rc=false;
    }
    return rc;
}
template <typename T>
void addBack(const T& data,T arr[],int sz){
    arr[sz]=data;
}
template <typename T>
void duplicateArray(T dest[], const T src[],int sz){
    for(int i=0;i<sz;i++){
        dest[i]=src[i];
    }
}

template <typename T>
int search(const T& data, T arr[],int sz){
    int rc=-1;
    for(int i=0;rc==-1 && i<sz;i++){
        if(arr[i]==data){
            rc=i;
        }
    }
    return rc;
}

template <typename T>
void printLists(const SortedList<T>& list,const T array[],int sz){
    std::cout << "your size() returned: " << list.size() << std::endl;
    std::cout << "correct size returned: " << sz << std::endl;
    auto it=list.begin();
    for(int i=0;i<sz;i++,(it==list.end())?it:it++){
        std::cout << "correct: "  << array[i];
        if(it!=list.end()){
            std::cout << " your list: " << *it << std::endl;
        }
        else{
            std::cout << "your list: " << "<no data>" <<  std::endl;
        }
    }
}
//returns iterator to the idx'th node in the list
template <typename T>
typename SortedList<T>::iterator setIterator(SortedList<T>& list, int idx){
    typename SortedList<T>::iterator it=list.begin();
    for(int i=0;i<idx;i++){
        it++;
    }
    return it;
}