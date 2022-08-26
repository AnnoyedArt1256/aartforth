: size 32 ;
: max size 1 - ;

variable rule
16 cells allot

0 rule !
1 rule 1 cells + !
1 rule 2 cells + !
1 rule 3 cells + !
0 rule 4 cells + !
1 rule 5 cells + !
1 rule 6 cells + !
0 rule 7 cells + !

variable tempa
variable tempb
variable tempc

variable j

variable tape
size cells allot
variable new_tape
size cells allot
1 tape size 2 - cells + !

size 0
do
 cr
 size 0
 do
   tape i cells + @ 1 =
   if 42 42 emit emit else 32 32 emit emit then
   0 j !

   i 1 - tempa !
   tempa @ max > if max tempa ! then
   tempa @ 0 < if 0 tempa ! then

   i 1 + tempc !
   tempc @ max > if max tempc ! then
   tempc @ 0 < if 0 tempc ! then

   tape tempa @ cells + @ 4 * j +!
   tape i cells + @ 2 * j +!
   tape tempc @ cells + @ j +!

   rule j @ cells + @
   new_tape i cells + !
 loop
 size 0
 do
   new_tape i cells + @ 
   tape i cells + !
 loop
loop
