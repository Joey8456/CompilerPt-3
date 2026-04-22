# ~ Official Test Documentation ~

## QUICK OVERVIEW
Test # | What it has/does\
1 | Variable instantiation, input, output, and string concatenation\
2 | Output without variable instantiation\
3 | Infinite while loop\
4 | Non-infinite while loop\
5 | Relational operators with strings\
6 | If statements with strings\
7 | Nested if statements\
8 | Divide by zero\
9 | Numerical operators + expression assignment

## TEST 1
Tests a basic if statement, integer input, and string concatenation.\
Code:
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
Expected output:
```
"first partsecond partlast part"
```

## TEST 2
Tests instantiation, output, and basic assignment, addition, and string concatenation.\
Code:
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
Expected output: 
```
0 (0 and an empty string)
x -> 0, z -> 10, a -> "", b -> "hello world"
```

## TEST 3
Tests a simple, but infinite, while loop.\
Code:
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
Expected output:
```
1
1
1
1
... (repeats infinitely)
```

## TEST 4
Tests a while loop. Should increment, output, and eventually stop.\
Code:
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
Expected output:
```
1
2
3
4
5
```

## TEST 5
Tests greater than and less than comparisons between two strings of equal length.\
Code:
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
Expected output:
```
congrats
congrats
```

## TEST 6
Tests if statements with an empty string and a non-empty string.\
Code:
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
Expected output:
```
good
good
```

## TEST 7
Tests nested if statements.\
Code:
```
var
	integer a, b, c;
main
	a = 7;
	b = 5;
	c = 10;
	if (a > b) then
		output("good")
		if (c > b) then
			output("also good")
			if (a > c) then
				output("not good")
			end if
		end if
	end if
end
```
Expected output:
```
good
also good
```

## TEST 8
Tests division by zero.\
Code:
```
var
	integer aNumber;
main
	aNumber = 7 / 0;
end
```
Expected output:
```
Error: Attempt to divide by zero.
```

## TEST 9
Tests assignment using an expression with several numerical operators. Verifies that precedence is implemented properly.\
Code:
```
var
	integer a, b, result;
main
	a = 0;
	b = 10;
	result = a + b * 3 - 2 + 7 % 2;
	output(result)
	output(29)
end
```
Expected output:
```
29
29
```
