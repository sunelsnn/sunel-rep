

	import java.io.IOException;
	import java.util.*;
	
	import org.apache.hadoop.fs.Path;
	import org.apache.hadoop.conf.*;
	import org.apache.hadoop.io.*;
//	import org.apache.hadoop.mapred.OutputCollector;
// import org.apache.hadoop.mapred.JobConf;
 import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.*;
	
	public class WordCount {
	
	    public static class WCMap extends Mapper<Object, Text, Text, IntWritable> {
	      private final static IntWritable one = new IntWritable(1);
	      private Text word = new Text();
	  //  private LongWritable word = new LongWritable() ;
	      
	      protected void setup (Context context) throws IOException, InterruptedException
	      {
	    	  
	    	  super.setup(context) ;
	    	  System.out.println("In MAP setup ") ;
	    	  Runtime rt = Runtime.getRuntime();
	    	  String tempfilename =  "touch " + new  String ("~/file") + new  String (  Long.toString(new Date().getTime())) ;
	    	  Process proc = rt.exec( "touch file1");
	    	  Configuration conf = context.getConfiguration();
	    	  System.out.println( conf.get("map.input.file")) ;
	    	  System.out.println( conf.toString()) ;
	    	 // System.out.println( conf.) ;
	      }
	      public void map(Object key, Text value, Context context ) throws IOException , InterruptedException {
	    	  
	    	  Configuration conf = context.getConfiguration();
	    	  String param = conf.get("PARM1");
	    	  System.out.println("pringint PARM" + param) ;
	    	  
	        String line = value.toString();
	        StringTokenizer tokenizer = new StringTokenizer(line);
	        while (tokenizer.hasMoreTokens()) {
	          word.set(tokenizer.nextToken());
	          context.write(word, one);
	        }
	      }
	    }
	
	    public static class WCReduce extends  Reducer<Text, IntWritable, Text, IntWritable> {
	      public void reduce(Text key, Iterable<IntWritable> valuesobj, Context context) throws IOException , InterruptedException  {
	    	  Configuration conf = context.getConfiguration();
	    	  String param = conf.get("PARM1");
	    	  System.out.println("pringint PARM in reducer" + param) ;
	        int sum = 0;
	        
	        Iterator<IntWritable> values = valuesobj.iterator() ; 
	        while (values.hasNext()) {
	          sum += values.next().get();
	        }
	        
	        /*
	        for (IntWritable val: values)
	        {
	        	sum += val.get() ;
	        }
	        */
	        context.write(key, new IntWritable(sum));
	      }
	    }
	    /*

	    public void testfunction()
	    {}
	    */
	    public static void main(String[] args) throws Exception {
	    	System.out.println("Entering job config dsfds") ;
	    	// System.in.read() ;
	    	Configuration conf = new Configuration();
	    	 conf.set("PARM1", "PARM1value");
		      conf.set("PARM2", "PARM2value") ;
	      Job job = new Job (conf, "WordCount");
	      job.setJarByClass(WordCount.class);
	      job.setMapperClass(WCMap.class);
	      job.setCombinerClass(WCReduce.class);
	      job.setReducerClass(WCReduce.class);
	      job.setOutputKeyClass(Text.class);
	      job.setOutputValueClass(IntWritable.class);
	     
	      
	 // job.setLong("temparm","someval") ;
	   
	      /*
	      conf.setJar("Wcountjar.jar") ;
	      conf.setJobName("WordCount");
	      conf.setOutputKeyClass(Text.class);
	      conf.setOutputValueClass(IntWritable.class);
	
	      conf.setMapperClass(Map.class);
	      conf.setCombinerClass(Reduce.class);
	      conf.setReducerClass(Reduce.class);
	
	      conf.setInputFormat(TextInputFormat.class);
	      conf.setOutputFormat(TextOutputFormat.class);
	      */
	      /*
	       * Job job = new Job(conf, "word count");
    job.setJarByClass(WordCount.class);
    job.setMapperClass(TokenizerMapper.class);
    job.setCombinerClass(IntSumReducer.class);
    job.setReducerClass(IntSumReducer.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);
	       */
	
	      FileInputFormat.addInputPath(job, new Path(args[0]));
	      FileOutputFormat.setOutputPath( job, new Path(args[1]));
	      
	      System.exit(job.waitForCompletion(true) ? 0 : 1);
	
	     // JobClient.runJob(conf);
	    
	}
	    
	    }
	

