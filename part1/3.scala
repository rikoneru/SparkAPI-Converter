sc.range(1,10)
  .map(i=>(4, i+2))
  .reduceByKey((a:Long, b:Long) => a-b)
  .collect()