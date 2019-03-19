ReadME
by Jingzhu He, Rithish Koneru

All the 6 functions that implemented on RDD, Dataset and Dataframe APIs are listed in each .scala file. There are 18 .scala files in total. I have included a.txt and b.txt for testing the codes.

The Scala file name indicates the corresponding function, which is described in our report. For example, count_rdd.scala means the code implements the count function on top of RDD API.

How to run?
You can start the Spark docker, then enter a working directory and start the Spark shell. You can paste the code inside each .scala file to the Spark shell to check the result. The same function should achieve the same results, although they are implemented on different APIs. For example, running count_rdd.scala, count_dataset.scala and count_dataframe.scala should get the same result.

ATTENTION!!!!!!!!!!!!!!!!!:
=========================================================================================
each code contains "filename". It means the file path of a .txt file. I have included a.txt and b.txt file. 

When you start Spark docker, COPY the a.txt and b.txt into your working directory. BE SURE that the working directory is the directory you start the Spark shell!!! If you meet the "filename" in the code, replace it with a.txt. For example, in count_rdd.scala, the code is sc.textFile("filename").count(). Then your pasted Scala code should be sc.textFile("a.txt").count(). If you meet "filename1" and "filename2", replace them with "a.txt" and "b.txt" correspondingly.

Also you can create your own .txt file. Be sure you are using correct file path.
=========================================================================================

