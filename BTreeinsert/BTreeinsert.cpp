/*
 * BTreeinsert.cpp
 *
 *  Created on: Oct 7, 2012
 *      Author: Sunil Mamidi
 *      Description : A regex function is implemented
 *      A main program that takes random tree structure and places into it an array of numbers that obeys binary tree principle.
 *
 *
 *
 */


// simple test
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>


using namespace std ;



class node
{

	int infocontent ;
public :

	 bool flag ;
	 node *leftchild ;
	 node *rightchild ;
     int nodeindex ;
     bool swapflag ;

	  node(int index)
		{
		  nodeindex = index;
		  infocontent = -10000 ;
		flag = false ;
		leftchild = NULL ;
		rightchild = NULL ;
		swapflag = false ;}

	  void setswapflag()
	  {
		  if(swapflag == false )
			  swapflag = true ;
		  else
			  {  std::cout<<" setting the swap flag twice  " ;  exit(0) ;}
	  }

  void  writeinfo( int value)
  {
	  infocontent = value;
  }

  int getinfo()
  {
	  return infocontent ;
  }
	};

class BinaryTree

{

private :

node *root ;


public :
  int globalreccount ;
 //  bool *swapflag ;
  BinaryTree() {  globalreccount=0 ; }
  BinaryTree(int numnodes,std::string str1) ;
// void BinaryTree(int, std::string) ;

  vector<std::string>  patternregex(std::string, std::string) ;

  //   void BinaryTree(int numnodes,std::string str1) ;

   bool  insertelements(int *elements, int  totalelements) ;
   node*  insertelement(node *n, int information ) ;
   node* navigate(node *rootnode, int index) ;
   bool inordertraversal(node *rootnode) ;
   void inordertraverse() ;
   node* returnparent(int nodeindex, int nodeinfo) ;
   node*  rec_insert(node *rootnode, int element ) ;

   bool unsetSwapflags(node *rootnode) ;
   int returnemptynodes(node* rootnode) ;
  };


bool BinaryTree::unsetSwapflags(node *rootnode)
   {

		if(rootnode == NULL)
				{  return false ;
				}
		unsetSwapflags(rootnode->leftchild) ;
	//  std::cout<<"\n nodeindex "<<rootnode->nodeindex<<" information "<< rootnode->info <<"  flag "<<rootnode->flag ;
		rootnode->swapflag = false ;
		unsetSwapflags(rootnode->rightchild) ;

   }

int BinaryTree::returnemptynodes(node* rootnode)
{

	int leftempty = 0;
	int rightempty = 0 ;
	int currentnodeempty=0 ;
	if(rootnode == NULL ) return 0 ;
	if (rootnode->leftchild != NULL)
	leftempty = returnemptynodes(rootnode->leftchild) ;
	if (rootnode->rightchild != NULL)
	 rightempty = returnemptynodes (rootnode->rightchild) ;
	if(rootnode != NULL)
	{  	if (rootnode->flag == false )
			currentnodeempty = 1;

	}

	int total = leftempty+rightempty+currentnodeempty ;
	return (total ) ;

	}
void BinaryTree::inordertraverse()
		{
	std::cout<<"\n" ;
	inordertraversal(root) ;
	std::cout<<"\n" ;

		}


node* BinaryTree:: returnparent(int nodeindex, int nodeinfo)
{

	node *tempnode = root ;
	node *parentnode ;
	 while(tempnode != NULL)
	 {
		   if(tempnode->nodeindex == nodeindex)
		   { parentnode = NULL ;  break ; // return NULL ;
		   		   }
		   else if (  ( tempnode->rightchild->nodeindex == nodeindex) || (tempnode->leftchild->nodeindex == nodeindex ) )
		   {   parentnode = tempnode ;
		   break ; // return tempnode ;
		   }

		 if(  nodeinfo > tempnode->getinfo()  )
			 tempnode = tempnode->rightchild ;
		 if(nodeinfo < tempnode->getinfo() )
			 tempnode = tempnode->leftchild ;

	 }
	 return parentnode ;
}

bool BinaryTree::inordertraversal(node *rootnode)
{
			if(rootnode == NULL)
					{  return false ; }
		inordertraversal(rootnode->leftchild) ;
    	std::cout<<"\n nodeindex "<<rootnode->nodeindex<<" information "<< rootnode->getinfo() <<"  flag "<<rootnode->flag ;
    	inordertraversal(rootnode->rightchild) ;

}

// Return NULL Node if the insertion is successful otherwise return the LASTNODE at which point insertion is not possible
node* BinaryTree::insertelement(node *tempnode, int element)
{

	std::string tempkbhistr ;
	getline(cin,tempkbhistr) ;
	bool insertflag =false ;
	node *parent ;
	node *child ;
	parent = tempnode ;
	while(tempnode != NULL and insertflag == false )
			{  if ( tempnode->flag == false)
			{  tempnode->writeinfo( element) ;
	            tempnode->flag = true ;
	            insertflag = true ;
	            std::cout<<"\n inserted an element at node "<< tempnode->nodeindex <<" " ;
	           break ;
			}
			 if (element > tempnode->getinfo())
			 {   parent= tempnode ;
				 tempnode = tempnode->rightchild ;
				 child = tempnode ;
			 }
			 else
			 {  parent = tempnode ;
				 tempnode = tempnode->leftchild ;
				 child = tempnode ;
			 }
			}

	std::cout<< "\n Finished inserting function " ;

  if (insertflag == true )
  {
	  return NULL ;
  }
  else
  {
	  return parent ;
  }
}






node*  BinaryTree::rec_insert(node *rootnode, int element )
{

	// Safety if the global rec calling count greater than certain number then exit() ;
	globalreccount++ ;
	std::cout<<" \n printing globalrecount "<<globalreccount
			<<"\n  rootnode index for rec_insert "<<rootnode->nodeindex<<"  value "<<element;
	inordertraverse() ;
	if (globalreccount  > 10000)
          {
		std::cout<<"\n globalrecount exceeds the limit" ;
		exit(0) ;
          }
	// bool swapstatus= false ;
	// Swap status for the elements if the at intermediate parent or child level
   node *returnnode =  insertelement(rootnode, element) ;
   node *parentnode = NULL ;
    if( returnnode == NULL)
    	return NULL ;

   //  std::cout<<" rootnode index  "<< rootnode->nodeindex <<" returnnode index  "<< returnnode->nodeindex  ;

     int temprootnodeindex = rootnode->nodeindex ;
     int tempreturnnodeindex = returnnode->nodeindex ;

     std::cout<<" rootnode index  "<< temprootnodeindex <<" returnnode index  "<< tempreturnnodeindex  ;
 //   if (rootnode->nodeindex == returnnode->nodeindex  )
     if ( tempreturnnodeindex == temprootnodeindex )
    {
    	 std::cout<<" \n the returned node is same as the root node " ;
    	 //  return rootnode ;
  	// node *parentnode = returnparent(rootnode->nodeindex,rootnode->info) ;
    // 	std::cout<<" \n the returned node is same as the root node " ;

    int tempelestorage ;
     // if (swapflag[rootnode->nodeindex-1] == false)
 if(rootnode->swapflag == false )
    {

	 std::cout<<"\n total leftchild empty " << returnemptynodes(rootnode->leftchild)
			 << " total rightchild empty "<< returnemptynodes(rootnode->rightchild)  ;

    	 if(rootnode->getinfo() < element  and returnemptynodes(rootnode->leftchild) !=0)
    	 {
    		 std::cout<< "     rootnode less element and leftchild empty nodes not equal to zero" ;
    		 tempelestorage =  rootnode->getinfo() ;
    	   	rootnode->writeinfo( element) ;


    	 std::cout<< " swap action  in root == return node " ;
    	std::cout<< " setting the swap flag for index  "<< rootnode->nodeindex ;
    // 	 swapflag[rootnode->nodeindex-1] = true ;
    	rootnode->swapflag == true ;
    	returnnode = rec_insert(rootnode->leftchild, tempelestorage) ;

        std::cout<< " swap flag is true " ;
        if(rootnode->nodeindex == 1) {  std::cout<< " swap status true and hit the root node " ;}
        if(returnnode == NULL )
        	return NULL ;
    	 }

    	 if(rootnode->getinfo() > element  and returnemptynodes(rootnode->rightchild) !=0)
    	 {

    		 std::cout<< "     rootnode less element and right child empty nodes not equal to zero" ;

    		 tempelestorage =  rootnode->getinfo() ;
    	   	rootnode->writeinfo( element) ;
    	   	rootnode->swapflag == true ;
    	   	returnnode = rec_insert(rootnode->rightchild, tempelestorage) ;
    	    if(returnnode == NULL )
    	           	return NULL ;


    	 }
    	 // rootnode->rightchild == NULL and rootnode->leftchild == NULL and
    	 node *tempparent = returnparent(rootnode->nodeindex, rootnode->getinfo()) ;
    	 if(  rootnode->getinfo() < element and tempparent->getinfo() > element )
    	 {

    		 std::cout<<"\n   left AVL rotation " ;
    		 tempelestorage = tempparent->getinfo() ;
    		 tempparent->writeinfo(element) ;
    		 returnnode = rec_insert( tempparent, tempelestorage) ;
    		 if(returnnode == NULL )
    		        	return NULL ;

    	 }


    	 if(  rootnode->getinfo() > element and
    			 tempparent->getinfo() < element)
    	     	 {

    		 std::cout<<"\n   right AVL rotation " ;
    	     		 tempelestorage = tempparent->getinfo() ;
    	     		tempparent->writeinfo(element) ;
    	     		 returnnode = rec_insert(tempparent, tempelestorage) ;
    	     		 if(returnnode == NULL )
    	     		        	return NULL ;

    	     	 }
    	 if(   ( rootnode->getinfo() < element  and  tempparent->getinfo() < rootnode->getinfo() )
    			 or
    			 ( rootnode->getinfo() > element  and  tempparent->getinfo() > rootnode->getinfo()))
    	 {

    		 std::cout<<"\n  simple child to parent parent to grandparent swwapping" ;
    		 tempelestorage = rootnode->getinfo() ;
    		 rootnode->writeinfo(element) ;
    		int tempparentelestorage =  tempparent->getinfo() ;
    		tempparent->writeinfo(tempelestorage) ;
    		 returnnode = rec_insert( tempparent, tempparentelestorage ) ;
    		 if(returnnode == NULL )
    		    	     		        	return NULL ;
    	 }

   }


 	 else      {





    	/*   if(rootnode->nodeindex != 1)
    	 {
    		 std::cout<<"\n the navigation goes to parent" ;
    	 parentnode = returnparent(rootnode->nodeindex,rootnode->getinfo()) ;
    	 int telestorage = parentnode->getinfo() ;
    	 parentnode->writeinfo(element) ;
    	 std::cout<<"\n swapped at the parent" ;
    	returnnode =  rec_insert(parentnode, telestorage) ;
    	if(returnnode == NULL )
    	  	return NULL ;
    	 }
    	  else
    	  {

    		  std::cout<< "\n swap status is True and  rootindex is 1 " ;
    		  //return  rootnode ;
    		  exit(0);

    	  }
    	  */
  }

    }
    else
       {

    	std::cout<<" \n jumping to returnnode" ;
    	    returnnode =  rec_insert( returnnode, element ) ;
    	    if(returnnode == NULL )
    	    	return NULL ;


    	/*

    	// if (swapflag[returnnode->nodeindex-1] == false)
    	 if(returnnode->swapflag == false )
    	 	{

    		std::cout<<" in return node  swap action   " ;
    	int tempelementstorage = returnnode->getinfo() ;
       returnnode->writeinfo(element) ;
       std::cout<<" setting the swap flag for the index "<<returnnode->nodeindex ;
      //  swapflag[returnnode->nodeindex-1]  == true ;
       returnnode->swapflag = true ;
       returnnode =  rec_insert(returnnode, tempelementstorage) ;
       if(returnnode == NULL )
               	return NULL ;

               	*/
    	// }
       }



        if(returnnode->nodeindex == 1)
        	return returnnode ;
}

bool BinaryTree::insertelements(int elements[] ,int totalelements)
{

	node *tempnode ;
	node *returnnode ;
	bool insertflag ;
	bool loopbreak = false ;
	int tempelementstorage ;
	for(int i=0 ; i<totalelements;i++)
	{

		globalreccount=0 ;
		unsetSwapflags(root) ;
	     if (  rec_insert(root, elements[i]) != NULL)
	    	 {

	    	 inordertraverse() ;
	    	 std::cout<< "\n  exiting because insertion is not successful" ; exit(0) ;
	    	 }

	     inordertraverse();
		 //tempnode = root ;
         //int count=0 ;

       //  returnnode = insertelement(tempnode, elements[i]) ;

       //  if(returnnode != NULL )  {
	/*	while (  returnnode != NULL  and count < totalelements )
				{
			  //   inordertraverse();
            //     tempelementstorage =   returnnode->info ;
                 returnnode->info = elements[i] ;
                 tempelementstorage =   returnnode->info ;
                  returnnode = insertelement(returnnode, tempelementstorage) ;
                 count++ ;
				}


		//  elements[i] = tempelementstorage ;
        // }
		if(returnnode != NULL)
		{
			loopbreak = true ;
			break ;
		}

  */
	}

	return loopbreak ;
}


node* BinaryTree::navigate(node *rootnode, int nodeindex1)
{
    	 if(rootnode->nodeindex == nodeindex1)
    	 {
    		 std::cout<<"\n matching node found in navigate " ;
    		 return rootnode ; }
    	node *leftnode=  navigate(rootnode->leftchild, nodeindex1) ;
    	if (leftnode !=NULL)
    		{ return leftnode ; }
    	node *rightnode =  navigate(rootnode->rightchild,nodeindex1) ;
    	if(rightnode != NULL)
    		{ return rightnode ; }
    	return NULL;


}
BinaryTree::BinaryTree(int numnodes,std::string str1)
 {


 	vector<std::string> tokenvec =  patternregex(str1, std::string(",")) ;
 	if (tokenvec.size() != numnodes)
 	{
 	 //	std::cout<<tokenvec ;

 		for (int i=0;i<tokenvec.size();i++)
 		{
 			std::cout<<tokenvec.at(i) ;

 		}
 		std::cout<<"\n "<<tokenvec.size() <<" "<<numnodes ;
 	//	return ;
 	}

 	std::cout<<"\n No of token nodes "<<tokenvec.size() ;
   node *rootnode = new node(1) ;
 	root = rootnode ;
 	std::istringstream buffer1();
 	int nodeind;
 	vector<std::string>  subtokenvectorLC ;
 	 vector<std::string>  subtokenvectorRC ;

 for(int i=1 ;i<tokenvec.size();i++)
 {

	  subtokenvectorLC =  vector<std::string>(patternregex(tokenvec.at(i),std::string("LC",2))) ;
	 subtokenvectorRC =  vector<std::string>( patternregex(tokenvec.at(i),std::string("RC",2))) ;
	 	 std::cout<<" node tokenization finished "<<i ;

	 	 std::cout<<"\n "<< subtokenvectorLC.size() <<" "<< subtokenvectorRC.size() ;
	 	 int  stvLClen = subtokenvectorLC.size() ;
	 	 int stvRClen = subtokenvectorRC.size() ;
	 	 inordertraversal(root) ;
	 if(stvLClen  == 2)
	 {
		 // navigate to node
	//  	std::string  tempstr1 = subtokenvectorLC.at(1) ;

		   std::cout << "\n Navigation starts" ;
		 rootnode = navigate(root, atoi(subtokenvectorLC.at(1).c_str())) ;

		 // After navigation create a leftchild

		 rootnode->leftchild = new node(atoi(subtokenvectorLC.at(0).c_str())) ;

	 }
	 else  if(stvRClen == 2)
	 	 {
		 	   std::cout << "\n Navigation starts" ;
		  rootnode = navigate(root,atoi(subtokenvectorRC.at(1).c_str()) ) ;

	 	 rootnode->rightchild = new node(atoi(subtokenvectorRC.at(0).c_str())) ;
	 	 }
	 else
	 {

		 std::cout<<  "\n LC size and RC size "<< subtokenvectorLC.size() <<" " << subtokenvectorRC.size() <<"\n" ;
/*		 std::cout<<"\n  LC parse size and  at0 "<<subtokenvectorLC.size() <<" "<< subtokenvectorLC.at(0)<<" at1 "<< subtokenvectorLC.at(1)
				 << "  at2 " <<  subtokenvectorLC.at(2)
				 <<" RCPARSE size and at0 "<<subtokenvectorRC.size()<<" "<< subtokenvectorRC.at(0)<<"\n" ;
				 */
     std::cout<<" some thing wrong with tokens" ; break ;
	 }
	 std::cout<<"\n processing finished index "<<i ;
 }
  std::cout<<"\n some thing to type because console is cutting bottom output lines" ;
 std::cout<<"\n FUNCTION BINARYTREE CONSTRUCTOR ENDS \n " ;

 /*swapflag = new bool[numnodes] ;
 for (int i=0 ; i< numnodes ;i++)
 {
	 swapflag[i] = false ;
 }
 */
 }


vector<std::string> BinaryTree::patternregex(std::string  searchstr ,std::string patt)
{
	vector<std::string>  tokens ;
	std::cout<<"\n FUNCTION PATTERNREGEX" ;
    std::cout<<"\n  searchstring  " << searchstr <<"  search pattern "<< patt ;
	const char  *strchars =  searchstr.c_str() ;
	const char  *pattchars = patt.c_str() ;
	int lastpushindex=0;
	char *substringchar;

	for (int i=0;i<searchstr.size();i++)
	{
		for (int j=0; j<patt.size(); j++)
		{
			if(strchars[i+j]==pattchars[j] and j== patt.size()-1)
			{
				// free(substringchar);
				substringchar = NULL ;
				substringchar = new char[i-lastpushindex] ;
				for (int k=0;k< i-lastpushindex ;k++)
				{
					substringchar[k] =strchars[lastpushindex+k] ;
				}
				std::string tempstrtopush(substringchar, i-lastpushindex ) ;
				//std::cout<<"\n printing 1st if block "<< tempstrtopush << " and size "<<tempstrtopush.size() <<" size allocated "<< i-lastpushindex;
				std::cout<<"\n "<<tempstrtopush ;
				tokens.push_back(tempstrtopush) ;
				lastpushindex = i+patt.size() ;
				i=i+patt.size()-1 ;
			}
			else if (strchars[i+j]==pattchars[j])
			{
				continue ;
			}


			else
			{ 	break ;
			}

		}
	}

    // std::cout<< " lastpushindex "<< lastpushindex << " stringsize "<< searchstr.size() ;
		if( searchstr.size() - lastpushindex > 0 )
					{
				//	std::cout<<"  in if block ";
					substringchar = (char*) calloc(searchstr.size() - lastpushindex, sizeof(char)) ;
						for (int k=0;k < searchstr.size()-lastpushindex ;k++)
										{
											substringchar[k] =strchars[lastpushindex+k] ;
										}
					//	std::cout<<"  after for loop " ;
						std::string tempstrtopush(substringchar,searchstr.size()-lastpushindex ) ;
					//	std::cout<< " after string alloc " ;
					//	std::cout<<" \n printing 2nd else if block "<< tempstrtopush << "\n what the heck " ;
						std::cout<<"\n "<<tempstrtopush  ;
						tokens.push_back(tempstrtopush) ;
					}

   std::cout<<"\n FUNCTION END" ;
	return tokens ;
}






int  main()
{
	std::string strtest = "1R0,2LC1,3RC1,4LC2,5RC4" ;
	int numnodes = 6 ;



	BinaryTree BT(numnodes,strtest) ;
	BT.inordertraverse() ;
	int  numarray[] = {17,13,37,73,56,11 } ;
	std::cout<<BT.insertelements(numarray, 6) ;

	BT.inordertraverse() ;

	std::cout<<"\n some junk" ;

}
