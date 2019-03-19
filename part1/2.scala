sc.range(1,10)
  .sortBy((a:Long)=>(a%2))
  .collect()