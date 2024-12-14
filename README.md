## To run locally on machine:

1. git clone the repository to desired location.
2. Change "#define READ (0)" to "#define READ (1)" in the helper_functions.h file to enable input retreival with curl (for this to work, the two steps below are necessary)


In helper_functions.h:

BEFORE:
```c
#define READ (0)
```
AFTER:
```c
#define READ (1)
```

4. Create config.h file in repository at root directory
5. Add the line "#define SESSIONID "[Your session ID for Advent of code]" this allows for automatic retrieval of your personal input. Don't share your sessionid accidentally by forgetting to add config.h in gitignore...
   You can retrieve your session ID by going to advent of code, inspect the webpage, applications -> cookies -> session. Copy the value into the config.h file. Please don't share this session ID with anyone as it could give
   them access to your Advent Of Code account.

 in Config.h:
```c
#define SESSIONID "[Your session ID for Advent of code]"
```
7. In terminal at root of repo run: "make && make test" to build and run. Once, you've run "make test" once, you can revert step 2 so you don't have to retrieve input from advent of code as this usually takes ~5 seconds.


## Info
The result is printed on the format below, if my solution could not calculate part 1 and 2 during the same run, individual times will be printed as well below total time. The individual time is calculated as total time subtracted by 
parts that only involve the the other part (naturally). OBS!!! TIME WILL NOT BE REPRESENTED CORRECTLY IF DATA IS BEING READY BY CURL, REVERT STEP 2!

\-----------Day XX-----------------  
Part 1 result: [result_value]  
Part 2 result: [result_value]  
Time: [time for part 1 & 2 in seconds]  
[Time Part 1: [time for part 1]]  
[Time Part 2: [time for part 2]]  
\---------------------------------

# REFLECTIONS

## DAY 1:
Not very structured code but concise. Pretty straightforward.

## DAY 2:
Perhaps writing everything in one function is something I should stop doing. Still breathing BOIS

## DAY 3:
Happy with the code, structured and concise. Not bad

## DAY 4:
For part two I realise you could write a similar direction array as for the first part. I did it and it did not work.
1 hour debug: I learnt that I suck at rotating objects with number representation.

## DAY 5
Very happy with the code. Accidentally skipped every second line on part one and still got the correct answer, a lot of margin it seems. Made debugging part two
quite the ride. Motivation still high!


## DAY 6
No words. I thought I had it all figured. Part one went very smoothly... then part two felt like someone shoved a glock down my mouth. I quickly thought alright,
we can only place obstructions on the path taken by the guard, we cannot put an obstruction where we've already been as that would make the current path unfeasible. I get the correct input
on the smaller input and then I experience the immeasurable joy of finding out my solution on the larger input did not work. I'm going crazy,  experimenting with different smaller inputs, ok, what if
the loop is independant from the obstruction? Na we got that covered. After a very rough day I found the bug. If the guard returns to the obstruction through a different path, he walks straight through like fucking
Juggernaut from X-MEN. Slowly losing my sanity. At least the code turned out alright and I can handle multiple guards, perhaps attempt to implement multithreaded for multiple guards and with visuals?

## DAY 7
Wow the previous one made this feel great. It was evident that the you would have to use data types which can store big enough numbers, yet I succeed in declaring ONE function as int and it ruined me. I didn't understand why it did not work. I'm
like they won't get me with that bullshit. Then I print the values and see the '-' sign and realise that they did in fact, get me with that bullshit.

## DAY 8
This one was very nice apart from the fact that they actually screwed me over with result for part one & two. The way I solved it, it is not possible to calculate each result by itself. Hence I actually run the algorithm
twice to generate the result for part one and two which sucks. Had I gone with a linked list then it would have been possible but linked list was less efficient as you would have to iterate through every unique 
antinode to make sure you don't add duplicate ones. I think the time complexity for simply checking a unique value would become O((N*N+1)/2) (?) which for my input would be 50721  (318 \* 319 / 2)  for part one and 634501  (1126 \* 1127 / 2)  . Instead I just used a 2d array of boolean values and when I placed an antinode, I simply put that coordinate to true. Then iterate through the list which is of size ASCII_TABLE_SIZE * ASCII_TABLE_SIZE  (128 \* 128)  which is 16384. Hence, I can't justify changing it :(

##DAY 9
