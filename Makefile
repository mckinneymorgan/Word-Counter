# CS315 Makefile for Program 4: Word Counter
# Feel free to modify as needed.
# Original author: Raphael Finkel 3/2020

CFLAGS = -Wall -g
CPPFLAGS = -Wall -g
GOAL = wordCount
DATA = data.txt
WORKING = workingWordCount

# compile and run the student program, placing the result in tmpRun.out
run: $(GOAL) $(DATA)
	./$(GOAL) < $(DATA) > tmpRun.out
	less tmpRun.out

# compile and run the student program, using student testing data
runTest: $(GOAL) $(DATA)
	./$(GOAL) < testData.txt > testOutput.out
	less testOutput.out

# run a known working program, placing the result in tmpWorking.out
runWorking: $(WORKING) $(DATA)
	./$(WORKING) < $(DATA) > tmpWorking.out
	less tmpWorking.out

# get the working program
$(WORKING):
	wget http://www.cs.uky.edu/~raphael/courses/CS315/prog4/$(WORKING)
	chmod +x $(WORKING)

# get the data
$(DATA):
	wget http://www.cs.uky.edu/~raphael/courses/CS315/prog4/$(DATA)

# Modify the following recipe to zip exactly what you want to include.
zipAll: 
	zip toSubmit.zip $(GOAL).* Makefile README.txt tmpRun.out testData.txt testOutput.out
								
.PHONY: clean
clean:
	rm -f $(GOAL) $(WORKING) $(DATA) tmp* toSubmit.zip
