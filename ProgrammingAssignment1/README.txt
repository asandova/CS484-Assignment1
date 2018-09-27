CS484: Programing Assignment 1

to Compile:
	use provided makefile by typing "make" in the directory the makefile is located

to run:
	after using the makefile
	a file "program1" will be generated.
	to run type ./program1
	The program accepts command line arguments
	example:
		./program -p 0.1 -t 5 -s 2
		The flags (these flags can be in any order, if multiple values with the same flag
			are present, then farthest one to the right will be used ):
			-p is the probability flag. It expects a decimal value between 1 and 0
				This represents the probability value that will be used in the binomial sum
			-t is the trials flag. It expects a integer value
				This represent the number of summations of the binomial function
			-s is the success flag. It expects a integer value
				This represent the number of successes in the binomial function
NOTE: The result of the calculation is slightly off. However, this problem only arises in results that have significant digits about
	5 to 6 to the right of the decimal point. This result of acumulation of rounding down values during division. So the result is still
	faitly accurate.