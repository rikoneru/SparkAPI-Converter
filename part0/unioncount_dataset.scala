spark.read.textFile("filename1").union(spark.read.textFile("filename2")).count()