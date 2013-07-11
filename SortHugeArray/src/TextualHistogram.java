/**
 *   textualHistogram.java
 *   Author: Sunil Mamidi
 *   Description:  Sorts a File with 1 million integers with atmost 2500 integers in memory in ascending order
 *   Logic : Linearly read the file into  block chunks of 2500 integers, and do in place sorting using java functions
 *   and store the stored blocks into different files. Merge the sorted files . Store the minimum most element
 *   from each file into the Array  (the size of this Array is 400 which is less than 2500 ). 
 *   Scan the above Array for minimum and it's count and repeat the scanning process until a there is no different in countvalue.
 *   The above scanning process repeats on maximum to 100000.
 *   time with out memory managed files 1:30 min
 * 
 */
import java.io.*;
import java.nio.IntBuffer;
import java.nio.channels.FileChannel;
import java.util.Arrays;
import java.util.Date;

//import java.nio.

public class TextualHistogram {

	public int[] Integerarray;
	int Totalelements;
	int memorySize;
	int fileBlocksize;
	int TotalfileBlockCount;
	String InputFileName;
	IntBuffer[] out;
	FileChannel[] fc;
	IntBuffer out1;
	RandomAccessFile raf;
	int[] currpointer;
	int[] localMapPointer;
	int mapsize = 1000;
	int blockFileReadBuffer;
	int maxFiles=100;

	public TextualHistogram(String InputFile) throws FileNotFoundException,
			IOException {

		memorySize = 20000000;
		fileBlocksize = memorySize / 2;
		// Integerarray = new int[Blocksize];
		InputFileName = new String(InputFile);
		Totalelements = countFileLength();
		TotalfileBlockCount = (int) Math.ceil(Totalelements / fileBlocksize);
		
		/*if (TotalfileBlockCount > maxFiles) 
			TotalfileBlockCount=maxFiles;
			*/
		
		// blockFileReadBuffer=
		// (memorySize-TotalfileBlockCount)/TotalfileBlockCount;
		blockFileReadBuffer = memorySize / TotalfileBlockCount;
		
		if( blockFileReadBuffer < 1) {
			System.out.println(" there morefiles than memorySize can accomodate \n Please provide more memory. Thank you");
			System.exit(0);
		}
		fc = new FileChannel[TotalfileBlockCount];
		out = new IntBuffer[TotalfileBlockCount];

		/*
		 * for (int i = 0; i < TotalBlockCount; i++) {
		 * 
		 * 
		 * // fc[i] = new RandomAccessFile("sorttempfile" + i,
		 * "r").getChannel(); // out[i] =
		 * fc[i].map(FileChannel.MapMode.READ_WRITE, 0, //
		 * mapsize).asIntBuffer();
		 * 
		 * 
		 * }
		 */
		currpointer = new int[TotalfileBlockCount];
		localMapPointer = new int[TotalfileBlockCount];

		System.out.println(" fileblocksize " + fileBlocksize
				+ " totalelements " + Totalelements + " TotalfileBlockCount "
				+ TotalfileBlockCount + " blockFileReadBuffer "
				+ blockFileReadBuffer);
	}

	/*
	 * public TextualHistogram(String InputFile, int BlockSize) {
	 * 
	 * fileBlocksize = BlockSize; // Integerarray = new int[Blocksize];
	 * InputFileName = new String(InputFile); Totalelements = countFileLength();
	 * TotalBlockCount = (int) Math.ceil(Totalelements / Blocksize);
	 * 
	 * }
	 */

	public int countFileLength() {
		int LineCounter = 0;
		try {
			BufferedReader InputFileReader = new BufferedReader(new FileReader(
					InputFileName));
			String TempStringStorage = new String();
			while ((TempStringStorage = InputFileReader.readLine()) != null) {
				LineCounter++;
			}

		} catch (IOException E) {
			E.printStackTrace();
		}

		return LineCounter;
	}

	public int getBlockSize() {
		return this.fileBlocksize;
	}

	public int getTotalBlockCount() {
		return this.TotalfileBlockCount;
	}

	public int getTotalElements() {
		return this.Totalelements;
	}

	public void partitionAndSort() throws Exception {
		System.out.println("partitionAndSort: start time "
				+ (new Date(System.currentTimeMillis())));
		System.out.println("partitionandsort : fileblocksize " + fileBlocksize);
		Integerarray = new int[fileBlocksize];

		BufferedReader Inputfilereader = new BufferedReader(new FileReader(
				this.InputFileName));

		for (int i = 0; i < this.TotalfileBlockCount; i++) {
			// String filenameindex = new String ("SortedBlockFile"+i) ;
			// BufferedWriter BFileWriter = new BufferedWriter ( new
			// FileWriter(filenameindex)) ;
			raf = new RandomAccessFile("sorttempfile" + i, "rw");
			out1 = raf.getChannel()
					.map(FileChannel.MapMode.READ_WRITE, 0, 4 * fileBlocksize)
					.asIntBuffer();

			for (int j = 0; j < this.fileBlocksize; j++) {
				this.Integerarray[j] = Integer.parseInt(Inputfilereader
						.readLine());
			}

			// for(int k=0 ; k< Blocksize ;k++)
			// {
			Arrays.sort(Integerarray); // this function presumably does inarray
			// sorting
			// System.out.println(Integerarray.length);
			// System.out.println(out[i].capacity() );

			/*
			 * for(int ind=0;ind<Integerarray.length;ind++) {
			 * out[i].put(Integerarray[ind]); }
			 */
			out1.put(Integerarray);
			out1.position(0);
			System.out.println(" the remainig elements "
					+ Integer.toString(out1.remaining()) + " "
					+ Integer.toString(out1.limit()));
			// out1.arrayOffset()+" "
			raf.close();
			System.gc();
			// BFileWriter.write(Integer.toString(Integerarray[k])+"\n");
			// }
			// BFileWriter.close();
		}
		Inputfilereader.close();

		System.out.println("partitionAndSort: end time "
				+ (new Date(System.currentTimeMillis())));
	}

	public void allocateArrayMemory(int memsize) {
		this.Integerarray = new int[memsize];

	}

	public void MergeSortedBlockFiles() throws Exception {

		System.out.println("MergeSortedBlockFiles: start time "
				+ (new Date(System.currentTimeMillis())));

		Integerarray = new int[TotalfileBlockCount];

		System.gc();

		// blockFileReadBuffer =
		// (int)(Blocksize-TotalBlockCount*2)/TotalBlockCount*2 ;

		int minelement = Integer.MAX_VALUE; // a int variable to track the
		// minimum most element
		int secondbestminelement = Integer.MAX_VALUE; // a int variable to track
		// second most minimum.
		int currentcount = 0; // counter to count the repeat of integer while
		// merging
		int previouscount = 0; // counter to store the count and check the
		// difference with next iteration
		String tempstr;
		int totalsortedelements = 0;
		int totallinereads = 0;
		int totalNoOfMaps=0;

		// BufferedReader[] MReaders = new BufferedReader[this.TotalBlockCount]
		// ; // 400 file readers are initialized.

		BufferedWriter SortfileWriter = new BufferedWriter(new FileWriter(
				"Sortedfile.txt")); // open a filewriter to store sorted
		// information

		// initialize all the FileReaders and read the first element in them
		for (int i = 0; i < this.TotalfileBlockCount; i++) {
			// MReaders[i] = new BufferedReader ( new FileReader
			// ("SortedBlockFile"+i)) ;
			fc[i] = new RandomAccessFile("sorttempfile" + i, "r").getChannel();
			System.out.println(" file #" + i + " size " + fc[i].size());
			out[i] = fc[i].map(FileChannel.MapMode.READ_ONLY, 0,
					blockFileReadBuffer * 4).asIntBuffer();
			System.out.println(" out remaining #"+i+" "+out[i].remaining());
			Integerarray[i] = out[i].get(0);
			this.currpointer[i] = 1;
			this.localMapPointer[i] = 1;
			if (minelement > Integerarray[i]) {
				minelement = Integerarray[i];
			}

		}

		totallinereads = this.TotalfileBlockCount;
		secondbestminelement = minelement;
		int prevtotallinereads = totallinereads;
		// Iterate the process of linearly scanning until all the 1 million
		// elements are retrieved.
		for (int i = 0; i <= this.Totalelements; i++) {

			// Linearly scan the Array for (minelement,count) and
			// secondbestminelement .

			for (int j = 0; j < this.TotalfileBlockCount; j++) {

				// compare minimum element with elements in the array,
				// a) if the minimum repeats increment its count and read the
				// nextline from the corresponding file
				// b) if the minimum > and an element in array, throw error
				// c) if the minimum is less the element in the array , check
				// for the second most minimum element.
				if (minelement < this.Integerarray[j]) {
					if (secondbestminelement > this.Integerarray[j]
							&& minelement < secondbestminelement) {
						secondbestminelement = this.Integerarray[j];
					} else if (minelement == secondbestminelement) {
						secondbestminelement = this.Integerarray[j];
						;
					}

					continue;
				} else if (minelement == this.Integerarray[j]) {
					currentcount++;
					i++;

					// if ( (tempstr = MReaders[j].readLine())!= null )
					Integer tempInt = Integer.MAX_VALUE;
					/*
					 * if ((tempInt = out[j].get(this.currpointer[j])) != null)
					 * { // this.Integerarray[j] // = //
					 * Integer.parseInt(tempstr) // ; this.Integerarray[j] =
					 * tempInt; totallinereads++; this.currpointer[j]++;
					 * 
					 * } else { this.Integerarray[j] = Integer.MAX_VALUE; }
					 */

					
				//	if (this.currpointer[j] >= this.out[j].remaining()) {
					if (this.currpointer[j] >= this.fileBlocksize) {
						this.Integerarray[j] = Integer.MAX_VALUE;
					} else {
						this.Integerarray[j] = out[j]
								.get(this.localMapPointer[j]);
						totallinereads++;
						this.currpointer[j]++;
						this.localMapPointer[j]++;

						try {
							// if(
							// (this.currpointer[j]-1)%this.blockFileReadBuffer==0
							// ||
							// this.localMapPointer[j]>this.blockFileReadBuffer)
							// {
							if ((this.currpointer[j])
									% this.blockFileReadBuffer == 0
									|| this.localMapPointer[j] >= this.blockFileReadBuffer) {
								if (this.currpointer[j]
										+ this.blockFileReadBuffer > this.fileBlocksize) {
									out[j] = fc[j].map(
											FileChannel.MapMode.READ_ONLY,
											(this.currpointer[j] ) * 4,
											(fileBlocksize-this.currpointer[j]) * 4).asIntBuffer();
								//			(fileBlocksize) * 4).asIntBuffer();
									totalNoOfMaps++;
								} else {

									out[j] = fc[j].map(
											FileChannel.MapMode.READ_ONLY,
											(this.currpointer[j] ) * 4,
										//	(this.currpointer[j] ) * 4 	+ 
											this.blockFileReadBuffer* 4).asIntBuffer();
									// out[j]=fc[j].map(FileChannel.MapMode.READ_ONLY,
									// (this.currpointer[j]-1)*4,
									// this.blockFileReadBuffer*4).asIntBuffer();
									totalNoOfMaps++;
								}
								this.localMapPointer[j] = 0;
								System.out.println(" resetting local map pointer "+j+" "+this.localMapPointer[j]+" current index i "+i) ;

							}
						} catch (Exception e) {
							System.out
									.println(" the j file #"
											+ j
											+ " current element pointer "
											+ this.currpointer[j]
											+ "  end of the map "
											+ (this.currpointer[j] + blockFileReadBuffer)
											+ " total fileblocksize "
											+ fileBlocksize);
							System.out.println(" localmap pointer "
									+ this.localMapPointer[j]);
							System.out.println(" the remaining elements "
									+ out[j].remaining() +" fcdetails fcsize" + fc[j].size()+ " fcposition "+ fc[j].position());
							System.out.println(e.toString());
						}
					}

				} else if (minelement > this.Integerarray[j]) {
					System.out.println(minelement + " " + Integerarray[j]);
					System.out.println("Some error in sorting");
					System.exit(0);

				}

			} // end for inner for loop

			// if there is a count difference of minimum value in previous and
			// current iteration, then store it.
			// else write the minimum element to the sorted file.
			if (previouscount < currentcount) {
				previouscount = currentcount;
				/*
				if (totallinereads - prevtotallinereads != 1) {
				//	System.out
				//			.println(" there was no read from memory mapped file : current counter "
				//					+ i);
				}
				*/
				prevtotallinereads = totallinereads;
				i = i - 1;
			} else if (previouscount == currentcount) {
				// System.out.println(minelement + " " + currentcount);
				SortfileWriter.write(minelement + "," + currentcount + "\n");
				minelement = secondbestminelement;
				previouscount = 0;
				currentcount = 0;
				i = i - 1;
				totalsortedelements++;
			}

		} // end of outer for loop.

		// Close all the files and delete the blockfiles
		SortfileWriter.close();
		System.out.println(" total sorted elements " + totalsortedelements
				+ " totallinereads " + totallinereads);
		System.out.println(" curr file pointer " + Arrays.toString(this.currpointer));
		System.out.println(" local buffer file pointer " + Arrays.toString(this.localMapPointer));
		System.out.println(" total no of file buffer remappings " + totalNoOfMaps);

		/*
		 * for (int i = 0; i < this.TotalfileBlockCount; i++) { //
		 * MReaders[i].close(); // out[i]. fc[i].close(); File delfile = new
		 * File("sorttempfile" + i); if (!delfile.exists())
		 * System.out.println("sorttempfile" + i + " doesn't exist"); if
		 * (!delfile.delete()) {
		 * System.out.println("unable to delete  file sorted" + i); }
		 * 
		 * } // file close for loop
		 */

		System.out.println("MergeSortedBlockFiles: End time "
				+ (new Date(System.currentTimeMillis())));

	}

	public static void main(String[] args) throws FileNotFoundException,
			IOException {

		System.out.println("start time "
				+ (new Date(System.currentTimeMillis())));

		String InputFileName = new String();

		// Usage
		try {
			if (args.length != 1 && args.length != 2) {
				System.out
						.println("\n TextualHistogram: \n Description: This program sorts the Inputfile with integers with limited memory "
								+ "\n Usage "
								+ "\n		Linux:		java -classpath $CLASSPATH:$PWD TextualHistogram InputFileName "
								+ "\n				java -classpath $CLASSPATH:$PWD TextualHistogram InputFileName  MemoryBlockSize"
								+ "\n		Windows:	java -classpath %CLASSPATH%;%PWD% TextualHistogram InputFileName"
								+ "\n Note: The system will process the InputFile even if the total Integers are less than 1 million ");

				System.out
						.println("\n Please enter a input file with integers or type 'quit' for quit \n\n");
				;
				InputStreamReader converter = new InputStreamReader(System.in);
				BufferedReader in = new BufferedReader(converter);
				InputFileName = in.readLine().trim();
				if (InputFileName.equals("quit")) {
					System.runFinalization();
					System.exit(0);
				}
				/*
				 * else if (!( new File(InputFileName).exists()) ) {
				 * System.out.println
				 * ("\n Sorry File does not exists. Please run the program again"
				 * ) ; System.exit(0) ; }
				 */
			} else {
				InputFileName = args[0];
				System.out.println(" given input file " + InputFileName);

				if (!(new File(InputFileName).exists())) {
					System.out.println("input file doesn't exists");
				}

			}

		} catch (Exception E) {
			E.printStackTrace();
		}

		/*
		 * finally { System.out.println("some error reading file");
		 * System.exit(0);
		 * 
		 * }
		 */

		TextualHistogram TextualHistogram_object = new TextualHistogram(
				InputFileName);
		if (args.length == 1) {
			TextualHistogram_object = new TextualHistogram(args[0]);
		} else if (args.length == 2) {
			/*
			 * TextualHistogram_object = new TextualHistogram(args[0],
			 * Integer.parseInt(args[1]));
			 */
		}

		try {

			// Sort Block Wise
			/*
			TextualHistogram_object.partitionAndSort();
			*/
			// Resize the Array
			/*
			 * TextualHistogram_object.allocateArrayMemory(TextualHistogram_object
			 * .getTotalBlockCount());
			 */

			// Merge the Sorted Block Files
			TextualHistogram_object.MergeSortedBlockFiles();

			System.out.println("all module end time "
					+ (new Date(System.currentTimeMillis())));

		} catch (Exception E) {
			E.printStackTrace();
		}
		/*
		 * finally { System.out.println("\n there was some exception") ; }
		 */

	}

};