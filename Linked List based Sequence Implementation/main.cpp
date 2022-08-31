#include"Sequence.h"
#include<string>
#include<iostream>
#include<cassert>

using namespace std;

int main()
{

	Sequence ww, qq, result1, result2;
	ItemType www, qqq;
	ww.insert(0, "A");
	ww.insert(1, "C");
	ww.insert(2, "E");
	ww.insert(3, "G");
	ww.insert(4, "I");
	ww.insert(5, "J");
	assert((ww.get(5, qqq) == true) && (qqq == "J"));
	qq.insert(0, "B");
	qq.insert(1, "D");
	qq.insert(2, "F");
	qq.insert(3, "H");

	interleave(ww, qq, result1);
	interleave(qq, ww, result2);
	ItemType arr1[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };
	ItemType arr2[] = { "B", "A", "D", "C", "F", "E", "H", "G", "I", "J" };
	assert((result1.size() == result2.size()) && (result1.size() == 10));


	for (int i = 0; i < result1.size(); i++)
	{
		result1.get(i, qqq);
		result2.get(i, www);
		assert(qqq == arr1[i]);
		assert(www == arr2[i]);
	}

	Sequence cek(result1), result3, result4;

	interleave(result3, result3, qq);
	assert(qq.empty() == true);
	interleave(cek,result1, result3);
	interleave(result1, result1, result4);

	for (int i = 0; i < result3.size(); i++)
	{
		result3.get(i, qqq);
		result4.get(i, www);
		assert(qqq == www);
	}


	//////////////////////////////// int interleave(const Sequence& seq1,const Sequence& seq2, Sequence& result) ////////////////////////////////////

	Sequence pubs;
	Sequence subs;
	pubs.insert(0, "30");
	pubs.insert(1, "21");
	pubs.insert(2, "63");
	pubs.insert(3, "42");
	pubs.insert(4, "17");
	pubs.insert(5, "63");
	pubs.insert(6, "17");
	pubs.insert(7, "29");
	pubs.insert(8, "8");
	pubs.insert(9, "32");
	 
	
	subs.insert(0, "63");
	subs.insert(1, "17");
	subs.insert(2, "29");
	assert(subsequence(pubs, subs) == 5);
	subs.set(0, "17");
	subs.set(1, "63");
	subs.set(2, "29");
	assert(subsequence(pubs, subs) == -1);
	assert(subsequence(subs, subs) == 0);
	assert(subsequence(pubs, pubs) == 0);


	//////////////////////////////// int subsequence(Sequence& seq1, Sequence& seq2) ////////////////////////////////////
	cout << "prophecy holds" << endl;
	ItemType x;
	Sequence s;	// does it initilize empty linked list?
	assert(s.empty() == true);
	assert(s.size() == 0);

	/////////////////////////////// default constructor ////////////////////////////////////////






	Sequence b = s;	// does it copy empty linked list?
	assert(b.empty() == true);	
	assert(b.size() == 0);
	s.insert("Hi");	// s = {Hi}

			// does it copy single element linked list?
	Sequence c = s;	// c = {Hi}
	assert(c.empty() == false);
	assert(c.size() == 1);
	assert(c.find("Hi") == 0);	// s = {Hi}
	s.insert("FF");	// s = {FF, Hi}


	s.insert("Hi");	//s  = {FF,Hi, Hi}
	

	Sequence d = s;	// does it copy multiple element linked list?
	assert(d.empty() == false);	//d = { FF,Hi, Hi }
	assert(d.size() == 3);
	assert(d.find("Hi") == 1);
	assert(d.get(2, x) == true);
	assert(x == "Hi");
	assert(d.get(0, x) == true);
	assert(x == "FF");

	/////////////////////////////// copy constructor ////////////////////////////////////////






	d = d; // does it account for aliasing?
	assert(d.empty() == false);
	assert(d.size() == 3);
	assert(d.find("Hi") == 1); //d  = {FF, Hi, Hi}
	assert(d.get(2, x) == true);
	assert(x == "Hi");
	assert(d.get(0, x) == true);
	assert(x == "FF");

	d = b;	// does it assign empty linked list correctly?
	assert(b.empty() == true); // b = {}
	assert(b.size() == 0);		

	d = c;	// does it assign single element linked list correctly?
	assert(c.empty() == false);	// c = {Hi}
	assert(c.size() == 1);
	assert(c.find("Hi") == 0);

	d = s;			// does it assign multiple element linked list correctly?
	assert(d.empty() == false);
	assert(d.size() == 3);
	assert(d.find("Hi") == 1); //d  = {FF, Hi, Hi}
	assert(d.get(2, x) == true);
	assert(x == "Hi");
	assert(d.get(0, x) == true);
	assert(x == "FF");

	/////////////////////////////// assignment operator ////////////////////////////////////////


	assert(d.empty() == false);	// does it have the correct output for empty/single element/multiple element linked lists?
	assert(c.empty() == false);
	assert(b.empty() == true);

	/////////////////////////////// bool empty() const; ////////////////////////////////////////
	
		// does it append  an element at the end of the linked list correctly?
	// does it append  an element at the start of the linked list correctly?
	// does it insert in the correct position?

	// The above questions are all tested below


	Sequence f = b;	// does it insert into empty linked list correctly?
	assert(f.insert(0, "HELLO") == 0);
	assert(f.insert(90, "HELLO") == -1);
	assert(f.find("HELLO") == 0);

	Sequence g = c, p = c;	// does it insert into single element linked list correctly?
	assert(g.insert(0, "WOW") == 0); // g = {WOW ,Hi}
	assert(p.insert(1, "WOW") == 1);	// p = {Hi, WOW}
	assert(g.find("WOW") == 0);
	assert(g.insert(90, "HELLO") == -1);
	assert(p.insert(90, "HELLO") == -1);
	assert(p.insert(-10, "HELLO") == -1);
	assert(p.find("WOW") == 1);


	Sequence k = d; // does it insert into multiple element linked list correctly?	
	cout << "Printing contents of s at line 118" << endl;
	for (int i = 0; i < k.size(); i++)
	{
		k.get(i, x);
		cout << x << endl;
	}
	k.insert(0, "Fluff");	// k = {"Fluff", FF, Hi, Hi}
	ItemType xx;
	cout << "Printing contents of s at line 126" << endl;
	for (int i = 0; i < k.size(); i++)
	{
		k.get(i, xx);
		cout << xx << endl;
	}
	assert(k.get(0, x) == true);
	assert(k.insert(90, "HELLO") == -1);
	assert(x == "Fluff");
	k.insert(k.size(), "Fun");	 // k = { "Fluff", FF, Hi, Hi, "Fun" }
	assert(k.get((k.size() - 1), x) == true);
	ItemType y;
	assert(k.get(4, y) == true);
	assert(x == y);
	assert(x == "Fun");
	k.insert(2, "Man");	// k = { "Fluff", FF, "Man", Hi, Hi, "Fun" }
	assert(k.get(2, x) == true);
	assert(x == "Man");

	k.insert(3, "FF");	// k = { "Fluff", FF, "Man", "FF", Hi, Hi, "Fun" }
	assert(k.get(3, x) == true);
	assert(x == "FF");
	k.insert(4, "A");	// k = { "Fluff", FF, "Man", "FF", A, Hi, Hi, "Fun" }
	assert(k.get(3, x) == true);
	assert(k.get(2, y) == true);
	assert(k.insert(90, "HELLO") == -1);
	assert(k.insert(-1, "HELLO") == -1);
	assert(x == "FF");
	assert(y == "Man");

	/////////////////////////////// int insert(int pos, const ItemType & value); ////////////////////////////////////////



	// does it append  an element at the end of the linked list correctly?
	// does it append  an element at the start of the linked list correctly?
	// does it return the correct integer output?
	// does it insert in the correct position?

	// The above questions are all tested below


	Sequence ff = b;	// does it insert into empty linked list correctly?
	assert(f.insert("A") == 0);
	assert(f.find("A") == 0);

	Sequence gg = c, pp = c;	// does it insert into single element linked list correctly?
	assert(gg.insert("A") == 0);
	assert(pp.insert("Ti") == 1);
	assert(gg.find("A") == 0); // gg = {A ,Hi} // p = {Hi, Ti}
	assert(pp.find("Ti") == 1);

	Sequence dd;
	assert(dd.insert("CC") == 0);
	assert(dd.insert("DD") == 1);
	Sequence kk = dd; // does it insert into multiple element linked list correctly?	
	assert(kk.insert("A") == 0);	// kk = {A, CC, DD}
	assert(kk.get(0, x) == true);
	assert(x == "A");
	assert(kk.insert("FF") == 3);	 // kk = {A, CC, DD, FF}
	assert(kk.get((kk.size() - 1), x) == true);
	assert(kk.get(3, y) == true);

	assert(x == y);
	assert(x == "FF");
	assert(kk.insert("B") == 1);	//kk = {A, B, CC, DD, FF}
	assert(kk.get(1, x) == true);
	assert(x == "B");
	assert(kk.insert("EE") == 4);	//kk = {A, B, CC, DD, EE, FF}
	assert(kk.get(4, x) == true);
	assert(x == "EE");
	/////////////////////////////// int Sequence::insert(const ItemType & value); ////////////////////////////////////////

	
	

	//does it handle empty linked list correctly?
	// does it erease from single element linked list correctly?
	// does it erease from multiple element linked list correctly?
	// does it return the correct boolean output?

	assert(kk.erase(90) == false);
	assert(kk.erase(0) == true);	//kk = {A, B, CC, DD, EE, FF}
	assert(kk.get(0, x) == true);	//kk = {B, CC, DD, EE, FF}
	assert(x == "B");

	assert((kk.size() - 1) == 4);
	assert(kk.erase(kk.size() - 1) == true);	//kk = {B, CC, DD, EE}
	assert(kk.get(2, x) == true);
	assert(x == "DD");
	assert(kk.get(3, x) == true);
	assert(x == "EE");
	assert(kk.get(1, x) == true);
	assert(x == "CC");
	assert(kk.get(0, x) == true);
	assert(x == "B");

	assert((kk.size() - 1) == 3);
	assert(kk.erase(1) == true);	//kk = {B, DD, EE}
	assert(kk.get(0, x) == true);
	assert(x == "B");
	assert(kk.get(1, x) == true);
	assert(x == "DD");

	
	assert(kk.get(2, x) == true);
	assert(x == "EE");
	assert(kk.erase(0) == true);	//kk = { DD, EE}
	assert(kk.erase(90) == false);
	assert(kk.erase(0) == true);	//kk = {EE}
	assert(kk.size() == 1);
	assert(kk.erase(1) == false);
	assert(kk.erase(-1) == false);
	assert(kk.erase(-100) == false);
	assert(kk.erase(90) == false);
	cout << "Printing contents of s at line 238" << endl;
	for (int i = 0; i < kk.size(); i++)
	{
		kk.get(i, x);
		cout << x << endl;
	}
	assert(kk.erase(0) == true);
	assert(kk.erase(-1) == false);
	assert(kk.erase(1) == false);
	assert(kk.empty() == true);
	



	/////////////////////////////// bool Sequence::erase(int pos); ////////////////////////////////////////
	

	//does it handle empty linked list correctly?
	// does it remove from single element linked list correctly?
	// does it remove from multiple element linked list correctly?
	// does it return the correct integer output?

	Sequence rem;
	for (int i = 0; i <= 64; i++)
	{
		if (i != 31)
		{
			rem.insert(i, "A");
		}
		else
		{
			rem.insert(31, "wow");
		}
	}

	assert(rem.get(31, y) == true);
	assert(y == "wow");

	for (int i = 0; i <= (rem.size()-1); i++)
	{
		rem.get(i, y);
		cout << y << " " << "element number: " << i << endl;
	}

	// k = { "Fluff", FF, "Man", "FF", A, Hi, Hi, "Fun" }
	assert(k.remove("Hi") == 2);
	assert(k.remove("FF") == 2);
	assert(k.remove("A") == 1);
	assert(k.remove("Hi") == 0);
	assert(k.remove("") == 0);
	assert(k.remove("HSDFHSKFS") == 0);
	///
	assert(k.remove("Fun") == 1);
	assert(k.remove("Fluff") == 1);
	assert(k.remove("Fluff") == 0);
	assert(k.remove("yolo") == 0);
	assert(k.remove("Man") == 1);
	assert(k.remove("Man") == 0);
	assert(k.remove("cannot remove from empty list") == 0);
	assert(rem.remove("A") == 64);

	
	for (int i = 1; i <= 64; i++)
	{
		rem.insert("wow");
	}

	for (int i = 0; i <= (rem.size() - 1); i++)
	{
		rem.get(i, y);
		cout << y << " " << "element number: " << i << endl;
	}

	assert(rem.remove("wow") == 65);
	assert((rem.empty() == true) && (rem.size() == 0));

	/////////////////////////////// int Sequence::remove(const ItemType& value); ////////////////////////////////////////


	// does this function return the correct value?
	// can this function work for empty linked lists?
	// can this function work for single element linked lists?
	//can this function work for multiple element linked lists?


	Sequence again;
	assert(again.get(-1, x) == false);
	assert(again.get(90, x) == false);
	assert(again.get(0, x) == false);
	assert(again.get(-100, x) == false);
	assert(again.get(1, x) == false);

	again.insert("A");
	assert(again.get(0, x) == true);
	assert(x == "A");
	assert(again.get(-1, x) == false);
	assert(again.get(90, x) == false);
	assert(again.get(0, x) == true);
	assert(again.get(-100, x) == false);
	assert(again.get(1, x) == false);

	again.insert("B");
	assert(again.get(0, x) == true);
	assert(x == "A");
	assert(again.get(1, x) == true);
	assert(x == "B");
	assert(again.get(-1, x) == false);
	assert(again.get(90, x) == false);
	assert(again.get(0, x) == true);
	assert(again.get(-100, x) == false);
	assert(again.get(1, x) == true);

	assert(again.insert("C") == 2);
	assert(again.get(0, x) == true);
	assert(x == "A");
	assert(again.get(1, x) == true);
	assert(x == "B");
	assert(again.get(2, x) == true);
	assert(x == "C");
	assert(again.get(-1, x) == false);
	assert(again.get(90, x) == false);
	assert(again.get(-100, x) == false);

	/////////////////////////////// bool Sequence::get(int pos, ItemType & value) const ////////////////////////////////////////

	// does this function return the correct value?
	// can this function work for empty linked lists?
	// can this function work for single element linked lists?
	//can this function work for multiple element linked lists?

	Sequence setter;
	assert(setter.set(0, "A") == false);
	assert(setter.set(-1, "A") == false);
	assert(setter.set(1, "A") == false);
	setter.insert(0, "A");
	assert(setter.set(0, "A") == true);
	assert(setter.set(-1, "A") == false);
	assert(setter.set(1, "A") == false);
	assert(setter.set(50, "A") == false);
	assert(setter.get(0, x) == true);
	assert(x == "A");
	assert(setter.set(0, "B") == true);
	assert(setter.get(0, x) == true);
	assert(x == "B");
	setter.insert(1, "B");
	assert(setter.set(0, "AAA") == true);
	assert(setter.set(1, "BBB") == true);
	assert(setter.set(50, "A") == false);
	assert(setter.set(-1, "A") == false);
	assert(setter.get(0, x) == true);
	assert(x == "AAA");
	assert(setter.get(1, x) == true);
	assert(x == "BBB");
	setter.insert(2, "CCC");
	assert(setter.set(0, "W") == true);
	assert(setter.set(1, "O") == true);
	assert(setter.set(2, "WW") == true);
	assert(setter.set(50, "A") == false);
	assert(setter.set(-1, "A") == false);
	assert(setter.get(0, x) == true);
	assert(x == "W");
	assert(setter.get(1, x) == true);
	assert(x == "O");
	assert(setter.get(2, x) == true);
	assert(x == "WW");
	
	/////////////////////////////// bool Sequence::set(int pos, const ItemType& value) ///////////////////////////////

	// does this function return the correct value?
	// can this function work for empty linked lists?
	// can this function work for single element linked lists?
	//can this function work for multiple element linked lists?

	Sequence finder;
	assert(finder.find("A") == -1);
	assert(finder.find("vvvvv") == -1);

	finder.insert(0, "A");
	assert(finder.find("A") == 0);
	assert(finder.find("vvvvv") == -1);

	finder.insert(1, "B");
	assert(finder.find("B") == 1);
	assert(finder.find("A") == 0);
	assert(finder.find("vvvvv") == -1);
	assert(finder.find("a") == -1);

	finder.insert(0, "bB");
	assert(finder.find("B") == 2);
	assert(finder.find("A") == 1);
	assert(finder.find("bB") == 0);
	assert(finder.find("a") == -1);

	/////////////////////////////// int Sequence::find(const ItemType& value) const ///////////////////////////////

	// does this function return the correct value?
	// can it handle aliasing?
	// can this function work for empty linked lists?
	// can this function work for single element linked lists?
	//can this function work for multiple element linked lists?
	// can we switch different types of linked lists (empty with nonempty, etc...)


	Sequence empty, singles, doubles, multiples;
	Sequence empty1, singles1, doubles1, multiples1;

	singles.insert("A");

	doubles.insert("B");
	doubles.insert("C");

	multiples.insert("D");
	multiples.insert("E");
	multiples.insert("F");
	multiples.insert("G");

	singles1.insert("1");

	doubles1.insert("2");
	doubles1.insert("3");

	multiples1.insert("4");
	multiples1.insert("5");
	multiples1.insert("6");
	multiples1.insert("7");

	empty.swap(empty);
	assert(empty.empty() == true);

	singles.swap(singles);
	assert(singles.find("A") == 0);

	doubles.swap(doubles);
	assert(doubles.find("B") == 0);
	assert(doubles.find("C") == 1);

	multiples.swap(multiples);
	assert(multiples.find("D") == 0);
	assert(multiples.find("E") == 1);
	assert(multiples.find("F") == 2);
	assert(multiples.find("G") == 3);


	empty.swap(empty1);
	assert(empty.empty() == true);

	singles.swap(singles1);
	assert(singles.find("1") == 0);
	assert(singles1.find("A") == 0);
	singles.swap(singles1);

	doubles.swap(doubles1);
	assert(doubles.find("2") == 0);
	assert(doubles.find("3") == 1);
	assert(doubles1.find("B") == 0);
	assert(doubles1.find("C") == 1);
	doubles.swap(doubles1);

	multiples.swap(multiples1);
	assert(multiples.find("4") == 0);
	assert(multiples.find("5") == 1);
	assert(multiples.find("6") == 2);
	assert(multiples.find("7") == 3);
	assert(multiples1.find("D") == 0);
	assert(multiples1.find("E") == 1);
	assert(multiples1.find("F") == 2);
	assert(multiples1.find("G") == 3);
	multiples.swap(multiples1);


	empty.swap(multiples);
	assert(multiples.empty() == true);
	assert(empty.find("D") == 0);
	assert(empty.find("E") == 1);
	assert(empty.find("F") == 2);
	assert(empty.find("G") == 3);
	empty.swap(multiples);

	empty.swap(doubles);
	assert(empty.find("B") == 0);
	assert(empty.find("C") == 1);
	assert(doubles.empty() == true);
	empty.swap(doubles);

	empty.swap(singles);
	assert(empty.find("A") == 0);
	assert(singles.empty() == true);
	empty.swap(singles);

	
	singles.swap(multiples);
	assert(singles.find("D") == 0);
	assert(singles.find("E") == 1);
	assert(singles.find("F") == 2);
	assert(singles.find("G") == 3);
	assert(multiples.find("A") == 0);
	singles.swap(multiples);

	singles.swap(doubles);
	assert(doubles.find("A") == 0);
	assert(singles.find("B") == 0);
	assert(singles.find("C") == 1);
	singles.swap(doubles);

	singles.swap(empty);
	assert(empty.find("A") == 0);
	assert(singles.empty() == true);
	singles.swap(empty);

	doubles.swap(multiples);
	assert(doubles.find("D") == 0);
	assert(doubles.find("E") == 1);
	assert(doubles.find("F") == 2);
	assert(doubles.find("G") == 3);
	assert(multiples.find("B") == 0);
	assert(multiples.find("C") == 1);
	doubles.swap(multiples);

	doubles.swap(singles);
	assert(doubles.find("A") == 0);
	assert(singles.find("B") == 0);
	assert(singles.find("C") == 1);
	doubles.swap(singles);

	doubles.swap(empty);
	assert(empty.find("B") == 0);
	assert(empty.find("C") == 1);
	assert(doubles.empty() == true);
	doubles.swap(empty);

	multiples.swap(doubles);
	assert(doubles.find("D") == 0);
	assert(doubles.find("E") == 1);
	assert(doubles.find("F") == 2);
	assert(doubles.find("G") == 3);
	assert(multiples.find("B") == 0);
	assert(multiples.find("C") == 1);
	multiples.swap(doubles);

	multiples.swap(singles);
	assert(singles.find("D") == 0);
	assert(singles.find("E") == 1);
	assert(singles.find("F") == 2);
	assert(singles.find("G") == 3);
	assert(multiples.find("A") == 0);
	multiples.swap(singles);


	multiples.swap(empty);
	assert(multiples.empty() == true);
	assert(empty.find("D") == 0);
	assert(empty.find("E") == 1);
	assert(empty.find("F") == 2);
	assert(empty.find("G") == 3);
	multiples.swap(empty);
	/////////////////////////////// void Sequence::swap(Sequence& other) ///////////////////////////////


	//END OF TEST
	return(0);
}