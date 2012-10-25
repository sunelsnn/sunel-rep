/*
 * testRTTI.cpp
 *
 *  Created on: Oct 21, 2012
 *      Author: root
 */


/* A base class pointer can point to objects of any class which is derived
 * from it. RTTI is useful to identify which type (derived class) of object is
 * pointed to by a base class pointer.
 */

#include <iostream>
#include <typeinfo>

class abc   // base class
{
public:
  virtual ~abc() { }
  virtual void hello()
  {
    std::cout << "in abc";
  }
};

class xyz : public abc
{
  public:
  void hello()
  {
    std::cout << "in xyz";
  }
};


class con
{

      struct node
      {
             int data;
                int rest;



};
    public:

      int a;
      int b;

      char k;

    //  char a;
      //  int k;
     //  int d;
      //  int d;
           con()
           {
        	  //  a=0 ;
        	 //   k=0 ;
        	  // d=0 ;

           }

      //   void printa() { //std::cout<<a ;
      //  	}

         //  virtual void printb() {} ;
         //   virtual void printc() {} ;
          //  virtual void printd() {} ;

           };




class lmn : public abc
{
public:
	void hello()
	{
		std::cout<< "\n in lmn" ;
	}
};

class base {
  public:
    virtual ~base(){}
};

/*
class derived : public base {
  public:
    virtual ~derived(){}
    int compare (derived &ref);
};
*/
/*
int my_comparison_method_for_generic_sort (base &ref1, base &ref2)
{
  derived & d = dynamic_cast<derived &>(ref1); // RTTI used here
  // RTTI enables the process to throw a bad_cast exception
  // if the cast is not successful
  return d.compare (dynamic_cast<derived &>(ref2));
}
*/

class Base
{

public:
	Base() { std::cout<<"\n +1" ;}
} ;
class D1: public  Base
{
} ;
class D2:virtual public Base
{
} ;

class D3 : public Base
{
} ;
class DD: public D1, public D2, public D3
{
} ;

class  charsizetest
{
char ch1 ;
char ch2 ;
char ch3 ;
char ch4 ;
char ch5 ;
char ch6 ;
char ch7 ;
char ch8 ;
char ch9 ;
// int x ;

public :
charsizetest()
{
//	ch1 = "abcd" ;
//	ch2[] ;

}
virtual void print() {} ;
} ;

int main()
{


	DD testobj;
	con c ;
	// c.printa() ;

	        std::cout<<"size of con class ="<<sizeof(c)<<"\n";

	      charsizetest   cst ;
	      std::cout<<"size of cst class ="<<sizeof(cst)<<"\n";
	int * a,b;
	  a=0; b=0;
	  if (typeid(a) != typeid(b))
	  {
	    std::cout << "a and b are of different types:\n";
	    std::cout << "a is: " << typeid(a).name() << '\n';
	    std::cout << "b is: " << typeid(b).name() << '\n';
	  }


  abc *abc_pointer = new lmn();
  xyz *xyz_pointer;


  int *tempint = new int[5] ;
  // to find whether abc_pointer is pointing to xyz type of object
  xyz_pointer = dynamic_cast<xyz*>(abc_pointer);
  std::cout<< "\n  xyz "<< xyz_pointer << " abc  " << abc_pointer ;

  if (xyz_pointer != NULL)
  {
    std::cout << "abc_pointer is pointing to a xyz class object";   // identified
  }
  else
  {
    std::cout << "abc_pointer is NOT pointing to a xyz class object";
  }

  xyz_pointer = static_cast<xyz*>(abc_pointer);
  std::cout<< "\n  xyz "<< xyz_pointer << " abc  " << abc_pointer ;

    if (xyz_pointer != NULL)
    {
      std::cout << "abc_pointer is pointing to a xyz class object";   // identified
    }
    else
    {
      std::cout << "abc_pointer is NOT pointing to a xyz class object";
    }

    xyz_pointer = reinterpret_cast <xyz*>(abc_pointer);
    std::cout<< "\n  xyz "<< xyz_pointer << " abc  " << abc_pointer ;

      if (xyz_pointer != NULL)
      {
        std::cout << "abc_pointer is pointing to a xyz class object";   // identified
      }
      else
      {
        std::cout << "abc_pointer is NOT pointing to a xyz class object";
      }

  // needs virtual destructor
  delete abc_pointer;

  return 0;
}
