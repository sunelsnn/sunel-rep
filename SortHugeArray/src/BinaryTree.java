
/*** a generic Binary Tree  
 * Supports java.lang.Integer and java.lang.Float 
 * **/

import java.math.*;
import java.util.HashMap;

//BinaryTree class
public class BinaryTree<T> {
	
	
	// Define a Node class
	public class node<T>
	{
		T info;
		node leftchild;
		node rightchild;
		
		//constructor
		public node()
		{
			leftchild = null ;
			rightchild = null ;
		}
		
		public node getLeftChild() 
		{
			return leftchild ;
		}
		
		public node getRightChild()
		{
			return rightchild ;
		}
		
		public T getInfo()
		{
			return info ;
		}
		
		public void setInfo(T NewInfo)
		{
			info = NewInfo ;
		}
		
		public void setRightChild(node rc)
		{
			rightchild = rc ;
		}
		
		public void setLeftChild(node lc)
		{
			leftchild = lc ;
		}
	};
	
	
	node<T>  RootNode ;
	int classtype ;
	
	public BinaryTree ()
	{
		RootNode= null ;
	}
	
	public void classnametype(T  Tobj)
	{
				
		String classname = Tobj.getClass().getName() ;
		HashMap<String, Integer> classmap = new HashMap<String,Integer>();
		classmap.put("java.lang.Integer", 1) ;
		classmap.put("java.lang.Float", 2 ) ;
		classmap.put("java.lang.Double", 3) ;
		classtype = classmap.get(classname);
		
	}
	
	
	public node<T> getRootNode()
	{
		return RootNode ;
	}
	
	public boolean insertElements(T element)
	{
	   node<T> tempnode = RootNode ;
	   
	   if (RootNode == null)
	   {
		   classnametype(element) ;
		   RootNode = new node<T>() ;
		   RootNode.setInfo(element) ;
		   return true ;
	   }
	   boolean insertflag = false ;
	 
	 //  System.out.println(" The class name and class type "+ classname+" "+classtype) ;
	   if(! (classtype >=1 && classtype <=3))  
	   {
		   System.runFinalizersOnExit(true) ;
		   System.exit(0) ;
		   
	   }
	   while(tempnode!= null)
	   {
		  
		   switch(classtype)
		   {
		   
		   case 1 :
			   
			   if(  (Integer) element  >= (Integer)tempnode.getInfo())
			   {   if (tempnode.getRightChild() == null)
		 		{
			 	    node<T>  Nodeinsert = new node<T>() ;
			 	    Nodeinsert.setInfo(element) ;
			 		tempnode.setRightChild(Nodeinsert) ;
			 		insertflag = true ;
			 		break ;
		 		}
			   else
		 		{
			 tempnode = tempnode.getRightChild() ;
		 		}
			   }	
			   else
			   {	
				   if (tempnode.getLeftChild() == null)
				   {
			 	    node<T>  Nodeinsert = new node<T>() ;
			 	    Nodeinsert.setInfo(element) ;
			 		tempnode.setLeftChild(Nodeinsert) ;
			 		insertflag = true ;
			 		break ;
		 		}
			 
				   if (tempnode.getLeftChild() == null) break ;
				   tempnode = tempnode.getLeftChild() ;
			   }
		 
		      break ;  // case 1 ends
		      
		   case 2 :
			   
			   if(  (Float) element  >= (Float)tempnode.getInfo())
			   {   
				   	if (tempnode.getRightChild() == null)
				   	{
				   		node<T>  Nodeinsert = new node<T>() ;
				   		Nodeinsert.setInfo(element) ;
				   		tempnode.setRightChild(Nodeinsert) ;
				   		insertflag = true ;
				   		break ;
				   	}
				   	else
				   	{
				   		tempnode = tempnode.getRightChild() ;
				   	}
			   }	
			   else
			   {	
				   if (tempnode.getLeftChild() == null)
				   {
			 	    node<T>  Nodeinsert = new node<T>() ;
			 	    Nodeinsert.setInfo(element) ;
			 		tempnode.setLeftChild(Nodeinsert) ;
			 		insertflag = true ;
			 		break ;
				   }
				   else
				   {
					   tempnode = tempnode.getLeftChild() ;
				   }   
			   }
		 
		      break ;  // case 2 ends
		   }// switch ends
		 
		   if (insertflag == true ) break ;
	   }  // while ends   
	   
	  return insertflag ;
	   
	}
	
	
	public void inOrderTraversal( node<T> NavigateNode )
	{
		if(NavigateNode == null) return ;
		inOrderTraversal(NavigateNode.getLeftChild()) ;
		
		System.out.print (" "+ NavigateNode.getInfo()+" ") ;
		
		inOrderTraversal(NavigateNode.getRightChild()) ;
	
	}
	
	
	public static void main(String[] args)
	{
		boolean flag = true ;
		BinaryTree<Float> BTobject = new BinaryTree<Float>() ;
		try
		{
				
		
		flag = BTobject.insertElements((float)15.1) ;
		System.out.println("1 "+flag) ;
		flag = BTobject.insertElements((float)20.2) ;
		System.out.println("2 "+flag) ;
		flag = BTobject.insertElements((float)20.1) ;
		System.out.println("3 "+flag) ;
		flag = BTobject.insertElements( (float)12.0) ;
		System.out.println("4 "+flag) ;
		}
		catch( Exception E)
		{
			E.printStackTrace() ;
		}
		finally
		{
			if (flag == false)
			{
			System.out.println("There was an error while inserting the element") ;
			}
		}
		
		BTobject.inOrderTraversal(BTobject.getRootNode()) ;
		
		
	}
    
} ;
