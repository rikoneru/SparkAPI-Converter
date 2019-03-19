sc.range(1,10)
  .map(i=>(i%5, 2))
  .reduceByKey((a:Int, b:Int) => a+b)
  .collect()