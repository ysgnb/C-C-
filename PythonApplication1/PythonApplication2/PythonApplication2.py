#计算三角形面积
import math  #引入库
a=int(input())
b=int(input())
c=int(input())

s=(a+b+c)/2
area=math.sqrt(s*(s-a)*(s-b)*(s-c))
print("三边：",a,b,c,end=' ')
print("面积：",area)