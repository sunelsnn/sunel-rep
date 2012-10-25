

	import java.io.IOException;
	import java.util.*;
	
	import org.apache.hadoop.fs.Path;
	import org.apache.hadoop.conf.*;
	import org.apache.hadoop.io.*;
//	import org.apache.hadoop.mapred.OutputCollector;
 import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.*;
	
	public class WordCount {
	
	    public static class Map extends Mapper<Object, Text, Text, IntWritable> {
	      private final static IntWritable one = new IntWritable(1);
	      private Text word = new Text();
	  //  private LongWritable word = new LongWritable() ;
	
	      public void map(Object key, Text value, Context context ) throws IOException , InterruptedException {
	        String line = value.toString();
	        StringTokenizer tokenizer = new StringTokenizer(line);
	        while (tokenizer.hasMoreTokens()) {
	          word.set(tokenizer.nextToken());
	          context.write(word, one);
	        }
	      }
	    }
	
	    public static class Reduce extends  Reducer<Text, IntWritable, Text, IntWritable> {
	      public void reduce(Text key, Iterator<IntWritable> values, Context context) throws IOException , InterruptedException  {
	        int sum = 0;
	        while (values.hasNext()) {
	          sum += values.next().get();
	        }
	        context.write(key, new IntWritable(sum));
	      }
	    }
	
	    public static void main(String[] args) throws Exception {
	    	Configuration conf = new Configuration();
	      Job job = new Job (conf, "WordCount");
	      job.setJarByClass(WordCount.class);
	      job.setMapperClass(Map.class);
	      job.setCombinerClass(Reduce.class);
	      job.setReducerClass(Reduce.class);
	      job.setOutputKeyClass(Text.class);
	      job.setOutputValueClass(IntWritable.class);
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
	

