spark.range(10,20).selectExpr("id as _1").selectExpr("_1%3*2+2 as _1" ,"if(_1%3>0,_1%3*2,_1) as _2","_1%3*2 as _3","if(_1%3*2-2+_1%3+2>0,_1%3*2-2+_1%3,_1) as _4")
.selectExpr("_1-_2+_3*_4 as _1")
.collect()