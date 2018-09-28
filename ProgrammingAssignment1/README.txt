CS484: Programing Assignment 1

to Compile:
	use provided makefile by typing "make" in the directory the makefile is located

to run:
	after using the makefile
	a file "program1" will be generated.
	to run type "./program1"
	The program only accepts command line arguments
	example:
		./program -p 0.1 -total 5 -tar 2

	The flags (these flags can be in any order, if multiple values with the same flag
			are present, then farthest one to the right will be used ):
			-p is the probability flag. It expects a decimal value between 1 and 0
				This represents the probability value that will be used in the binomial sum
			-total is the total flag. It expects a integer value
				This represent the number of total number space of the binomial function
			-tar is the target flag. It expects a integer value
				This represent the number of summation in the binomial function

			-test:	is to run the program in a testing mode. 
				Will take flags -p -t -s and just test the binomial functions.
				will cause the program to ignore the active, idle, bwu and bwl flags

			-active:	is the proability of a user being active. This value is a decimal value
					Note: will cause an error when used with the -idle flag. 
					This is bacause the idle value will be generated from the active value
			-idle:	is the proability of a user being idle. This value is a decimal value
					Note: will cause an error when used with the -active flag.
					This is because the active value will be generated from the idle value
			-bwu:	Is the user bandwidth measured in mb/s
					expects a real number
			-bwl:	Is the link bandwidth measured in mb/s
					expects a real number

NOTE: The result of the calculation is slightly off. However, this is due to early termination of the division.
	this is to prevent the it from calulating values when the quotient of two values that are irrational.
	otherwise, it will round down values that have the decimal values longer then the numerator.