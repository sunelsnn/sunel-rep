import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import java.util.Map.Entry;
import java.util.concurrent.Callable;


public class MergeThread implements Callable<String> {
		
		String[] fileList;
		int totalFileCount;
		int[] inputFileSize;
		int[]  mergeWindow=null;
		int totalElementCount;
		String outputReturnFile=null;
		List<Entry<String,FileInfo>> fileSet=null;
		
		
		public MergeThread(List<Entry<String,FileInfo>>  fileSet, String outputReturnFile) {
			this.fileSet= fileSet;
			this.outputReturnFile=outputReturnFile;
			this.totalFileCount=this.fileSet.size();
			this.mergeWindow = new int [this.totalFileCount];
			
			for(Entry<String,FileInfo>  fileEntry : this.fileSet) {
				this.totalElementCount+=fileEntry.getValue().fileSize;
				}
			
			this.outputReturnFile=outputReturnFile;
			
			
		}
		
		
		public MergeThread(String[] filelist, int[] fileSize, String outputFile) {
			this.fileList=filelist;
			this.totalFileCount=filelist.length;
			this.inputFileSize = fileSize;
			if(this.inputFileSize.length != totalFileCount) {
				System.out.println("the filelist  and filesize array has different sizes");
			}
			this.mergeWindow = new int[this.totalFileCount];
			
			this.totalElementCount=0;
			
			for(int i=0;i<this.totalFileCount;i++) {
			this.totalElementCount+=this.inputFileSize[i];
			}
			
			this.outputReturnFile=outputReturnFile;
			
		}
		
		public String call() throws Exception {
			
			// TODO Auto-generated method stub
			//mergeOperation();
			
			return mergeOperationWithFreq() ;
		}
		
		public class  NumFreq {
			public int token;
			public int freq;
			
			public NumFreq(int token, int freq){
				this.token=token;
				this.freq=freq;
			}
		};
		
		public  NumFreq splitLineToNumFreq(String line) {
				NumFreq nmObj = new NumFreq(Integer.parseInt(line.split(",")[0]), Integer.parseInt(line.split(",")[1]));
				return nmObj;
		}
		
private String mergeOperationWithFreq() throws IOException {
			
			int minElement=Integer.MAX_VALUE;
			int secondBestMinElement=Integer.MAX_VALUE;
			int currentFrequencyCount=0;
			String tempStr;
			int totalFileReads = 0;
			int previousFrequencyCount=0;
			int prevTotalFileReads=0;
			BufferedWriter SortOutputFileWriter=null;
			int totalSortedElements=0;
			
			NumFreq[] mergeWindowQueue =new NumFreq[this.totalFileCount];
			
			SortOutputFileWriter= new BufferedWriter( new FileWriter(this.outputReturnFile));
			BufferedReader[]  mReaders= new BufferedReader[this.totalFileCount];
							
			int fileIndex = 0;
			String fileReadLine = null;
			for(Entry<String,FileInfo>  fileEntry : fileSet) {
				mReaders[fileIndex] = new BufferedReader ( new FileReader(fileEntry.getKey()));
				fileReadLine = mReaders[fileIndex].readLine();
				mergeWindowQueue[fileIndex] = splitLineToNumFreq(fileReadLine);
				if(minElement > mergeWindowQueue[fileIndex].token) {
					minElement = mergeWindowQueue[fileIndex].token;
				}
				
			}
			
			for(int i=0; i<=this.totalElementCount ;i++ )
			    {
			        	
			    	//Linearly scan the Array for  (minelement,count)  and secondbestminelement .
			    	    	
			    	for (int j=0;j<this.totalFileCount ; j++)
			    	{
			    		
			    		// compare minimum element with elements in the array,
			    		//  a) if the minimum repeats increment its count and read the nextline from the corresponding file
			    		//  b) if the minimum > and an element in array, throw error
			    		//  c) if the minimum is less the element in the array , check for the second most minimum element.
			   //		if (minElement < this.mergeWindow[j])
			    		if (minElement < mergeWindowQueue[i].token)
			    		{
			    			 if (  secondBestMinElement >  mergeWindowQueue[i].token  && minElement < secondBestMinElement)
			    			 {
			    				// secondBestMinElement = this.mergeWindow[j] ;
			    				 
			    				 secondBestMinElement = mergeWindowQueue[i].token  ;
			    			 }
			    			 else if( minElement== secondBestMinElement)
			    			 {
			    				 secondBestMinElement = mergeWindowQueue[i].token   ; 
			    			 }
			    			
			    			continue ;
			    		}
			    	// 	else if (minElement ==  this.mergeWindow[j])
			    		else if (minElement ==  mergeWindowQueue[j].token)
			    		{
			    			// currentFrequencyCount++ ; 
			    			currentFrequencyCount=currentFrequencyCount+mergeWindowQueue[j].freq;
			    			i++ ;
			    			
			    			if ( (tempStr = mReaders[j].readLine())!= null ) {		// this.mergeWindow[j] = Integer.parseInt(tempStr) ;
			    				mergeWindowQueue[j]= splitLineToNumFreq(tempStr) ;
			    				totalFileReads++ ;			    				    			
			    			}
			    			else {
			    				// this.mergeWindow[j] = Integer.MAX_VALUE ;
			    				mergeWindowQueue[j] = new NumFreq(Integer.MAX_VALUE,0);
			    			}
			    		    
			    			
			    		}
			    		// else if(minElement > this.mergeWindow[j]) {
			    			else if(minElement > mergeWindowQueue[j].token) {
			    			System.out.println("Some error in sorting") ;
			    			System.exit(0);
			    			}
			    	   		
			    	}  // end for inner for loop

			    	// if there is a count difference of minimum value in previous and current iteration, then store it.
			    	// else  write the minimum element to the sorted file.
			    	if (previousFrequencyCount < currentFrequencyCount )
			    	 {  previousFrequencyCount = currentFrequencyCount ;
			    	   	 i=i-1 ;		
			    	   	 
			    	   	if (totalFileReads - prevTotalFileReads != 1) {
							System.out
									.println(" there was no read from memory mapped file : current counter "
											+ i);
						}
						prevTotalFileReads = totalFileReads;
			    	 }
			    	else if ( previousFrequencyCount == currentFrequencyCount )
			    	{
			    		SortOutputFileWriter.write(minElement+","+currentFrequencyCount+"\n") ;
			    		minElement = secondBestMinElement ;
			    		previousFrequencyCount = 0 ;
			    		currentFrequencyCount =0  ;
			    		 i=i-1 ;
			    		totalSortedElements++ ;
			    	}
			    	
			    }  // end of outer for loop.
			 
			 SortOutputFileWriter.close();
			 
			 for (int i=0; i<this.totalFileCount ; i++)
			    {
			    	mReaders[i].close();
			    	File delfile = new File (fileList[i]);
			    	 if ( !delfile.delete() ) 
			    	 { System.out.println("unable to delete  file sorted"+fileList[i]) ; }
			    	
			    	
			    }
			 
			 return this.outputReturnFile+","+Integer.toString(totalSortedElements);
		}
	}