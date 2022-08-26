27 emit
." [1;1H"
27 emit
." [2J"

: width 10 ;
: height 7 ;

variable x
variable y
variable c

variable char
3 cells allot
 
32 char !
62 char 1 cells + !
42 char 2 cells + !

variable py
height 2 / py !

variable ex
variable ey

height 1 - rand ey !
width 1 - ex !
100000000 0
do
  27 emit
  ." [1;1H"
  0 y !
  height 0 
  do 
   0 x !
   width 0
   do
     0 c !

     x @ 0 = 
     y @ py @ =
     and 
     if 1 c ! then

     x @ ex @ = 
     y @ ey @ =
     and 
     if 2 c ! then


     char c @ cells + @ emit
     1 x +!
   loop
   cr
   1 y +!
  loop

  key? 
  if 
   key 32 = 
   if leave then
  then

  key? 
  if 
   key 119 = 
   if -1 py +! then 
  then

  key? 
  if 
   key 115 = 
   if 1 py +! then 
  then

  py @ 0 < if 0 py ! then
  py @ height 1 - > if height 1 - py ! then

  0 ex @ = 
  py @ ey @ =
  and
  if leave then

  -1 ex +!
  ex @ -1 = 
  if 
   height 1 - rand ey !
   width 1 - ex !
  then

   
loop
." Game Over"
