(*
问题实质：将1--F的元素按升序填入V个空，使得∑Aij最大（其中i元素填在j号空）。
算法： 动态规划：
	1.	状态转移方程
		f[i,j]表示前i个花，填入前j个花瓶能创造的最大美学价值。
		则f[i,j]:=MAX{f[i,j-1], f[i-1,j-1] + A[i,j]}
	2.	方程含义
		为了保证升序，且所有的花都须放置，所以以瓶子为阶段：
			对于f[i,j]
			(1)第j个瓶子不放花：f[i,j] <- f[i,j-1]
			(2)第j个瓶子要放花：f[i,j] <- f[i-1,j-1]+A[i,j]
	3.	初始化
		f[i,0]:=0;
		f[0,j]:=0;
		f[i,j]:=-INFINITY	|(i<>0)and(j<>0)
可能出现的错误：
1.	边界条件没考虑清楚。
2.	f[i,j]中，要一直维护i<=j。
3.	输出时循环不能写成顺序，因为求最优值的时候是顺序的，所以求方案就要倒推回去。
*)
Program SGU_104;

Type 
  TCounter = Longint;
  TIndex = Longint;
  TWeight = Longint;
  TUsed = Boolean;
  TFlower_Index = TIndex;
  TVase_Index = TIndex;
Var 
  Flower_Num, Vase_Num: TCounter;
  A, F: Array[0..100, 0..100] Of TWeight;
  G: Array[0..100, 0..100] Of TUsed;

Procedure Init;
  Var 
    i, j: TIndex;
  Begin 
    Readln(Flower_Num, Vase_Num);
    For i := 1 To Flower_Num Do 
      For j := 1 To Vase_Num Do 
          Read(A[i, j]);
  End;

Procedure DP;
  Var 
    i, j: TIndex;
  Begin 
    For i := 1 To Flower_Num Do 
      Begin 
        f[i, i - 1] := -MaxLongint;
        For j := i To Vase_Num Do 
          Begin 
            f[i, j] := f[i, j - 1];
            G[i, j] := FALSE;
            If (f[i - 1, j - 1] + A[i, j]) > f[i, j] Then 
              Begin 
                f[i, j] := f[i - 1, j - 1] + A[i, j];
                G[i, j] := TRUE;
              End;
          End;
      End;
  End;

Procedure Print;
  Var 
    i: TFlower_Index;
    j: TVase_Index;
    plen: TCounter;
    p: Array[1..100] Of TFlower_Index;
  Begin 
    Writeln(f[Flower_Num, Vase_Num]);
	{i := Flower_Num;
    plen := 0;
    For j := Vase_Num Downto 1 Do 
      If G[i, j] Then 
        Begin 
          Inc(plen);
          p[plen] := j;
          Dec(i);
        End;
    Write(p[Flower_Num]);
    For i := Flower_Num - 1 Downto 1 Do 
      Write(' ', p[i]);}
  End;

Begin 
	assign(input, 't.in'); reset(input);
    Init;
    DP;
    Print;
  End.
