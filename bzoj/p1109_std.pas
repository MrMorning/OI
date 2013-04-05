Program Klo;
Const
 MaxN = 100000 ;
Var
 A , B , Q : Array[ 0..MaxN ] of Longint ;
 N , M , Ans : Longint ;

Procedure Gf_Qsort( l , r : Longint ) ;
Var  i , j , t , Mid_A , Mid_B : Longint ;
Begin
 i := l ; j := r ; Mid_A := A[ ( l + r ) Shr 1 ] ; Mid_B := B[ ( l + r ) Shr 1 ] ;
 Repeat
  While ( B[i] > Mid_B ) Or ( B[i] = Mid_B ) And ( A[i] < Mid_A ) Do Inc( i ) ;
  While ( B[j] < Mid_B ) Or ( B[j] = Mid_B ) And ( A[j] > Mid_A ) Do Dec( j ) ;
  If ( i <= j ) Then
   Begin
    t := A[ i ] ; A[ i ] := A[ j ] ; A[ j ] := t ;
    t := B[ i ] ; B[ i ] := B[ j ] ; B[ j ] := t ;
    Inc( i ) ; Dec( j ) ;
   End;
 Until ( i > j ) ;
 If ( i < r ) Then Gf_Qsort( i , r ) ;
 If ( j > l ) Then Gf_Qsort( l , j ) ;
End;

Procedure Gf_Init;
Var  i , x : Longint ;
Begin
 Readln( N ) ;
 For i := 1 To N Do
  Begin
   Read( x ) ;
   If ( x <= i ) Then
    Begin
     Inc( M ) ; A[ M ] := x ; B[ M ] := x - i ;
    End;
  End;
End ;

Procedure Gf_Work;
Var  i , l , r , Mid : Longint ;
Begin
 N := M ; Gf_Qsort( 1,N ) ;
 Fillchar( Q , Sizeof(Q) , 127 ) ;
 For i := 1 To N Do
  Begin
   l := 1 ; r := Ans ;
   If ( A[ i ] > Q[ Ans ] ) Then
    Begin
     Inc( Ans ) ; Q[ Ans ] := A[ i ] ; Continue ;
    End;
   While ( l < r ) Do
    Begin
     Mid := ( l + r ) Shr 1 ;
     If ( Q[ Mid ] = A[ i ] ) Then Begin  l := Mid ; Break ;  End ;
     If ( Q[ Mid ] < A[ i ] ) Then l := Mid + 1 Else r := mid ;
    End;
   Q[ l ] := A[ i ] ; If ( l > Ans ) Then Ans := l ;
  End;
End;

Procedure Gf_Print;
Begin
 Writeln(  Ans  ) ;
End;

Begin
assign(input, 't.in'); reset(input);
 Gf_Init;
 Gf_Work;
 Gf_Print;
End.


