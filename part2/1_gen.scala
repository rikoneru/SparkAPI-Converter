spark.range(10,100).selectExpr("id as _1").selectExpr("_1%3*2 as _1" ,"if(_1%3==0,_1*5,_1) as _2","_1%3*2+1 as _3")
.selectExpr("_1*_2+_3 as _1")
.collect()