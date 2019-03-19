sc.range(10,100)
  .map(i=>{val j=i%3; val m=3+j; (m+2, if(j==0) m else i, i, if(m!=0) m else m*2)})
  .map(r=>r._1*r._2-r._3+r._4)
  .collect()