sc.range(10,20)
  .map(i=>{val j=i%3; val m=j*2; val k=m-2+j; (m+2, if(j>0) m else i, m, if(k+2>0) k else i)})
  .map(r=>r._1-r._2+r._3*r._4)
  .collect()