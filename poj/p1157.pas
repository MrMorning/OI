(*
����ʵ�ʣ���1--F��Ԫ�ذ���������V���գ�ʹ�á�Aij�������iԪ������j�ſգ���
�㷨�� ��̬�滮��
	1.	״̬ת�Ʒ���
		f[i,j]��ʾǰi����������ǰj����ƿ�ܴ���������ѧ��ֵ��
		��f[i,j]:=MAX{f[i,j-1], f[i-1,j-1] + A[i,j]}
	2.	���̺���
		Ϊ�˱�֤���������еĻ�������ã�������ƿ��Ϊ�׶Σ�
			����f[i,j]
			(1)��j��ƿ�Ӳ��Ż���f[i,j] <- f[i,j-1]
			(2)��j��ƿ��Ҫ�Ż���f[i,j] <- f[i-1,j-1]+A[i,j]
	3.	��ʼ��
		f[i,0]:=0;
		f[0,j]:=0;
		f[i,j]:=-INFINITY	|(i<>0)and(j<>0)
���ܳ��ֵĴ���
1.	�߽�����û���������
2.	f[i,j]�У�Ҫһֱά��i<=j��
3.	���ʱѭ������д��˳����Ϊ������ֵ��ʱ����˳��ģ������󷽰���Ҫ���ƻ�ȥ��
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
