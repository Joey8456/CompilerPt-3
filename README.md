# ~ Official Test Documentation ~

## QUICK OVERVIEW
Test # | What it has/does\
1 | Variable instantiation, input, output, and string concatenation\
2 | Output without variable instantiation\
3 | Infinite while loop\
4 | Non-infinite while loop\
5 | Relational operators with strings\
6 | If statements with strings

## TEST 1
Tests a basic if statement, integer input, and string concatenation.
```
var integer x, y, z;
string varA
main
    input(x)
    if (x > 5) then
        x = 10;
    end if
    varA = "first part";
    varA = varA + "second part" + "last part"
    output(varA)
end
```

output:
```
"first partsecond partlast part"
```

## TEST 2
Tests instantiation, output, and basic assignment, addition, and string concatenation.
```
var integer x, z;
string a, b;
main
	output(x)
	output(a)
	z = z + 10;
	b = b + "hello world";
end
```

output: 
```
0 (0 and an empty string)
x -> 0, z -> 10, a -> "", b -> "hello world"
```

## TEST 3
Tests a simple, but infinite, while loop.
```
var
	integer x;
main
	x = 10;
	while (x > 0) loop
		output(1)
	end loop
end
```

output:
```
1
1
1
1
... (repeats infinitely)
```

## TEST 4
Tests a while loop. Should increment, output, and eventually stop.
```
var
	integer x;
main
	x = 1;
	while (x < 5) loop
		output(x)
		x = x + 1;
	end loop
end
```
output:
```
1
2
3
4
5
```

## TEST 5
Tests greater than and less than comparisons between two strings of equal length.
```
var
	string first, second;
main
	first = "aaa";
	second = "zzz";
	if (first < second) then
		output("this should not print")
	else
		output("congrats")
	end if
	if (first > second) then
		output("congrats")
	else
		output("this should not print")
	end if
end
```
output:
```
congrats
congrats
```

## TEST 6
Tests if statements with an empty string and a non-empty string.
```
var
	string empty, notEmpty;
main
	notEmpty = "hello";
	if (empty) then
		output(good)
	else
		output(bad)
	end if
	if (notEmpty) then
		output(good)
	else
		output(bad)
	end if
end
```
output:
```
good
good
```
