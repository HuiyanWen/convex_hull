# 求解凸包问题
详细过程可参考pdf文档或代码。
## 蛮力法
算法Bruteforce(Q)
<br>输入 :平面上n个点的集合Q
<br>输出 :CH(Q)，Q的凸包
<br>1:  For ∀A,B,C,D∈Q Do
<br>2:     If   D位于ABC组成的三角形内(根据面积判定)
<br>3:        Then    从Q中删除该点
<br>4:   A←Q中横坐标最大的点
<br>5:   B←Q中横坐标最小的点
<br>6:   SL←{P|P∈Q且P位于AB直线的下方}
<br>7:   SU←{P|P∈Q且P位于AB直线的上方}
<br>8:   对SL和SU分别升序排序
<br>9:   输出A, SL, B, 逆序SU
## Graham-Scan
算法Graham-Scan(Q)
<br>输入 :平面上n个点的集合Q
<br>输出 :CH(Q)，Q的凸包
<br>1:  求Q中y坐标最小的点p0，若存在多个点，则选x坐标最小的
<br>2:  按照与p0的极角逆时针排序其余点< p0, p1, …, pm>，
<br>3:  如果存在极角相同的点，选择欧式距离更近的点在前
<br>4:   S.push(p0), S.push(p1), S.push(p2)
<br>5:   For i←3 To m Do
<br>6:      While S.next_to_top(), S.Top()和pi形成非左 Do
<br>7:         S.Pop()
<br>8:         S.push(pi)
<br>9:   Return S
## 分治法
算法Divide_and_conquer(Q)
<br>输入 :平面上n个点的集合Q
<br>输出 :CH(Q)，Q的凸包
<br>•	Preprocess:找到横坐标最大的点A和最小的点B，标记每个点是否访问，若全部访问则算法停止。(时间复杂度为O(n))；
<br>•	Divide:作直线AB，把凸包分为SL和SU上下两个子集，对每个部分求得点Pmax,使得SABPmax最大。将三角形三个点和三角形内部的点标记为已访问，删去所有三角形内部及边上的点。(时间复杂度为O(n))；
<br>•	Conquer: 进一步依据△ABPmax划分成左右两个部分，当作SL和SU，分治递归、不断重复。(时间复杂度为2T(n/2))。

![](https://github.com/HuiyanWen/convex_hull/blob/master/divide.png)

## 随机生成数据点并求解凸包
![](https://github.com/HuiyanWen/convex_hull/blob/master/%E5%9B%BE%E7%89%87%201.png)
