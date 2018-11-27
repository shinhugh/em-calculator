# Expectation-Maximization Calculator (WIP)

A command line utility that takes in data and uses
expectation-maximization to calculate unobserved
data values.<br/>
Feed the program data and it will learn on its own about the
subjects involved.<br/>
<br/>
This project is still a work-in-progress.

## Goal

The program will take data and, given that person X has not given a
definite response to a specific topic (i.e. responded "don't know"
to "Avicii"), determine the most likely response person X would make
to that same topic (i.e. person X is most likely to be a fan of
Avicii). To make this calculation, the program learns from the inputs
made by all others on this category as well as the inputs made by
person X on the other categories.

## Input files

There are 3 different files to feed into the program:<br/>
* Initial prior probability values
* Initial conditional probability values
* Data samples

### Initial prior probability values

These values hold P(Y = i). Y is the unobserved hidden parameter,
the sole parent of all X parameters. There can be as many possible
i values as desired.<br/>
These values don't necessarily have to be true; they serve as
starting points that the EM algorithm will start from.<br/>
**Format**: Place each value on a new line, going down from i = 1 to
whatever number of options the user desires.

### Initial conditional probability values

These values hold P(R<sub>c</sub> = j \| Y = i). X is the observed
parameter, and j is the response to that parameter that a person
may make.<br/>
For example, one such value may represent the probability that
person #3 (c = 3) gives response #2 (j = 2) given that his/her
hidden parameter is #4 (Y = 4).<br/>
These values don't necessarily have to be true; they serve as
starting points that the EM algorithm will start from.<br/>
**Format**: TBD

### Data samples

The data contains input from many people on different topics.<br/>
For example, 200 people can respond to whether they like, dislike,
don't care for, or don't know 50 celebrities. As a result, there
would be 200 x 50 inputs.<br/>
**Format**: Place each sample/person's inputs on a single line. Each
line represents a single sample/person, and the inputs go from
left to right, going from c = 1 to however many categories are
specified by the user. Separate each input with a space. A input
of 0 signifies no input (i.e. "I don't know", "I haven't seen it").
The meanings of all other values can be assigned by the user; make
sure that only integers are used and that no value is skipped.