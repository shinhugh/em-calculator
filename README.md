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

## Get started

Coming soon

## Input files

There are 4 different files to feed into the program:<br/>
* Initial prior probability values
* Initial conditional probability values
* Data samples
* Titles/meanings

### Initial prior probability values

These values hold P(Y = *i*). Y is the unobserved hidden parameter,
the sole parent of all X parameters. There can be as many possible
*i* values as desired.<br/>
These values don't necessarily have to be true; they serve as
starting points that the EM algorithm will start from.<br/>
**Format**:<br/>
Place each value on a new line, going down from *i* = 1
to whatever number of options the user desires.

### Initial conditional probability values

These values hold P(X<sub>c</sub> = *j* \| Y = *i*). X is the
observed parameter, and *j* is the response to that parameter that a
person may make.<br/>
For example, one such value may represent the probability that
person #3 (*c* = 3) gives response #2 (*j* = 2) given that his/her
hidden parameter is #4 (*i* = 4).<br/>
Make sure that the range of Y values is consistent with what is
provided in the prior probability file.<br/>
These values don't necessarily have to be true; they serve as
starting points that the EM algorithm will start from.<br/>
**Format**:<br/>
Place each probability P(X<sub>c</sub> = *j* \| Y = *i*)
on the line represented by *i* and *c*. The first line represents
*i* = 0, *c* = 0. The probability values are placed on that line, in
order of increasing j. The top left probability should be
P(X<sub>0</sub> = 0 \| Y = 0).<br/>
The second line represents *i* = 0, *c* = 1. This pattern repeats
until the maximum *c*-value is reached, upon which *c* resets to 0
and *i* increases by 1. This repeats until all *i*-values are
exhausted.<br/>
There should be a total of *k* x *n* lines, where *k* is the total
number of possible Y-values and *n* is the total number of categories.
There should be a total of *k* x *n* x *m* probability values,
where *m* is the total number of possible X-values.

### Data samples

The data contains input from many people on different topics.<br/>
For example, 200 people can respond to whether they like, dislike,
don't care for, or don't know 50 celebrities. As a result, there
would be 200 x 50 inputs.<br/>
**Format**:<br/>
Place each sample/person's inputs on a single line. Each
line represents a single sample/person. The inputs go from left to
right, going from *c* = 1 to however many categories are
specified by the user. Separate each input with a space. A input
of 0 signifies no input (i.e. "I don't know", "I haven't seen it").
The meanings of all other values can be assigned by the user; make
sure that only integers are used and that no value is skipped.
Again, **0** is reserved for signifying no input.

### Titles/meanings

This file doesn't affect or contribute to the EM calculations but
provides meaning to the calculations made. It enables the program
to have meaningful user interaction.<br/>
It holds 3 segments:<br/>
* labels for all *n* categories
* meanings assigned to all m possible responses (0 reserved for
"no response")
* names of all samples/people in the data
**Format**:<br/>
Place the items in the order given immediately above.
Every label/meaning/name goes on its own line. Separate the segments
with a single empty line. Don't insert any empty lines in between
items of the same segment. The items in a segment must be ordered
in the same order they are portrayed within the other files.<br/>
The sample names are not case-sensitive.