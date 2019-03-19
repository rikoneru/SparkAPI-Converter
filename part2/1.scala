sc.range(10,100)
  .map(i=>{val j=i%3; val m=j*2; (m, if(j==0)i*5 else i, m+1)})
  .map(r=>r._1*r._2+r._3)
  .collect()