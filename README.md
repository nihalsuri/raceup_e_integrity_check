# Formula Student-RaceUP-E Recruitment Task 
Optional recruitement task for software department at RaceUP-e 

## Rules 
* Don’t change integrity_check_db.h and integrity_check_db.c files.
* Comments that explain what you are doing and your way of thinking are
 very welcomed
* NO OTHER EXTERNAL LIBRARIES ALLOWED

## Getting Started
- 

## Functionality & Debugging





## Design Decisions 
- Log the unit test case results with the timestamp to a file following an easy and portable JSON structure
- Mature batch file usage for easy debugging purposes -> Prompt user if a compiler is available or not for the program to run


## Recommendations to the main task
- Clear decleration in the task of the version of MinGW to be consumed, and link provided to the setup tool as well with the guide
- Wrong command mentioned in the guide for version check, can be mentioned in future recruitment tasks, if ever required again. 
![guide1](images/guide_incorrect.png)
![guide2](images/guide_prood.png)


## Future Improvements
- Usage of MakeFile when this unit testing library grows and multiple object files are required 
- Thread locking mechanisms can be added like mutexes, currently its not a major concern as the size of our project is quite limited, but if we would like to develop on the same and grow it, then the program can be structured in such a way
- Stronger and more restricted unit testing approach can be applied if more requirements are defined, a framework such as [CUnit](https://cunit.sourceforge.net/) can maybe be consumed