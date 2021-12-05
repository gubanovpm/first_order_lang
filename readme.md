# Second task 
## You can build Makefile by yourself:
```
mkdir build
cd ./build
cmake ..
make
./first_order_language
```

## To run some examples (if your current location is /first_order_language/build ) :
```
./first_order_language < ../tests/complete/test_1.dat
./first_order_language < ../tests/complete/test_2.dat
...
```

### IMPORTANT: current main.cpp made to support input in a specific view in files located in ./tests/test/

### Initially, there are only functions:
```
+    -- addition of two numbers
+M N -- addition of two numbers by a predetermined modulus N
*    -- multiplication of two numbers
*M N -- multiplication of two numbers by a predetermined modulus N
+S   -- next element
+S N -- the next element according to a predefined module N
```
### And predicates:
```
<  -- if the first of the two numbers is less than
>  -- if the first of the two numbers is greater than
=  -- checking the equality of two numbers
<> -- checking the inequality of two numbers
<= -- if the first is less than or equal to the second
>= -- if the first is greater than or equal to the second
```
### An example of a correctly set signature (you can also see it in ./tests/signature/)
#### First you need to specify the number of constants, and then list them. The next section - descriptions of functions - first enter their number, and then the names from the above list (or names from your own implementation). In the last section, describe the predicates - also their number, followed by their names :
```
2 
0 1
2
+M 3 *M 3
2
= <> 
```
### An example of a correct formula description (can also be seen in ./tests/lexer/).
#### Logical operations
```
&  -- logical AND
|  -- logical OR
~  -- logical NOT
-> -- logical IMPLICATION
```
#### Description of a function or predicate - first its name and in parentheses to the right its arguments: =(x, x).

#### Full example of formula:
```
!A x (<>(x, 0) -> !E y ( =(*M(x,y), 1)))
```