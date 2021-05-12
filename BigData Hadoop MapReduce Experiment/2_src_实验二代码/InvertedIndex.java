import java.io.IOException;
import java.util.StringTokenizer;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class InvertedIndex {
    public static class InvertedIndexMapper extends Mapper<Object, Text, Text, Text> {
        private Text keyInfo = new Text();
        private Text valueInfo = new Text();
        private FileSplit split;

        public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
            split = (FileSplit)context.getInputSplit();
            StringTokenizer itr = new StringTokenizer(value.toString());

            while(itr.hasMoreTokens()) {
                keyInfo.set(itr.nextToken() + ":" + split.getPath().toString().substring(split.getPath().toString().lastIndexOf('/')+1));
                valueInfo.set("1");
                context.write(keyInfo, valueInfo);
            }
        }

    }
    public static class InvertedIndexCombiner extends Reducer<Text, Text, Text, Text> {
        private Text info = new Text();
        public void reduce(Text key, Iterable<Text>values, Context context) throws IOException, InterruptedException {
            int sum = 0;
            for(Text value : values) {
                sum += Integer.parseInt(value.toString());
            }
            int splitIndex= key.toString().lastIndexOf(":");
            info.set(key.toString().substring(splitIndex + 1) + ":" + sum);
            key.set(key.toString().substring(0, splitIndex));
            context.write(key, info);
        }
    }
    public static class InvertedIndexReducer extends Reducer<Text, Text, Text, Text> {
        private Text result = new Text();
        public void reduce(Text key, Iterable<Text>values, Context context) throws IOException, InterruptedException {
            StringBuilder fileList = new StringBuilder();
            fileList.append('[');
            for(Text value : values) {
                fileList.append(value.toString()).append(",");
            }
            fileList.deleteCharAt(fileList.length()-1);
            fileList.append(']');
            result.set(fileList.toString());
            context.write(key, result);
        }
    }
    public static void main(String[] args) throws Exception{
        // TODO Auto-generated method stub
        Configuration conf = new Configuration();
        Job job = new Job(conf, "InvertedIndex");
        job.setJarByClass(InvertedIndex.class);
        job.setMapperClass(InvertedIndexMapper.class);
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(Text.class);
        job.setCombinerClass(InvertedIndexCombiner.class);
        job.setReducerClass(InvertedIndexReducer.class);

        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);

        String inputfile = "hdfs://localhost/input/";
        String outputFile = "hdfs://localhost/output/";
        FileInputFormat.addInputPath(job, new Path(inputfile));
        FileOutputFormat.setOutputPath(job, new Path(outputFile));
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}





