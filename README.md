~ Official Test Documentation ~
// TESTING DOCUMENTATION

QUICK OVERVIEW:
Test # | What it has/does
1 | Instantiates integers and strings,
tests an input and an if statement,
string concatenation, outputs string
2 | Outputs string and integer WITHOUT assignment,
this tests instantiation
// TEST 1
// Tests a basic if statement, integer input, and string concatenation
var integer x, y, z; string varA
main input ( x ) if ( x > 5 ) then x = 10 ; end if
varA = "first part" ;
varA = varA + "second part" + "last part"
output ( varA ) end

// output -> "first partsecond partlast part"

// TEST 2
// Tests instantiation, output, and basic assignment, addition, and string concatenation
var integer x, z; string a, b;
main output ( x ) output ( a ) z = z + 10; b = b + "hello world"; end

//output -> 0 (0 and an empty string)
x -> 0, z -> 10, a -> "", b -> "hello world"

// TEST 3
// Tests a simple, but infinite while loop
var integer x;
main x = 10;
while ( x > 0 ) loop
output ( 1 ) end loop
end

// Should print 1 infinitely

// TEST 4
// Tests a while loop, should increment, output, and eventually stop
var integer x;
main x = 1 ;
while ( x < 5 )
loop output ( x ) x = x + 1 ;
end loop
end
