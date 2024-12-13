# To run locally on machine:

1. git clone the repository to desired location.
2. create config.h file in repository at root directory
3. add the line "#define SESSIONID [you're advent of code sessionid]" this allows for automatic retrieval of your personal input. Don't share your sessionid accidentally by forgetting to add config.h in gitignore...
4. in terminal at root of repo: "make && make test" to build and run.


# REFLECTIONS

## DAY 1:
Not very structured code but concise. Pretty straightforward.

## DAY 2:
Perhaps writing everything in one function is something I should stop doing. Still breathing BOIS

## DAY 3:
Very happy with the code, structured and concise. Not bad

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
Juggernaut from X-MEN. Slowly losing my sanity. At least the code turned out alright and I can handle multiple guards, perhaps attempt to implement multithreaded for multiple guards?

##DAY 7
Wow the previous one made this feel great. It was evident that the you would have to use data types which can store big enough numbers, yet I succeed in declaring ONE function as int and it ruined me. I didn't understand why it did not work. I'm
like they won't get me with that bullshit. Then I print the values and see the dogshit '-' sign and realise that they did in fact, get me with that bullshit.
