27 emit ." [1;1H" 27 emit ." [2J"
: del 50  ;
variable k
variable l
variable keycode
variable keyif
variable n
variable y

variable flip
32 cells allot
0 flip 0 cells + !
16 flip 1 cells + !
8 flip 2 cells + !
24 flip 3 cells + !
4 flip 4 cells + !
20 flip 5 cells + !
12 flip 6 cells + !
28 flip 7 cells + !
2 flip 8 cells + !
18 flip 9 cells + !
10 flip 10 cells + !
26 flip 11 cells + !
6 flip 12 cells + !
22 flip 13 cells + !
14 flip 14 cells + !
30 flip 15 cells + !
1 flip 16 cells + !
17 flip 17 cells + !
9 flip 18 cells + !
25 flip 19 cells + !
5 flip 20 cells + !
21 flip 21 cells + !
13 flip 22 cells + !
29 flip 23 cells + !
3 flip 24 cells + !
19 flip 25 cells + !
11 flip 26 cells + !
27 flip 27 cells + !
7 flip 28 cells + !
23 flip 29 cells + !
15 flip 30 cells + !
31 flip 31 cells + !

4 n !
0 y !
variable temp
0 temp !
variable a
16 cells allot
255 a 6 cells + !
variable temp2

: j 
 a y @ 1 + cells + @ 
 n @ and 0 = 
 if
  1 y +!
 else 
  a y @ cells + @ 
  n @ or
  a y @ cells + !

  0 y !

  1 rand 1 = 
  if 4 n ! else 6 n ! then
 then
;

: rb if 42 emit else 95 emit then ;
: r
 6 0
 do
  a i cells + @ 30 >
  if
    i temp2 !
    temp2 @ 0
    do
      a temp2 @ i - 1 - cells + @
      a temp2 @ i - cells + !
    loop
  then 
 loop
 27 emit ." [1;1H"
 6 0
 do
  a i cells + @ k !
  i y @ = if k @ n @ or k ! then
  k @ 1 and 1 = rb
  k @ 2 and 2 = rb
  k @ 4 and 4 = rb
  k @ 8 and 8 = rb
  k @ 16 and 16 = rb
  cr
 loop
 a 1 cells + @ 0 >
 y @ 0 = and
 if
  4 n !
  0 y !
  0 a !
  0 a 1 cells + !
  0 a 2 cells + !
  0 a 3 cells + !
  0 a 4 cells + !
  0 a 5 cells + !
  255 a 6 cells + !
 then

;
: in
 n @ l !
 key? keyif !

 keyif @
 if
  key keycode !
 then

 keyif @
 if
  keycode @ 97 =
  if
    flip n @ cells + @
    2 * 32 <
    if n @ 2 / n ! then
  then
 then

 keyif @
 if
  keycode @ 32 =
  if leave then
 then

 keyif @
 if
  keycode @ 100 =
  if
    n @ 2 * 32 <
    if n @ 2 * n ! then
  then
 then

 keyif @
 if
  keycode @ 115 =
  if j then
 then

 a y @ cells + @ 
 n @ and 0 >
 if l @ n ! then
 r
;
r
100000000 0
do
 in del sleep
 in del sleep
 in del sleep
 in del sleep
 in del sleep
 in del sleep
 in del sleep
 in del sleep
 in del sleep
 j in del sleep
loop
