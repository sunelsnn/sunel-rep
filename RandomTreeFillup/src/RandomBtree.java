import java.util.ArrayList;
import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.io.*;

/*
 * Description: A class to fill up integer values into  a random tree structure that obeys binary tree property 
 * sort the elements first and also keep a sort index in each node that tracks their inorder traverse index.
 * the inorder sort index should be matched with the sorted elements , to store the elements into tree nodes.
 * 
 */

public class RandomBtree {
	
	node root=null;
	ArrayList<node> nodeList=null;
	
	public RandomBtree() {
		nodeList=new ArrayList<node>();
	}
	
	public class node {
		public int info;
		public node left=null;
		public node right=null;
		public node parent=null;
		public int sortindex;
		public int index;
		public node (int index) {
			this.index=index;
		}
		};
	
		
	public void buildRadTree(String linkageStr) throws IOException {
	    System.out.println("Tree linkages, Format to enter node#XLCnode#Y for node#Y as left child of node#X");
	 //   String linkStr=System.in.toString();
	   // String linkStr=new BufferedReader(new InputStreamReader(System.in)).readLine();
	    String linkStr=linkageStr;
	    String[] linkStrArray= linkStr.split(",");
	    for(int i=0;i<linkStrArray.length;i++) {
	    	if(linkStrArray[i].matches("(.*)LC(.*)")){
	    		String[] nodeInLink=linkStrArray[i].split("LC");
	    		if(nodeInLink.length!=2){
	    			System.out.println("Link is not correctly specified");
		    		System.exit(0);
	    		}
	    		int firstNodeIndex=Integer.parseInt(nodeInLink[0]);
	    		int secondNodeIndex=Integer.parseInt(nodeInLink[1]);
	    		node firstNode=null;
	    		node secondNode=null;
	    		if (nodeList.size() > firstNodeIndex && nodeList.get(firstNodeIndex)!=null) {
	    			firstNode=nodeList.get(firstNodeIndex);
	    		} else {
	    			firstNode=new node(firstNodeIndex);
	    			nodeList.add(firstNodeIndex,firstNode);
	    		} 
	    		
	    		if (nodeList.size() > secondNodeIndex && nodeList.get(secondNodeIndex)!=null) {
	    			secondNode=nodeList.get(secondNodeIndex);
	    		} else {
	    			secondNode=new node(secondNodeIndex);
	    			nodeList.add(secondNodeIndex,secondNode);
	    		}
	    		
	    		firstNode.left=secondNode;
	    		secondNode.parent=firstNode;
	    		
	    		
	    	} else 	if(linkStrArray[i].matches("(.*)RC(.*)")){
	    		
	    		String[] nodeInLink=linkStrArray[i].split("RC");
	    		if(nodeInLink.length!=2){
	    			System.out.println("Link is not correctly specified");
		    		System.exit(0);
	    		}
	    		int firstNodeIndex=Integer.parseInt(nodeInLink[0]);
	    		int secondNodeIndex=Integer.parseInt(nodeInLink[1]);
	    		node firstNode=null;
	    		node secondNode=null;
	    		if (nodeList.size()>firstNodeIndex && nodeList.get(firstNodeIndex)!=null) {
	    			firstNode=nodeList.get(firstNodeIndex);
	    		} else {
	    			firstNode=new node(firstNodeIndex);
	    			nodeList.add(firstNodeIndex,firstNode);
	    		} 
	    		
	    		if (nodeList.size()>secondNodeIndex && nodeList.get(secondNodeIndex)!=null) {
	    			secondNode=nodeList.get(secondNodeIndex);
	    		} else {
	    			secondNode=new node(secondNodeIndex);
	    			nodeList.add(secondNodeIndex,secondNode);
	    		}
	    		
	    		firstNode.right=secondNode;
	    		secondNode.parent=firstNode;
	    		
	    	} else {
	    		System.out.println("Link is not correct specified");
	    		System.exit(0);
	    	}
	    	
	    }
	    
	    //find root node
	    int rootNodeIndex=Integer.MIN_VALUE;
	    int cRootNodeIndex=Integer.MIN_VALUE;
	    
	    	//verify that root traversed from all the nodes is same
	     for (int i=0; i<nodeList.size();i++) {
	    	 node currentNode=nodeList.get(i);
	    	 cRootNodeIndex=currentNode.index;
	    	 while(currentNode.parent!=null){
	    		 cRootNodeIndex=currentNode.parent.index;
	    		 currentNode=currentNode.parent;
	    	 } 
	    	 
	    	 if (rootNodeIndex==Integer.MIN_VALUE) {
	    		 rootNodeIndex=cRootNodeIndex;
	    	 } else if( rootNodeIndex!=cRootNodeIndex) {
	    		 System.out.println( "root traversed from two different nodes is not same");
	    		 System.exit(0);
	    	 }
	    	 
	     }
	    // set the root 
	    if(rootNodeIndex!=Integer.MIN_VALUE) {
	    	this.root=nodeList.get(rootNodeIndex);
	    	System.out.println("Build Tree successful");
	    }
	    
	    // Build sorting info  //inorder traversal
	    
	    int sIndex=inorderTraverse(root,0);
	    if(sIndex!=nodeList.size()) {
	    	System.out.println("the inorderTraverse Index is not same size as node list "+sIndex+" "+nodeList.size());
	    }
	    
	    System.out.println("Sort Indexing successfully completed");
	    
	     
	}
	
	
	public int inorderTraverse(node currNode,int currSortIndex) {
		int cSIndex;
		if (currNode.left!=null) {
		cSIndex= inorderTraverse(currNode.left,currSortIndex);
		
		currNode.sortindex=cSIndex;
		System.out.println("assing sort index to listindex "+ currNode.sortindex +" "+currNode.index);
		cSIndex++;
		} else {
			currNode.sortindex=currSortIndex;
			System.out.println("assing sort index to listindex "+ currNode.sortindex +" "+currNode.index);
			cSIndex=currSortIndex+1;
		}
		
		if (currNode.right!=null) {
		cSIndex=inorderTraverse(currNode.right,cSIndex);
		}
		return cSIndex;
	}
	
	
	public void insertArray(int[] infoArray) {
		if(nodeList.size()!=infoArray.length) {
			System.out.println(" Length of built tree doesn't match to the length of array");
			System.exit(0);
			}
		Arrays.sort(infoArray);	
		fillInfo(root,infoArray);
		
	}
	
	public void fillInfo(node currNode, int[] infoArray ) {
		if(currNode.left!=null) {
		fillInfo(currNode.left,infoArray); 
		}
		currNode.info=infoArray[currNode.sortindex];
		if(currNode.right!=null) {
		fillInfo(currNode.right,infoArray);
		}
	}
	
	public boolean testBinaryTreeProperty(node currNode) {
		boolean testFlag=false ;
		boolean testRightFlag=false;
		boolean testLeftFlag=false;
		
			if(currNode.left!=null) {
			testLeftFlag=testBinaryTreeProperty(currNode.left);
			} else {
				testLeftFlag=true;
			}
		
		if (currNode.left!=null && currNode.right!=null) {
		if(currNode.info > currNode.left.info && currNode.info < currNode.right.info) {
			testFlag=true;
		}
		}else if(currNode.left!=null){
			if(currNode.info > currNode.left.info ){
				testFlag=true;
			}
			
		}else if(currNode.right!=null){
			if (currNode.info < currNode.right.info) {
				testFlag=true;
			}
		}else {
			return true;
		}
		
		
		if(currNode.right!=null) {
			testRightFlag=testBinaryTreeProperty(currNode.right);
			} else {
				testRightFlag=true;
			}
		if(testFlag==false || testLeftFlag==false || testRightFlag==false) {
			return false ;
		} else {
			return true;
		}
		
	}
	
	public void printIndexAndInfo(node currNode) {
		
		if(currNode.left!=null){
			printIndexAndInfo(currNode.left);
		}
		
		System.out.println(" sort index and info and listindex"+ currNode.sortindex +" "+currNode.info +" "+ currNode.index);
		
		if(currNode.right!=null){
			printIndexAndInfo(currNode.right);
		}
		
	}
 public static void main(String[] args) throws IOException{
	 
	 if(args.length!=2){
		 System.out.println(" arguments not 2, provide  tree structure and info array like this \n ");
		 System.out.println( "example \"0LC1,0RC2,1LC3,1RC4,2LC5,5RC6,6LC7\" 8,3,10,5,7,13,11,19");
	 }
	 
	 /*
	 String teststr="k@@$&K@k765QW";
	 String patt="(?=.*[a-z]).{2,10}(?=.*[A-Z]).{2,4}(?=.*[0-9])(?=.*[$@&]).{7,20}";
	 boolean testbool= teststr.matches(patt);
	 
	 if(testbool) { System.out.println("match") ; }
	 else { System.out.println("not match") ;}
	 
	 String str = "Hello {World} this {is} a {Tokens} test";
	 String secondstr = "Alert:Date:12321321321:testmsgs";
	 
	 Pattern pt = Pattern.compile("Alert:Date:([0-9].*):([ a-zA-Z].*)");
	 
	 Matcher m = pt.matcher(secondstr);
	 
	 while(m.find()) {
		  System.out.println(m.group(0)); 
		  System.out.println(m.group(1)); 
		  System.out.println(m.group(2)); 
	 }
	 */
	 
	 RandomBtree bt=new RandomBtree();
	 bt.buildRadTree(args[0]);
	 int[] infoArray = new int[bt.nodeList.size()];
	 
	 String infoArrayStr=args[1];
	 String[] infoArrayToken=infoArrayStr.split(",");
	 if(infoArrayToken.length!=bt.nodeList.size()) {
		 System.out.println("size of tree and info array is not same");
	 }
	 for(int i=0;i<infoArrayToken.length;i++) {
		 infoArray[i]=Integer.parseInt(infoArrayToken[i]);
	 }
	 bt.insertArray(infoArray);
	 System.out.println(" binary property test"+ bt.testBinaryTreeProperty(bt.root));
	 bt.printIndexAndInfo(bt.root);
	 
 }
}

